/*
	Trabalho de Estrutura de Dados.

	Registro de Furacoes.

	Copyright 2018
	Gabriel Herrique Silva Bernardo
	Ricardo Lopes Teixeira 
	Lucas Bernardes

*/

#ifndef MARVEL_HPP
#define MARVEL_HPP

using namespace std;

struct Heroi{
int id;
char nome[50];
char poderes[50];
char biografia[200];
};

class bloco {
	friend class tabelaHash;
private:
	unsigned int quantidade;
	Heroi integrante0;
	Heroi integrante1;
	Heroi integrante2;
	Heroi integrante3;
public:
	bloco();
};

class tabelaHash {
private:
	int quantBloco;
public:
	tabelaHash();
	void insere();
	void remove();
	void busca(int procurado_id);
	void imprime();

};

#endif






