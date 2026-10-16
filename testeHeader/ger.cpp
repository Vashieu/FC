#include "meu_header.h"
#include <iostream>

using namespace std;

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