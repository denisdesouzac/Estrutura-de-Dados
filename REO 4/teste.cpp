/* avl - Árvore Binária de Busca com Balanceamento AVL
 *
 * by Joukim, Outubro de 2019 - Estrutura de Dados (GCC216)
 * Caracteristicas de implementação outubro de 2019:
 * -> tratamento de exceção
 * -> usa pokemon na forma id/valor
 * -> uso de métodos recursivos
 * -> sem duplo encadeamento
 * -> invés de transplanta, usa removeMenor
 */

#include <iostream>
#include <stdexcept>
#include <algorithm>
using namespace std;

struct pokemon {
    unsigned id;
    string nome;
    string tipo;
    int nivel;
};

typedef unsigned tipoChave;

ostream& operator<<(ostream& saida, const pokemon& e) {
    saida << "(" << e.id << "," << e.nome << "," << e.tipo << "," << e.nivel << ")";
    return saida;
}

istream& operator>>(istream& entrada, pokemon& e) {
    entrada >> e.id >> e.nome >> e.tipo >> e.nivel;
    return entrada;
}

class noh {
    friend class avl;
    private:
        pokemon elemento;
        noh* esq;
        noh* dir;
        unsigned altura;
    public:
        noh(const pokemon& umPokemon):
            elemento(umPokemon),  esq(NULL), dir(NULL), altura(1) { }
        ~noh() { }
        int fatorBalanceamento();
};

int noh::fatorBalanceamento() {
    //#WARNING implemente
    int aux_esq,aux_dir;
	
	if(esq == NULL) aux_esq = 0;
	else aux_esq = esq->altura;
	
	if(dir == NULL) aux_dir = 0;
	else aux_dir = dir->altura;
	
	return aux_esq - aux_dir;
}

class avl {
    friend ostream& operator<<(ostream& output, avl& arvore);
    private:
        noh* raiz;
        // percorrimento em ordem da árvore
        //void percorreEmOrdemAux(noh* atual, int nivel);
        // funções auxiliares para remoção
        noh* encontraMenor(noh* raizSub);
        noh* removeMenor(noh* raizSub);
        // funções auxiliares para inserção e remoção usando método recursivo
        // retorna o nó para ajustar o pai ou o raiz
        noh* insereAux(noh* umNoh, const pokemon& umPokemon);//   *** OK ***
        noh* removeAux(noh* umNoh, tipoChave id);
        // métodos para manutenção do balanceamento
        noh* rotacaoEsquerda(noh* umNoh);//   *** OK ***
        noh* rotacaoDireita(noh* umNoh);//    *** OK ***
        noh* arrumaBalanceamento(noh* umNoh);//    *** OK ***
        // busca, método iterativo
        noh* buscaAux(tipoChave id);
        // função auxiliar do destrutor, usa percorrimento pós-ordem
        void destruirRecursivamente(noh* umNoh);
        void imprimirDir(const std::string& prefixo, const noh* meuNoh);//   *** OK ***
        void imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao);//   *** OK ***
        int levantamentoAux(noh* umNoh, string tipo, int nivel, unsigned &contador);

        unsigned informarAltura(noh* umNoh);//   *** OK ***
        void atualizaAltura(noh* umNoh);//   *** OK ***
        //noh* minimoAux(noh* raizSub);
    public:
        avl() { raiz = NULL; }
        ~avl();
        void imprimir();//   *** OK ***
        // inserção e remoção são recursivos
        void insere(const pokemon& umPokemon);//   *** OK ***
        void remove(tipoChave id);
        // inserção e remoção, métodos recursivos
        // busca retorna uma cópia do objeto armazenado
        pokemon busca(tipoChave id);
        // efetua levantamento de quantos pokemons existem de um dado tipo e nível
        int levantamento(string tipo, int nivel);
};

// destrutor
avl::~avl() {
    destruirRecursivamente(raiz);
}

// destrutor é recursivo, fazendo percorrimento pós-ordem
void avl::destruirRecursivamente(noh* umNoh) {
    //#WARNING implemente
    if(umNoh != NULL){
        destruirRecursivamente(umNoh->esq);
        destruirRecursivamente(umNoh->dir);
        delete umNoh;
    }
}

void avl::insere(const pokemon& umDado) {
    raiz = insereAux(raiz, umDado);
}

// inserção recursiva, devolve nó para atribuição de pai ou raiz
noh* avl::insereAux(noh* umNoh, const pokemon& umDado) {
    //#WARNING implemente
    if(umNoh == NULL){
		noh*novo = new noh(umDado);
		return novo;
	}else{
		// não é folha nula, checa inserção à esquerda ou direita
		if(umDado.id < umNoh->elemento.id) umNoh->esq = insereAux(umNoh->esq,umDado);
		else umNoh->dir = insereAux(umNoh->dir,umDado);
	}
	return arrumaBalanceamento(umNoh);
}

// checa e arruma, se necessário, o balanceamento em umNoh,
// fazendo as rotações e ajustes necessários
noh* avl::arrumaBalanceamento(noh* umNoh) {
    //#WARNING implemente
    if(umNoh == NULL) return umNoh;
	// Inicialmente atualiza a altura de umNoh
	atualizaAltura(umNoh);
	// Checa o balanceamento no nó
	int fatorbal = umNoh->fatorBalanceamento();
	// retorna o nó acima na árvore, caso esteja balanceado
	if((fatorbal >= -1) and (fatorbal <= 1)) return umNoh;
	// Caso o nó esteja desbalanceado, há 4 situações
	// 1. Desbalanceamento Esquerda Esquerda
	if((fatorbal > 1) and ((umNoh->esq->fatorBalanceamento()) >= 0)) return rotacaoDireita(umNoh);
	// 2. Desbalanceamento Esquerda Direita
	if((fatorbal >1) and ((umNoh->esq->fatorBalanceamento()) < 0)){
		umNoh->esq = rotacaoEsquerda(umNoh->esq);
		return rotacaoDireita(umNoh);
	}
	// Caso o nó esteja desbalanceado, há 4 situações
	// 3. Desbalanceamento Direita Direita
	if((fatorbal < -1) and ((umNoh->dir->fatorBalanceamento()) <= 0)) return rotacaoEsquerda(umNoh);
	// 4. Desbalanceamento Direita Esquerda
	if((fatorbal < -1) and ((umNoh->dir->fatorBalanceamento()) > 0)){
		umNoh->dir = rotacaoDireita(umNoh->dir);
		return rotacaoEsquerda(umNoh);
	}
	return umNoh;
}


// rotação à esquerda na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
noh* avl::rotacaoEsquerda(noh* umNoh) {
    // acha filho à direita da raiz da subárvore
    noh* nohAux;
    nohAux = umNoh->dir;

    // armazena subárvore à esquerda do nó auxiliar
    umNoh->dir = nohAux->esq;

    //posiciona um nó como filho à esquerda de nohAux
    nohAux->esq = umNoh;

    //atualiza alturas
    atualizaAltura(umNoh);
    atualizaAltura(nohAux);

    return nohAux;
}


// rotação à direita na subárvore com raiz em umNoh
// retorna o novo pai da subárvore
noh* avl::rotacaoDireita(noh* umNoh) {
    // acha filho à esquerda da raiz da subárvore
    noh* nohAux;
    nohAux = umNoh->esq;

    // armazena subárvore à esquerda do nó auxiliar
    umNoh->esq = nohAux->dir;

    //posiciona um nó como filho à direita de nohAux
    nohAux->dir = umNoh;

    //atualiza alturas
    atualizaAltura(umNoh);
    atualizaAltura(nohAux);

    return nohAux;
}


// método de busca auxiliar (retorna o nó), iterativo
noh* avl::buscaAux(tipoChave chave) {
    noh* atual = raiz;
    while(atual != NULL){
        if(atual->elemento.id == chave){
            return atual;
        }else if(atual->elemento.id > chave){
            atual = atual->esq;
        }else{
            atual = atual->dir;
        }
    }
    return atual;
}

// busca elemento com uma dada chave na árvore e retorna o registro completo
pokemon avl::busca(tipoChave chave) {
    noh* resultado = buscaAux(chave);
    if (resultado != NULL)
        return resultado->elemento;
    else
        throw runtime_error("Erro na busca: elemento não encontrado!");
}

// nó mínimo (sucessor) de subárvore com raiz em raizSub (folha mais à esquerda)
noh* avl::encontraMenor(noh* raizSub) {
    //#WARNING implemente
    /*noh* nohMenor;

    if(raizSub == NULL){
        runtime_error("Árvore vazia");
    }else{
        nohMenor = minimoAux(raizSub);
        return nohMenor;
    }
    return raizSub;*/

    if (raizSub->esq != NULL) raizSub = encontraMenor(raizSub->esq);
    return raizSub;
}

/*noh* avl::minimoAux(noh* raizSub){
    while(raizSub->esq != NULL){
        raizSub = raizSub->esq;
    }
    return raizSub;
}*/

// procedimento auxiliar para remover o sucessor substituíndo-o pelo
// seu filho à direita
noh* avl::removeMenor(noh* raizSub) {
    
    if(raizSub->esq == NULL){
        return raizSub->dir;
    }else{
        raizSub->esq = removeMenor(raizSub->esq);
        return arrumaBalanceamento(raizSub);
    }
}

// remoção recursiva
void avl::remove(tipoChave chave) {
    raiz = removeAux(raiz, chave);
}

noh* avl::removeAux(noh* umNoh, tipoChave chave) {
    //#WARNING implemente
    if(umNoh == NULL){
        throw runtime_error("Nó não encontrado");
    }

    noh* novaRaizSubArvore = umNoh;

    if(chave < umNoh->elemento.id){
        umNoh->esq = removeAux(umNoh->esq, chave);
    }else if(chave > umNoh->elemento.id){
        umNoh->dir = removeAux(umNoh->dir, chave);
    }else{
        // novaRaizSubArvore = encontraMenor(umNoh->dir);
        // novaRaizSubArvore->dir = removeMenor(umNoh->dir);
        // novaRaizSubArvore->esq = umNoh->esq;
        if(umNoh->esq == NULL){
            novaRaizSubArvore = umNoh->dir;
        }else if(umNoh->dir == NULL){
            novaRaizSubArvore = umNoh->esq;
        }
		else{// nó tem dois filhos
			// trocando pelo sucessor
			novaRaizSubArvore = encontraMenor(umNoh->dir);
			// onde antes estava o sucessor fica agora seu filho à direita
			novaRaizSubArvore->dir = removeMenor(umNoh->dir);
			// filho à esquerda de umNoh torna-se filho à esquerda de sucessor
			novaRaizSubArvore->esq = umNoh->esq;
		}
		// ponteiros ajustados, apaga o 
        delete umNoh;
    }
    return arrumaBalanceamento(novaRaizSubArvore);
}

// utiliza o nó atual e seu nível na árvore (para facilitar visualização)
/*void avl::percorreEmOrdemAux(noh* atual, int nivel) {
    if(atual != NULL){
        percorreEmOrdemAux(atual->esq, nivel++);
        //Executa ação
        percorreEmOrdemAux(atual->dir, nivel++);
    }
}*/

ostream& operator<<(ostream& output, avl& arvore) {
    arvore.imprimir();
    return output;
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirDir(const std::string& prefixo, const noh* meuNoh)
{
    if( meuNoh != nullptr )
    {
        std::cout << prefixo
                  << "└d─"
                  << "(" << meuNoh->elemento.id << "," << meuNoh->elemento.nome << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "    " , meuNoh->esq , meuNoh->dir==nullptr );
        imprimirDir( prefixo + "    " , meuNoh->dir );
    }
}

// imprime formatado seguindo o padrao tree as subarvores direitas de uma avl
void avl::imprimirEsq(const std::string& prefixo, const noh* meuNoh, bool temIrmao)
{
    if( meuNoh != nullptr )
    {
        std::cout << prefixo ;

        // A impressao da arvore esquerda depende da indicacao se existe o irmao a direita
        if (temIrmao)
            std::cout << "└e─" ;
        else
            std::cout << "├e─";

        std::cout << "(" << meuNoh->elemento.id << "," << meuNoh->elemento.nome << ")"
                  << std::endl;

        // Repassa o prefixo para manter o historico de como deve ser a formatacao e chama no filho direito e esquerdo
        imprimirEsq( prefixo + "│   " , meuNoh->esq, meuNoh->dir==nullptr );
        imprimirDir( prefixo + "│   " , meuNoh->dir );
    }
}

// imprime formatado seguindo o padrao tree uma avl
void avl::imprimir()
{
    if( this->raiz != nullptr )
    {
        std::cout << "(" << this->raiz->elemento.id << "," << this->raiz->elemento.nome << ")" << std::endl;
        // apos imprimir a raiz, chama os respectivos metodos de impressao nas subarvore esquerda e direita
        // a chamada para a impressao da subarvore esquerda depende da existencia da subarvore direita
        imprimirEsq( " " , this->raiz->esq, this->raiz->dir==nullptr );
        imprimirDir( " " , this->raiz->dir );
    } else
        std::cout << "*arvore vazia*" << std::endl;
}

unsigned avl::informarAltura(noh* umNoh){
    if(umNoh == NULL){
        return 0;
    }else{
        return umNoh->altura;
    }
}

void avl::atualizaAltura(noh* umNoh){
    int altArvEsq, altArvDir;
    
    altArvEsq = informarAltura(umNoh->esq);  
    altArvDir = informarAltura(umNoh->dir);
    umNoh->altura = 1 + max(altArvEsq, altArvDir);
    //if(altArvEsq >= altArvDir) umNoh->altura = 1 + altArvEsq;
	//else umNoh->altura = 1 + altArvDir;
}

int avl::levantamento(string tipo, int nivel){
    unsigned contador = 0;
    int levanta = levantamentoAux(this->raiz, tipo, nivel, contador);
    return levanta;
}

int avl::levantamentoAux(noh* umNoh, string tipo, int nivel, unsigned &contador){
    if(umNoh != NULL){
        levantamentoAux(umNoh->esq, tipo, nivel, contador);
        if((umNoh->elemento.tipo == tipo) and (umNoh->elemento.nivel == nivel)){
            contador ++;
        }
        levantamentoAux(umNoh->dir, tipo, nivel, contador);
    }
    return contador;
}


int main() {
    avl arvore;
    tipoChave id;
    pokemon umPokemon;
    string tipo;
    int nivel;
    int quantidade;

    char operacao;

    do {
        try {
            cin >> operacao;
            switch (operacao) {
                case 'i': // Inserir recursivamente
                    // objeto recebe id, nome, tipo e nível
                    cin >> umPokemon;
                    arvore.insere(umPokemon);
                    break;
                case 'r': // Remover recursivamente
                    cin >> id;
                    arvore.remove(id);
                    break;
                case 'b': // Buscar
                    cin >> id; // ler o id
                    umPokemon = arvore.busca(id); // escrever dados do pokemon
                    cout << "Elemento buscado: " << umPokemon << endl;
                    break;
                case 'l': // Levantamento por tipo e nível
                    cin >> tipo >> nivel;
                    quantidade = arvore.levantamento(tipo, nivel);
                    cout << "Levantamento de pokemons tipo " << tipo
                         << " e nível " << nivel << ": " << quantidade << endl;
                    break;
                case 'e': // Escrever tudo (em ordem)
                    cout << arvore;
                    break;
                case 'f': // Finalizar execução
                    break;
                default:
                    cout << "Comando invalido!\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (operacao != 'f');

    return 0;
}