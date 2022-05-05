#include <iostream>	// Pode usar varias coisas prontas
#include <vector>	// mas e' preciso completar a classe
#include <limits>	// classe Heap. E' permitido fazer
#include <string>	// alteracoes na classe Heap.
#include <stdexcept>
#include <cstdlib>

class Atividade {
	public:
		int nota;
		int tentativas;
};

class Aluno {
	public:
		Aluno();
		Aluno(unsigned matr, const std::string& n);
		~Aluno();
		void InserirAtividade(const Atividade& a);
		std::string Nome() const { return nome; }
		unsigned Matricula() { return matricula; }
		float Media() const;
		int Tentativas() const;
	protected:
		unsigned matricula;
		std::string nome;
		std::vector<Atividade> vetAtividades;
};

Aluno::Aluno()
	: matricula(0), nome(), vetAtividades() {
}

Aluno::Aluno(unsigned matr, const std::string& n)
	: matricula(matr), nome(n), vetAtividades() {
}

Aluno::~Aluno() {
}

void Aluno::InserirAtividade(const Atividade& a) {
	vetAtividades.push_back(a);
}

float Aluno::Media() const {
	float soma = 0.0f;
	unsigned nroAtividades = unsigned(vetAtividades.size());
	for (unsigned i = 0; i < nroAtividades; ++i)
	soma += float(vetAtividades.at(i).nota);
	return soma / float(nroAtividades);
}

int Aluno::Tentativas() const {
	int tentativas = 0;
	unsigned nroAtividades = unsigned(vetAtividades.size());
	for (unsigned i = 0; i < nroAtividades; ++i)
		tentativas += vetAtividades[i].tentativas;
	return tentativas;
}

bool operator>(const Aluno& a1, const Aluno& a2){
	if(a1 > a2){
		return true;
	}else{
		return false;
	}
}

typedef Aluno TDado;

class Heap {
	// classe Heap (max-heap, o maior fica na raiz/inicio)
	public:
	// Criar heap sem dados e com capacidade informada
		Heap(int cap);
		// Destruttor
		~Heap();
		// Inserir um dado na heap
		void Inserir(const TDado& d);
		// Consulta a raiz
		TDado Raiz();
		// Retira e retorna a raiz
		TDado Retirar();
		// Verifica se a heap está vazia
		bool Vazia();
	protected:
		void ArrumarDescendo(int i);
		void ArrumarSubindo(int i);
		inline int Direito(int i);
		inline int Esquerdo(int i);
		inline int Pai(int i);
		int mCapacidade;
		int mTamanho;
		TDado* mVetDados;
};

using namespace std;

Heap::Heap(int cap) {// IMPLEMENTADO *
	mCapacidade = cap;
	mTamanho = 0;
	mVetDados = new TDado[mCapacidade];
}

Heap::~Heap() {// IMPLEMENTADO *
	delete[]mVetDados;
}

void Heap::ArrumarDescendo(int i){// IMPLEMENTADO *
	// Arruma as posicoes de i para baixo.
	int esq = Esquerdo(i);
	int dir = Direito(i);
	int maior = i;

	float media_maior = mVetDados[i].Media();
	float media_esq = mVetDados[esq].Media();
	float media_dir = mVetDados[dir].Media();

	int tentativas_maior = mVetDados[i].Tentativas();
	int tentativas_esq = mVetDados[esq].Tentativas();
	int tentativas_dir = mVetDados[dir].Tentativas();

	if (esq < mTamanho and media_esq > media_maior){
		if(tentativas_esq < tentativas_maior){
			maior = esq;
		}
	}
	
	if (dir < mTamanho and media_dir > media_maior){
		if(tentativas_dir < tentativas_maior){
			maior = dir;
		}
	}

	if (i != maior){
		swap(mVetDados[maior], mVetDados[i]);
		ArrumarDescendo(maior);
	}
}

void Heap::ArrumarSubindo(int i) {// IMPLEMENTADO *
	// Arruma as posicoes de i para cima.
	int p = Pai(i);

	float media_i = mVetDados[i].Media();
	float media_p = mVetDados[p].Media();

	int tentativas_i = mVetDados[i].Tentativas();
	int tentativas_p = mVetDados[p].Tentativas();

	if (i != 0){
		if (media_i > media_p){
			swap(mVetDados[p], mVetDados[i]);
			ArrumarSubindo(p);
		}else if(media_i == media_p and tentativas_i < tentativas_p){
			swap(mVetDados[p], mVetDados[i]);
			ArrumarSubindo(p);
		}
	}
}

int Heap::Pai(int i) {// IMPLEMENTADO *
	return (i - 1) / 2;
}

int Heap::Esquerdo(int i) {// IMPLEMENTADO *
	return (2 * i) + 1;
}

int Heap::Direito(int i) {// IMPLEMENTADO *
	return (2 * i) + 2;
}

TDado Heap::Raiz() {
	if (mTamanho == 0) {
		cerr << "Heap vazia nao tem raiz." << endl;
		exit(EXIT_FAILURE);
	}
	// completar
	return mVetDados[0];
}

TDado Heap::Retirar() {
	if(mTamanho == 0) {
		cerr << "Impossivel retirar de heap vazia." << endl;
		exit(EXIT_FAILURE);
	}
	// completar
	TDado aux = mVetDados[0];
	swap(mVetDados[0], mVetDados[mTamanho - 1]);
	mTamanho--;
	if (mTamanho > 1){
		ArrumarDescendo(0);
	}
	return aux;
}

bool Heap::Vazia(){
	return(mTamanho == 0);
}

void Heap::Inserir(const TDado& d){// IMPLEMENTADO *
	if(mTamanho == mCapacidade) {
		cerr << "Impossivel inserir em heap cheio.\n";
		exit(EXIT_FAILURE);
	}
	// completar
	mVetDados[mTamanho] = d;
	ArrumarSubindo(mTamanho);
	mTamanho++;
}

int main() {
	unsigned qtdeAlunos;
	cin >> qtdeAlunos;
	unsigned qtdeAtividades;
	cin >> qtdeAtividades;
	Heap heap(qtdeAlunos);
	Atividade atividade;
	string nome;
	unsigned matricula;
	for (unsigned i = 0; i < qtdeAlunos; ++i) {
		cin >> matricula >> nome;
		Aluno aluno(matricula, nome);
		for (unsigned i = 0; i < qtdeAtividades; ++i) {
			cin >> atividade.nota >> atividade.tentativas;
			aluno.InserirAtividade(atividade);
		}
		heap.Inserir(aluno);
	}
	Aluno alunoDestaque(heap.Retirar());
	cout << '[' << alunoDestaque.Matricula() << "] " << alunoDestaque.Nome() << endl;
	return 0;
}
