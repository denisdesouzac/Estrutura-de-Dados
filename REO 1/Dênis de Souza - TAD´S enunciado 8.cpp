/*
Aluno: Dênis de Souza Cordeiro
Matricula: 202110235
----------------------- Enunciado 8 ---------------------

Obs: 
1 - Na função de busca(procurar_musica) além de procurar
a música de determinado estilo, o programa também retorna
as bandas e artistas do mesmo estilo.

2 - O procedimento "menu_resposta" foi inserido apenas para
interação com o usuário.

3 - Como as classes "documento" e "banda" não possuem compor-
tamento, foram implementadas como struct senguindo o exemplo.
*/
#include <iostream>
using namespace std;

struct documento{
    string nome_musica;
    string nome_compositor;
    string estilo;
    string tipo; // partitura, tablatura ou cifra
};

struct banda{
    string nome_banda_artista;
    string instrumento;
    string estilo;
};

class instrumentista{

private:
    documento *lista_musicas;
    banda *lista_bandas;
    int quantidade_musicas;
    int quantidade_bandas;

public:
    instrumentista(int qtd_musicas, int qtd_bandas);
    ~instrumentista();
    void cadastrar_musica();
    void cadastrar_banda();
    void procurar_musica(string estilo_requerido);
};

// Cria os vetores
instrumentista::instrumentista(int qtd_musicas, int qtd_bandas){
    quantidade_bandas = qtd_bandas;
    quantidade_musicas = qtd_musicas;
    lista_musicas = new documento[quantidade_musicas];
    lista_bandas = new banda[quantidade_bandas];
}

instrumentista::~instrumentista(){
    delete[]lista_musicas;
    delete[]lista_bandas;
}

// Cadastra as músicas
void instrumentista::cadastrar_musica(){

    for(int i = 0; i < quantidade_musicas; i++){

        cout << "--------- CADASTRO DE MUSICAS ---------" << "\n" << "\n";
        
        cout << "Digite o nome da musica" << "\n";
        cin.ignore();
        getline(cin, lista_musicas[i].nome_musica);

        cout << "Digite o nome do compositor" << "\n";// Apenas primeiro nome
        cin >>  lista_musicas[i].nome_compositor;

        cout << "Digite o estilo da musica?" << "\n";
        cin >> lista_musicas[i].estilo;

        cout << "Digite o tipo desse documento musical" << "\n";
        cin >>  lista_musicas[i].tipo;

        cout  << "\n" << "Cadastrado com sucesso!" << "\n" << "\n";
    }
}

// Cadastra as bandas
void instrumentista::cadastrar_banda(){

    for(int i = 0; i < quantidade_bandas; i++){

        cout << "--------- CADASTRO DE BANDAS E ARTISTAS ---------" << "\n" << "\n";

        cout << "Digite o nome da banda ou artista" << "\n";
        cin.ignore();
        getline(cin, lista_bandas[i].nome_banda_artista);

        cout << "Digite o nome do instrumento utilizado" << "\n";
        cin >> lista_bandas[i].instrumento;

        cout << "Digite o estilo da banda/artista" << "\n";
        cin >> lista_bandas[i].estilo;

        cout << "\n" << "Cadastrado com sucesso!" << "\n" << "\n";
    }
}

// Procura a música pelo estilo
void instrumentista::procurar_musica(string estilo_requerido){

    for(int i  = 0; i < quantidade_musicas; i++){
        if(lista_musicas[i].estilo == estilo_requerido){
            cout << "\n" <<"Nome da musica: " << lista_musicas[i].nome_musica << "\n";
            cout << "Nome do compositor: " << lista_musicas[i].nome_compositor << "\n";
            cout << "Estilo: " << lista_musicas[i].estilo << "\n";
            cout << "Tipo: " << lista_musicas[i].tipo << "\n" << "\n";
        }
    }

    cout << "Bandas relacionadas:" << "\n" << "\n";

    for(int i  = 0; i < quantidade_musicas; i++){
        if(lista_bandas[i].estilo == estilo_requerido){
            cout << "Nome da banda/artista: " << lista_bandas[i].nome_banda_artista << "\n";
            cout << "Nome do instrumento: " << lista_bandas[i].instrumento << "\n";
            cout << "Estilo: " << lista_bandas[i].estilo << "\n" << "\n";
        }
    }
}

void menu_resposta(){
    cout << "1-Sim" << "\n";
    cout << "2-Nao" << "\n";
}

int main(){

    int qtd_musicas, qtd_bandas;
    cout << "Quantas musicas voce quer cadastrar?" << "\n";
    cin >> qtd_musicas;
    cout << "Quantas bandas ou artistas voce quer cadastrar?" << "\n";
    cin >> qtd_bandas;

    instrumentista *ponteiro = new instrumentista(qtd_musicas, qtd_bandas);

    ponteiro->cadastrar_musica();
    ponteiro->cadastrar_banda();

    string estilo_requerido;
    int resposta;

    cout << "Voce deseja procurar alguma musica ?" << "\n";
    menu_resposta();
    cin >> resposta;

    if(resposta ==  1){
        cout << "\n" << "As musicas de qual estilo voce procura?" << "\n";
        cin >>  estilo_requerido;
        ponteiro->procurar_musica(estilo_requerido);
    }else if(resposta == 2){
        cout << "\n" << "Terminado" << "\n";
    }

    ponteiro->~instrumentista();

    return 0;
}