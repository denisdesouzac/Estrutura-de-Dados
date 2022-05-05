#include <iostream>
using namespace std;

class noh{
	friend class fila;
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

class fila{
	
	private:
		noh* mInicio;
		noh* mFim;
		unsigned mTamanho;
	public:
	
		fila();
		~fila();
		unsigned tamanho();
		void enfileira(int valor);
		int desenfileira();
		void limpaFila();
		bool vazia();
};

fila::fila(){
	mInicio = NULL;
	mFim = NULL;
	mTamanho = 0;
}

fila::~fila(){
	limpaFila();
}

void fila::limpaFila(){
	
	while( mTamanho > 0){
		desenfileira();
	};
}

unsigned fila::tamanho(){
	return mTamanho;
}

bool fila::vazia(){
	return(mTamanho == 0);
}

void fila::enfileira(int valor){
	noh *novo = new noh(valor);
	mFim->mProximo = novo;
	mFim = novo;
	mTamanho++;
}

int fila::desenfileira(){
	
	int valor = mInicio->mValor;
	noh *temp = mInicio;
	mInicio = mInicio->mProximo;
	delete temp;
	mTamanho--;
	return valor;
}

int main(){
	
	
	return 0;
}
