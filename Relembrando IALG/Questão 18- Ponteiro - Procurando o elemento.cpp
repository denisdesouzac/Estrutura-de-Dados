#include <iostream>
using namespace std;

void procura_num(int **matriz, int num_busca, int *pos_linha, int *pos_coluna, int quant_linhas, int quant_colunas);

int main(){

    int quant_linhas, quant_colunas;
    cin >> quant_linhas >> quant_colunas;
    int **matriz;

    matriz = new int* [quant_linhas];
    for(int i = 0; i < quant_linhas; i++){
        matriz[i] = new int [quant_colunas];
    }

    // Estrutura que preenche a matriz.
    for(int i = 0; i < quant_linhas; i++){
        for(int j = 0; j < quant_colunas; j++){
            cin >> matriz[i][j];
        }
    }

    int pos_linha = -1;
    int pos_coluna = -1;
    int num_busca;
    cin >> num_busca;

    procura_num(matriz, num_busca, &pos_linha, &pos_coluna, quant_linhas, quant_colunas);

    if(pos_linha != -1){
        cout << pos_linha << " " << pos_coluna << endl; 
    }else{
        cout << "ausente" << endl;
    }

    for (int i = 0; i < quant_linhas; i++){
        // aqui se desalocam as colunas de cada linha
        delete[] matriz[i];
    }  

    delete[] matriz; // aqui se desalocam as linhas
    
    return 0;
}

void procura_num(int** matriz, int num_busca, int* pos_linha, int* pos_coluna, int quant_linhas, int quant_colunas){

    for(int i = 0; i < quant_linhas; i++){
        for(int j = 0; j < quant_colunas; j++){
            if(num_busca == matriz[i][j]){
                *pos_linha = i;
                *pos_coluna = j;
                quant_linhas = i;
                quant_colunas = j;
            }
        }
    }
}
