#include "pessoa.hpp"
#include <string>
#include "baralho.hpp"
#include <iostream>
#include <cstdlib>
#include "botFacil.hpp"
#include <ctime>
#include "gamecontrol.hpp"
using namespace std;

BotFacil::BotFacil():Jogador(){}

BotFacil::BotFacil(string nome, Baralho* monte):Jogador(nome, monte){};

int BotFacil::escolher_opcao(Carta &c){
	//bot facil escolhe atributo aleatorio
	srand(time(NULL));
	int opcao;
	int a = 1;
	int b = c.get_n_atr();
	string aux;
	opcao = (rand()%(b-a+1))+a;
	if(!press_enter())
		opcao=0;
	return opcao;
}