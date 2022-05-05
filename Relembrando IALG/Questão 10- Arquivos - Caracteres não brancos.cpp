#include <iostream>
#include <fstream>
using namespace std;

int main(){

    fstream entrada;
    entrada.open("Meu_Arquivo.txt", ios::in);

    char letras;// Char que armazena as letras do arquivo
    int sem_espaco = 0;

    while(entrada >> letras){
        if(letras != ' '){
            sem_espaco++;
        }
    }
    
    entrada.close();// Fecha arquivo

    cout << sem_espaco;
    return 0;
}