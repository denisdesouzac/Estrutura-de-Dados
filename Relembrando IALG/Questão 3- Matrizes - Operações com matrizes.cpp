#include <iostream>
using namespace std;

void preenche_matriz(int matriz[10][10]);
void copia_matriz(int matriz[10][10], int matriz1[10][10]);
void troca1(int matriz[10][10], int matriz1[10][10]);
void troca2(int matriz[10][10], int matriz2[10][10]);
void troca3(int matriz[10][10], int matriz3[10][10]);
void troca4(int matriz[10][10], int matriz4[10][10]);

int main(){

    int matriz_modelo[10][10];
    preenche_matriz(matriz_modelo);

    int matriz1[10][10];
    copia_matriz(matriz_modelo, matriz1);
    troca1(matriz_modelo, matriz1);

    int matriz2[10][10];
    copia_matriz(matriz_modelo, matriz2);
    troca2(matriz_modelo, matriz2);

    int matriz3[10][10];
    copia_matriz(matriz_modelo, matriz3);
    troca3(matriz_modelo, matriz3);

    int matriz4[10][10];
    copia_matriz(matriz_modelo, matriz4);
    troca4(matriz_modelo, matriz4);

    return 0;
}

void preenche_matriz(int matriz[10][10]){

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            cin >> matriz[i][j];
        }
    }
}

void copia_matriz(int matriz[10][10], int matriz1[10][10]){

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            matriz1[i][j] = matriz[i][j];
        }
    }
}

void troca1(int matriz[10][10], int matriz1[10][10]){

    for(int j = 0; j < 10; j++){
        matriz1[1][j] = matriz[7][j];
    }

    for(int j = 0; j < 10; j++){
        matriz1[7][j] = matriz[1][j];
    }

    cout << "1." << endl;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            cout << matriz1[i][j] << " ";
        }
        cout << endl;
    }
}

void troca2(int matriz[10][10], int matriz2[10][10]){

    for(int i = 0; i < 10; i++){
        matriz2[i][3] = matriz[i][9];
    }

    for(int i = 0; i < 10; i++){
        matriz2[i][9] = matriz[i][3];
    }    

    cout << "2." << endl;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            cout << matriz2[i][j] << " ";
        }
        cout << endl;
    }
}

void troca3(int matriz[10][10], int matriz3[10][10]){

    int i = 0, j = 9;
    while(i < 10){
        matriz3[i][i] = matriz[i][j];
        j--;
        i++;
    }

    i = 0, j = 9;
    while(i < 10){
        matriz3[i][j] = matriz[i][i];
        j--;
        i++;
    }

    cout << "3." << endl;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            cout << matriz3[i][j] << " ";
        }
        cout << endl;
    }
}

void troca4(int matriz[10][10], int matriz4[10][10]){

    for(int j = 0; j < 10; j++){
        matriz4[4][j] = matriz[j][9];
    }

    for(int j = 0; j < 10; j++){
        matriz4[j][9] = matriz[4][j];
    }

    cout << "4." << endl;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            cout << matriz4[i][j] << " ";
        }
        cout << endl;
    }
}