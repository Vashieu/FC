#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include<fstream>

using namespace std;

vector <double> geraleatorio(int seed, int tamanho, unsigned long long Nmax);
void quiquadrado (vector <double> y, int div, int tamanho);
vector <double> randfunc(int seed,int tamanho, unsigned long long Nmax);
void circulo (vector <double> y);


int main()
{
    int seed = 21;
    int tamanho = 60;  
    int div = 30;
    int i;
    int escolha1=0;
    int escolha2=0;
    const unsigned long long Nmax = 31;
    vector <double> y;

    cout << "Escolhe o gerador aleatorio a utilizar 1-Func Criada ou 2-Func C++:" << endl;
    cin >> escolha1;
   
    if(escolha1 == 1)
    {
      y = geraleatorio(seed, tamanho, Nmax);
    }
    else 
    {  
       y = randfunc(seed, tamanho, Nmax);
    }

    escolha1=0;

    cout << "Quer fazer mais alguma coisa com os numeros gerados 1-Nao (Fazer teste Quadrado/Cubo), 2-Fazer um circulo, 3-Descobrir o Qui Quadrado:" << endl;
    cin >> escolha1;
    if(escolha1 == 1)
    {
     cout << "Quer fazer que teste 1- Quadrado ou 2- Cubo" << endl;
     cin >> escolha2;
     if(escolha2 == 1)
     {
       ofstream fout("teste.dat");
       for(i=0;i<y.size();i+=2)
       {
         fout<<y[i]<<"\t"<<y[i+1]<<endl;
       }
       fout.close();
     }
     if(escolha2 == 2)
     {
       ofstream fout("teste.dat");
       for(i=0;i<y.size();i+=3)
       {
         fout<<y[i]<<"\t"<<y[i+1]<<"\t"<<y[i+2]<<endl;
       }
       fout.close();
     }
     
    }
    else if(escolha1 == 2)
    {  
       circulo (y);
    }
    else
    {
        quiquadrado (y, div, tamanho);
    }
    
 return 0;

}


vector <double> geraleatorio(int seed, int tamanho, unsigned long long Nmax)
{
    int a = 0;
    int i;
    const unsigned long long c = 3;
    vector<unsigned long long> num(tamanho);
    vector<double> y(tamanho);

    num[0] = seed;

    for (i = 0; i < num.size() - 1; i++)
    {
        num[i + 1] = (c * num[i] + a) % Nmax;
    }

    for (i = 0; i < num.size(); i++)
    {
        y[i] = num[i] / (double)Nmax;
    }
    return y;
}

void circulo (vector <double> y)
{
    int a;
    const double Raio = 1.0; 
    const double doispi = 2*M_PI;
    double r;
    double theta;
    double u1;
    double u2;
    double xcart;
    double ycart;
    
    ofstream fout("teste.dat");
    for (a=0; a<y.size(); a+=2)
    {
        u1 = y[a];
        u2 = y[a+1];
        r = Raio*sqrt(u1);
        theta = doispi * u2;
        xcart = r*cos(theta);
        ycart = r*sin(theta);

        fout << xcart << "\t" << ycart << endl;
    }  
    fout.close();
}

void quiquadrado (vector <double> y, int div, int tamanho)
{
    vector <int> O(div, 0);
    double p_i = 1.0/div;
    double qui = 0;
    int i;
    int interv;

    for(i=0;i<y.size();i++)
    {
        interv = (int)(y[i]*div);
        if(interv>=div)
        {
            interv= div - 1;
        }
        O[interv] += 1;
    }

    for(i=0; i<div; i++)
    {
        qui += pow((O[i]-(double)(tamanho*p_i)),2)/(double)(tamanho*p_i);
    }

    cout << "O Qui Quadrado para estas condicoes e:" << "\t" << qui << endl;
}

vector <double> randfunc(int seed, int tamanho, unsigned long long Nmax)
{
    int escolha;
    int a;
    vector <double> num(tamanho);
    vector <double> y(tamanho);
    int i;

    cout << "Escolhe o gerador aleatorio a utilizar 1-rand() ou 2-drand48():" << endl;
    cin >> escolha;
    cout << "Escolhe o inicio do intervalo:" << endl;
    cin >> a;
    num[0]=seed;

    if(escolha == 1)
    {  
       srand(seed);
      for(i=1; i<num.size(); i++)
      {
        num[i] = (rand() % (Nmax-a+1))+a;
      }
      for (i = 0; i < num.size(); i++)
      {
         y[i] = num[i] / (double)Nmax;
      }
    }
    else 
    {  
       srand48(seed);
      for(i=1; i<y.size(); i++)
      {
         num[i] = a + (drand48() * (Nmax - a));
      }
       for (i = 0; i < num.size(); i++)
       {
         y[i] = num[i] / (double)Nmax;
       }
    }
    return y;
}