#ifndef GAMECONTROL_HPP
#define GAMECONTROL_HPP

#include <iostream>
#include <string>

#define BARRA 15	//tamanho da barra 
#define DELAY 35	//numero de delay para crescimento da barra
#define ESPERA 700	//numero de delay para impressao de frases
#define MODO_TESTE 0	//ativa modo de teste (cancela press_enter e delays)
#define TAM_MAX 20	//tamanho maximo do nome do atributo na impressao da carta

using namespace std;

//funcoes para controle do jogo
int press_enter();	//pede para pressionar enter

void espera(int n);	//chama delay

void limpar_tela();	//limpa tela

int validar_float(string aux);	//verifica se string pode ser float

int get_int(int erro);	//pega int da entrada

float get_float(float erro);	//pega float da entrada

#endif