#include "personalizar_baralho.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <thread>
#include "gamecontrol.hpp"
#include "atributo.hpp"
#include "carta.hpp"
#include "baralho.hpp"

using namespace std;

//funcoes da personalizacao de baralhos
//criar baralho
//modificar baralho
//vizualizar baralho
//deletar baralho


float valor_aleat(float min, float max){	//retorna valor aleatorio entre limites passados
	if(max < min){
		float aux = max;
		max = min;
		min = aux;
	}
	else if(max==min){
		min=0;
		if(max==0)
			max=100000;
	}

	return (float)(min + (rand() % ((int)(max-min)+1)));
}

void consoante_aleat(char &letra1){	//atribui uma consoante aleatoria ao char passado
	char letra;
	do{
		letra = 97 + (rand()%26);
	}while(letra=='a' or letra=='e' or letra=='i' or letra=='o' or letra=='u' or letra=='q');
	letra1 = letra;
}

void vogal_aleat(char &letra2){	//atribui uma vogal aleatoria ao char passado
	char letra;
	letra = rand()%5;
	if(letra==0)
		letra='a';
	else if(letra==1)
		letra='e';
	else if(letra==2)
		letra='i';
	else if(letra==3)
		letra='o';
	else if(letra==4)
		letra='u';

	letra2 = letra;
}

string nome_aleat(){	//cria um nome aleatorio
	char letra1, letra2;
	int tam = 4+(rand()%7);	//tamanho aleatorio entre 4 e 10
	if(tam%2==1)
		tam--;

	string nome(tam, ' ');
	for(int i=0;i<tam;i+=2){
		thread let1(consoante_aleat, std::ref(letra1));	//cria consoantes e vogais aleatorias em paralelo
		thread let2(vogal_aleat, std::ref(letra2));
		let1.join();	//sincroniza
		let2.join();
		nome[i]=letra1;	//atribui ao nome
		nome[i+1]=letra2;
	}
	nome[0]-=32;	//transforma primeira letra em maiuscula

	return nome;
}

int criar_cartas(int& n_cartas, int& n_atr, vector<Carta> &vet, vector<Atributo<float>> &atr){
	// cria as cartas do baralho a ser criado
	string aux;
	float valor;
	int mensagem=0;
	vector<string> nomes;	//vetor de nomes para verificar repetição
	vector<float> menor;	//armazena menores valores dos atributos para utilizar como limite 
							//nos numeros aleatorios
	vector<float> maior;	//armazena maiores valores dos atributos
	int aleat=0;			//flag para saber se irá escolher algo aleatorio
	int cancel=0;			//flag para cancelar alguma acao

	for(int i=0;i<n_atr;i++){	//inicializa menores e maiores atributos
		menor.push_back(VALOR_MAX);
		maior.push_back(VALOR_MIN);
	}

	for(int i=0;i<n_cartas;i++){	//loop para criar as cartas
		Carta card;
		card.set_n_atr(n_atr);
		card.set_atr_all(n_atr, atr);	//cria carta com atributos
		mensagem=0;
		cancel=0;
		do{	//escolhe nome da carta
			limpar_tela();

			if(aleat==0){	//se nao tiver indicado para aleatorizar nome
				if(mensagem==1)
					cout<<"Nome invalido."<<endl;
				else if(mensagem==2)
					cout<<"Nome invalido (nome repetido)."<<endl;	
				mensagem=0;

				cout<<"Qual o nome da carta "<<i+1<<" (";

				if(i==0)
					cout<<"Super Trunfo)?"<<endl;
				else if(i<(n_cartas/4)+1)
					cout<<"Tipo A)?"<<endl;
				else
					cout<<"Tipo B)?"<<endl;

				cout<<"1 - Nome aleatorio"<<endl;
				cout<<"2 - Aleatorizar carta (nome e atributos)"<<endl;
				cout<<"3 - Aleatorizar tudo (todas as cartas restantes)"<<endl;
				cout<<"4 - Voltar carta"<<endl;
				cout<<"0 - Voltar"<<endl;
				cout<<"insira o nome da carta (max 30 letras): ";
				getline(cin, aux);

				if(aux == "1"){
					aux = nome_aleat();	//aleatoriza nome
				}
				else if(aux == "2"){
					aux = nome_aleat();	//aleatoriza nome e indica que atributos tambem serao aleatorios
					aleat = 1;
				}
				else if(aux == "3"){	//aleatoriza nome e indica que vai aleatorizar baralho inteiro
					aleat =2;
					aux = nome_aleat();
				}
				else if(aux == "4"){	//volta um carta
					if(i>0){	//se ja criou uma carta
						vet.pop_back();	//tira do vetor de cartas
						nomes.pop_back();	//tira nome do vetor de nomes
						i-=2;	//volta 2 (incrementa 1 no final do for)
						cancel=1;	//indica que carta foi cancelada
					}
					
				}
				else if(aux.size()>30 or aux=="")	//se inseriu nome invalido
					mensagem=1;
				for(int j=0;j<(int)nomes.size();j++){	//verifica se o nome ja existe entre as cartas
					if(aux == nomes[j]){	//se ja existir, indica erro
						j=nomes.size();
						mensagem=2;
					}
				}
			}
			else if(aleat>0)	//se tiver indicado para aleatorizar nome
				aux = nome_aleat();
			

		}while(mensagem!=0);	//repete enquanto houver erro

		if(aux=="0"){	//se inserir 0, cancela tudo
			vet.clear();
			atr.clear();
			return 1;
		}
		if(!cancel){	//se nao cancelou carta
			cancel=0;
			card.set_nome(aux);	//atribui nome da carta

			for(int j=0;j<n_atr;j++){	//loop para atribuir os valores dos atributos
				mensagem=0;
				do{
					limpar_tela();
					if(aleat==0){	//se nao for para aleatorizar
						if(mensagem)
							cout<<"Numero inalido."<<endl;
						mensagem=0;

						cout<<"Qual o valor de "<<atr[j].get_nome()<<" de "<<card.get_nome()<<"?"<<endl;
						cout<<"a - Valor aleatorio"<<endl;
						cout<<"b - Aleatorizar atributos restantes"<<endl;
						cout<<"c - Aleatorizar tudo (cartas restantes)"<<endl;
						cout<<"d - Voltar atributo"<<endl;
						cout<<"e - Voltar carta"<<endl;
						cout<<"f - Voltar"<<endl;
						cout<<"Insira um valor ("<<VALOR_MIN<<" a "<<VALOR_MAX<<") ou escolha uma opcao (a a f): ";
						getline(cin, aux);
						if(aux == "a")
							valor = valor_aleat(menor[j], maior[j]);	//valor aleatorio
						else if(aux == "b"){
							aleat=1;
							valor = valor_aleat(menor[j], maior[j]);	//valor aleatorio e indica que o resto tambem sera
						}
						else if(aux == "c"){
							valor = valor_aleat(menor[j], maior[j]);	//valor aleatorio e indica que todo o baralho tambem sera
							aleat=2;
						}
						else if(aux=="d"){	//volta um atributo
							if(j>0){
								j-=2;
								cancel=1;
							}
							else
								valor=-1;
						}
						else if(aux == "e"){	//volta uma carta
							if(i>0){
								i-=2;
								vet.pop_back();
								nomes.pop_back();
								cancel=1;
								j=n_atr;
							}
							else
								valor=-1;
						}
						else if(aux=="f"){	//cancela tudo
							vet.clear();
							atr.clear();
							return 1;
						}
						else if(validar_float(aux)){	//se inserir um valor
							valor = atof(aux.c_str());

							if(valor<menor[j])	//atualiza menores e maiores atributos
								menor[j] = valor;
							if(valor>maior[j])
								maior[j] = valor;
						}
						else{
							valor=-1;
							mensagem=1;
						}
					}
					else if(aleat>0){	//se for para aleatorizar
						valor = valor_aleat(menor[j], maior[j]);
					}
					
				}while(valor< 0 or valor>100000);	//repete enquanto numero for invalido

				if(!cancel)	//se nao cancelar
					card.set_atr(j, atr[j].get_nome(), valor);	//atribui valor ao atributo da carta
			}
		}
		
		if(aleat==1)	//se era pra aleatorizar só uma carta, muda flag de aleatorio
		aleat=0;

		if(!cancel){	//se carta nao foi cancelada, insere no vetor de cartas e o nome no vetor de nomes
			vet.push_back(card);
			nomes.push_back(card.get_nome());
		}
	}

	return n_atr;
}

int definir_n_atributos(int& n_cartas, int& n_atr, vector<Carta> &vet){	//define atributos das cartas do baralho
	string aux;
	int baralho_cancelado=1;	//indica que baralho foi cancelado
	vector<Atributo<float>> atr;	//vetor de atributos
	int mensagem=0;
	do{
		baralho_cancelado=1;
		limpar_tela();

		if(mensagem)
			cout<<"Numero invalido."<<endl;
		mensagem=0;

		cout<<"Quantos atributos terao as cartas do seu baralho?"<<endl;
		cout<<"Insira um numero (3 a 10): ";

		n_atr = get_int(-1);		//pega inteiro da entrada, retorna o argumento se ocorrer erro

		if(3<=n_atr and n_atr<=10){
			Atributo<float> at;
			for(int i=0;i<n_atr;i++){
				do{
					limpar_tela();
					cout<<"Qual o nome do atributo "<<i+1<<"?"<<endl;
					cout<<"0 - Voltar"<<endl;
					cout<<"Insira um nome (max 15 letras): ";
					getline(cin, aux);					
				}while((aux.size()>15 or aux=="") and aux!="0");
				if(aux=="0"){
					n_atr=1;
				}
				at.set_nome(aux);	//insere atributo no vetor de atributos
				atr.push_back(at);
			}
			if(n_atr!=1){
				n_atr = criar_cartas(n_cartas, n_atr, vet, atr);	//cria as cartas
				if(n_atr!=1)
					baralho_cancelado=0;
			}
		}
		else if(n_atr!=0)
			mensagem=1;
	}while(n_atr != 0 and baralho_cancelado);
	return n_atr;

}

int definir_n_cartas(int& n_cartas, int& n_atr, vector<Carta> &vet){	//define numero de cartas do baralho
	string aux;
	int mensagem=0;
	do{
		limpar_tela();

		if(mensagem)
			cout<<"Numero invalido."<<endl;
		mensagem=0;
		cout<<"Quantas cartas tera seu baralho?"<<endl;
		cout<<"0 - Voltar"<<endl;
		cout<<"Insira um numero (10 a 100): ";
		
		n_cartas = get_int(-1);		//pega inteiro da entrada, retorna o argumento se ocorrer erro
		if(10<=n_cartas and n_cartas<=100)
			n_atr = definir_n_atributos(n_cartas, n_atr, vet);
		else if(n_cartas!=0)
			mensagem=1;

	}while(n_cartas != 0 and n_atr==0);
	if(n_cartas==0)
		return 1;
	return 0;
}

void criar_novo_baralho(){	//cria novo baralho
	string nome_baralho;
	string aux;
	int n_baralhos;
	int n_cartas=0;
	int n_atr=0;
	int baralho_cancelado=0;
	vector<Carta> vet;		//vetor de cartas do baralho
	vector<string> nomes;	//vetor de nomes
	int mensagem=0;

	fstream arq2("baralhos.txt");
	getline(arq2, aux);
	n_baralhos = atoi(aux.c_str());
	for(int i=0;i<n_baralhos;i++){	//insere nomes dos baralhos existentes no vetor de nomes
		getline(arq2, aux);
		nomes.push_back(aux);
	}
	arq2.close();

	do{	//define nome do baralho
		limpar_tela();

		if(mensagem==1)
			cout<<"Nome invalido."<<endl;
		else if(mensagem==2)
			cout<<"Este baralho ja existe."<<endl;
		mensagem=0;

		baralho_cancelado=1;
		cout<<"Qual sera o nome do seu baralho?"<<endl;
		cout<<"0 - Voltar"<<endl;
		cout<<"Insira o nome do seu baralho (max 20 letra): ";
		getline(cin, nome_baralho);

		if(nome_baralho.size()>20 or nome_baralho=="")
			mensagem=1;
		for(int i=0;i<(int)nomes.size();i++){	//verifica se nome ja existe
			if(nome_baralho == nomes[i]){
				mensagem=2;
				i = nomes.size();
			}
		}

		if(mensagem==0 and nome_baralho!="0")
			baralho_cancelado = definir_n_cartas(n_cartas, n_atr, vet);	//chama funcoes para criacao das cartas

	}while(nome_baralho!="0" and (nome_baralho.size()>20 or nome_baralho=="" or baralho_cancelado));	


	if(!baralho_cancelado and nome_baralho!="0"){	//se todos os passos foram realizados
		ofstream arq(nome_baralho.c_str());	//cria o arquivo do baralho

		arq<<n_cartas<<endl;	//coloca numero de cartas
		arq<<n_atr<<endl;		//coloca numero de atributos

		for(int i=0;i<n_atr;i++){
			arq<<vet[0].get_atr(i).get_nome()<<endl;	//coloca nomes dos atributos
		}
		
		for(int i=0;i<n_cartas;i++){	//loop que passa pelas cartas
			arq<<vet[i].get_nome()<<endl;	//coloca nome da carta
			for(int j=0;j<n_atr;j++){	//coloca valor dos atributos
				arq<<vet[i].get_atr(j).get_valor()<<endl;
			}
		}
		arq.close();

		nomes.clear();	//limpa vetor pois utilizara para outra coisa

		arq2.open("baralhos.txt");	//abre arquivo de baralhos

		getline(arq2, aux);		//pega numero de baralhos
		n_baralhos = atoi(aux.c_str());

		for(int i=0;i<n_baralhos;i++){	//pega nomes dos baralhos e insere no vetor de nomes
			getline(arq2, aux);
			nomes.push_back(aux);
		}

		arq2.close();	//fecha e abre de novo para resolver bug (quando chega em EOF, arquivo para de ler e escrever)
		arq2.open("baralhos.txt");

		arq2<<n_baralhos+1<<endl;	//escreve numero de baralhos incrementado
		for(int i=0;i<(int)nomes.size();i++){	//coloca os nomes dos baralhos inseridos no vetor
			arq2<<nomes[i]<<endl;
		}	
		arq2<<nome_baralho<<endl;	//coloca nome do novo baralho

		arq2.close();

		limpar_tela();
		cout<<"Baralho criado com sucesso."<<endl;
		press_enter();
	}

}

void imprimir_baralho(string arquivo){	//imprime as cartas de um baralho
	limpar_tela();

	int opcao;
	string aux;
	Baralho* bar = new Baralho(arquivo);	//cria o baralho atraves do nome do arquivo
	Carta card;

	do{
		limpar_tela();

		for(int i=0;i<bar->get_n_cartas();i++){	//passa pelas cartas do baralho e imprime
			card = bar->ver_primeira_carta();
			cout<<card<<endl;
			bar->rodar();
		}

		cout<<"0 - Voltar"<<endl;

		opcao = get_int(-1);		//pega inteiro da entrada, retorna o argumento se ocorrer erro
	}while(opcao!=0);

	delete bar;

}

void visualizar_baralho(){	//seleciona baralho a visualizar
	int opcao;
	string aux;
	int n;
	vector<string> baralhos;	//vetor de nomes de baralhos
	int mensagem=0;

	ifstream bar("baralhos.txt");	//abre o arquivo de baralhos
	getline(bar, aux);	//pega numero d baralhos

	n = atoi(aux.c_str());

	for(int i=0;i<n;i++){	//pega nomes dos baralhos e insere no vetor
		getline(bar, aux);
		baralhos.push_back(aux);
	}
	bar.close();

	do{
		limpar_tela();

		if(mensagem)
			cout<<"Opcao invalida."<<endl;
		mensagem=0;
		
		cout<<"Qual baralho deseja visualizar?"<<endl;
		for(int i=0;i<n;i++){			
			cout<<i+1<<" - "<<baralhos[i]<<endl;
		}
		cout<<"0 - voltar"<<endl;
		cout<<"Escolha uma opcao (0 a "<<n<<"): ";

		opcao = get_int(-1);		//pega inteiro da entrada, retorna o argumento se ocorrer erro	//escolhe o baralho
		if(opcao>0 and opcao<=n){
			imprimir_baralho(baralhos[opcao-1]);	//chama impressao
		}
		else if(opcao!=0)
			mensagem=1;

	}while(opcao!=0);

}

void apagar_baralho(string arq, int opcao){	//apaga um baralho escolhido
	string aux;
	int i;
	int n_baralhos;

	cout<<"Digite o nome do baralho ("<<arq<<") para confirmar."<<endl;
	getline(cin, aux);	//confirma remocao do baralho
	if(aux==arq){	//se confirmou
		opcao+=BLOQUEADOS;
		remove(arq.c_str());	//apaga arquivo

		fstream arq2("baralhos.txt");	//abre arquivo de baralhos

		getline(arq2, aux);
		n_baralhos = atoi(aux.c_str());	//numero de baralhos

		vector<string> vet;

		while(arq2.eof()==0){	//pega os nomes de todos os baralhos e insere no vetor
			getline(arq2, aux);
			vet.push_back(aux);
		}

		arq2.close();	//fecha e abre de novo para resolver bug (quando chega no EOF, arquivo para de ler e escrever)
		arq2.open("baralhos.txt");

		n_baralhos--;

		arq2<<n_baralhos<<endl;	//coloca numero de baralhos decrementado
		
		for(i=0;i<(int)vet.size();i++){	//coloca os nomes dos baralhos menos o nome do removido
			if(vet[i]!=arq)
				arq2<<vet[i]<<endl;
		}
		arq2.close();

		cout<<"Baralho deletado com sucesso."<<endl;
	}
	else{
		cout<<"Nome incorreto. Operacao cancelada."<<endl;
	}
	press_enter();
}

void deletar_baralho(){	//seleciona baralho a ser deletado
	int opcao;
	string aux;
	int n;
	vector<string> baralhos;	//vetor de nomes de baralhos
	int mensagem=0;
	do{
		limpar_tela();

		if(mensagem)
			cout<<"Opcao invalida."<<endl;
		mensagem=0;

		ifstream bar("baralhos.txt");	//abre arquivo de baralhos
		getline(bar, aux);
		n = atoi(aux.c_str());	//pega numero de baralhos			

		for(int i=0;i<n;i++){	//pega nomes dos baralhos
			getline(bar, aux);
			if(i>=BLOQUEADOS)	//insere no vetor de nomes se baralho nao for bloqueado
				baralhos.push_back(aux);
		}

		cout<<"Qual baralho deseja deletar?"<<endl;
		for(int i=0;i<n-BLOQUEADOS;i++){
			cout<<i+1<<" - "<<baralhos[i]<<endl;
		}
		cout<<"0 - voltar"<<endl;
		cout<<"Escolha uma opcao (0 a "<<n-BLOQUEADOS<<"): ";

		opcao = get_int(-1);		//pega inteiro da entrada, retorna o argumento se ocorrer erro //escolhe baralho
		if(opcao>0 and opcao<=n-BLOQUEADOS){
			apagar_baralho(baralhos[opcao-1], opcao);	//chama remocao
		}
		else if(opcao!=0)
			mensagem=1;

		bar.close();
		baralhos.clear();
	}while(opcao!=0);
		
}

void alterar_nome_atributo(string arq, int numero){	//altera nome de atributo
	string aux;
	string nome;
	int mensagem=0;
    do{
        limpar_tela();

        if(mensagem)
        	cout<<"Nome invalido."<<endl;
        mensagem=0;

        cout<<"Qual sera o novo nome desse atributo?"<<endl;
        cout<<"0 - Voltar"<<endl;
        cout<<"Insira o novo nome (max 15 letras): ";

        getline(cin, nome);

        if(nome.size()>15 or nome=="")
        	mensagem=1;

    }while(nome.size()>15 or nome=="");

    if(nome!="0"){
    	vector<string> vet;	//vetor para salvar strings a serem shiftadas depois da atualizacao
	    fstream arq2(arq.c_str());	//abre arquivo do baralho
	    for(int i=0;i<numero+2;i++){	//vai para a posicao depois do nome a ser alterado
	    	getline(arq2, aux);
	    }
	    while(arq2.eof()==0){	//salva tudo que estiver depois dele no vetor
	    	getline(arq2, aux);
	    	vet.push_back(aux);
	    }
	    arq2.close();	//fecha e abre de novo para resolver bug

	    arq2.open(arq.c_str());
	    for(int i=0;i<numero+1;i++){	//vai para posicao do nome a ser alterado
	    	getline(arq2, aux);
	    }
	   	arq2<<nome<<endl;	//escreve novo nome
	   	for(int i=0;i<(int)vet.size();i++){	//escreve as strings a serem shiftadas
	   		arq2<<vet[i]<<endl;
	   	}
	   	arq2.close();

	   	cout<<"Atributo alterado para "<<nome<<endl;
	   	press_enter();
	  }    
}

void modificar_atributo(string arq){	//seleciona atributo cujo nome sera alterado
    string aux;
    int opcao;
    int n_atr;
    int mensagem=0;
    do{
        limpar_tela();
        if(mensagem)
        	cout<<"Opcao invalida."<<endl;
        mensagem=0;

        cout<<"Qual atributo deseja modificar?"<<endl;
    	fstream arq2(arq.c_str());	//abre arquivo do baralho
        getline(arq2, aux);	//pula numero de cartas
        getline(arq2, aux);	
        n_atr = atoi(aux.c_str());	//pega numero de atributos
        for(int i=0;i<n_atr;i++){	//pega nomes dos atributos
            getline(arq2, aux);
            if(aux[aux.size()-1]=='\r'){	
                aux[aux.size()-1] = '\0';
            }
            cout<<i+1<<" - "<<aux<<endl;
        }
    	arq2.close();
        cout<<"0 - voltar"<<endl;
        cout<<"Escolha uma opcao (0 a "<<n_atr<<"): ";

        opcao = get_int(-1);		//pega inteiro da entrada, retorna o argumento se ocorrer erro //pega opcao
        
        if(opcao>0 and opcao<=n_atr)
        	alterar_nome_atributo(arq, opcao);	//chama alteracao do nome
        else if(opcao!=0)
        	mensagem=1;

    }while(opcao!=0);

}

string modificar_nome(string arq, int opcao){	//modifica nome de um baralho
	string aux;
    string nome;
    int n_baralhos;
    int mensagem=0;
    vector<string> vet;

    fstream arq2("baralhos.txt");	//abre arquivo de baralhos
    getline(arq2, aux);	
    n_baralhos = atoi(aux.c_str());	//pega numero de baralhos
    for(int i=0;i<n_baralhos;i++){	//insere no vetor de nomes, os nomes de todos os baralhos
    	getline(arq2, aux);
    	vet.push_back(aux);
    }
    arq2.close();

    do{
    	limpar_tela();

    	if(mensagem==1)
    		cout<<"Nome invalido."<<endl;
    	else if(mensagem==2)
    		cout<<"Este nome pertence a outro baralho."<<endl;
    	mensagem=0;

	    cout<<"Qual sera o novo nome do baralho?"<<endl;
	    cout<<"0 - Voltar"<<endl;
	    cout<<"Insira o novo nome do baralho (max 25 letras):";
	    getline(cin, nome);	//pega novo nome

	    if(nome.size()>25 or nome=="")
	    	mensagem=1;
	    for(int i=0;i<(int)vet.size();i++){	//verifica se nome eh repetido
	    	if(nome==vet[i]){
	    		mensagem=2;
	    		i = vet.size();
	    	}
	    }

    }while(nome.size()>25 or nome=="" or mensagem!=0);	//repete enquanto nome for invalido
    
    if(nome!="0"){	//se nome nao foi cancelado
    	opcao+=BLOQUEADOS;

        rename(arq.c_str(), nome.c_str());	//renomeia arquivo do baralho

        arq2.open("baralhos.txt");	//abre arquivo de baralhos

        getline(arq2, aux);

        for(int i=0;i<(int)vet.size();i++){	//coloca os nomes dos baralhos e o nome alterado
            if(vet[i]==arq)
            	arq2<<nome<<endl;
            else
            	arq2<<vet[i]<<endl;
        }
        arq2.close();
        return nome;
    }
    return arq;

}

void alterar_nome_carta(string arq, long pos){	//altera nome de uma carta
	string aux;
	string nome;
	vector<string> vet;
	int mensagem=0;
	int n_atr;
	int n_cartas;

	fstream arq2(arq.c_str());	//abre arquivp
	getline(arq2, aux);
	n_cartas = atoi(aux.c_str());	//pega numero de cartas
	getline(arq2, aux);
	n_atr = atoi(aux.c_str());	//numero de atributos
	for(int i=0;i<n_atr;i++){	//pula os atributos
		getline(arq2, aux);
	}
	for(int i=0;i<n_cartas;i++){	//insere os nomes das cartas no vetor de nomes
		getline(arq2, aux);
		vet.push_back(aux);
		for(int j=0;j<n_atr;j++){	//pula os valores dos atributos
			getline(arq2, aux);
		}
	}
	arq2.close();

	do{
		limpar_tela();

		if(mensagem==1)
			cout<<"Nome invalido."<<endl;
		else if(mensagem==2)
			cout<<"Este nome ja pertence a outra carta."<<endl;
		mensagem=0;

		cout<<"Qual sera o novo nome da carta?"<<endl;
		cout<<"0 - Voltar"<<endl;
		cout<<"Insira um nome (max 30 letras):";
		getline(cin, nome);

		if(nome=="" or nome.size()>30)	//verifica se nome eh valido
			mensagem=1;
		for(int i=0;i<(int)vet.size();i++){	//verifica se nome eh repetido
			if(nome==vet[i]){
				mensagem=2;
				i=vet.size();
			}
		}

	}while(nome=="" or nome.size()>30 or mensagem!=0);

	if(nome!="0"){	//se nao foi cancelado
		vet.clear();	//limpa vetor para usar pra outra coisa
		arq2.open(arq.c_str());	//abre arquivo
		arq2.seekg(pos, ios_base::beg);	//pula para posicao da carta
		getline(arq2, aux);	//pula nome da carta
		while(arq2.eof()==0){	//salva tudo depois do nome no vetor
			getline(arq2, aux);
			vet.push_back(aux);
		}
		arq2.close();	//fecha e abre de novo para resolver bug (quando chega no eof, para de funcionar)
		arq2.open(arq.c_str());
		arq2.seekp(pos, ios_base::beg);	//pula para posicao da carta
		arq2<<nome<<endl;	//escreve novo nome
		for(int i=0;i<(int)vet.size();i++){	//escreve o resto do arquivo
			arq2<<vet[i]<<endl;
		}
		arq2.close();

		cout<<"Nome alterado com sucesso."<<endl;
		press_enter();
	}
	
}

void alterar_valor(string arq, long pos, int opcao){	//altera valor de um atributo de uma carta

	string aux;
	float valor=0, novo_valor=0;
	vector<string> vet;
	fstream arq2(arq.c_str());	//abre o arquivo
	arq2.seekg(pos, ios_base::beg);	//pula para posicao da carta
	for(int i=0;i<opcao;i++){	//pula para posicao do atributo
		getline(arq2, aux);
	}
	getline(arq2, aux);
	valor = atof(aux.c_str());	//pega valor atual do atributo
	while(arq2.eof()==0){	//salva tudo depois do atributo no vetor
		getline(arq2, aux);
		vet.push_back(aux);
	}
	arq2.close();

	do{
		limpar_tela();

		if(novo_valor==-1)
			cout<<"Numero invalido."<<endl;

		cout<<"Qual o novo valor do atributo (atual = "<<valor<<")?"<<endl;
		cout<<"a - Voltar"<<endl;
		cout<<"Insira o novo valor (0 a 100000): ";
		getline(cin, aux);
		if(aux=="a"){
			valor=0;
		}
		else if(validar_float(aux))	//pega novo valor
			novo_valor = atof(aux.c_str());
		else
			novo_valor=-1;
		
	}while(novo_valor < 0 or novo_valor>100000);

	if(aux!="a"){	//se nao cancelou
		valor=novo_valor;
	
		arq2.open(arq.c_str());	//abre arquivo
		arq2.seekp(pos, ios_base::beg);	//pula para posicao da carta
		for(int i=0;i<opcao;i++){	//pula ateh posicao do atributo
			getline(arq2, aux);
		}
		arq2<<valor<<endl;	//escreve novo valor
		for(int i=0;i<(int)vet.size();i++){	//escree resto do arquivo
			arq2<<vet[i]<<endl;
		}

		cout<<"Valor alterado para "<<valor<<" com sucesso."<<endl;
		press_enter();
	}
	
}

void alterar_valor_atributo(string arq, long pos){	//ßeleciona qual atributo tera valor alterado
	string aux;
	int opcao;
	int n_atr;
	int mensagem=0;

	do{
		limpar_tela();

		if(mensagem)
			cout<<"Opcao invalida."<<endl;
		mensagem=0;

        cout<<"Qual atributo deseja modificar?"<<endl;
    	fstream arq2(arq.c_str());	//abre arquivo
        getline(arq2, aux);	//pula numero de cartas
        getline(arq2, aux);
        n_atr = atoi(aux.c_str());	//pega numero de atributos
        for(int i=0;i<n_atr;i++){	//pega nomes de atrobutos
            getline(arq2, aux);
            if(aux[aux.size()-1]=='\r'){
                aux[aux.size()-1] = '\0';
            }
            cout<<i+1<<" - "<<aux<<endl;
        }
    	arq2.close();
        cout<<"0 - voltar"<<endl;
        cout<<"Escolha uma opcao (0 a "<<n_atr<<"): ";
        opcao = get_int(-1);		//pega inteiro da entrada, retorna o argumento se ocorrer erro
        
        if(opcao>0 and opcao<=n_atr)
        	alterar_valor(arq, pos, opcao);
        else if(opcao!=0)
        	mensagem=1;

	}while(opcao != 0);
}

void alterar_carta(string arq, long pos){	//seleciona alteracao na carta
	string aux;
	int opcao;
	int mensagem=0;

	do{
		limpar_tela();

		if(mensagem)
			cout<<"Opcao invalida."<<endl;
		mensagem=0;

		cout<<"O que deseja alterar na carta?"<<endl;
		cout<<"1 - Alterar nome"<<endl;
		cout<<"2 - Alterar valor de um atributo"<<endl;
		cout<<"0 - Voltar"<<endl;
		cout<<"Escolha uma opcao (0 a 2): ";
		opcao = get_int(-1);		//pega inteiro da entrada, retorna o argumento se ocorrer erro
		if(opcao == 1)
			alterar_nome_carta(arq, pos);
		else if(opcao == 2)
			alterar_valor_atributo(arq, pos);
		else if(opcao!=0)
			mensagem =1;
	}while(opcao != 0);
}

void modificar_carta(string arq){	//seleciona carta a ser modificada
	string aux;
	string nome;
	int achou=0;
	int n_cartas;
	int n_atr;
	long posicao;
	vector<string> vet;
	int mensagem=0;


    do{
        limpar_tela();

        if(mensagem)
        	cout<<"Carta nao encontrada (nome invalido)."<<endl;
        mensagem=0;

        cout<<"Qual o nome da carta que deseja alterar?"<<endl;
        cout<<"0 - Voltar"<<endl;
        cout<<"Insira o nome da carta: ";
        getline(cin, nome);	//pega nome da carta

        achou =0;

        fstream arq2(arq.c_str());	//abre arquivo
        getline(arq2, aux);
        n_cartas = atoi(aux.c_str());	//pega numerod e cartas
       	getline(arq2, aux);
       	n_atr = atoi(aux.c_str());	//pega numero de atributos
       	for(int i=0;i<n_atr;i++){	//pula nomes de atributos
       		getline(arq2, aux);
       	}
       	for(int i=0;i<n_cartas;i++){	//pega cartas comparando o nome inserido
       		getline(arq2, aux);
       		if(aux == nome){
       			achou = 1;
       			posicao = arq2.tellg() - (long)nome.size();	//se achou, salva posicao do arquivo
       			posicao--;
       			i = n_cartas;
       		}
       		
       		else{
       			for(int i=0;i<n_atr;i++){	//pula valores de atributos
       				getline(arq2, aux);
       			}
       		}
       	}
       	arq2.close();
       	if(achou)
       		alterar_carta(arq, posicao);	//chama alteracao da carta
       	else
       		mensagem=1;	//se nao achou carta, mensagem de erro

    }while(nome!="0");
}

void escolher_modificacao(string arq, int numero){	//seleciona qual modificacao ira fazer no baralho
    string aux;
    string nome = arq;
    int opcao;
    int mensagem=0;
    do{
        limpar_tela();
        if(mensagem)
        	cout<<"Opcao invalida."<<endl;
        mensagem=0;

        cout<<"O que deseja fazer em '"<<nome<<"'?"<<endl;
        cout<<"1 - Modificar nome do baralho"<<endl;
        cout<<"2 - Modificar nome de um atributo"<<endl;
        cout<<"3 - Modificar uma carta do baralho"<<endl;
        cout<<"0 - Voltar"<<endl;
        cout<<"Escolha uma opcao (0 a 2): ";
       
       	opcao = get_int(-1);		//pega inteiro da entrada, retorna o argumento se ocorrer erro
        if(opcao == 1)
            nome = modificar_nome(nome, numero);
        else if(opcao == 2)
            modificar_atributo(nome);
        else if(opcao == 3)
        	modificar_carta(nome);
        else if(opcao!=0)
        	mensagem=1;
    }while(opcao!=0);
}

void modificar_baralho(){	//seleciona qual baralho sera modificado

    int opcao;
    string aux;
    int n;
    vector<string> baralhos;
    int mensagem=0;
    
    do{
        limpar_tela();

        if(mensagem)
        	cout<<"Opcao invalida."<<endl;
        mensagem=0;

        ifstream bar("baralhos.txt");
        getline(bar, aux);
        n = atoi(aux.c_str());

        for(int i=0;i<n;i++){
            getline(bar, aux);
            if(i>=BLOQUEADOS)
            	baralhos.push_back(aux);
        }
        bar.close();

        cout<<"Qual baralho deseja alterar?"<<endl;
        for(int i=0;i<n-BLOQUEADOS;i++){
            cout<<i+1<<" - "<<baralhos[i]<<endl;
        }
            
        cout<<"0 - voltar"<<endl;
        cout<<"Escolha uma opcao (0 a "<<n-BLOQUEADOS<<"): ";
        
        opcao = get_int(-1);		//pega inteiro da entrada, retorna o argumento se ocorrer erro
        if(opcao>0 and opcao<=n-BLOQUEADOS){
            escolher_modificacao(baralhos[opcao-1], opcao);
        }
        else if(opcao!=0)
            mensagem=1;

        bar.close();
        baralhos.clear();
    }while(opcao!=0);	
}

void personalizar_baralho(){	//seleciona personalizacao do baralho
	string aux;
	int opcao;
	int mensagem=0;
	do{
		limpar_tela();
		if(mensagem)
			cout<<"Opcao invalida."<<endl;
		mensagem=0;

		cout<<"O que deseja fazer?"<<endl;
		cout<<"1 - Criar novo baralho"<<endl;
		cout<<"2 - Modificar baralho existente"<<endl;
		cout<<"3 - Visualizar baralho existente"<<endl;
		cout<<"4 - Deletar baralho existente"<<endl;
		cout<<"0 - Voltar"<<endl;
		cout<<"Escolha uma opcao (0 a 4): ";
		
		opcao = get_int(-1);		//pega inteiro da entrada, retorna o argumento se ocorrer erro
		if(opcao == 1)
			criar_novo_baralho();
		else if(opcao == 2)
			modificar_baralho();
		else if(opcao == 3)
			visualizar_baralho();
		else if(opcao ==4)
			deletar_baralho();
		else if(opcao!=0)
			mensagem=1;
		
	}while(opcao!=0);
}