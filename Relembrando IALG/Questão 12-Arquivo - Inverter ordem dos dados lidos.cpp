#include <iostream>
#include <fstream>
using namespace std;

int main(){

    fstream entrada;
    entrada.open("entrada.txt", ios::in);
    int vetor[100];

    int i = 0;
    while(entrada >> vetor[i]){
        i++;
    }

    fstream saida;
    saida.open("saida.txt", ios::out);

    for(int j = i-1 ; j >= 0; j--){
        saida << vetor[j] << " ";
    }

    entrada.close();
    saida.close();
    
    return 0;
}
