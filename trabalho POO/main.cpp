#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <vector>
#include <cstdlib>
#include <thread>
#include <chrono>
#include "atributo.hpp"
#include "carta.hpp"
#include "baralho.hpp"
#include "jogador.hpp"
#include "pessoa.hpp"
#include "botFacil.hpp"
#include "botMedio.hpp"
#include "botDificil.hpp"
#include "botImpossivel.hpp"
#include "botProf.hpp"
#include <ctime>
#include "gamecontrol.hpp"
#include <climits>
#include "personalizar_baralho.hpp"

using namespace std;

void print_mystery_card(Carta &card){
	//imprime carta escondendo nome e atributos
	string aux;
	cout<<"??? [???]:"<<endl;	//nome e tipo escondidos
	for(int i=0;i<card.get_n_atr();i++){	//loop de atributos
		cout<<i+1<<"- ";					//imrpime o numero do atributo
		aux = card.get_atr(i).get_nome();	//nome do atributo
		aux.append(TAM_MAX-aux.size(), '.');//preenche com pontos ateh a posicao do valor
		cout<<aux;							//imprime
		cout<<"???";						//imprime o valor do atributo
		cout<<endl;
	}
}

void print_cards(int vez, int tipo, vector<Carta> &cardx, vector<Jogador*> &players){
	//imprime as cartas da rodada
	//tipo 1: mostra as duas cartas
	//tipo 2: mostra apenas a carta que escolhe o atributo e esconde a outra

	if(tipo==1){
		cout<<"("<<players[0]->get_nome()<<")"<<endl;	//imprime nome do jogador da carta
		cout<<(cardx[0]);	//imprime carta
		cout<<endl;

		cout<<"("<<players[1]->get_nome()<<")"<<endl;	//outro jogador
		cout<<(cardx[1]);	//outra carta
	}
	else if(tipo==2){
		cout<<"("<<players[0]->get_nome()<<")"<<endl;	//imprime nome do jogador 1
		if(vez==0){						//se for a vez do jogador 1
			cout<<(cardx[0]);			//mostra a carta do jogador 1
			cout<<endl;
			cout<<"("<<players[1]->get_nome()<<")"<<endl;//imprime nome do jogador 2
			print_mystery_card(cardx[1]);	//esconde carta do jogador 2
		}
		else{	//se for vez do jogador 2
			print_mystery_card(cardx[0]);	//esconde carta do jogador 1
			cout<<endl;
			cout<<"("<<players[1]->get_nome()<<")"<<endl;	//nome do jogador 2
			cout<<(cardx[1]);	//imprime carta do jogador 2
		}	
		cout<<endl;		
	}	
}

void print_duelo(int vez, int tipo, vector<Carta> &cardx, vector<Jogador*> &players, Carta* cMax, int escolha){
	//imrime barras de comparacao dos valores das cartas
	//tipo 1: imprime com delay (animacaozinha da barra crescendo)
	//tipo 2: imprime sem delay

	int menorT;
	int maiorT;
	int menor;
	string aux;

	cout<<"("<<players[vez]->get_nome()<<") "<<cardx[vez].get_nome();	//imrpime nome do jogador que escolhe
																		//e nome da sua carta
		
	cout<<" x ";

	cout<<cardx[!vez].get_nome()<<" ("<<players[!vez]->get_nome()<<") "; //nome da outra carta e do outro jogador

	cout<<endl;
	
	// se uma carta for super trunfo, nao importa o atributo escolhido
	if(cardx[vez].get_tipo()=="SUPER TRUNFO"){
		cout<<players[vez]->get_nome()<<" esta com Super Trunfo!"<<endl;
	}
	else if(cardx[!vez].get_tipo()=="SUPER TRUNFO"){
		cout<<players[!vez]->get_nome()<<" esta com Super Trunfo!"<<endl;
	}
	else{	//se nao, imprime qual atributo foi escolhido
		cout<<players[vez]->get_nome()<<" escolheu \""<<cMax->get_atr(escolha-1).get_nome()<<"\""<<endl;
	}

	if(cardx[vez].get_nome().size() > cardx[!vez].get_nome().size()){	//compara tamanhos dos nomes das cartas
		menorT = cardx[!vez].get_nome().size();	//menor tamanho em menorT
		maiorT = cardx[vez].get_nome().size();	//maior em maiorT
		menor = !vez;	//indica que menor nome eh do jogador que nao escolhe
	}
	else{
		menorT = cardx[vez].get_nome().size();
		maiorT = cardx[!vez].get_nome().size();
		menor = vez;
	}

	float tam;

	cout<<cardx[vez].get_nome()<<": ";	//imprime nome da carta da vez
	if(menor==vez){	//se nome dela for menor que o outro
		aux = "";
		aux.append(maiorT-menorT, ' ');
		cout<<aux;	//imprime espacos ateh igualar o tamanho (para alinhar as barras)
	}
	if(tipo==1)
		espera(ESPERA);	//delay


	if(cardx[vez].get_tipo()=="SUPER TRUNFO" or cardx[!vez].get_tipo()=="SUPER TRUNFO"){
		//se uma das cartas for super trunfo
		if(cardx[vez].get_tipo()=="SUPER TRUNFO")
			tam = BARRA/2;
		else if(cardx[vez].get_tipo()=="A")
			tam = BARRA;
		else
			tam = BARRA/4;
	}
	else{
		// se nao, calcula tamanho da barra com base no maior valor do atributo
		tam = cardx[vez].get_atr(escolha-1).get_valor() / cMax->get_atr(escolha-1).get_valor();
		tam = tam * BARRA;
	}
		
	for(int i=0;i< tam;i++){	//imprime a barra
		cout<<">";
		if(tipo==1)
			espera(DELAY);
	}
	cout<<" ";
	if(cardx[vez].get_tipo()=="SUPER TRUNFO" or cardx[!vez].get_tipo()=="SUPER TRUNFO"){
		cout<<cardx[vez].get_tipo()<<endl;	//se um dos dois for trunfo, imprime o tipo
	}
	else{	//se nao, imprime o valor do atributo escolhido
		cout<<cardx[vez].get_atr(escolha-1).get_valor()<<endl;
	}
		
	//repete para outra carta
	cout<<cardx[!vez].get_nome()<<": ";
	if(menor!=vez){
		aux ="";
		aux.append(maiorT-menorT, ' ');
		cout<<aux;
	}
	if(tipo==1)
		espera(ESPERA);

	if(cardx[vez].get_tipo()=="SUPER TRUNFO" or cardx[!vez].get_tipo()=="SUPER TRUNFO"){
		if(cardx[!vez].get_tipo()=="SUPER TRUNFO")
			tam = BARRA/2;
		else if(cardx[!vez].get_tipo()=="A")
			tam = BARRA;
		else
			tam = BARRA/4;
	}
	else{
		tam = cardx[!vez].get_atr(escolha-1).get_valor() / cMax->get_atr(escolha-1).get_valor();
		tam = tam * BARRA;
	}
		
	for(int i=0;i< tam;i++){
		cout<<">";
		if(tipo==1)
			espera(DELAY);
		
	}
	cout<<" ";
	if(cardx[vez].get_tipo()=="SUPER TRUNFO" or cardx[!vez].get_tipo()=="SUPER TRUNFO"){
		cout<<cardx[!vez].get_tipo()<<endl;
	}
	else{
		cout<<cardx[!vez].get_atr(escolha-1).get_valor()<<endl;
	}
			
	
}

Carta* criar_carta_max(Baralho* deck){
	//cria carta maxima do baralho
	//carta maxima eh uma carta que possui o maximo em todos os atributos
	//baseado nas cartas do baralho passado

	int n_atr;	//numero de atributos das cartas
	
	int n_cartas;	//numero de cartas do baralho

	float valor;

	n_cartas = deck->get_n_cartas();

	n_atr = deck->ver_primeira_carta().get_n_atr();

	vector<Atributo<float>> atr;

	for(int i=0;i<n_atr;i++){	//cria vetor de atributos para a carta
		Atributo<float> at;
		at.set_nome(deck->ver_primeira_carta().get_atr(i).get_nome());
		at.set_valor(0);
		atr.push_back(at);
	}
	Carta* card = new Carta("max", n_atr, atr, "A");	//cria a carta
	for(int i=0;i<n_cartas;i++){	//passa pelas cartas do baralho
		for(int i=0;i<n_atr;i++){	//passa pelos atributos, pegando os maiores valores
			valor = deck->ver_primeira_carta().get_atr(i).get_valor();
			if(valor > card->get_atr(i).get_valor())
				card->set_atr(i, atr[i].get_nome(), valor);
		}
		deck->rodar();
	}
		
	return card;
}

float definir_pts_max(){
	//define pontuacao maxima para fim de jogo
	float opcao;
	string aux;
	int mensagem=0;
	do{
		limpar_tela();

		if(mensagem)
			cout<<"Numero invalido."<<endl;
		mensagem=0;
		cout<<"Finalizar jogo por pontos?"<<endl;
		cout<<"Sim -> insira numero max de pontos (max 100000)."<<endl;
		cout<<"Nao -> insira 0."<<endl;

		opcao = get_float(-1);

		if(opcao<0 or opcao > 100000)
			mensagem=1;

	}while(mensagem!=0);
	return opcao;
}

float get_pontos(Carta &win, Carta &lose, Carta* max){
	//calcula pontuacao da rodada
	//se uma carta mais forte ganha de uma mais fraca, ganha menos pontos
	//se uma mais fraca ganha de uma mais forte, mais pontos
	//pontos sao calculados com base na porcentagem dos atributos das cartas em relacao a carta maxima
	float pontos=0;
	float totalw=0, totall=0;	//total da carta win (vencedora) e total da carta lose (perdedora)
	int n_atr = max->get_n_atr();//numero de atributos das cartas

	if(win.get_tipo()=="SUPER TRUNFO"){	//se a que ganha for trunfo, pontos nao dependem dos atributos
		return win.get_n_atr() * 100;
	}
	else if(lose.get_tipo()=="SUPER TRUNFO"){//se trunfo perde, rodada vale mais pontos
		return win.get_n_atr() * 200;
	}

	for(int i=0;i<n_atr;i++){	//percorre os atributos das cartas somando as porcentagens dos atributos
		totalw += win.get_atr(i).get_valor()*100/max->get_atr(i).get_valor();
		totall += lose.get_atr(i).get_valor()*100/max->get_atr(i).get_valor();		
	}
	pontos = (100*n_atr) + totall - totalw;	//retorna a diferenca das somas
	return pontos;
}

void iniciar_jogo(Baralho* monte_ref, Jogador* player1, Jogador* player2){
	//funcao que contem o procedimento do jogo em si
	//monte_ref eh o baralho a ser usado, mas as cartas ja estao nos montes dos jogadores (cartas duplicadas)

	limpar_tela();
	int n_atr;			//numero de atributos das cartas	
	int vez= rand()%2;	//vez de que comeca
	int escolha;		//escolha dos jogadores
	string aux;
	float pontos;		//pontos a serem ganhos
	int fim=0;			//indica se jogo acabou
	float pts_max=0;	//pontuacao maxima a ser decidida

	pts_max = definir_pts_max();	//define pontuacao maxima

	vector<Jogador*> players;		//coloca jogadores num vetor
	players.push_back(player1);
	players.push_back(player2);

	Carta* carta_max = criar_carta_max(monte_ref);	//cria carta maxima (para calcular os pontos)

	vector<Carta> cardx;			//cria um vetor de duas cartas (um para cada jogador) para os duelos
	cardx.push_back(*carta_max);
	cardx.push_back(*carta_max);

	n_atr = carta_max->get_n_atr();	//seta numero de atributos com a carta maxima

	while(fim==0){

		cardx[0] = players[0]->ver_carta();	//pega as primeiras cartas dos dois jogadores
		cardx[1] = players[1]->ver_carta();	
		
		do{	//loop para o jogador da vez escolher um atributo
			limpar_tela();
			//imprime nomes e pontos de cada jogador
			cout<<players[0]->get_nome()<<": "<<players[0]->n_cartas()<<" c, ";
			cout<<players[0]->get_pontos()<<" pts"<<endl;
			cout<<players[1]->get_nome()<<": "<<players[1]->n_cartas()<<" c, ";
			cout<<players[1]->get_pontos()<<" pts"<<endl;
			cout<<endl;
			cout<<"--VEZ DE "<<players[vez]->get_nome()<<"--"<<endl;
			cout<< endl;

			print_cards(vez, 2, cardx, players);	//imprime as cartas, escondendo uma

			escolha = players[vez]->escolher_opcao(cardx[vez]);	//chama a funcao do jogador da vez para escolher um atributo
			cout<<endl;
		}while(escolha<0 or escolha >n_atr);	//repete enquanto a escolha for invalida
		
		if(escolha==0){	//se escolher 0, sai do jogo
			delete carta_max;
			return;
		}
		
		limpar_tela();

		print_cards(vez, 1, cardx, players); //imprime as cartas, revelando a que estava escondida

		cout<<endl;
		print_duelo(vez, 1, cardx, players, carta_max, escolha);	//imprime a comparacao dos valores (com as barras)
		
		if(!press_enter()){		//pede para pressionar enter, se inserir 0, sai do jogo
			delete carta_max;
			return;
		}

		limpar_tela();
		print_cards(vez, 1, cardx, players);	//reimprime as cartas (para a tela continuar igual)
												//mas sem o pedido de pressionar enter

		cout<<endl;
		print_duelo(vez, 2, cardx, players, carta_max, escolha);	//imprime a comparacao de novo, mas sem delay

		
		//verifica qual carta venceu
		if(cardx[!vez].get_tipo()=="SUPER TRUNFO" or cardx[vez].get_tipo()=="SUPER TRUNFO"){	//se uma eh trunfo
			if(cardx[!vez].get_tipo()=="SUPER TRUNFO" and cardx[vez].get_tipo()!="A"){
				vez = !vez;
			}
			else if(cardx[vez].get_tipo()=="SUPER TRUNFO" and cardx[!vez].get_tipo()=="A"){
				vez = !vez;
			}
		}		
		else if(cardx[!vez].get_atr(escolha-1).get_valor() > cardx[vez].get_atr(escolha-1).get_valor()){
			//se a que nao escolheu vence, troca a vez
			vez = !vez;
		}
		else if(cardx[!vez].get_atr(escolha-1).get_valor() == cardx[vez].get_atr(escolha-1).get_valor()){
			//se valores forem iguais, usa funcao de calculo de pontos para ver qual carta eh mais fraca
			//a carta mais fraca ganha
			//se o total das duas cartas for igual, carta de quem nao escolheu atributo ganha
			if(get_pontos(cardx[vez], cardx[!vez], carta_max) < cardx[vez].get_n_atr()*100){
				vez = !vez;
			}
		}
		
		pontos = get_pontos(cardx[vez], cardx[!vez], carta_max);	//calcula pontos
		
		cout<<endl;
		cout<<cardx[vez].get_nome()<<" vence!"<<endl;
		cout<<cardx[!vez].get_nome()<<" foi adicionado ao monte de "<<players[vez]->get_nome()<<"."<<endl;
		cout<<players[vez]->get_nome()<<" ganhou "<<pontos<<" pontos!"<<endl;


		players[vez]->rodar_carta();	//jogador que ganhou nao perde carta
		
		players[!vez]->perder_carta();	//o que perdeu, perde a carta

		players[vez]->ganhar_carta(cardx[!vez]);	//vencedor ganha a carta do outro

		players[vez]->ganhar_pontos(pontos);	//vencedor ganha os pontos
		
		if(!press_enter()){
			delete carta_max;
			return;
		}

		//verifica se jogo acabou
		if(players[0]->n_cartas()==0 or players[1]->n_cartas()==0){	//se acabou cartas de algum jogador
			fim=1;

		}
		else if(pts_max and (players[0]->get_pontos()>=pts_max or players[1]->get_pontos()>=pts_max)){
			//se algum jogador alcancou pontuacao maxima
			fim=1;
		}

	}
	//depois que o jogo acabou

	do{
		limpar_tela();
		//imprime resultados (nomes, numero de cartas e pontos)
		cout<<players[0]->get_nome()<<": "<<players[0]->n_cartas()<<" c, ";
		cout<<players[0]->get_pontos()<<" pts"<<endl;
		cout<<players[1]->get_nome()<<": "<<players[1]->n_cartas()<<" c, ";
		cout<<players[1]->get_pontos()<<" pts"<<endl;
		cout<<endl;
		cout<<players[vez]->get_nome()<<" venceu!"<<endl;
		cout<<endl;
		press_enter();
		if(MODO_TESTE)
			getline(cin, aux);
	}while(MODO_TESTE and aux!="0");	//para sair daqui, no modo teste, precisa inserir 0
	delete carta_max;	
}	

Baralho** distribuir_cartas(Baralho* deck){
	//distribui cartas do baralho em 2 montes
	
	Baralho** montes = NULL;

	try{
		montes = new Baralho*[2];	//cria montes
		montes[0] = new Baralho();
		montes[1] = new Baralho();
	}catch(int a){
		if(a==-1){
			cout<<"Baralho nao pode ser criado. Arquivo nao existe."<<endl;
			throw a;
		}
	}
	

	int j=0;
	Carta card;
	while(deck->get_n_cartas()>0){
		card = deck->ver_primeira_carta();	//pega primeira carta do baralho
		(*montes[j])+=card;	//adiciona a um monte
		(*deck)--;			//retira carta do baralho
		j = !j;				//troca o monte
	}
	montes[0]->embaralhar();
	montes[1]->embaralhar();
	return montes;
}

void singleplayer(string arq){
	//escolhe a dificuldade do jogo no modo singleplayer
	int opcao;
	int mensagem=0;
	string aux;

	Baralho* deck;		//baralho escolhido
	Baralho* monte_ref;	//copia do baralho
	Baralho** montes;	//montes dos jogadores
	Pessoa* p1;			//objeto da pessoa

	do{
		limpar_tela();

		if(mensagem)
			cout<<"Opcao invalida."<<endl;
		mensagem=0;

		try{
			deck = new Baralho(arq);	//cria o baralho com o arquivo passado
			monte_ref = new Baralho(arq);		//copia do baralho
		}catch(int a){
			if(a==-1){
				cout<<"Baralho nao pode ser criado. Arquivo nao existe."<<endl;
				throw a;
			}

		}
			

		deck->embaralhar();			//embaralha
		montes = distribuir_cartas(deck);	//distribui para os jogadores
		p1 = new Pessoa("PLAYER 1", montes[0]);	//cria o objeto pessoa
		Carta* carta_max = criar_carta_max(monte_ref);	//cria carta maxima do baralho

		cout<<"Qual dificuldade?"<<endl;
		cout<<"1 - Facil"<<endl;
		cout<<"2 - Medio"<<endl;
		cout<<"3 - Dificil"<<endl;
		cout<<"4 - Muito dificil"<<endl;
		cout<<"5 - Impossivel"<<endl;
		cout<<"0 - voltar"<<endl;
		cout<<"Escolha uma opcao (0 a 5): ";
		
		opcao = get_int(-1);	//pega opcao na entrada

		//cria o bot escolhido e inicia o jogo
		if(opcao==1){			
			//bot iniciante recebe apenas o proprio monte
			BotFacil* bot = new BotFacil("Bot Iniciante", montes[1]);
			iniciar_jogo(monte_ref, p1, bot);
			delete bot;
			bot=NULL;
		}
		else if(opcao==2){
			//bot medio recebe carta maxima para escolher atributos
			BotMedio* bot = new BotMedio("Bot Amador", montes[1], carta_max);
			iniciar_jogo(monte_ref, p1, bot);
			delete bot;
			bot=NULL;
		}
		else if(opcao==3){
			//bot dificil recebe carta max e copia do baralho usado
			BotDificil* bot = new BotDificil("Bot Experiente", montes[1], carta_max, monte_ref);
			iniciar_jogo(monte_ref, p1, bot);
			delete bot;
			bot=NULL;
		}
		else if(opcao==4){
			//bor profissional recebe acesso ao monte do oponente
			BotProf* bot = new BotProf("Bot Profissional", montes[1], carta_max, monte_ref, montes[0]);
			iniciar_jogo(monte_ref, p1, bot);
			delete bot;
			bot=NULL;
		}
		else if(opcao==5){
			//bot trapaceiro tambem recebe acesso ao monte do oponente
			BotImpossivel* bot = new BotImpossivel("Bot Trapaceiro", montes[1], carta_max, monte_ref, montes[0]);
			iniciar_jogo(monte_ref, p1, bot);
			delete bot;
			bot=NULL;
		}
		else if(opcao!=0)
			mensagem=1;

		//depois de jogar, retorna aqui e libera tudo que foi alocado
		delete deck;
		delete monte_ref;
		delete montes[0];
		delete montes[1];
		delete[] montes;
		delete p1;
		delete carta_max;

	}while(opcao!=0);
}

void multiplayer(string arq){
	//cria o baralho e os jogadores e inicia o jogo multiplayer

	Baralho* deck = NULL;	//baralho
	Baralho* monte_ref = NULL;	//copia do baralho para o jogo

	try{
		deck = new Baralho(arq);	//cria o baralho com o arquivo passado
		monte_ref = new Baralho(arq);		//copia do baralho
	}catch(int a){
		if(a==-1){
			cout<<"Baralho nao pode ser criado. Arquivo nao existe."<<endl;
			throw a;
		}

	}

	deck->embaralhar();	//embaralha

	Baralho** montes = distribuir_cartas(deck);	//cria montes dos jogadores

	montes[0]->embaralhar();
	montes[1]->embaralhar();
	Pessoa* p1 = new Pessoa("PLAYER 1", montes[0]);	//cria jogador 1

	Pessoa* p2 = new Pessoa("PLAYER 2", montes[1]);	//cria jogador 2


	iniciar_jogo(monte_ref, p1, p2);	//inicia o jogo
	delete p1;
	delete p2;
	delete deck;
	delete montes[0];
	delete montes[1];
	delete[] montes;
	delete monte_ref;
}

void escolher_bot2(Baralho* monte_ref, Jogador* bot1, Baralho** montes){
	//selecao do bot 2 no bot x bot
	//monte ref eh copia do baralho a ser usado no jogo
	int opcao;
	string aux;
	int mensagem=0;
	do{
		Carta* carta_max = criar_carta_max(monte_ref);	//cria carta maxima
		limpar_tela();

		if(mensagem)
			cout<<"Opcao invalida."<<endl;
		mensagem=0;

		cout<<"Qual nivel do bot 2?"<<endl;
		cout<<"1 - Facil"<<endl;
		cout<<"2 - Medio"<<endl;
		cout<<"3 - Dificil"<<endl;
		cout<<"4 - Muito dificil"<<endl;
		cout<<"5 - Impossivel"<<endl;
		cout<<"0 - voltar"<<endl;
		cout<<"Escolha uma opcao (0 a 5): ";

		opcao = get_int(-1);	
			
		if(opcao==1){
			//cria bot facil
			BotFacil* bot = new BotFacil("Bot2 Iniciante", montes[1]);
			iniciar_jogo(monte_ref, bot1, bot);
			delete bot;
			bot=NULL;
			return;
		}
		else if(opcao==2){
			//bot medio recebe carta maxima
			BotMedio* bot = new BotMedio("Bot2 Amador", montes[1], carta_max);
			iniciar_jogo(monte_ref, bot1, bot);
			delete bot;
			bot=NULL;			
			return;
		}
		else if(opcao==3){
			//bot dificil recebe copia do baralho
			BotDificil* bot = new BotDificil("Bot2 Experiente", montes[1], carta_max, monte_ref);
			iniciar_jogo(monte_ref, bot1, bot);
			delete bot;
			bot=NULL;
			return;
		}
		else if(opcao==4){
			//bot profissional recebe acesso ao monte do outro bot
			BotProf* bot = new BotProf("Bot2 Profissional", montes[1], carta_max, monte_ref, montes[0]);
			iniciar_jogo(monte_ref, bot1, bot);
			delete bot;
			bot=NULL;
			return; 
		}
		else if(opcao==5){
			//bot trapaceiro tambem recebe acesso ao monte do outro
			BotImpossivel* bot = new BotImpossivel("Bot2 Trapaceiro", montes[1], carta_max, monte_ref, montes[0]);
			iniciar_jogo(monte_ref, bot1, bot);
			delete bot;
			bot=NULL;
			return;
		}
		else if(opcao!=0)
			mensagem=1;

		delete carta_max;
		carta_max=NULL;

	}while(opcao!=0);
}

void botXbot(string arq){
	//seleciona bot 1 para o bot x bot
	//arq eh nome do arquivo do baralho a ser usado no jogo
	int opcao;
	string aux;

	Baralho* deck;
	Baralho* monte_ref;
	
	Baralho** montes;
	int mensagem=0;

	do{
		limpar_tela();

		if(mensagem)
			cout<<"Opcao invalida."<<endl;
		mensagem=0;

		try{
			deck = new Baralho(arq);	//cria o baralho com o arquivo passado
			monte_ref = new Baralho(arq);		//copia do baralho
		}catch(int a){
			if(a==-1){
				cout<<"Baralho nao pode ser criado. Arquivo nao existe."<<endl;
				throw a;
			}

		}

		deck->embaralhar();			//embaralha
		montes = distribuir_cartas(deck);//cria montes dos bots
		montes[0]->embaralhar();
		montes[1]->embaralhar();

		Carta* carta_max = criar_carta_max(monte_ref);	//carta maxima

		cout<<"Qual nivel do bot 1?"<<endl;
		cout<<"1 - Facil"<<endl;
		cout<<"2 - Medio"<<endl;
		cout<<"3 - Dificil"<<endl;
		cout<<"4 - Muito dificil"<<endl;
		cout<<"5 - Impossivel"<<endl;
		cout<<"0 - voltar"<<endl;
		cout<<"Escolha uma opcao (0 a 5): ";
		
		opcao = get_int(-1);
		if(opcao==1){
			//cria bot iniciante	
			BotFacil* bot = new BotFacil("Bot1 Iniciante", montes[0]);
			escolher_bot2(monte_ref, bot, montes);
			delete bot;
			bot=NULL;
		}
		else if(opcao==2){
			//bot medio recebe carta maxima
			BotMedio* bot = new BotMedio("Bot1 Amador", montes[0], carta_max);
			escolher_bot2(monte_ref, bot, montes);
			delete bot;
			bot=NULL;
			carta_max=NULL;
		}
		else if(opcao==3){
			//bot dificil recebe carta maxima e copia do baralho
			BotDificil* bot = new BotDificil("Bot1 Experiente", montes[0], carta_max, monte_ref);
			escolher_bot2(monte_ref, bot, montes);
			delete bot;
			bot=NULL;
		}
		else if(opcao==4){
			//bot prof recebe acesso ao monte do oponente
			BotProf* bot = new BotProf("Bot1 Profissional", montes[0], carta_max, monte_ref, montes[1]);
			escolher_bot2(monte_ref, bot, montes);
			delete bot;
			bot=NULL;
		}
		else if(opcao==5){
			//bot impossivel tambem recebe acesso ao monte do oponente
			BotImpossivel* bot = new BotImpossivel("Bot1 Trapaceiro", montes[0], carta_max, monte_ref, montes[1]);
			escolher_bot2(monte_ref, bot, montes);
			delete bot;
			bot=NULL;
		}
		else if(opcao!=0)
			mensagem=1;

		delete carta_max;
		delete deck;
		delete montes[0];
		delete montes[1];
		delete[] montes;
		delete monte_ref;
	}while(opcao!=0);
}

void modo_de_jogo(string arq){
	//seleciona modo de jogo
	//arq eh nome do baralho a ser usado no jogo
	int opcao;
	string aux;
	int mensagem=0;
	do{
		limpar_tela();

		if(mensagem)
			cout<<"Opcao invalida."<<endl;
		mensagem=0;

		cout<<"Qual modo de jogo?"<<endl;
		cout<<"1 - PLAYER 1 x Bot"<<endl;
		cout<<"2 - PLAYER 1 x PLAYER 2"<<endl;
		cout<<"3 - Bot x Bot"<<endl;
		cout<<"0 - voltar"<<endl;
		cout<<"Escolha uma opcao (0 a 3): ";
		opcao = get_int(-1);
		if(opcao==1)
			singleplayer(arq);
		else if(opcao==2)
			multiplayer(arq);
		else if(opcao==3)
			botXbot(arq);
		else if(opcao!=0)
			mensagem=1;

	}while(opcao!=0);
}
void jogar(){
	//seleciona qual baralho sera usado no jogo
	int opcao;
	string aux;
	int n;
	ifstream bar("baralhos.txt");	//abre arquivo que contm os baralhos salvos
	getline(bar, aux);
	bar.close();
	n = atoi(aux.c_str());	//numero de baralhos
	vector<string> baralhos;	//vetor de nomes de baralhos
	int mensagem=0;


	do{
		limpar_tela();

		if(mensagem)
			cout<<"Opcao invalida."<<endl;
		mensagem=0;

		bar.open("baralhos.txt");	//abre arquivo que contem os nomes dos baralhos
		getline(bar, aux);
		cout<<"Com qual baralho deseja jogar?"<<endl;
		for(int i=0;i<n;i++){
			getline(bar, aux);
			cout<<i+1<<" - "<<aux<<endl;	//imprime os nomes
			baralhos.push_back(aux);		//adiciona no vetor
		}
		cout<<"0 - voltar"<<endl;
		cout<<"Escolha uma opcao (0 a "<<n<<"): ";
		
		opcao = get_int(-1);
		if(opcao>0 and opcao<=n){
			modo_de_jogo(baralhos[opcao-1]);	//manda escolher modo de jogo com o baralho passado
		}
		else if(opcao!=0)
			mensagem=1;

		bar.close();
	}while(opcao!=0);

}

void tela_inicial(){
	string aux;
	int opcao;
	int mensagem=0;
	do{
		limpar_tela();
		if(mensagem)
			cout<<"Opcao invalida."<<endl;
		mensagem=0;
		
		cout<<"O que deseja fazer?"<<endl;
		cout<<"1 - jogar"<<endl;
		cout<<"2 - personalizar baralhos"<<endl;
		cout<<"0 - sair"<<endl;
		cout<<"Escolha uma opcao (0 a 2): ";
		
		opcao = get_int(-1);
		if(opcao == 1)
			jogar();
		else if(opcao==2)
			personalizar_baralho();
		else if(opcao!=0)
			mensagem++;
	}while(opcao!=0);
}

int main(){
	srand(time(NULL));

	tela_inicial();

	return 0;
}