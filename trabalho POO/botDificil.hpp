#ifndef BOT_DIFICIL_HPP
#define BOT_DIFICIL_HPP
#include "jogador.hpp"
#include "botMedio.hpp"
#include <iostream>
#include <string>
#include "baralho.hpp"

class BotDificil : public BotMedio{
protected:
	Baralho* monte_ref;	//monte de referencia para escolha do atributo
public:
	BotDificil();
	BotDificil(string nome, Baralho* monte);
	BotDificil(string nome, Baralho* monte, Carta* c_ref, Baralho* m_ref);

	virtual void set_monte_ref(Baralho* monte_ref);

	virtual int escolher_opcao(Carta &c);
};

#endif