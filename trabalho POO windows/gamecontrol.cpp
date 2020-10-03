#include "gamecontrol.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <unistd.h>

using namespace std;

int press_enter(){	//pede para pressionae enter
	//para o jogo enquanto nao pressionar enter
	string aux = "\0";
	cout<<"<<Pressione ENTER>>";
	if(!MODO_TESTE)
		getline(cin, aux);
	if(aux=="0")
		return 0;
	return 1;
}

void espera(int n){
	//chama delay com base no numero passado
	cout.flush();
	if(!MODO_TESTE){
		//this_thread::sleep_for(chrono::milliseconds(n));
		for(int i=0;i<n;i++){

		}
	}
}

void limpar_tela(){
	//limpa tela
	cout<<string(50, '\n');
}

int get_int(int erro){
	//pega inteiro da entrada
	//se inteiro for invalido, retorna valor de erro passado
	string aux;
	getline(cin, aux);

	int t = aux.size();
	for(int i=0;i<t;i++){
		if(aux[i]<'0' || aux[i]>'9')
			return erro;
	}
	if(t>0)
		return atoi(aux.c_str());

	return erro;
}

float get_float(float erro){
	//pega float da entrada
	//se float for invalido, retorna erro passado
	string aux;
	getline(cin, aux);
	int t = aux.size();
	int ponto=0;
	for(int i=0;i<t;i++){
		if((aux[i]<'0' || aux[i]>'9') and aux[i]!='.')
			return erro;
		else if(aux[i]=='.'){
			if(ponto==0)
				ponto++;
			else
				return erro;
		}
	}
	if(t>0)
		return atof(aux.c_str());
	return erro;
}

int validar_float(string aux){
	//verifica se string pode ser float
	int t = aux.size();
	int ponto=0;
	for(int i=0;i<t;i++){
		if((aux[i]<'0' || aux[i]>'9') and aux[i]!='.')
			return 0;
		else if(aux[i]=='.'){
			if(ponto==0)
				ponto++;
			else
				return 0;
		}
	}
	if(t>0)
		return 1;
	return 0;
}