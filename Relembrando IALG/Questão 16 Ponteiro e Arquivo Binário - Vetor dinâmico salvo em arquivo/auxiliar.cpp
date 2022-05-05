#include <iostream>
#include <fstream>
using namespace std;


int main(){
	
	ofstream entrada;
	entrada.open("dados.bin");
	
	int num;
	
	for(int i = 0; i < 7; i++){
		cin >> num;
		entrada.write((const char *) &num, sizeof(int));
	}
	
	entrada.close();

	return 0;
}

