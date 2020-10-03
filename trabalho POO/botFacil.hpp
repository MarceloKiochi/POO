#ifndef BOT_FACIL_HPP
#define BOT_FACIL_HPP
#include "jogador.hpp"
#include <iostream>
#include <string>
#include "baralho.hpp"

class BotFacil : public Jogador{
public:
	BotFacil();
	BotFacil(string nome, Baralho* monte);
	virtual int escolher_opcao(Carta &c);
};

#endif
