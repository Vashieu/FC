#include "latticeview.h"
#include <vector>
#include <cmath>

#define N 1300          //Lateral number of cells
#define ImageWidth 1000  //image width
#define ImageHeight 1000 //image height

int find(int x, vector<int>& labels);
void uniao(int x, int y, vector<int>& labels);
vector<int> percolation(int *lattice, vector<int>& aglomerados);
int queima(int *lattice, int &passos);


int main() {
    int lat[N*N];  //create lattice
    int icounter; //counters
    vector<int> labels(N*N);
    int passos;
    double p = 0.595;
    srand48(time(NULL));
    
    for (icounter = 0; icounter < N*N; icounter++) lat[icounter] = (drand48() < p) ? 1 : 0;
    // Contagem de aglomerados
    vector<int> aglomerados = percolation(lat, labels);

    int total = labels.size();  
    vector<int> count(total, 0);

    for (int i = 0; i < N*N; i++)
    if (aglomerados[i] != 0) count[aglomerados[i]]++;

    int nclusters = 0;
    for (int l = 1; l < total; l++)
    if (find(l, labels) == l) nclusters++;

    cout << "Numero de aglomerados: " << nclusters << endl;

    for (int l = 1; l < total; l++) {
    int root = find(l, labels);
    if (root == l)
        cout << "Aglomerado: " << l << ": " << count[l] << " pontos" << endl;
    else
        cout << "Aglomerado " << l << ": -" << root << endl;
}

    Print_lattice(lat, N, N, ImageWidth, ImageHeight, "randomcolor.ppm");

    // Percolacao
    int percola = queima(lat, passos);
    if (percola > 0) cout << "Percola. Caminho mais curto: " << passos << " passos, " << percola << " pontos" << endl;
    else cout << "Nao percola" << endl;

    Print_lattice(lat, N, N, ImageWidth, ImageHeight, "queimado.ppm");

    // Dependencia da percolacao relativamente ah probabilidade
    for(int i = 1; i < 100; i++) {
        p = i * p / (double) 100;
        for (icounter = 0; icounter < N*N; icounter++) lat[icounter] = (drand48() < p) ? 1 : 0;

        int percola1 = queima(lat, passos);
        if (percola1 > 0) cout << "Percola. Caminho mais curto: " << passos << " passos, " << percola1 << " pontos" << endl;
        else cout << "Nao percola" << endl;
    }

    return 0;
}

void bernoulli(int cP, int cF, int nprovas) {
    double p = cP / (double) (cP + cF);
    ofstream outfile0("distribuicao.dat");

    // C(n,0) = 1; construir C(n,i) por recorrencia C(n,i-1):  C(n,i) = C(n,i-1)*(n-i+1)/i
    double comb = 1.0;
    for (int i = 0; i <= nprovas; i++) {
        double dist = comb * pow(p, i) * pow(1 - p, nprovas - i);
        outfile0 << i << '\t' << dist << endl;

        // proxima combinacao
        comb = comb * (nprovas - i) / (i + 1);
    }
    outfile0.close();
}

//o codigo da percolacao foi essencialmente baseado no pseudo-codigo do algoritmo Hoshen-Kopelman da wikipedia

vector<int> percolation(int *lattice, vector<int>& labels) {
    int largest_label = 0;
    vector<int> label(N*N, 0);
    labels.resize(N*N + 1);
    //inicializar o vetor das posicoes com a posicao individual de cada celula da malha
    for (int i = 0; i <= N*N; i++) labels[i] = i;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int x = i * N + j;
            if (lattice[x] == 0) continue;

            int left   = (j > 0) ? label[x - 1] : 0;   // indice do ponto ah esquerda
            int bottom = (i > 0) ? label[x - N] : 0;   // indice do ponto em baixo (utiliza-se um ternário para verificar que nao estamos fora da indexacao permitida)

            if (left == 0 && bottom == 0) {
                largest_label++;
                label[x] = largest_label;
            }
            else if (left != 0 && bottom == 0) {
                label[x] = find(left, labels);
            }
            else if (left == 0 && bottom != 0) {
                label[x] = find(bottom, labels);
            }
            else {
                uniao(left, bottom, labels);
                label[x] = find(left, labels);
            }
        }
    }

    // devolver o indice de cada aglomerado ao ponto de início (trivial se for no ponto que iniciou o aglomerado)
    for (int i = 0; i < N*N; i++) {
        if (label[i] != 0) label[i] = find(label[i], labels);
    }

    labels.resize(largest_label + 1);
    return label;
}

int find(int x, vector<int>& labels) {
    int y = x;

    while(labels[y] != y) {
        y = labels[y];
    }

    while (labels[x] != x)  {
        int z = labels[x];
        labels[x] = y;
        x = z;
    }
    return y;
}

void uniao(int x, int y, vector<int>& labels) {
    int rx = find(x, labels);
    int ry = find(y, labels);
    if (rx < ry)      labels[ry] = rx;   // verificar qual indice do aglomerado é o primeiro
    else if (ry < rx) labels[rx] = ry;
}

int queima(int *lattice, int &passos) {
    // 0 = empty, 1 = occupied, 2 = burning now, 3 = burnt
    vector<int> frente, proxima;

    for (int j = 0; j < N; j++)
        if (lattice[j] == 1) { lattice[j] = 2; frente.push_back(j); }

    int t = 0;          // generation of the current front (top row = 0)
    passos = -1;        // -1 means the bottom row was never reached

    while (!frente.empty()) {
        proxima.clear();

        for (int x : frente) {
            int i = x / N, j = x % N;

            if (i > 0     && lattice[x - N] == 1) { lattice[x - N] = 2; proxima.push_back(x - N); }
            if (i < N - 1 && lattice[x + N] == 1) { lattice[x + N] = 2; proxima.push_back(x + N); }
            if (j > 0     && lattice[x - 1] == 1) { lattice[x - 1] = 2; proxima.push_back(x - 1); }
            if (j < N - 1 && lattice[x + 1] == 1) { lattice[x + 1] = 2; proxima.push_back(x + 1); }

            lattice[x] = 3;
        }

        t++;            // the sites in 'proxima' ignited at generation t

        if (passos < 0) {                       // record only the FIRST arrival
            for (int x : proxima)
                if (x / N == N - 1) { passos = t; break; }
        }

        frente.swap(proxima);
    }

    return (passos < 0) ? 0 : passos + 1;       // number of sites in the shortest path
}
