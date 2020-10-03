#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <iostream>
#include <string>
#include "baralho.hpp"
#include "carta.hpp"
using namespace std;

class Jogador{	//clsse abstrata de jogador
private:
	string nome;	//nome do jogador
	float pontos;	//pontuacao
protected:
	Baralho* monte;	//monte de cartas

public:
	Jogador();
	Jogador(string nome, Baralho* monte);
	virtual ~Jogador();
	void set_nome(string nome);
	string get_nome();

	void set_pontos(float pontos);
	float get_pontos();
	virtual void ganhar_pontos(float pontos);

	void set_monte(Baralho* monte);

	virtual void ganhar_carta(Carta &card);
	
	virtual Carta ver_carta();

	virtual void perder_carta();

	void rodar_carta();

	virtual int escolher_opcao(Carta &c)=0;
	int n_cartas();
};
#endif