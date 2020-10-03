#include <string>
#include "baralho.hpp"
#include <iostream>
#include <cstdlib>
#include "botDificil.hpp"
#include "gamecontrol.hpp"
using namespace std;


BotDificil::BotDificil():BotMedio(){}

BotDificil::BotDificil(string nome, Baralho* monte):BotMedio(nome, monte){}

BotDificil::BotDificil(string nome, Baralho* monte, Carta* c_ref, Baralho* m_ref):BotMedio(nome, monte, c_ref){
	this->monte_ref = m_ref;
};

int BotDificil::escolher_opcao(Carta &c){
	//compara carta com todas as cartas do monte_ref e escolhe atributo que tem menos chance de perder
	//monte_ref deve ser copia do baralho usado no jogo

	int n_atr;
	int opcao;
	string aux;
	float valor;

	if(this->monte_ref!=NULL and this->monte_ref->get_n_cartas()>0){	//verifica se monte ref existe
		n_atr = this->monte_ref->ver_primeira_carta().get_n_atr();
		if(c.get_n_atr() != n_atr){
			cout<<"BotDificil erro: carta de monte ref diferente da carta passada"<<endl;
			throw -1;
		}	
		
		int n_cartas = this->monte_ref->get_n_cartas();		

		vector<int> maiores;
		for(int i=0;i<n_atr;i++){	//vetor para contar quantas vezes cada atributo perde
			maiores.push_back(0);
		}

		for(int i=0;i<n_cartas;i++){
			for(int j=0;j<n_atr;j++){
				valor = this->monte_ref->ver_primeira_carta().get_atr(j).get_valor();
				if(valor >= c.get_atr(j).get_valor()){	//aumenta contador sempre que acha valor maior
					maiores[j]++;
				}
			}
			this->monte_ref->rodar();
		}

		int menor=maiores[0];
		opcao=1;
		for(int i=0;i<n_atr;i++){	//pega o menor contador e escolhe o atributo
			if(maiores[i]<menor){
				menor = maiores[i];
				opcao=i+1;
			}
		}
		if(!press_enter())
			opcao=0;
	}
	else{	//se nao tem monte ref, escolhe como bot medio
		opcao = BotMedio::escolher_opcao(c);
	}				
	
	return opcao;
}

void BotDificil::set_monte_ref(Baralho* ref){
	this->monte_ref = ref;
}