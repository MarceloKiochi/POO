#include <string>
#include "baralho.hpp"
#include <iostream>
#include <cstdlib>
#include "botProf.hpp"
#include "gamecontrol.hpp"
using namespace std;

BotProf::BotProf():BotDificil(){
	this->monte_op=NULL;
	this->n_cartas_desc=-1;
}

BotProf::BotProf(string nome, Baralho* monte):BotDificil(nome, monte){
	this->monte_op=NULL;
	this->n_cartas_desc=-1;
}

BotProf::BotProf(string nome, Baralho* monte, Carta* c_ref, Baralho* m_ref, 
				Baralho* op):BotDificil(nome, monte, c_ref, m_ref){
	this->monte_op = op;
	this->n_cartas_desc = op->get_n_cartas();
};

int BotProf::escolher_opcao(Carta &c){
	//decora a ordem das cartas do oponente
	//enquanto nao viu todas as cartas do oponente, escolhe como bot dificil
	//depois que viu todas, compara as duas cartas para escolher atributo
	//monte_op eh o acesso ao monte do oponente, para ver a primeira carta e comparar
	
	int opcao=1;
	string aux;
	int n_atr;
	if(this->n_cartas_desc==0 and this->monte_op!=NULL){	//se nao ha cartas desconhecidas
		n_atr = this->monte_op->ver_primeira_carta().get_n_atr();
		if(c.get_n_atr()!=n_atr){
			cout<<"Erro: carta de monte op de Bot Prof diferente de carta passada"<<endl;
			throw -1;
		}
		Carta c_op = this->monte_op->ver_primeira_carta();
		int nao_achou=1;
		int i=0;
		float v1, v2;	
		while(nao_achou and i<n_atr){	//compara atributos e escolhe um que ganha
			v1 = c.get_atr(i).get_valor();
			v2 = c_op.get_atr(i).get_valor();
			if(v1>v2 or (v1==v2 and this->porcentagem_atr(c) < this->porcentagem_atr(c_op))){
				opcao = i+1;
				nao_achou=0;
			}
			i++;
		}
		if(!press_enter())
		opcao=0;
	}
	else{	//se ainda ha cartas desconhecidas, ou se nao tem acesso ao monte do oponente
		//escolhe como bot dificil
		opcao = BotDificil::escolher_opcao(c);
	}
	
	return opcao;
}

void BotProf::set_monte_op(Baralho* op){
	this->monte_op = op;
	this->n_cartas_desc = op->get_n_cartas();
}

//sempre que ganha ou perde uma carta (passou uma rodada), conhece uma carta do oponente
void BotProf::ganhar_carta(Carta &card){
	if(this->n_cartas_desc>0){
		this->n_cartas_desc--;
	}
	Jogador::ganhar_carta(card);
}

void BotProf::perder_carta(){
	if(this->n_cartas_desc>0){
		this->n_cartas_desc--;
	}
	Jogador::perder_carta();
}

float BotProf::porcentagem_atr(Carta &card){
	float res=0;
	//calcula valor total dos atributos em porcentagem
	//em relacao a carta com atributos maximos
	for(int i=0;i<card.get_n_atr();i++){
		res+= (card.get_atr(i).get_valor() * 100)/ this->carta_ref->get_atr(i).get_valor();
	}
	return res;
}