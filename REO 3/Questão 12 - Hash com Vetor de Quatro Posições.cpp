#include <iostream>

using namespace std;

int calculaHash(int chave, int capacidade){
	return chave % capacidade;
}

struct InfoHash{
	int chave;
	string valor;
};

class Hash{
public:
	Hash(int capacidade);
	~Hash();
	void Inserir(int chave, string valor);
	void InsereFim(int chave, string valor, int pos);
	void Recupera(int chave);
	void Imprimir();
	void AumentaContador(int pos);
	int RetornaContador(int pos);
	//void IniciaContador();

private:
	int Buscar(int chave);
	InfoHash **tabela;
	int capacidade;
	int tamanho;
	int *vetor_contador;
};
// Construtor
Hash::Hash(int capacidade){
	this->capacidade = capacidade;
	tabela = new InfoHash*[capacidade];
	for (int i = 0; i < capacidade; i++){
		tabela[i] = new InfoHash[4];
	}

	for(int i = 0; i < capacidade; i++){
		for(int j = 0; j < 4; j++){
			tabela[i][j].chave = -1;
			tabela[i][j].valor = "";
		}
	}
	
	vetor_contador = new int[capacidade];
	for(int i = 0; i < capacidade; i++){
		vetor_contador[i] = 0;
	}
	
	tamanho = 0;
}
//Destrutor
Hash::~Hash(){
	delete[] tabela;
}
//Função de busca
int Hash::Buscar(int chave){
	int pos = calculaHash(chave, capacidade);

	for(int i = 0; i < capacidade; i++){
		if(tabela[pos][i].chave == chave){
			return chave;
		}
	}

	return -1;// percorreu o vetor e não encontrou
}
//Função de inserção
void Hash::Inserir(int chave, string valor){
	
	int pos = calculaHash(chave, capacidade);
	if (Buscar(chave) == -1){
		InsereFim(chave, valor, pos);
	}else{
		cout << "ITEM JÁ ESTÁ NA TABELA!" << endl;
	}
}

void Hash::InsereFim(int chave, string valor, int pos){

	for(int i = 0; i < capacidade; i++){
		if(tabela[pos][i].chave == -1){
			tabela[pos][i].chave = chave;
			tabela[pos][i].valor = valor;
			i = capacidade;
		}
	}
}

void Hash::Imprimir(){
	
	for(int i = 0; i < capacidade; i++){
		cout << i << ':';
		for(int j = 0; j < 4; j++){
			cout << '[' << tabela[i][j].chave << '/' << tabela[i][j].valor << ']';
		}
		cout << endl;
	}
}

void Hash::Recupera(int chave){
	
	if(Buscar(chave) == -1){
		cout << "NÃO ENCONTRADO!" << endl;
	}else{
		
		int pos = calculaHash(chave, capacidade);
		
		for(int i = 0; i < 4; i++){
			if(tabela[pos][i].chave == chave){
				cout << tabela[pos][i].valor << endl;
				i = 4;
			}
		}
	}
	
}
// Função que incrementa o contador na posição;
void Hash::AumentaContador(int pos){
	vetor_contador[pos]++;
}
// Função que retorna apenas a quantidade de itens do contador
int Hash::RetornaContador(int pos){
	return vetor_contador[pos];
}

/*void Hash::IniciaContador(){
	for(int i = 0; i < capacidade; i++){
		vetor_contador[i] = 0;
	}
}*/

int main(){
	
	int capacidadeHash;
	cin >> capacidadeHash;// Insere qual a capacidade
	
	Hash Tabela(capacidadeHash);// Cria a tabela Hash com a capacidade
	
	int quantidade_inserir;
	cin >> quantidade_inserir;// Itens a inserir
	
	int chave;
	string valor;
	InfoHash vet_dados[quantidade_inserir];
	int posicao;
	
	//Inserção de dados
	for(int i = 0; i < quantidade_inserir; i++){
		cin >> chave >> valor;
		posicao = calculaHash(chave, capacidadeHash);// Calcula a posição
		//Tabela.AumentaContador(posicao);// Contador de itens de cada posição da tabela
		vet_dados[i].chave = chave;
		vet_dados[i].valor = valor;
		Tabela.Inserir(chave, valor);// Chamada a função de inserção
	}
	
	//Recuperação de dados
	int chave_recupera;
	int vet_recupera[4];
	for(int i = 0; i < 4; i++){// Insere em um vetor as chaves de recuperação
		cin >> chave_recupera;
		vet_recupera[i] = chave_recupera;
	}
	
	int retorno;
	for(int i = 0; i < quantidade_inserir; i++){
		posicao = calculaHash(vet_dados[i].chave, capacidadeHash);// Calcula a posição
		Tabela.AumentaContador(posicao);
		retorno = Tabela.RetornaContador(posicao);
		if(retorno > 4){
			cout << "NÚMERO MÁXIMO DE COLISÕES PARA CHAVE!" << endl;
		}
	}
	
	for(int i = 0; i < 4; i++){// Chama a função para todas as chaves
		Tabela.Recupera(vet_recupera[i]);
	}
	
	Tabela.Imprimir();// Feita a impressão;
	return 0;
}
