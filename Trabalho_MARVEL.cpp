#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

struct Heroi{
int id;
char nome[50];
char poderes[50];
char biografia[200];
};

int funcaohash(int m){
	int h = 13;
	return m%h;
}

class bloco {
	friend class tabelaHash;
private:
	unsigned int quantidade;
	Heroi marvel1;
	Heroi marvel2;
	Heroi marvel3;
	Heroi marvel4;
public:
	bloco();
	~bloco();
};

bloco::bloco(){
	quantidade =0;
	marvel1.id = 0;
	marvel2.id = 0;
	marvel3.id = 0;
	marvel4.id = 0;
};

class tabelaHash {
private:
	int quantBloco;
	fstream arq;
public:
	tabelaHash();
	~tabelaHash();
	void insere();
	void remove();
	void busca(fstream *arq, int id);
	void imprimi(fstream *arq);

};

tabelaHash::tabelaHash(){
	quantBloco = 16;
	bloco inicio;
		arq.open("SHILDE.bin", ios::out | ios::in | ios::binary);
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
}
tabelaHash::~tabelaHash(){
	arq.close();
}
void tabelaHash::insere(){
	Heroi marvel;
	cout << "Identificacao do Heroi: ";
		cin >> marvel.id;
	cout << "Nome do Heroi: ";
		cin.ignore();
		cin.getline(marvel.nome,50);
	cout << "Habilidades do Heroi: ";
		cin.getline(marvel.poderes,50);
	cout << "Historia do Heroi: ";
		cin.getline(marvel.biografia,200);

	bloco equipe;//NOME ALTERADO
	int chave = funcaohash(marvel.id);

	arq.seekg(sizeof(int)+sizeof(bloco)*chave);
	arq.read((char*) &equipe, sizeof(bloco));
	if(equipe.quantidade < 4){
		if(equipe.quantidade == 0){
			equipe.marvel1 = marvel;
		}
		equipe.quantidade++;
	}
	else{
		cout << "A equipe" << chave << "ja esta cheia" << endl;
	}
	arq.seekp(sizeof(int)+sizeof(bloco)*chave);
	arq.write((char*) &equipe, sizeof(bloco));

}

void tabelaHash::remove(){
	int id;
	cout << "Digite a Identificacao do Heroi: ";
	cin >> id;

	Heroi marvel;
	bloco equipe;
	int chave = funcaohash(id);

	arq.seekg(sizeof(int)+ sizeof(bloco)*chave);
	arq.read((char*) &equipe, sizeof(bloco));
	if(equipe.quantidade!=0){
		equipe.quantidade--;
	}
	else{
		cout <<"A equipe" << chave << "onde o Heroi com Identificacao: " << marvel.id << " estava, ja esta vazia" << endl; //FRASE ALTERADA
	}
	arq.seekp(sizeof(int)+sizeof(bloco)*chave);
	arq.write((char*) &equipe, sizeof(bloco));
}

void imprimi(fstream *arq){
	arq->seekg(0);
	int x;
	arq->read((char *) &x, sizeof(int));
	Heroi aux;

	for (int i = 0; i < x; ++i){
		arq->read((char *) &aux, sizeof(Heroi));
		cout << "ID: " << aux.id << endl
			 << "Nome: " << aux.nome << endl
			 << "Podereses: " << aux.poderes << endl
			 << "Biografia: " << aux.biografia << endl;
	}
}

int main(){
	tabelaHash X; //Mudar nome
	int comando = 0;
	fstream arq("SHILD.bin");

	while(comando!=6){
		cout << "Escolha uma opcaoo!" << endl
			 << "1-Inserir um novo Heroi na equipe" << endl
			 << "2-Listar os Heroi" << endl
			 << "3-Remover um Heroi da equipe" << endl
			 << "4-Convocar um Heroi" << endl
			 << "5-Sair" << endl;
			 cin >> comando;
			 cout << endl;
	}
	switch (comando){
		case 1:
			X.insere();
			break;
		case 2:
			X.imprimi(&arq);
			break;
		case 3:
			X.remove();
			break;
		case 4:
			cout << "ID :";
			int id;
			cin >> id;
			X.busca(&arq,id);
			break;
		case 5:
			cout << "Fim do programa!" << endl;
			break;
		default:
			cout << "Opcao invalida!";

	}


	return 0;

	}
