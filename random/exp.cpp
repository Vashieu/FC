#include <iostream>
#include <cmath>

using namespace std;

// void difP(double ft0);

void difS(double ft0, double fft0);

int main() {
double ft0 = 0;
double fft0 = 1;
difS(ft0, fft0);
return 0;
}

 void difP( double ft0) {
    const int N = 200;
    double h = 2 * M_PI / (double) N;
    double func[N];
    func[0] = ft0;

    for(int i = 0; i < N; i++) {
        func[i + 1] = h * func[i] + func[i];
    }

    for(int i = 0; i < N; i++) {
        cout << i << '\t' << func[i] << endl;
    }
}

void difS( double ft0, double fft0) {
    const int N = 200;
    double h = 2 * M_PI / (double) N;
    double func[N];
    func[0] = ft0;
    func[1] = ft0 + h * fft0;
    for(int i = 0; i < N - 2; i++) {
        func[i + 2] = (2 - h * h) * func[i + 1] - func[i];
    };
    
    for(int i = 0; i < N; i++) {
        cout << i * h << "\t" << func[i] << endl;
    };
}