#include "pessoa.hpp"
#include <string>
#include "baralho.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "gamecontrol.hpp"

using namespace std;


Pessoa::Pessoa():Jogador(){}

Pessoa::Pessoa(string nome, Baralho* monte):Jogador(nome, monte){};

int Pessoa::escolher_opcao(Carta &c){
	//pede para pessoa escolher um atributo
	string aux;
	int opcao;
	int a= c.get_n_atr();
	cout<<"Escolha um atributo ("<<"1"<<" a "<<a<<"): ";
	
	opcao = get_int(-1);
	return opcao;
}