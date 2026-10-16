#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


vector<double> gerador(unsigned long long seed);

int seq = 20000;

int main() {
    unsigned long long seed1 = 15000;
    unsigned long long seed2 = 3000000;
    vector<double> theta = gerador(seed1);
    vector<double> r = gerador(seed2);

    double x;
    double y;

    for(int i = 0; i < seq; i++) {
        double raio = sqrt( 2 * r[i]);
        x = raio * cos(2 * M_PI * theta[i]);
        y = raio * sin(2 * M_PI * theta[i]);
        cout << x << '\t' << y << endl;
    }

    return 0;
}

vector<double> gerador(unsigned long long seed) {

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


