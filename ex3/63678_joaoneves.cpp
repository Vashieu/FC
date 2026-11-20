#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using namespace std;

void funcao_intensidade(const vector<double>& cumulativa, const vector<double>& espaco, const vector<string>& linhas, double rho_Al, double I_0, size_t nFotoes, size_t n_divisoes_espaco);
double somar_linha(const string& line, int saltar_indice, int contador_atenuadores);
vector<string> ler_linhas(const string& caminho);
double calcular_mu(const vector<double>& cumulativa, const vector<string>& linhas);
void reamostrar_1keV(vector<double>& energias_kev, vector<double>& N);


int main(int argc, char *argv[]) {

    if (argc < 2) {
        cout << "Usar: " << argv[0] << " 110kV.spec ou claude_espectro.spec" << endl;
        return 1;
    }

    string caminho_spec = argv[1];

    srand48(time(NULL)); //comentar ou remover esta linha para reprodutibilidade dos resultados
    // variaveis globais
    const size_t n_divisoes_espaco = 1000;   
    const size_t nFotoes = 100000;         
    const double x_max = 3.0;  
    double I_0 = 1.0;
    double rho_Al = 2.70;             

    vector<double> espaco(n_divisoes_espaco);
    vector<double> energias_kev;
    vector<double> probabilidades;
    double N_total = 0.0;

    // ----- Exercicio 3.2 e 3.3 ----- //

    ifstream energias(caminho_spec);
    if (!energias) throw runtime_error("Erro ao abrir 110kV.spec");

    string dados;
    // saltar o cabecalho
    while (getline(energias, dados))
        if (dados.find("Energy[keV]") != string::npos) break;

    // ler as linhas energias e N de fotoes para cada uma
    while (getline(energias, dados)) {
        istringstream iss(dados);
        double E, N;
        if (!(iss >> E >> N)) continue;   // ignora linhas vazias
        energias_kev.push_back(E);
        probabilidades.push_back(N);
    }
    
    energias.close();

    reamostrar_1keV(energias_kev, probabilidades);
    N_total = accumulate(probabilidades.begin(), probabilidades.end(), 0.0);


    for (double& p : probabilidades) p /= N_total;

    vector<double> cumulativa(probabilidades.size());
    partial_sum(probabilidades.begin(), probabilidades.end(), cumulativa.begin());

    for (size_t i = 0; i < n_divisoes_espaco; i++) espaco[i] = x_max * i / (n_divisoes_espaco - 1);

    vector<string> linhas = ler_linhas("Al.txt");

    funcao_intensidade(cumulativa, espaco, linhas, rho_Al, I_0, nFotoes, n_divisoes_espaco);

    return 0;
}


void funcao_intensidade(const vector<double>& cumulativa, const vector<double>& espaco, const vector<string>& linhas, double rho_Al, double I_0, size_t nFotoes, size_t n_divisoes_espaco) {
   
    bool flag_metade = false;

    ofstream ficheiro("grafico.dat");

    vector<double> distribuicao_x(nFotoes);

    for(size_t i = 0; i < nFotoes; i++) {

        double lambda = (double) 1 / (calcular_mu(cumulativa, linhas) * rho_Al);

        distribuicao_x[i] = - lambda * log(1 - drand48());
    }

    sort(distribuicao_x.begin(), distribuicao_x.end());

    for(size_t i = 0; i < n_divisoes_espaco; i++) {

        auto k = upper_bound(distribuicao_x.begin(), distribuicao_x.end(), espaco[i]) - distribuicao_x.begin();
        double I = I_0 * (nFotoes - k) / (double) nFotoes;
        if(I <= I_0 / 2 && flag_metade == false) {
            cout << "A intensidade atinge a flag_metade em: x = " << espaco[i] << endl;
            flag_metade = true;
        }
        ficheiro << espaco[i] << '\t' << I / I_0 << endl;
    }
    ficheiro.close();
}


double somar_linha(const string& line, int saltar_indice, int contador_atenuadores) {
    const char* p = line.c_str();
    char* end = nullptr;
    double soma = 0.0;
    for (int i = 0; i < saltar_indice + contador_atenuadores; ++i) {
        double v = strtod(p, &end);
        if (end == p) throw runtime_error("Nao ha numeros nesta linha");
        if (i >= saltar_indice) soma += v;
        p = end;
    }
    return soma;
}

vector<string> ler_linhas(const string& caminho) {
    ifstream f(caminho);
    if (!f) throw runtime_error("Erro ao abrir o ficheiro.");
    vector<string> linhas;
    string l;
    while (getline(f, l)) linhas.push_back(l);
    return linhas;
}

double calcular_mu(const vector<double>& cumulativa, const vector<string>& linhas) {
    double x = drand48() * cumulativa.back();
    size_t j = lower_bound(cumulativa.begin(), cumulativa.end(), x) - cumulativa.begin();
    if (j >= cumulativa.size()) j = cumulativa.size() - 1;

    size_t linha = j;
    if (linha >= linhas.size()) throw runtime_error("Al.txt tem menos linhas do que o esperado");

    double u_total = somar_linha(linhas[linha], 1, 3); // saltar a coluna das energias e somar u_F, u_R, u_C

    return u_total;  
}

void reamostrar_1keV(vector<double>& energias_kev, vector<double>& N) {
    vector<double> E_novo, N_novo;
    for (int e = 11; e <= 110; e++) {
        double valor = 0.0;
        auto it = lower_bound(energias_kev.begin(), energias_kev.end(), (double) e);
        if (it != energias_kev.end()) {
            size_t i = it - energias_kev.begin();
            if (*it == e) valor = N[i];
            else if (i > 0) {
                double t = (e - energias_kev[i-1]) / (energias_kev[i] - energias_kev[i-1]);
                valor = N[i-1] + t * (N[i] - N[i-1]);
            }
        }
        E_novo.push_back(e);
        N_novo.push_back(valor);
    }
    energias_kev = E_novo;
    N = N_novo;
}