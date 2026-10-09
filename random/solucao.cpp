#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int N = 200;
double h = 2 * M_PI / (double) N;

vector<double> difX (double Xt0, double Xt1);

vector<double> difT (double Tt0);

int main() {
    double x0 = 0;
    double xx0 = 1;
    double t0 = 1;
    vector<double> X = difX(x0, xx0);
    vector<double> T = difT(t0);

    double u;
    for(int i = 0; i < N; i++) {
        double t = h * i;
        for(int j = 0; j < N; j++) {
            double x = h * j;
            u = X[j] * T[i];
            cout << x << '\t' << t << '\t' << u << endl;
        };
        cout << endl;
    };

    return 0;
}

vector<double> difX( double Xt0, double Xt1) {

    vector<double> func(N);
    func[0] = Xt0;
    func[1] = Xt0 + h * Xt1;
    for(int i = 0; i < N - 2; i++) {
        func[i + 2] = (2 - h * h) * func[i + 1] - func[i];
    };
    
    return func;
}

 vector<double> difT(double Tt0) {

    vector<double> func(N);
    func[0] = Tt0;

    for(int i = 0; i < N - 1; i++) {
        func[i + 1] = func[i] * (1 - h);
    };

    return func;
}