#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

typedef int dado;
const int INVALIDO = -1;

class torneio{
	private:
		dado *heap;
		int capacidade;
		int tamanho;
		int iniciadados;
        inline int pai(int i);
		inline int esquerda(int i);
		inline int direita(int i);
		void arruma();
		void copiamaior(int i, int &cont);
        void copiaSubindo(int i);
	public:
		torneio( int vet[], int tam);
        torneio(int numFolhas);
		~torneio();
        void insere(dado d);
		void imprime();
	
};

torneio::torneio(int vet[],int tam){

	capacidade = 1;
	while(capacidade < tam){
		capacidade *= 2;
	}

	capacidade = capacidade - 1 + tam;

	heap = new dado[capacidade];
	iniciadados = capacidade - tam;
	
	//cout << "Inicio dados vet:" << iniciadados << endl;
	//cout << "Capacidade vet:" << capacidade << endl;
	
	memcpy(&heap[iniciadados], vet, tam*sizeof(int));

	tamanho = tam;
	arruma();
}

torneio::torneio(int numFolhas){

	capacidade = 1;
    while(capacidade < numFolhas){
        capacidade *= 2;
    }

    capacidade = capacidade - 1 + numFolhas;

	heap = new dado[capacidade];
	iniciadados = capacidade - numFolhas;
	
	//cout << "Inicio dados vet:" << iniciadados << endl;
	//cout << "Capacidade vet:" << capacidade << endl;

    for(int i = 0; i < capacidade; i++){
        heap[i] = INVALIDO;
    }

	arruma();
}

torneio::~torneio(){
	delete[] heap;
}

void torneio::arruma(){
	int cont = 0;
	//cout << "arruma:" << iniciadados-1 << endl;
	for(int i = iniciadados-1; i >= 0; i--){
		cont++;
		copiamaior(i, cont);
	}
	//cont = 0;
}

int torneio::pai(int i){
	return (i -1) / 2;
}

int torneio::esquerda(int i){
	return 2*i+1;
}

int torneio::direita(int i){
	return 2*i+2;
}

void torneio::copiamaior(int i, int &cont){
	int esq = esquerda(i);
	int dir = direita(i);
	//cout << "I:" << i << " " << "E:" << esq << " " << "D:" << dir << " ";
	int maior = INVALIDO;
	//cout << "ESQ:" << esq << " " << "DIR:" << dir;
	
	if(esq < capacidade){
		if(cont%2 != 0){
			if((dir < capacidade) and (heap[dir] > heap[esq])){
				maior = dir;
			}
			else{
				maior = esq;
			}
			//cout << maior << endl;
			heap[i] = heap[maior];
		}
		else{
			if((dir < capacidade) and (heap[dir] < heap[esq])){
				maior = dir;
			}
			else{
				maior = esq;
			}
			//cout << maior << endl;
			heap[i] = heap[maior];
		}
	}
	else{
		heap[i] = INVALIDO;
	}
	//cout << " " << "MAIOR:" << maior << " HEAP[MAIOR]:" << heap[maior] << endl;
}

void torneio::copiaSubindo(int i){
    int p = pai(i);
    if(heap[i] > heap[p]){
        heap[p] = heap[i];
        copiaSubindo(p);
    }

}

void torneio::insere(dado d){
    if(tamanho == capacidade) {
		cerr << "Impossivel inserir em heap cheio.\n";
		exit(EXIT_FAILURE);
	}
    heap[tamanho + iniciadados] = d;
    copiaSubindo(tamanho+iniciadados);
    tamanho++;
}

void torneio::imprime(){
	cout << heap[0] << endl;
	//cout << "HEAP:" << endl;
	//for(int i = 0; i < capacidade; i++){
		//cout << heap[i] << " ";
		//cout << "pos" << i << ":" << heap[i] << endl;
	//}
	//cout << endl;
}

int main(){
	
	int tam;
	cin >> tam;
	dado vet[tam];
	torneio *h = new torneio(tam);

	for(int i =0; i < tam; i++){
		cin >> vet[i];
		h->insere(vet[i]);
	}
	//torneio *h = new torneio(vet,tam);
	h->imprime();
	delete h;
	
	return 0;
}
