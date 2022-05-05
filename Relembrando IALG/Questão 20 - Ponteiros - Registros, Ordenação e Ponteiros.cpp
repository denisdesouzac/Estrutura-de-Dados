#include <iostream>
using namespace std;

struct alunos{
    string nome;
    float media;
    int faltas;
};

void bubble_sort(alunos vetor[], int tam) {
    alunos aux_troca;
    for (int i = 0; i < tam-1; i++) {
        for (int j = 0; j < tam-1-i; j++) {
            if (vetor[j].media < vetor[j+1].media) {
                aux_troca = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = aux_troca;
            }
        }
    }
}


void imprime(alunos vetor[], int tam){
    for(int i = 0; i < tam; i++){
        cout << vetor[i].nome << "\n";
    }
}


int main(){

    int quantidade_estudantes;
    cin >> quantidade_estudantes;

    alunos *ptr = new alunos[quantidade_estudantes];

    for(int i = 0; i < quantidade_estudantes; i++){
        cin >> ptr[i].nome;
        cin >> ptr[i].media;
        cin >> ptr[i].faltas;
    }

    bubble_sort(ptr, quantidade_estudantes);
    imprime(ptr, quantidade_estudantes);

    delete[]ptr;

    return 0;
}