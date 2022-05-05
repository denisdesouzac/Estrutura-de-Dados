#include <iostream>
using namespace std;

class noh{
	
	friend class pilha;
	
	private:
		char mValor;
		noh* mProximo;
	public:
		noh(char valor);
};

noh::noh(char valor){
	mValor = valor;
	mProximo = NULL;
}

class pilha{
	
	private:
	
		noh* mTopo;
		unsigned mTamanho;
	
	public:
	
		pilha();
		~pilha();
		void limpaPilha();
		char desempilha();
		void empilha(char valor);
		bool vazia();
		unsigned tamanho();
};

pilha::pilha(){
	mTopo = NULL;
	mTamanho = 0;
}

pilha::~pilha(){
	limpaPilha();
}

void pilha::limpaPilha(){
	
	while(mTamanho > 0){
		desempilha();
	}
}

bool pilha::vazia(){
	return(mTamanho == 0);
}

char pilha::desempilha(){
	
	char valor = mTopo->mValor;
	noh* temp = mTopo;
	mTopo = mTopo->mProximo;
	delete temp;
	mTamanho--;
	return valor;
}

void pilha::empilha(char valor){
	
	noh* novo = new noh(valor);
	novo->mProximo = mTopo;
	mTopo = novo;
	mTamanho++;
}



int main(){
	
	
	
	return 0;
}
