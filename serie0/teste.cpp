#include <iostream>

#define _USE_MATH_DEFINES

#include <cmath>


using namespace std;

int main() {
    for(int i = -100; i <= 100; i++) {
        double k = 3.141592653*i*0.01;
        cout << k << "\t" << sin(k) << endl;
    }
    return 0;
}