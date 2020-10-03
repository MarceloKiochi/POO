#ifndef BOT_MEDIO_HPP
#define BOT_MEDIO_HPP
#include "botFacil.hpp"
#include <iostream>
#include <string>
#include "baralho.hpp"

class BotMedio : public BotFacil{
protected:
	Carta* carta_ref;	//carta de referencia para escolha de atributo
public:
	BotMedio();
	BotMedio(string nome, Baralho* monte);
	BotMedio(string nome, Baralho* monte, Carta* ref);

	virtual void set_carta_ref(Carta* ref);

	virtual int escolher_opcao(Carta &c);
};

#endif