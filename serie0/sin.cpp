#include <iostream>
#include <math.h>

using namespace std;

int main() {
    for(int i = -100; i <= 100; i++) {
        double k = i * M_PI * 0.01;
        cout << k << "\t" << sin(k) << endl; 
    }
    return 0;
}