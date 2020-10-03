#ifndef PERSONALIZAR_BARALHO_HPP
#define PERSONALIZAR_BARALHO_HPP

#include <iostream>
#include <vector>
#include "atributo.hpp"
#include "carta.hpp"

using namespace std;

#define VALOR_MIN 0
#define VALOR_MAX 100000
#define BLOQUEADOS 4


int criar_cartas(int& n_cartas, int& n_atr, vector<Carta> &vet, vector<Atributo<float>> &atr);

int definir_n_atributos(int& n_cartas, int& n_atr, vector<Carta> &vet);

int definir_n_cartas(int& n_cartas, int& n_atr, vector<Carta> &vet);

void criar_novo_baralho();

void imprimir_baralho(string arquivo);

void visualizar_baralho();

void apagar_baralho(string arq, int opcao);

void deletar_baralho();

void alterar_nome_atributo(string arq, int numero);

void modificar_atributo(string arq);

string modificar_nome(string arq, int opcao);

void alterar_nome_carta(string arq, long pos);

void alterar_valor(string arq, long pos, int opcao);

void alterar_valor_atributo(string arq, long pos);

void alterar_carta(string arq, long pos);

void modificar_carta(string arq);

void escolher_modificacao(string arq, int numero);

void modificar_baralho();

void personalizar_baralho();

#endif