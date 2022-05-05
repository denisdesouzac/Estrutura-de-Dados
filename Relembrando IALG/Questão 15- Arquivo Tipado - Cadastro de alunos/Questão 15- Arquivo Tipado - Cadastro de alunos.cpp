#include <iostream>
#include <fstream>
using namespace std;

struct aluno{
    string nome;
    int matricula;
    float nota;
};

// Função que irá fazer a busca binária.
int busca(aluno &dados, int pos_final, int num_buscado, int num_troca){

    int pos_inicial = 0;
	
	while(pos_inicial <= pos_final){
		
		int meio = (pos_inicial + pos_final) / 2;

		if(num_buscado == dados.matricula){
			dados.matricula = num_troca;
			pos_inicial = pos_final + 1;
		}else{
			if(num_buscado > dados.matricula){
				pos_inicial = meio + 1;
			}else{
				pos_final = meio - 1;
			}
		}
	}
	return 0;
}

int main(){

    int quantidade_alunos;
    cin >> quantidade_alunos;

    aluno dados;

    ofstream entrada;
    entrada.open("alunos.bin", ios::out | ios::trunc | ios::binary);

    entrada.write((const char *) (&quantidade_alunos), sizeof(int));

    for(int i = 0; i < quantidade_alunos; i++){

        cin >> dados.nome >> dados.matricula >> dados.nota;// Entrada das informações do aluno.

        entrada.write((const char *) (&dados), sizeof(aluno));// Informações sendo gravadas no arquivo.
    }

    int matricula_busca, matricula_troca;
    cin >> matricula_busca >> matricula_troca;

    busca(dados, quantidade_alunos, matricula_busca, matricula_troca);

    entrada.write((const char *) (&dados.matricula), sizeof(aluno));

    cout << dados.matricula << endl;

    entrada.close();
    
    return 0;
}