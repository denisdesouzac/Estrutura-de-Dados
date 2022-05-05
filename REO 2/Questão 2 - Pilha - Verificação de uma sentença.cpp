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
		unsigned tamanho();
		void empilha(char valor);
		char desempilha();
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

void pilha::empilha(char valor){
	noh *novo = new noh(valor);
	novo->mProximo = mTopo;
	mTopo = novo;
	mTamanho++;
}

char pilha::desempilha(){
	
	char valor = mTopo->mValor;
	noh *temp = mTopo;
	mTopo = mTopo->mProximo;
	delete temp;
	mTamanho--;
	return valor;
}

int main(){
	
	pilha *pa = new pilha();// Pilha de A
	pilha *pc = new pilha();// Pilha de C
	int quant_B = 0;

	char letra_anterior = 'A';
	char letra;
	cin >> letra;
	
	while(letra != 'X'){
		
		if(letra == 'A' and letra >= letra_anterior){
			
			pa->empilha(letra);
			
		}else if(letra == 'C' and letra >= letra_anterior){
			
			pc->empilha(letra);
			
		}else if(letra == 'B' and letra >= letra_anterior){
			quant_B++;
		}
		
		letra_anterior = letra;
		cin >> letra;
	}
	
	// Desempilhamento
	while((pa->tamanho()) > 0 and (pc->tamanho()) > 1){
		pa->desempilha();
		pc->desempilha();
		pc->desempilha();
	}
	
	// Saída
	if((2 * pa->tamanho()) == (pc->tamanho()) and quant_B == 1){
		cout << "sim" << " " << pa->tamanho() << " " << pc->tamanho() << endl;
	}else{
		cout << "nao" << " " << pa->tamanho() << " " << pc->tamanho() << endl;
	}
	
	pa->~pilha();
	pc->~pilha();
	
	return 0;
}
