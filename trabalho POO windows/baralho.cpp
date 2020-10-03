#include "baralho.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "atributo.hpp"
#include "gamecontrol.hpp"
using namespace std;

bool aleat(Carta &A, Carta &B){	//funcao de comparacao aleatoria para embaralhar baralho
	int a;

	if(A.get_nome()<B.get_nome())
		a = rand()%2;
	else{
		a = rand()%2;
		a= !a;
	}

	if(a) return true;
	return false;
}

Baralho::Baralho(){
	this->n_cartas=0;
}
Baralho::Baralho(int n_cartas, list<Carta> &cartas){
	this->n_cartas=n_cartas;
	this->cartas = cartas;
}

Baralho::Baralho(string arquivo){	//cria baralho salvo no arquivo passado
	//estrutura do arquivo:
	//numero de cartas (n_cartas)
	//numero de atributos por carta (n_atr)
	//n_atr nomes de atributos
	//n_cartas cartas (nome e valores de atributos, um em cada linha)

	int n_atr;
	string aux;
	string nome;
	string tipo;
	
	list<Carta>::iterator i;	
	
	ifstream arq(arquivo.c_str());	//abre arquivo

	if(arq.is_open()==0)
		throw -1;

	getline(arq, aux);

	this->n_cartas = atoi(aux.c_str());	//pega numerod e cartas

	getline(arq, aux);

	n_atr = atof(aux.c_str());	//pega numero de atributos

	vector<Atributo<float>> atr;	//vetor de atributos das cartas
	Carta card;
	card.set_n_atr(n_atr);

	for(int i=0;i<n_atr;i++){	//insere nomes dos atributos no vetor
		getline(arq, nome);

		if(nome[nome.size()-1] == '\r'){
			nome.erase(nome.size()-1);
		}
		Atributo<float> at(nome, 0);
		atr.push_back(at);
	}	

	for(int i=0;i<this->n_cartas;i++){	//pega o nome e os valores das cartas
		getline(arq, nome);

		if(nome[nome.size()-1] == '\r'){
			nome.erase(nome.size()-1);
		}
		for(int j=0;j<n_atr;j++){
			getline(arq, aux);
			atr[j].set_valor(atof(aux.c_str()));
		}

		if(i==0)
			tipo = "SUPER TRUNFO";
		else if(i<(this->n_cartas/4)+1)
			tipo = "A";
		else
			tipo = "B";

		card.set_nome(nome);
		card.set_tipo(tipo);
		card.set_atr_all(n_atr, atr);
		this->cartas.push_back(card);	//insere cada carta no baralho
	}
	
	arq.close();
}

int Baralho::get_n_cartas(){
	return this->n_cartas;
}

Carta Baralho::ver_primeira_carta(){	//retorna carta do topo do baralho
	if(!this->cartas.empty()){
		list<Carta>::iterator c;
		c = this->cartas.begin();
		return *c;
	}
	Carta card;
	return card;
}

void Baralho::retirar_primeira_carta(){	//retira carta do topo do baralho
	if(!this->cartas.empty()){
		this->cartas.pop_front();
		this->n_cartas--;
	}
}

void Baralho::inserir_carta(Carta card){	//insere carta no fim do baralho
	this->cartas.push_back(card);
	this->n_cartas++;
}

void Baralho::rodar(){	//retira carta do topo e insere no fim
	if(!this->cartas.empty()){
		list<Carta>::iterator i;
		i = this->cartas.begin();
		this->cartas.push_back(*i);
		this->cartas.pop_front();
	}
}

void Baralho::embaralhar(){	//embaralha
	//ordena com funcao aleatoria 3 vezes
	this->cartas.sort(aleat);
	this->cartas.sort(aleat);
	this->cartas.sort(aleat);
}

Baralho& Baralho::operator+=(Carta c){

	Baralho::inserir_carta(c);
	return *this;
}

Baralho& Baralho::operator--(){
	Baralho::retirar_primeira_carta();
	return *this;
}

Baralho Baralho::operator--(int){
	Baralho temp = *this;
	--(*this);
	return temp;
}