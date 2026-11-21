#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string.h>

using namespace std;

void funcao_intensidade(const vector<double>& x, const vector<double>& espaco, double I_0, int nFotoes, int n_divisoes_espaco, bool flag_metade);


int main() {
    // variaveis globais
    const int n_divisoes_espaco = 1000; // alterar a particao do intervalo para que a cada iteracao ocorra um processo de scattering
    int nFotoes = 100000;
    bool flag_metade = false;
    vector<double> x(nFotoes);
    vector<double> espaco(n_divisoes_espaco);
    vector<double> probabilidades;
    string dados;
    double N_total = 0.0;
    double N_atual;

    // variaveis e constantes problema 3.1
    
    double u_R = 6.09;
    double u_C = 3.83 * pow(10,-2);
    double u_F = 3.19 * pow(10,3);

    double u = u_F + u_R + u_C;
    double lambda = (double) 1 / u;

    double I_0 = 1;  

    for(int i = 0; i < n_divisoes_espaco; i++) espaco[i] = 5 * pow(10,-4) * (double) i / n_divisoes_espaco;
    for(int i = 0; i < nFotoes; i++) x[i] = -lambda * log(1 - drand48()); //salvaguardar drand = 0 sabendo que Y ~ U(0,1) entao 1 - Y ~ U(0,1)

    sort(x.begin(), x.end());

    funcao_intensidade(x, espaco, I_0, nFotoes, n_divisoes_espaco, flag_metade); 

    return 0;
}

void funcao_intensidade(const vector<double>& x, const vector<double>& espaco, double I_0, int nFotoes, int n_divisoes_espaco, bool flag_metade) {
        ofstream ficheiro("grafico.dat");

    for(int i = 0; i < n_divisoes_espaco; i++) {
        auto k = upper_bound(x.begin(), x.end(), espaco[i]) - x.begin();
        double I = I_0 * (nFotoes - k) / (double) nFotoes;
        if(I <= I_0 / 2 && flag_metade == false) {
            cout << "A intensidade atinge a flag_metade em: x = " << espaco[i] << endl;
            flag_metade = true;
        }
        ficheiro << espaco[i] << '\t' << I / I_0 << endl;
    }
    ficheiro.close();
}