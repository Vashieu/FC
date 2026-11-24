#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;

const double G = 6.67e-20;               // km^3 / (kg s^2)
const double MASSA_S = 1.988e30;         // kg
const double POSICAO_INICIAL = 6.172e13; // km (2 pc)
const double VELOCIDADE_INICIAL = 0.02;  // km/s 

struct vec{
    double x;
    double y;
};


vec accel(vec r, double GM) {
    double d = sqrt(r.x * r.x + r.y * r.y);
    double f = -GM / (d * d * d);
    return { f * r.x, f * r.y };
}

int main() {
    const int n_fotos = 10000;
    const double periodo =  5 * 2.85e15;  
    const double dt = periodo / n_fotos;
    const double GM = 2 * G * MASSA_S;

    // Condicoes iniciais
    vec r0 = {POSICAO_INICIAL, 0};
    vec v0 = {0, 2 * VELOCIDADE_INICIAL};
    vec a0 = accel(r0, GM);
    vec r1 = {r0.x + v0.x * dt + 0.5 * a0.x * dt * dt, r0.y + v0.y * dt + 0.5 * a0.y * dt * dt};

    vector<vec> posicao;
    posicao.push_back(r0);
    posicao.push_back(r1);


    for(int i = 1; i < n_fotos - 1; i++) {
        vec a = accel(posicao[i], GM);
        vec r_atual = {2 * posicao[i].x - posicao[i - 1].x + a.x * dt * dt, 2 * posicao[i].y - posicao[i - 1].y + a.y * dt * dt};
        posicao.push_back(r_atual);
    }

    ofstream file("Energia.dat");
    
    vec v = v0;
    for(size_t i = 0; i < posicao.size(); i++) {

        double t = i * dt;
        double dist = sqrt(posicao[i].x * posicao[i].x + posicao[i].y * posicao[i].y);

        double V = - G * MASSA_S * MASSA_S / dist;
        double T = 0.25 * MASSA_S * (v.x * v.x + v.y * v.y);
        double E = T + V;

        file << t << '\t' << dist << '\t'<< V << '\n'
         << t << '\t' << dist << '\t' << T << '\n'
         << t << '\t' << dist << '\t' << E << '\n';

        if(i < posicao.size() - 2)
        v = {(posicao[i + 2].x - posicao[i].x)/(2*dt), (posicao[i + 2].y - posicao[i].y)/(2*dt)};
        //v_(i+1) = x_(i + 2) - x_(i) / 2dt
    } 
    file.close();

    return 0;
}

