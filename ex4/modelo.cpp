#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double G = 6.67e-20;               // km^3 / (kg s^2)
const double MASSA_S = 1.988e30;         // kg
const double POSICAO_INICIAL = 6.172e13; // km (2 pc)
const double VELOCIDADE_INICIAL = 0.02;  // km/s (tangential, each star)

struct Vec { double x, y; };

Vec accel(Vec r, double GM) {
    double d = sqrt(r.x * r.x + r.y * r.y);
    double f = -GM / (d * d * d);
    return { f * r.x, f * r.y };
}

int main() {
    const int n_fotos = 2000;
    const double periodo = 5.0 * 2.85e15;      // s, Kepler period for these inputs
    const double dt = periodo / n_fotos;

    double M = 2 * MASSA_S;
    double GM = G * M;

    Vec r0 = { POSICAO_INICIAL, 0 };
    Vec v0 = { 0, 2 * VELOCIDADE_INICIAL };   // relative velocity

    vector<Vec> r;
    r.push_back(r0);
    Vec a0 = accel(r0, GM);
    r.push_back({ r0.x + v0.x * dt + 0.5 * a0.x * dt * dt,
                  r0.y + v0.y * dt + 0.5 * a0.y * dt * dt });

    for (int i = 1; i < n_fotos - 1; i++) {
        Vec a = accel(r[i], GM);
        r.push_back({ 2 * r[i].x - r[i-1].x + a.x * dt * dt,
                      2 * r[i].y - r[i-1].y + a.y * dt * dt });
    }

    for (size_t i = 0; i < r.size(); i++) {
        double dist = sqrt(r[i].x * r[i].x + r[i].y * r[i].y);
        cout << 0.5 * dist << '\t' << - G * M * M / (2 * dist) << endl;         
    }
    return 0;
}