#include <iostream>
using namespace std;

class Aviao{

    private:

    public:

    int vel = 0;
    int velMax;
    string tipo;
    void ini(int tp);
};

void Aviao::ini(int tp){

    if(tp == 1){
        this->velMax = 800;
        this->tipo = "Jato";
    }else if(tp == 2){
        this->velMax = 350;
        this->tipo = "Monomotor";
    }else if(tp == 3){
        this->velMax = 180;
        this->tipo = "Planador";
    }

}


int main(){

    int numero;

    cout << "Insira um numero de 1 a 3 :" << endl;
    cin >> numero;

    Aviao *av1 = new Aviao();
    av1->ini(numero);

    cout << "Tipo: " << av1->tipo << endl;
    cout << "Velocidade: " << av1->velMax << endl;

    return 0;
}