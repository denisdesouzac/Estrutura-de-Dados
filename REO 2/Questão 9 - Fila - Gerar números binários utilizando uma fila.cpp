#include <iostream>
#include <sstream>
using namespace std;

class noh{
	friend class fila;
	private:
		string mValor;
		noh* mProximo;
	public:
		noh(string valor);
};

noh::noh(string valor){
	
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
		void enfileira(string valor);
		string desenfileira();
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

void fila::enfileira(string valor){
	noh *novo = new noh(valor);
	if(mTamanho == 0){
		mInicio = novo;
	}else{
		mFim->mProximo = novo;
	}
	mFim = novo;
	mTamanho++;
}

string fila::desenfileira(){
	
	string valor = mInicio->mValor;
	noh *temp = mInicio;
	mInicio = mInicio->mProximo;
	delete temp;
	mTamanho--;
	if(mTamanho == 0){
		mFim = NULL;
	}
	return valor;
}

//Função que gera o número binário.
string gera_binario(int num){
	
	int resto;
	string resto_string;
	string bin;
	
	while(num != 0){
		
		resto = num % 2;
		
		stringstream aux;
		aux << resto;
		resto_string = aux.str();// Conversão de int para string
		
		num = num/2;
		
		bin = resto_string + bin;// Concatenação
	}
	
	return bin;
}


int main(){
	
	int quantidade, contador = 1;
	string binario, resultado;
	cin >> quantidade;
	
	fila f1;
	
	while(contador <= quantidade){
		binario = gera_binario(contador);// Gera o binário 
		f1.enfileira(binario);// Enfileira i binário
		contador++;
	}
	
	// Desenfileiramento com imprensão de dados
	while(not f1.vazia()){
		resultado = f1.desenfileira();
		cout << resultado << " ";
	}
	
	return 0;
}
