#include <iostream>
#include <vector>

#define POSICAO_INICIAL 6.172e13
#define VELOCIDADE_INICIAL 0.02
#define MASSA_S 1.988e30

using namespace std;

// Variaveis globais

    struct Estrela {
        double posicao;
        double velocidade;
        double massa;
    };

    const double G = 6.67e-20; //   km³/kgs²

// funcoes

vector<double> atualizacao_posicao(Estrela &obj1, Estrela &obj2, double dt, double M, int n_fotos);

// main

int main() {

    const int n_fotos = 100;
    const double periodo_orbital = 2.85e15;
    double dt = periodo_orbital / (double) n_fotos;


    Estrela Sirius;

    Sirius.massa = MASSA_S;
    Sirius.posicao = POSICAO_INICIAL;
    Sirius.velocidade = VELOCIDADE_INICIAL;

    Estrela Steven;

    Steven.massa = MASSA_S;
    Steven.posicao = 0;
    Steven.velocidade = - VELOCIDADE_INICIAL;

    // reducao ao problema dum corpo
    double M = Sirius.massa + Steven.massa;
    double u = Sirius.massa * Steven.massa / M;

    vector<double> coord = atualizacao_posicao(Sirius, Steven, dt, M, n_fotos);

    for(size_t i = 0; i < coord.size(); i++) cout << coord[i] << endl;



    return 0;
}

vector<double> atualizacao_posicao(Estrela &obj1, Estrela &obj2, double dt, double M, int n_fotos) {
    vector<double> r;
    double dt2 = dt * dt;

    r.push_back(obj1.posicao - obj2.posicao);
    r.push_back(r[0] + dt * (obj1.velocidade - obj2.velocidade) - 0.5 * G * M * dt2 / (r[0]*r[0]));
    
    for(int i = 1; i < n_fotos - 1; i++)
        r.push_back(2 * r[i] - r[i - 1]  - G * M * dt2/ (r[i]*r[i]));

    return r;
}