/*
	Trabalho de Estrutura de Dados.

	Registro de Furacoes.

	Copyright 2018
	Gabriel Herrique Silva Bernardo
	Ricardo Lopes Teixeira 
	Lucas Bernardes

*/

#include <iostream>
#include <fstream>
#include "MARVEL.hpp"

using namespace std;

int main(){
	tabelaHash legiao; //Mudar nome
	int comando =0;

	while(comando!=5){
		cout << "Escolha uma opção!" << endl
			 << "1-Inserir um novo Herói na equipe" << endl
			 << "2-Listar os Herói" << endl
			 << "3-Remover um Herói da equipe" << endl
			 << "4-Convocar um Herói" << endl
			 << "5-Sair" << endl;
			 cin >> comando;
			 cout << endl;
	
	switch (comando){
		case 1:
			legiao.insere();
			break;
		case 2:
			legiao.imprime();
			break;
		case 3:
			legiao.remove();
			break;
		case 4:
			int procurado;
			cout << "Quem vc procura?:  ";
			cin >> procurado;
			legiao.busca(procurado);
			break;
		case 5:
			cout << "Fim do programa!" << endl;
			break;
		default:
			cout << "Opção invalida!";

	}
}

	return 0;

	}
