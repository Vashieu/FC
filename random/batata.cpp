#include <iostream>
#include <cmath>

using namespace std;

void queda (double v0, double ang, double x, double y, double x0, double y0);

struct Projetil {
    double x;
    double y;
    double v0;
    double ang;
};

int main() {
    Projetil projetil;
    projetil.x = 0;
    projetil.y= 0;
    projetil.v0 = 1;
    projetil.ang = 45.0;

    queda(projetil.v0, projetil.ang, projetil.x, projetil.y, 0.0, 5.0);
    return 0;
}


void queda(double v0, double ang, double x, double y, double x0, double y0) {
    double angulo = M_PI * ang / 180.0;
    double g = 9.8;
    double vx = cos(angulo) * v0;
    double vy = sin(angulo) * v0;
    for(int i = 0; i <= 100; i++) {
        double dt = 0.01 * i;
        x = x0 + vx * dt;
        y = y0 + vy * dt - (g/2) * dt * dt;
        cout << x << "\t" << y << endl;
        if(y < 0) break;
    }

}