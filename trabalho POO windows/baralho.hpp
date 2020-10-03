#ifndef BARALHO_HPP
#define BARALHO_HPP

#include <iostream>
#include <string>
#include <list>
#include "carta.hpp"

using namespace std;

class Baralho{
private:
	int n_cartas;		//numero de cartas
	list<Carta> cartas;	//conjunto de cartas

public:
	Baralho();
	Baralho(int n_cartas, list<Carta> &cartas);
	Baralho(string arq);	//cria baralho salvo em arquivo

	int get_n_cartas();	//retorna numero de cartas do baralho

	Carta ver_primeira_carta();	//retorna carta do topo do baralho

	void retirar_primeira_carta();	//retira carta do topo do baralho

	void inserir_carta(Carta card);	//insere carta no fim do baralho

	void rodar();	//retira carta do topo e insere a mesma no fim

	void embaralhar();	//embaralha

	Baralho& operator+=(Carta c);	//operador sobrecarregado para inserir carta
	
	//operador sobrecarregado para retirar carta do baralho
	Baralho& operator--();
	Baralho operator--(int);
};
#endif