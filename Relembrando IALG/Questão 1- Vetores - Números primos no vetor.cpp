#include <iostream>
using namespace std;

int main(){

    int vetor[9];
    int divisoes = 0;

    for(int i = 0; i < 9; i++){
        cin >> vetor[i];
    }

    for(int i = 0; i < 9; i++){

        if(vetor[i] % 1 == 0){
            divisoes++;
        }
        if((vetor[i] % 2 == 0) and (vetor[i] > 2)){
            divisoes++;
        }
        if((vetor[i] % 3 == 0) and (vetor[i] > 3)){
            divisoes++;
        }
        if((vetor[i] % 5 == 0) and (vetor[i] > 5)){
            divisoes++;
        }
        if((vetor[i] % 7 == 0) and (vetor[i] > 7)){
            divisoes++;
        }
        if(vetor[i] % vetor[i] == 0){
            divisoes++;
        }
        if(divisoes == 2){
            cout << vetor[i] << " " << i << "\n";
        }

        divisoes = 0;
    }

    return 0;
}