#include <iostream>
#include <fstream>
using namespace std;

int main(){

    fstream entrada;
    entrada.open("entrada.txt", ios::in);
    
    int tamanho;
    entrada >> tamanho;
    int vetor[tamanho];
    int cont = 0, num, i = 1;

    while(i <= tamanho){
		
		entrada >> num;
		
		for(int j = i - 1; j >= 0; j--){
			
			if(num == vetor[j]){// A cada número igual já colocado no vetor...
				cont ++;// Contador aumenta 1.
			}
		}
		if(cont == 0){// Se o contador estiver em 0...
			vetor[i-1] = num;// O número comparado é colocado no vetor.
			i++;
		}else{// Caso contrário
			tamanho--;// Diminui 1 na quantidade.
		}
		cont = 0;// Zera contador.
	}
	
    fstream saida;
    saida.open("saida.txt", ios::out);

    for(i = 0; i < tamanho; i++){
        saida << vetor[i] << " ";
    }

    entrada.close();
    saida.close();
    
    return 0;
}