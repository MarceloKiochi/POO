#include <string>
#include "baralho.hpp"
#include <iostream>
#include <cstdlib>
#include "botImpossivel.hpp"
#include "gamecontrol.hpp"
using namespace std;


BotImpossivel::BotImpossivel():BotProf(){
	this->monte_op=NULL;
}

BotImpossivel::BotImpossivel(string nome, Baralho* monte):BotProf(nome, monte){
	this->monte_op=NULL;
}

BotImpossivel::BotImpossivel(string nome, Baralho* monte, Carta* c_ref, Baralho* m_ref, 
				Baralho* op):BotProf(nome, monte, c_ref, m_ref, op){
	this->monte_op = op;
};

int BotImpossivel::escolher_opcao(Carta &c){
	//olha carta do oponente para escolher um atributo que ganhe
	
	int opcao=1;
	string aux;
	int n_atr;
	if(this->monte_op!=NULL){	//verifica se tem acesso ao monte do oponente
		n_atr = this->monte_op->ver_primeira_carta().get_n_atr();
		if(c.get_n_atr()!=n_atr){
			cout<<"Erro: carta de monte op de Bot Prof diferente de carta passada"<<endl;
			throw -1;
		}
		Carta c_op = this->monte_op->ver_primeira_carta();
		int nao_achou=1;
		int i=0;
		float v1, v2;
		while(nao_achou and i<n_atr){	//procura atributo com maior valor e escolhe
			v1 = c.get_atr(i).get_valor();
			v2 = c_op.get_atr(i).get_valor();
			if(v1>v2 or (v1==v2 and BotProf::porcentagem_atr(c) < BotProf::porcentagem_atr(c_op))){
				opcao = i+1;
				nao_achou=0;
			}
			i++;
		}
		if(!press_enter())
		opcao=0;
	}
	else{	//se nao tiver monte do oponente, escolhe como bot prof
		opcao = BotProf::escolher_opcao(c);
	}
	
	return opcao;
}

void BotImpossivel::set_monte_op(Baralho* op){
	this->monte_op = op;
}

void BotImpossivel::ganhar_pontos(float pontos){
	float p = 1.2 * pontos;	//ganha 20% mais pontos
	Jogador::ganhar_pontos(p);
}
Carta BotImpossivel::ver_carta(){
	//quando ve a primeira carta do monte
	//verifica se tem algum atributo que ganhe do oponente
	//se nao tiver, troca carta ateh achar uma que ganhe

	Carta c_op = this->monte_op->ver_primeira_carta();	
	int nao_achou=1;
	int i=0;
	int j=0;
	float v1, v2;
	Carta propria;
	while(nao_achou and j<this->monte->get_n_cartas()){
		i=0;
		propria = this->monte->ver_primeira_carta();
		while(nao_achou and i<c_op.get_n_atr()){
			v1 = c_op.get_atr(i).get_valor();
			v2 = propria.get_atr(i).get_valor();
			//verifica se um atributo ganha do poonente
			if(v1<v2 or (v1==v2 and BotProf::porcentagem_atr(propria) < BotProf::porcentagem_atr(c_op))){
				nao_achou=0;
			}
			i++;
		}
		if(nao_achou){	//se nao achou, fica com a primeira cata mesmo
			this->monte->retirar_primeira_carta();
			this->monte->inserir_carta(propria);
			propria = this->monte->ver_primeira_carta();
		}
		j++;
	}
	return propria;
}