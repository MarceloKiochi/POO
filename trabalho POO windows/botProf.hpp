#ifndef BOT_PROF_HPP
#define BOT_PROF_HPP
#include "botDificil.hpp"
#include <iostream>
#include <string>
#include "baralho.hpp"

class BotProf : public BotDificil{
protected:
	Baralho* monte_op;	//monte do oponente
	float porcentagem_atr(Carta &card);	//calcula soma dos atributos em porcentagem
private:
	int n_cartas_desc;	//numero de cartas desconehcidas do oponente
public:
	BotProf();
	BotProf(string nome, Baralho* monte);
	BotProf(string nome, Baralho* monte, Carta* c_ref, Baralho* m_ref, Baralho* op);

	void set_monte_op(Baralho* monte_op);

	int escolher_opcao(Carta &c);

	void ganhar_carta(Carta &card);

	void perder_carta();
};

#endif