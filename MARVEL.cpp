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

int funcaohash(int id){
	int chave = 0;
	chave = ((13*id)%17)%16;
	return chave;
}

tabelaHash::tabelaHash(){
	quantBloco = 16;
	bloco inicio;
	fstream arq("SHILDE.bin", ios::out | ios::in | ios::binary);
	if(!arq.good()){
		arq.open("SHILDE.bin", ios::out | ios::in | ios::binary | ios::trunc);
		arq.write((char*) &quantBloco, sizeof(int));
	}else{
		arq.seekg(0);
		arq.write((char*) &quantBloco,sizeof(int));
	}
	for (int i = 0; i < quantBloco; ++i){
		arq.seekp(sizeof(int)+sizeof(bloco)*i);
		arq.write((char*) &inicio, sizeof(bloco));

	}
	arq.close();
}

bloco::bloco(){
	quantidade = 0;
	integrante0.id = 0;
	integrante1.id = 0;
	integrante2.id = 0;
	integrante3.id = 0;
};

void tabelaHash::insere(){
	fstream arq;
	Heroi integrante;
	arq.open("SHILDE.bin", ios::out | ios::in | ios::binary);
	cout << "Identificação do Herói: ";
		cin >> integrante.id;
	cout << "Nome do Herói: ";
		cin.ignore();
		cin.getline(integrante.nome,50);
	cout << "Habilidades do Herói: ";
		cin.getline(integrante.poderes,50);
	cout << "História do Herói: ";
		cin.getline(integrante.biografia,250);
	cout << endl;
	cout << " Dados Coletados!" << endl;
	cout << endl;
	bloco equipe;//NOME ALTERADO
	int chave = funcaohash(integrante.id);

	arq.seekg(sizeof(int)+sizeof(bloco)*chave);
	arq.read((char*) &equipe, sizeof(bloco));
	if(equipe.quantidade < 4){
	if (!arq.good()){
		cout << "ERRO" << endl;
	}
	if (equipe.quantidade == 0){
		equipe.integrante0 = integrante;	
	}
	else if (equipe.integrante0.id > integrante.id){
			equipe.integrante3 = equipe.integrante2;
			equipe.integrante2 = equipe.integrante1;
			equipe.integrante1 = equipe.integrante0;
			equipe.integrante0 = integrante;
	}
	else if (equipe.integrante1.id > integrante.id or equipe.quantidade == 1){
			equipe.integrante3 = equipe.integrante2;
			equipe.integrante2 = equipe.integrante1;
			equipe.integrante1 = integrante;
	}
	else if (equipe.integrante2.id > integrante.id or equipe.quantidade == 2){
			equipe.integrante3 = equipe.integrante2;
			equipe.integrante2 = integrante;
	}
	else{
		equipe.integrante3=integrante;
	}
	equipe.quantidade++;
	arq.flush();
	}
	else cout << "A Equipe " << chave << "ja esta cheia" << endl;
	cout << endl;
	
	arq.seekp(sizeof(int)+(int) sizeof(bloco)*chave);
	arq.write((char*) &equipe, sizeof(bloco));
	arq.close();
}

void tabelaHash::remove(){
	fstream arq;
	bool removido = false;
	int id;
	cout << "Digite a Identificação do Herói: ";
	cin >> id;
	Heroi integrante;
	bloco equipe;
	int chave = funcaohash(id);

	arq.seekg(sizeof(int)+ sizeof(bloco)*chave);
	arq.read((char*) &equipe, sizeof(bloco));
	if(equipe.quantidade!=0){
		if(equipe.quantidade == 4 and (not removido)){
			if(equipe.integrante0.id == integrante.id){
				equipe.integrante0 = equipe.integrante1;
				equipe.integrante1 = equipe.integrante2;
				equipe.integrante2 = equipe.integrante3;
			}
			else if (equipe.integrante1.id == integrante.id){
				equipe.integrante1 = equipe.integrante2;
				equipe.integrante2 = equipe.integrante3;
			}
			else if (equipe.integrante2.id == integrante.id){
				equipe.integrante2 = equipe.integrante3;
			}
			else
				equipe.quantidade--;
		equipe.quantidade--;
		removido = true;
	}
	else if (equipe.quantidade == 3 and (not removido)){
		if(equipe.integrante0.id == integrante.id){
				equipe.integrante0 = equipe.integrante1;
				equipe.integrante1 = equipe.integrante2;
			}
			else if (equipe.integrante1.id == integrante.id){
				equipe.integrante1 = equipe.integrante2;
			}
			else
				equipe.quantidade--;
			equipe.quantidade--;
			removido = true;
	}
	else if (equipe.quantidade == 2 and (not removido)){
		if(equipe.integrante0.id == integrante.id){
				equipe.integrante0 = equipe.integrante1;
			}
		else 
			equipe.quantidade--;
		equipe.quantidade--;
	}
		else{
			equipe.quantidade--;
			removido = true;
		}
	
	arq.seekp(sizeof(int)+sizeof(bloco)*chave);
	arq.write((char*) &equipe, sizeof(bloco));
}
	else 
		cout <<"A equipe" << chave << "onde o Heroi com Identificaoo: " << id << " estava, ja esta vazia" << endl;

	arq.close();
}
void tabelaHash::imprime(){

	fstream arq;
	arq.open("SHILDE.bin", ios::out | ios::in | ios::binary);
	bloco equipe;
	for (int i = 0; i < quantBloco; ++i){
		arq.seekg(sizeof(int)+ sizeof(bloco)*i);
		arq.read((char*) &equipe, sizeof(bloco));
		cout << "Bloco" << i << endl;
			if (equipe.quantidade >= 1){
				cout << equipe.integrante0.id << endl
					 << equipe.integrante0.nome << endl
					 << equipe.integrante0.poderes << endl
					 << equipe.integrante0.biografia << endl;
			}
			if (equipe.quantidade >= 2){
				cout << equipe.integrante1.id << endl
					 << equipe.integrante1.nome << endl
					 << equipe.integrante1.poderes << endl
					 << equipe.integrante1.biografia << endl;
			}
			if (equipe.quantidade >= 3){
				cout << equipe.integrante2.id << endl
					 << equipe.integrante2.nome << endl
					 << equipe.integrante2.poderes << endl
					 << equipe.integrante2.biografia << endl;
			}
			if (equipe.quantidade == 4){
				cout << equipe.integrante3.id << endl
					 << equipe.integrante3.nome << endl
					 << equipe.integrante3.poderes << endl
					 << equipe.integrante3.biografia << endl;
			}
			arq.flush();
			cout << endl;
	}
	arq.close();

}
void tabelaHash::busca(int procurado_id){
	fstream arq;
	arq.open("SHILDE.bin", ios::out | ios::in | ios::binary);
	bloco equipe;
	bool achou = false;

	for (int i = 0; (i < quantBloco) and !achou; ++i){
		arq.seekg(sizeof(int)+sizeof(bloco)*i);
		arq.read((char*) &equipe, sizeof(bloco));

		if (equipe.integrante0.id == procurado_id and equipe.quantidade >= 1){
			cout << equipe.integrante0.id << endl
				 << equipe.integrante0.nome << endl
				 << equipe.integrante0.poderes << endl
				 << equipe.integrante0.biografia << endl;
			achou = true;
		}
		else if (equipe.integrante1.id == procurado_id and equipe.quantidade >=2){
				cout << equipe.integrante1.id << endl
				     << equipe.integrante1.nome << endl
					 << equipe.integrante1.poderes << endl
					 << equipe.integrante1.biografia << endl;
				achou = true;
		}
		else if (equipe.integrante2.id == procurado_id and equipe.quantidade >= 3){
				cout << equipe.integrante2.id << endl
					 << equipe.integrante2.nome << endl
					 << equipe.integrante2.poderes << endl
					 << equipe.integrante2.biografia << endl;
				achou = true;
		}
		else if (equipe.integrante3.id == procurado_id and equipe.quantidade >= 4){
				cout << equipe.integrante3.id << endl
					 << equipe.integrante3.nome << endl
					 << equipe.integrante3.poderes << endl
					 << equipe.integrante3.biografia << endl;
				achou = true;
		}
		arq.flush();
	}
	arq.close();
}