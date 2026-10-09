#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int N = 100;
    double h = 1/ (double) N;
    double func;
    for(int i = 0; i < N; i++) {
        double x = h * i;

        for(int j = 0; j < N; j++) {
            double y = h * j;

            func = y * y - x * x * x;
            cout << x << '\t' << y << '\t' << func << endl;
        };
    };
    return 0;
}