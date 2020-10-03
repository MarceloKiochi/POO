#include <iostream>
#include <string>
#include "atributo.hpp"
#include "carta.hpp"
#include "gamecontrol.hpp"
#include <vector>
using namespace std;

Carta::Carta(){
	this->n_atr=0;
	this->nome = "\0";
	this->tipo.set_nome("Tipo");
}

Carta::Carta(string nome, int n_atr, vector<Atributo<float>> atr, string tipo){
	this->n_atr = n_atr;
	this->nome = nome;
	this->tipo.set_valor(tipo);
	this->tipo.set_nome("Tipo");
	for(int i=0;i<n_atr;i++){
		Atributo<float> at(atr[i].get_nome(), atr[i].get_valor());
		this->atr.push_back(at);
	}
}

void Carta::set_n_atr(int n){
	this->n_atr = n;
	for(int i=0;i<n;i++){
		Atributo<float> at("", 0);
		this->atr.push_back(at);
	}
}

void Carta::set_atr(int i, string nome, float valor){
	if(i>=this->n_atr or i<0)
		throw -1;

	else{
		this->atr[i].set_nome(nome);
		this->atr[i].set_valor(valor);
	}	
}

void Carta::set_nome(string nome){
	this->nome = nome;
}

void Carta::set_tipo(string tipo){
	this->tipo.set_valor(tipo);
}

void Carta::set_atr_all(int n_atr, vector<Atributo<float>> atr){
	if(this->n_atr!=n_atr){
		throw -1;
	}
	else{
		for(int i=0;i<n_atr;i++){
			this->atr[i].set_nome(atr[i].get_nome());
			this->atr[i].set_valor(atr[i].get_valor());
		}
	}
}

int Carta::get_n_atr(){
	return this->n_atr;
}

Atributo<float> Carta::get_atr(int i){
	if(i>=this->n_atr){
		throw -1;
	}
	else{
		return this->atr[i];
	}
}

string Carta::get_nome(){
	return this->nome;
}

string Carta::get_tipo(){
	return this->tipo.get_valor();
}

void Carta::print_card(){
	string aux;
	cout<<this->nome<<" ["<<this->tipo.get_nome()<<"]:"<<endl;
	for(int i=0;i<this->n_atr;i++){
		cout<<i+1<<"- ";
		aux = this->atr[i].get_nome();
		aux.append(TAM_MAX-aux.size(), '.');
		cout<<aux;
		cout<<this->atr[i].get_valor();
		cout<<endl;
	}
}

ostream& operator<<(ostream& os, Carta &card){
	string aux;
	cout<<card.get_nome()<<" ["<<card.get_tipo()<<"]:"<<endl;
	for(int i=0;i<card.get_n_atr();i++){
		cout<<i+1<<"- ";
		aux = card.get_atr(i).get_nome();
		aux.append(TAM_MAX-aux.size(), '.');
		cout<<aux;
		cout<<card.get_atr(i).get_valor();
		cout<<endl;
	}
	return os;
}