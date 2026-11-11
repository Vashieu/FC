#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

void funcao_intensidade(const vector<double>& x, const vector<double>& espaco, double I_0, int nFotoes, int N, bool metade);

int main() {
    // variaveis e constantes
    const int N = 1000;
    int nFotoes = 100000;
    double u_R = 6.09;
    double u_C = 3.83 * pow(10,-2);
    double u_F = 3.19 * pow(10,3);

    double u = u_F + u_R + u_C;
    double lambda = (double) 1 / u;

    double p_R = u_R / u;
    double p_C = u_C / u;
    double p_F = u_F / u;

    double I_0 = 1;
    bool metade = false;

    vector<double> x(nFotoes);
    vector<double> espaco(N);
    //implementacao

    for(int i = 0; i < N; i++) espaco[i] = 5 * pow(10,-4) * (double) i / N;
    for(int i = 0; i < nFotoes; i++) x[i] = -lambda * log(1 - drand48()); //salvaguardar drand = 0 sabendo que Y ~ U(0,1) entao 1 - Y ~ U(0,1)

    sort(x.begin(), x.end());

    funcao_intensidade(x, espaco, I_0, nFotoes, N, metade);

    return 0;
}

void funcao_intensidade(const vector<double>& x, const vector<double>& espaco, double I_0, int nFotoes, int N, bool metade) {
        ofstream ficheiro("grafico.dat");

    for(int i = 0; i < N; i++) {
        auto k = upper_bound(x.begin(), x.end(), espaco[i]) - x.begin();
        double I = I_0 * (nFotoes - k) / (double) nFotoes;
        if(I <= I_0 / 2 && metade == false) {
            cout << "A intensidade atinge a metade em: x = " << espaco[i] << endl;
            metade = true;
        }
        ficheiro << espaco[i] << '\t' << I / I_0 << endl;
    }
    ficheiro.close();
}