#include <iostream>
using namespace std;

int main(){

    int num_linhas, num_colunas;

    cin >> num_linhas >> num_colunas;

    int matriz[num_linhas][num_colunas];

    for(int i = 0; i < num_linhas; i++){
        for(int j = 0; j < num_colunas; j++){
            cin >> matriz[i][j];
        }
    }

    for(int j = 0; j < num_colunas; j++){
        for(int i = 0; i < num_linhas; i++){
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}