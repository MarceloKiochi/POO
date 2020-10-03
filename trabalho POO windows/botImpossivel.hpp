#ifndef BOT_IMPOSSIVEL_HPP
#define BOT_IMPOSSIVEL_HPP
#include "botProf.hpp"
#include <iostream>
#include <string>
#include "baralho.hpp"

class BotImpossivel : public BotProf{
public:
	BotImpossivel();
	BotImpossivel(string nome, Baralho* monte);
	BotImpossivel(string nome, Baralho* monte, Carta* c_ref, Baralho* m_ref, Baralho* op);

	int escolher_opcao(Carta &c);

	void set_monte_op(Baralho* op);

	void ganhar_pontos(float pontos);

	Carta ver_carta();
};

#endif