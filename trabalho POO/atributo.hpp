#ifndef ATRIBUTO_HPP
#define ATRIBUTO_HPP

#include <iostream>
#include <string>
using namespace std;

template<class T>
class Atributo{	//classe que representa um atributo de uma carta
private:
	string nome;	//nome do atributo
	T valor;		//valor do atributo
public:
	Atributo();
	Atributo(string nome, T valor);

	void set_nome(string nome);
	void set_valor(T valor);

	string get_nome();
	T get_valor();
};

template<class T>
Atributo<T>::Atributo(){
	this->nome = "\0";
}

template<class T>
Atributo<T>::Atributo(string nome, T valor){
	this->nome = nome;
	this->valor = valor;
}

template<class T>
void Atributo<T>::set_nome(string nome){
	this->nome = nome;
}

template<class T>
void Atributo<T>::set_valor(T valor){
	this->valor = valor;
}

template<class T>
string Atributo<T>::get_nome(){
	return this->nome;
}

template<class T>
T Atributo<T>::get_valor(){
	return this->valor;
}
#endif