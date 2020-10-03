#ifndef PESSOA_HPP
#define PESSOA_HPP

#include "jogador.hpp"
#include <iostream>
#include <string>
#include "baralho.hpp"

using namespace std;
 class Pessoa : public Jogador{
 public:
 	Pessoa();
 	Pessoa(string nome, Baralho* monte);
 	int escolher_opcao(Carta &c);
 };

 #endif