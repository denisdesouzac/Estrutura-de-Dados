#include <iostream>
using namespace std;

struct Hidrocarboneto{
    int C, H;
};

int calcula_massa(Hidrocarboneto ptr){
    int quantidade_carbono, quantidade_hidrogenio;
    cin >> quantidade_carbono >> quantidade_hidrogenio;

    int massa_carbono, massa_hidrogenio, massa_total;
    massa_carbono = 12 * quantidade_carbono;
    massa_hidrogenio = 1 * quantidade_hidrogenio;

    ptr.C = massa_carbono;
    ptr.H = massa_hidrogenio;

    massa_total = ptr.C + ptr.H;

    return massa_total;
}

int main(){

    int massa;

    Hidrocarboneto *ptr = NULL;
    ptr = new Hidrocarboneto;

    massa = calcula_massa(*ptr);

    cout << massa << endl;

    delete ptr;
    return 0;
}

