#include <iostream>
#include <string>
#include "jogador.hpp"
#include "baralho.hpp"

using namespace std;


Jogador::Jogador(){
	this->nome = "\0";
	this->monte = NULL;
	this->pontos=0;
}
Jogador::Jogador(string nome, Baralho* monte){
	this->nome = nome;
	this->monte = monte;
	this->pontos=0;
}

Jogador::~Jogador(){}	//tira warning para delete

void Jogador::set_nome(string nome){
	this->nome = nome;
}

string Jogador::get_nome(){
	return this->nome;
}

void Jogador::set_pontos(float pontos){
	this->pontos = pontos;
}

void Jogador::ganhar_pontos(float pontos){
	this->pontos+=pontos;
}

float Jogador::get_pontos(){
	return this->pontos;
}

void Jogador::set_monte(Baralho* monte){
	this->monte = monte;
}

void Jogador::ganhar_carta(Carta &card){
	if(this->monte!=NULL){
		(*this->monte)+=card;
	}
	else{
		cout<<"Erro (ganhar carta): "<<this->nome<<" nao possui um monte"<<endl;
	}
}

Carta Jogador::ver_carta(){
	if(this->monte!=NULL){
		return this->monte->ver_primeira_carta();
	}
	else{
		cout<<"Erro (ver carta): "<<this->nome<<" nao possui um monte"<<endl;
	}
	Carta card;
	return card;	
}

void Jogador::perder_carta(){
	if(this->monte!=NULL){
		(*this->monte)--;
	}
	else{
		cout<<"Erro (perder carta): "<<this->nome<<" nao possui um monte"<<endl;
	}	
}

void Jogador::rodar_carta(){
	if(this->monte!=NULL){
		this->monte->rodar();
	}
	else{
		cout<<"Erro (perder carta): "<<this->nome<<" nao possui um monte"<<endl;
	}	
}

int Jogador::n_cartas(){
	if(this->monte!=NULL){
		return this->monte->get_n_cartas();
	}
	else{
		return 0;
	}	
}