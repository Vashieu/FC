#include "meu_header.h"
#include <cmath>

std::vector<double> gerador(unsigned long long seed, int seq) {

    const unsigned long long Nmax = 2147483647ULL;
    const unsigned long long c = 16807ULL;
    int a = 0;
    std::vector<unsigned long long> x(seq);
    std::vector<double> y(seq);
    x[0] = seed;

    for(int i = 0; i < seq - 1; i++) {
        x[i + 1] = (c * x[i] + a) % Nmax;
    };


    for(int i = 0; i < seq; i++) {
        y[i] = x[i] / (double) Nmax;
    };
    return y;
}


double chi2(const std::vector<double>& y, int k) {
    double x2 = 0;
    double E = y.size() / (double) k;
    std::vector<int> N(k,0);
    for(int i = 0; i < k; i++) {
        for(int j = 0; j < y.size(); j++) {
            if ((i / (double) k) <= y[j] && y[j] < (i + 1)/(double) k) N[i]++;
        }

    }

    for(int i = 0; i < k; i++) {
        x2 += pow(N[i] - E, 2) / E;
    };

    return x2;
}

double media(const std::vector<double>& y) {
    double media = 0;
    for(int i = 0; i < y.size(); i++) {
        media += y[i] / y.size();
    };
    return media;
}