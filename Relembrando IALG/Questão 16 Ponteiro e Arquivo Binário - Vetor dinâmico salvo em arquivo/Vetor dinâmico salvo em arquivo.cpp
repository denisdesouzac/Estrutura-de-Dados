#include <iostream>
#include <fstream>
using namespace std;

void redimensionarCapacidade(int &capacidadeMaxima, int vetor[]){
	
	cout << endl;

	int *vetorAux = new int[capacidadeMaxima];;
	for(int i = 0; i < capacidadeMaxima; i++){
		vetorAux[i] = vetor[i];
	}
	
	for(int i = 0; i < capacidadeMaxima; i++){
		cout << vetorAux[i] << " ";
	}
	
	cout << endl;

	delete[]vetor;

	int capacidadeMaximaAntiga = capacidadeMaxima;
	capacidadeMaxima = capacidadeMaxima + 5;
	vetor = new int[capacidadeMaxima];

	for(int i = 0; i < capacidadeMaximaAntiga; i++){
		vetor[i] = vetorAux[i];
	}
	
	for(int i = 0; i < capacidadeMaximaAntiga; i++){
		cout << vetor[i] << " ";
	}
	
	cout << endl;
	
	delete[]vetorAux;
}


int main(){
	
	int capacidadeMaxima = 5;
	int *vetor = new int[capacidadeMaxima];
	
	ifstream arquivo;
	arquivo.open("dados.bin");

	int numero = 1;
	int contador = 0, cont_alocacao = 0;

	while(numero > 0){

		if(capacidadeMaxima == contador){
			redimensionarCapacidade(capacidadeMaxima, vetor);
			cont_alocacao++;
		}
		arquivo.read((char *)(&numero), sizeof(int));
		
		if(numero != 0){
			vetor[contador] = numero;
		}
		
		contador++;
		if(numero <= 0){
			contador--;
		}
	}
	
	for(int i = 0; i < contador; i++){
		cout << vetor[i] << " ";
	}

	int num_inserido;
	cin >> num_inserido;

	while(num_inserido > 0){

		if (capacidadeMaxima == contador){
			redimensionarCapacidade(capacidadeMaxima, vetor);
			cont_alocacao++;
		}
		vetor[contador] = num_inserido;
		contador++;
		cin >> num_inserido;
	}
	
	

	arquivo.close();

	ofstream saida;// Imprensão de dados e finalização
	saida.open("dados.bin");
	
	
	for(int i = 0; i < contador; i++){
		saida.write((const char *) &vetor[i], sizeof(int));
	}
	
	for(int i = 0; i < contador; i++){
		cout << vetor[i] << " ";
	}

	cout << endl << capacidadeMaxima << endl;
	cout << cont_alocacao << endl;

	saida.close();
	delete[]vetor;

	return 0;
}
