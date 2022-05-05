#include <iostream>
using namespace std;

class noh{
	friend class pilha;
	private:
		int mValor;
		noh* mProximo;
	public:
		noh(int valor);
};

noh::noh(int valor){
	
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
		unsigned tamanho();
		void empilha(int valor);
		int desempilha();
		void limpaPilha();
		bool vazia();
};

pilha::pilha(){
	mTopo = NULL;
	mTamanho = 0;
}

pilha::~pilha(){
	limpaPilha();
}

void pilha::limpaPilha(){
	
	while( mTamanho > 0){
		desempilha();
	};
}

unsigned pilha::tamanho(){
	return mTamanho;
}

bool pilha::vazia(){
	return(mTamanho == 0);
}

void pilha::empilha(int valor){
	noh *novo = new noh(valor);
	novo->mProximo = mTopo;
	mTopo = novo;
	mTamanho++;
}

int pilha::desempilha(){
	
	int valor = mTopo->mValor;
	noh *temp = mTopo;
	mTopo = mTopo->mProximo;
	delete temp;
	mTamanho--;
	return valor;
}

int main(){
	
	
	return 0;
}
