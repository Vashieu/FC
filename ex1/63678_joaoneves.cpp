#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

// declaracao das funcoes

vector<double> gerador(unsigned long long seed, unsigned long long Nmax, unsigned long long c, unsigned long long a, int tamanho);

void testequadrado(const vector<double>& y);

void testecubo(const vector<double>& y);

void circulo(unsigned long long seed, unsigned long long Nmax, unsigned long long c, unsigned long long a, int tamanho, double raio);

double chi2(const vector<double>& y, int k);

// main

int main() {
    int k = 100; // numero de sub-intervalos para X^2
    unsigned long long seed;
    double raio;
    int a;
    unsigned long long c;
    unsigned long long Nmax;
    int tamanho;

    cout << "Escolha nesta ordem: seed -> Nmax -> Multiplicador -> offset -> n de numeros gerados:" << endl;
    cin >> seed;
    cin >> Nmax;
    cin >> c;
    cin >> a;
    cin >> tamanho;

    srand((unsigned) seed);
    srand48((long) seed);

    vector<double> vetor1 = gerador(seed, Nmax, c, a, tamanho);
    double chi_1 = chi2(vetor1, k);

    for(int i = 0; i < tamanho; i++) {
        cout << vetor1[i] << endl;
    }
    cout << "- - - - - -" << endl;
    cout << "Chi^2 = " << chi_1 << endl;

    testequadrado(vetor1);
    
    testecubo(vetor1);

    // circulo
    cout << "Parametros para gerar um circulo na seguinte ordem:" << endl;
    cout << "seed -> Nmax -> Multiplicador -> offset -> n de numeros gerados - > raio:" << endl;
    cin >> seed;
    cin >> Nmax;
    cin >> c;
    cin >> a;
    cin >> tamanho;
    cin >> raio;

    circulo(seed, Nmax, c, a, tamanho, raio);

    return 0;
}

// implementacao das funcoes

vector<double> gerador(unsigned long long seed, unsigned long long Nmax, unsigned long long c, unsigned long long a, int tamanho) {
    if(seed == 0 && a == 0) seed = 10000; //Usei 10000 como uma seed "default"
    seed = seed % Nmax;
    vector<double> y(tamanho);
    unsigned long long x = seed;


    for(int i = 0; i < tamanho; i++) {
        y[i] = x / (double) Nmax;
        x = (c * x + a) % Nmax;

    };
    return y;
    // A funcao recebe os parametros para o gerador linear X_(n + 1) = (cX_n + a) mod Nmax
    // c - Multiplicador, a - offset, X_0 - seed, Nmax - Numero que indica valores possiveis de 0 a Nmax - 1
}

void circulo(unsigned long long seed, unsigned long long Nmax, unsigned long long c, unsigned long long a, int tamanho, double raio) {
    
    vector<double> circulo = gerador(seed, Nmax, c, a, tamanho);
    double r;
    double angulo;
    double x,y;

    ofstream outfile ("circulo.dat");

    for(int i = 0; i < tamanho - 1; i += 2) {
        r = raio * sqrt(circulo[i]);
        angulo = 2 * M_PI * circulo[i + 1];
        x = r * cos(angulo);
        y = r * sin(angulo);
        outfile << x << '\t' << y << endl;
    }
    outfile.close();
}

void testequadrado(const vector<double>& y) {
        ofstream outfile0("meu_gerador_quadrado.dat");
        for(int i = 0; i < y.size() - 1; i += 2) {
            outfile0 << y[i] << '\t' << y[i + 1] << endl;
        }
        outfile0.close();

        // funcao rand para geracao de pontos
        ofstream outfile1("rand_quadrado.dat");
        
        for(int i = 0; i < y.size() - 1; i += 2) {
            double x1 = rand() / (double) RAND_MAX;
            double y1 = rand() / (double) RAND_MAX;
            outfile1 << x1 << '\t' << y1 << endl;
        }
        outfile1.close();

        //funcao drand48 para geracao de pontos
        ofstream outfile2("drand48_quadrado.dat");
        
        for(int i = 0; i < y.size() - 1; i += 2) {
            double x2 = drand48();
            double y2 = drand48();
            outfile2 << x2 << '\t' << y2 << endl;
        }
        outfile2.close();
}

void testecubo(const vector<double>& y) {
        ofstream outfile0("meu_gerador_cubo.dat");
        for(int i = 0; i < y.size() - 2; i += 3) {
            outfile0 << y[i] << '\t' << y[i + 1] << '\t' << y[i + 2] << endl;
        }
        outfile0.close();

        // funcao rand para geracao de pontos

        ofstream outfile1("rand_cubo.dat");
        
        for(int i = 0; i < y.size() - 2; i += 3) {
            double x1 = rand() / (double) RAND_MAX;
            double y1 = rand() / (double) RAND_MAX;
            double z1 = rand() / (double) RAND_MAX;
            outfile1 << x1 << '\t' << y1 << '\t' << z1 << endl;
        }
        outfile1.close();

        // funcao drand48 para geracao de pontos

        ofstream outfile2("drand48_cubo.dat");
        
        for(int i = 0; i < y.size() - 1; i += 2) {
            double x2 = drand48();
            double y2 = drand48();
            double z2 = drand48();

            outfile2 << x2 << '\t' << y2 << '\t' << z2 << endl;
        }
        outfile2.close();
}

double chi2(const vector<double>& y, int k) {
    double X2 = 0;
    double E = y.size() / (double) k;
    vector<int> N(k,0);
    for(int i = 0; i < k; i++) {
        for(int j = 0; j < y.size(); j++) {
            if ((i / (double) k) <= y[j] && y[j] < (i + 1)/(double) k) N[i]++;
        }

    }

    for(int i = 0; i < k; i++) {
        X2 += pow(N[i] - E, 2) / E;
    };

    return X2;
}