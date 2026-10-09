#include <iostream>
#include <cmath>

using namespace std;

void aleatorio(int seed);

int main() {
    int seed = 9;
    aleatorio(seed);
    return 0;
}

void aleatorio(int seed) {
    int Nmax = 13;
    int c = 16807;
    int a;
    double y;
    if      (Nmax % 2 != 0) a = 2;
    else if (Nmax % 3 != 0) a = 3;
    else if (Nmax % 5 != 0) a = 5;
    else if (Nmax % 7 != 0) a = 7;
    else a = 1;  

    int numx[20];
    numx[0] = seed;

    int numy[20];
    numy[0] = floor(seed / (float) Nmax);

    for(int i = 0; i < 20; i++) {
        numx[i + 1] = (c * numx[i] + a) % Nmax;
        y = numx[i + 1] / (double) Nmax;
        numy[i + 1] = floor(y);
        cout << numx[i] << ' ';
    }
}