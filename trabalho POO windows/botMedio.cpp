#include <string>
#include "baralho.hpp"
#include <iostream>
#include <cstdlib>
#include "botMedio.hpp"
#include "gamecontrol.hpp"
using namespace std;


BotMedio::BotMedio():BotFacil(){}

BotMedio::BotMedio(string nome, Baralho* monte):BotFacil(nome, monte){}

BotMedio::BotMedio(string nome, Baralho* monte, Carta* ref):BotFacil(nome, monte){
	this->carta_ref= ref;
};

int BotMedio::escolher_opcao(Carta &c){
	//escolhe atributo com maior valor em porcentagem
	//carta de referencia deve ser uma carta com os maiores valores dos atributos
	int opcao=1;
	string aux;
	float maior=0;

	if(this->carta_ref!=NULL and this->carta_ref->get_n_atr()>0){	//verifica se existe carta ref
		if(this->carta_ref->get_n_atr() != c.get_n_atr()){
			cout<<"Erro: carta ref de Bot Medio diferente de carta passada"<<endl;
			throw -1;
		}
		for(int i=0;i<c.get_n_atr();i++){	//verifica qual atributo tem  maior porcentagem e escolhe
			if(c.get_atr(i).get_valor() / this->carta_ref->get_atr(i).get_valor() > maior){
				maior = c.get_atr(i).get_valor() / this->carta_ref->get_atr(i).get_valor();
				opcao = i+1;
			}
		}
		if(!press_enter())
			opcao=0;
	}
	else{	//se nao tem carta ref, escolhe como bot facil
		opcao = BotFacil::escolher_opcao(c);
	}	
	
	return opcao;
}

void BotMedio::set_carta_ref(Carta* ref){
	this->carta_ref = ref;
}