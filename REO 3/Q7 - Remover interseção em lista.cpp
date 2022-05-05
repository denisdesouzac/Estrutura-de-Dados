#include <iostream>
#include <cstdlib>

using namespace std;

// para facilitar a troca de int para outro tipo
// estamos criando um apelido para int chamado dado
// com issso, destaca-se que a lista pode ser uma lista
// de qualquer objeto, não apenas inteiros...
// ou seja, é uma lista de dados.
typedef int Dado; //typedef permite criar novos tipos a partir de outros

class noh{
	friend class listadup;
	private:
		// dado está como constante para não permitir alteração//
		const Dado dado; // poderia ser outro tipo de variável
		noh* proximo;
		noh* anterior;
	public:
		//noh();
		noh(Dado d = 0);
};

// construindo dado chamando seu construtor
noh::noh(Dado d) : dado(d){
	//dado = d;
	proximo = NULL;
	anterior = NULL;
}

// lista dinamicamente encadeada
class listadup{
private:
	noh* primeiro;
	noh* ultimo;
	int tamanho;
	void removetodos();// remove todos os elementos da lista
public:
	// construtores e destrutores
	listadup();
	listadup(const listadup& umalista);
	~listadup();
	// sobrecarga do operador de atribuição
	listadup& operator=(const listadup& umalista);
	// inserção, remoção e procura
	inline void insere(Dado dado);
	void inserenofim(Dado dado);
	void inserenoinicio(Dado dado);
	void inserenaposicao(int posicao, Dado dado);
	int procura (Dado valor); // retorna a posição
	// métodos adicionais (impressão, vazia)
	void imprime();
	inline bool vazia();
	void removevalor(Dado valor);
	void remove(listadup umaLista);
	int tamanhoLista();
};

// constrói uma lista inicialmente vazia
listadup::listadup(){
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
}

// construtor de copia
listadup::listadup(const listadup& umalista){
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;

	// percorre a lista recebida como parâmetro, copian do os dados
	noh* aux = umalista.primeiro;
	
	while(aux != NULL){
		inserenofim(aux->dado);
		aux = aux->proximo;
	}
}

// destrutor da lista (chama a função privada aux)
listadup::~listadup(){
	removetodos();
}

// remove todos os elementos da lista
void listadup::removetodos(){
	noh* aux = primeiro;
	noh* temp;
	
	while(aux != NULL){
		temp = aux;
		aux = aux->proximo;
		delete temp;
	}
	// redirecionado ponteiros
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
}

// sobrecarga do operador de atruibuição
listadup& listadup::operator =(const listadup& umalista){
	// limpa a lista atual
	removetodos();
	// percorre a lista recebida como parâmetro, copiando os dados
	noh* aux = umalista.primeiro;
	
	while(aux != NULL){
		inserenofim(aux->dado);
		aux = aux->proximo;
	}
	return *this;
}

// insere por padrão no final da lista
void listadup::insere(Dado dado){
	inserenofim(dado);
}

// insere no final da lista 
void listadup::inserenofim(Dado dado){
	// *primeiro criamos o novo nó
	noh* novo = new noh(dado);
	
	// * agora inserioms o nó na lista
	// se a lista estiver vazia, inserimos o primeiro nó
	if( vazia() ){ // ou (primeiro == NULL) ou (tamanho == 0)
		primeiro = novo;
		ultimo = novo;
	}
	else{ // já tem elementos na lista, insere no final
		ultimo->proximo = novo;
		novo->anterior = ultimo;
		ultimo = novo;
	}
	tamanho++;
}

// insere no início da lista
void listadup::inserenoinicio(Dado dado){
	// *primeiro criamos o novo nó
	noh* novo = new noh(dado);
	
	// * agora inserioms o nó na lista
	// se a lista estiver vazia, inserimos o primeiro nó
	if( vazia() ){ // ou (primeiro == NULL) ou (tamanho == 0)
		primeiro = novo;
		ultimo = novo;
	}
	else{ // já tem elementos na lista, insere no início
		novo->proximo = primeiro;
		primeiro->anterior = novo;
		primeiro = novo;
	}
	tamanho++;
}

// insere em uma determinada posição da lista
void listadup::inserenaposicao(int posicao, Dado dado){
	// *primeiro criamos o novo nó
	noh* novo = new noh(dado);
	
	// *agora inserimos o nó na lista
	// verificamos antes se é possível inserir na posição
	if( (posicao <= tamanho) and (posicao >= 0) ){
		if( vazia() ){ // ou (primeiro == NULL) ou (tamanho == 0)
			primeiro = novo;
			ultimo = novo;
		}else if(posicao == 0){ // insere no início
			novo->proximo = primeiro;
			primeiro->anterior = novo;
			primeiro = novo;
		}else if( posicao == tamanho){ // insere no fim
			ultimo->proximo = novo;
			novo->anterior = ultimo;
			ultimo = novo;
		}else{ // insere no meio da lista
			noh* aux = primeiro;
			int posaux = 0;
			
			// chegando na posição da lista
			while( posaux < (posicao-1) ){
				aux = aux->proximo;
				posaux++;
			}
			novo->proximo = aux->proximo;
			aux->proximo->anterior = novo;
			aux->proximo = novo;
			novo->anterior = aux;
		}
		tamanho++;
	}else{
		cerr << "Posicao inexistente!" << endl;
		exit(EXIT_FAILURE);
	}
}

int listadup::procura(Dado valor){
	noh* aux = primeiro;
	int posaux = 0;
	
	while((aux != NULL) and (aux->dado != valor)){
		posaux++;
		aux = aux->proximo;
	}
	if(aux == NULL){
		posaux = -1;
	}
	return posaux;
}

// método básico que percorre uma lista, imprimindo seus elementos
void listadup::imprime(){
	noh* aux = primeiro;
	
	while(aux != NULL){
		cout << aux->dado << " ";
		aux = aux->proximo;
	}
	cout << endl;
	
	// imprime reverso(para mostrar o duplo encadeamento)
	aux = ultimo;
	while(aux != NULL){
		cout << aux->dado << " ";
		aux = aux->anterior;
	}
	cout << endl;
}

// verifica SE ESTÁ VAZIA
inline bool listadup::vazia(){
	return (tamanho == 0);
}

int listadup::tamanhoLista(){
	return tamanho;
}

void listadup::removevalor(Dado valor){
	noh* aux = primeiro;
	
	while((aux != NULL) and (aux->dado != valor)){
		aux = aux->proximo;
	}
	if(aux == NULL){
		exit(EXIT_FAILURE);
	}else{
		noh* anterior = aux->anterior;
		noh* proximo = aux->proximo;
		if(anterior != NULL){
			anterior->proximo = proximo;
		}else{
			primeiro = aux->proximo;
		}
		if(proximo != NULL){
			proximo->anterior = anterior;
		}else{
			ultimo = aux->anterior;
		}
		delete aux;
	}
	tamanho--;
	if( vazia() ){
		ultimo = NULL;
		primeiro = NULL;
	}
}

void listadup::remove(listadup umaLista){// NOVA IMPLEMENTAÇÃO
	
	noh* aux1 = primeiro;// Começa no primeiro da lista 1
	noh* aux2 = NULL;
	
	Dado vetor[tamanho];// Vetor para armazenar dados iguais
	int contador = 0;
	
	while(aux1 != NULL){
		
		aux2 = umaLista.primeiro;// Começa no primeiro da lista 2
		
		while(aux2 != NULL){// Compara com todos os dados da lista 2
			if(aux1->dado == aux2->dado){// Se for igual
				vetor[contador] = aux2->dado;// Armazena o valor que será removido
				contador++;
			}
			aux2 = aux2->proximo;
		}
		aux1 = aux1->proximo;
	}
	
	for(int i = 0; i < contador; i++){//Chama a função de remoção
		removevalor(vetor[i]);		//para cada item identificado como igual
	}
}

int main (){
	listadup L1, L2;
	
	int quantidade1, quantidade2, numLista;
	cin >> quantidade1;
	
	//Inserção na primeira lista
	for(int i = 0; i < quantidade1; i++){
		cin >> numLista;
		L1.insere(numLista);
	}
	
	cin >> quantidade2;
	//Inserção na segunda lista
	for(int i = 0; i < quantidade2; i++){
		cin >> numLista;
		L2.insere(numLista);
	}
	
	L1.remove(L2);
	
	//saída de dados
	
	if(L1.tamanhoLista() == 0){
		cout << "-1" << endl;
	}else{
		L1.imprime();// Imprime lista 1
	}
	
	return 0;
}
