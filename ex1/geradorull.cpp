#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


vector<double> gerador(unsigned long long seed, int seq);

double media(const vector<double>& y);

double chi2(const vector<double>& y, int k);


int main() {
    int seed = 4;
    int seq = 1000;
    vector<double> y = gerador(seed, seq);
    double med  = media(y);
    double x = chi2(y, 100);

    for(int i = 0; i < seq; i++) {
        cout << y[i] << endl;
    };

    cout << "- - - - - -" << endl;
    cout << "Media:" << '\t' << med << endl;
    cout << "Chi^2:" << '\t' << x << endl;
    return 0;
}

vector<double> gerador(unsigned long long seed, int seq) {

    const unsigned long long Nmax = 2147483647ULL;
    const unsigned long long c = 16807ULL;
    int a = 0;
    vector <unsigned long long> x(seq);
    vector<double> y(seq);
    x[0] = seed;

    for(int i = 0; i < seq - 1; i++) {
        x[i + 1] = (c * x[i] + a) % Nmax;
    };


    for(int i = 0; i < seq; i++) {
        y[i] = x[i] / (double) Nmax;
    };
    return y;
}


double chi2(const vector<double>& y, int k) {
    double x2 = 0;
    double E = y.size() / (double) k;
    vector<int> N(k,0);
    for(int i = 0; i < k; i++) {
        for(int j = 0; j < y.size(); j++) {
            if ((i / (double) k) <= y[j] && y[j] < (i + 1)/(double) k) N[i]++;
        }

    }

    for(int i = 0; i < k; i++) {
        x2 += pow(N[i] - E, 2) / E;
    };

    return x2;
};

double media(const vector<double>& y) {
    double media = 0;
    for(int i = 0; i < y.size(); i++) {
        media += y[i] / y.size();
    };
    return media;
}

/*
O c++ nao gosta de vetores como C usa, entao usar #include <vector> e trabalhar assim.
eh mais facil passar vetores como argumentos de funcoes, trabalhar com os indices eh igual.

*/
