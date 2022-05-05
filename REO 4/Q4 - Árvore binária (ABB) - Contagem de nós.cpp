#include <iostream>

typedef int Dado;

using namespace std;

class Noh{
    friend class ArvoreABB;
    private:
        Noh* mPai;
        Noh* mDireito;
        Noh* mEsquerdo;
        Dado valor;
    public:
        Noh(Dado umValor);
};

Noh::Noh(Dado umValor){//Construtor
    mPai = NULL;
    mDireito = NULL;
    mEsquerdo = NULL;
    valor = umValor;
}

class ArvoreABB{

    private:
        Noh* mRaiz;

    public:
        ArvoreABB();
        ~ArvoreABB();
        void insere(Dado umValor);
        unsigned percorreDaRaiz();
        int percorreSubArvore();
        unsigned contaTamanho(Noh* atual, unsigned &contador);
        void destroi(Noh* atual);
};

ArvoreABB::ArvoreABB(){//Construtor
    mRaiz = NULL;
}

ArvoreABB::~ArvoreABB(){//Destrutor
    destroi(mRaiz);
}

void ArvoreABB::destroi(Noh* atual){
    
    if(atual != NULL){
        destroi(atual->mEsquerdo);
        destroi(atual->mDireito);
        delete atual;
    }
}

void ArvoreABB::insere(Dado umValor){

    Noh* novo = new Noh(umValor);
    if(mRaiz == NULL){
        mRaiz = novo;
    }else{

        Noh* atual = mRaiz;
        Noh* anterior = NULL;
        
        while(atual != NULL){
            anterior = atual;
            if(atual -> valor > umValor){
                atual = atual -> mEsquerdo;
            } else {
                atual = atual -> mDireito;
            }
        }

        novo -> mPai = anterior;
        if(anterior -> valor > novo -> valor){
            anterior -> mEsquerdo = novo;
        } else {
            anterior -> mDireito = novo;
        }
    }
}

unsigned ArvoreABB::percorreDaRaiz(){//Variação da "percorreEmOrdem"
    unsigned contador = 0;// Inciacializa o contador
    return contaTamanho(mRaiz, contador);// Calcula o tamanho da árvore
}

int ArvoreABB::percorreSubArvore(){//Variação da "percorreEmOrdem"
    
    unsigned subEsquerda = 0, subDireita = 0, contador;

    if(mRaiz != NULL){
        // Se a raiz tiver filho a esquerda
        if(mRaiz->mEsquerdo != NULL){
            contador = 0;// Inciacializa o contador
            subEsquerda = contaTamanho(mRaiz->mEsquerdo, contador);// Calcula o tamanho da sub-árvore
        }
        // Se a raiz tiver filho a direita
        if(mRaiz->mDireito != NULL){
            contador = 0;// Inciacializa o contador
            subDireita = contaTamanho(mRaiz->mDireito, contador);// Calcula o tamanho da sub-árvore
        }
    }

    int resultado;
    resultado = subEsquerda - subDireita;

    return resultado;
}

// Função que conta o tamanho a partir de um nó
unsigned ArvoreABB::contaTamanho(Noh* atual, unsigned &contador){//Variação da "percorreEmOrdemAux"

    if(atual != NULL){
        contaTamanho(atual->mEsquerdo, contador);
        contador ++;
        contaTamanho(atual->mDireito, contador);
    }

    return contador;
}

int main(){

    ArvoreABB goiabeira;// Criada a árvore
    Dado valor;
    cin >> valor;

    while(valor != -1){// Enquanto for diferente de -1
        goiabeira.insere(valor);// Insere o valor
        cin >> valor;
    }

    //Imprime o tamanho
    cout << goiabeira.percorreDaRaiz() << " ";
    //Imprime a diferença das sub-árvores
    cout << goiabeira.percorreSubArvore() << endl;
    
	return 0;
}
