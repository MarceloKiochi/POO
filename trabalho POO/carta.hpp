#ifndef CARTA_HPP
#define CARTA_HPP

#include <iostream>
#include <string>
#include "atributo.hpp"
#include <vector>
using namespace std;

class Carta{	//classe que representa as cartas do jogo
private:
	string nome;	//nome do personagem da carta
	int n_atr;		//numero de atributos
	vector<Atributo<float>> atr;	//vetor de atributos
	Atributo<string> tipo;	//atributo de tipo (A, B ou SUPER TRUNFO)

public:
	Carta();
	Carta(string nome, int n_atr, vector<Atributo<float>> atr, string tipo);

	void set_n_atr(int n);
	void set_atr(int i, string nome, float valor);
	void set_nome(string nome);
	void set_tipo(string tipo);
	void set_atr_all(int n_atr, vector<Atributo<float>> atr);

	int get_n_atr();
	Atributo<float> get_atr(int i);
	string get_nome();
	string get_tipo();

	void print_card();	//imprime carta no formato do jogo

	friend ostream& operator<<(ostream& os, Carta& card);	//sobrecarga do << para inpressao da carta
};

#endif