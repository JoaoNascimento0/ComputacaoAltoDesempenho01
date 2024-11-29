#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "array.h"

#define D  1.0       //coeficiente de difusão
#define nx 100       //numero de pontos em x
#define ny 100       //numero de pontos em y
#define Lx 1.0       //dimensao do dominio em x
#define Ly 1.0       //dimensao do dominio em y
#define Lt 0.3       //tempo máximo

void saveVetor(double* vet, int lin, const char* nome){
    FILE* arq = fopen(nome, "wt");
 
    // Escreve os dados da matriz no arquivo
    for(int i=0; i<lin; i++){
        fprintf(arq, "%d\t%g\n", i,  vet[i]);
    }

    fclose(arq);
    printf("\n\nVetor salva em %s\n", nome);
}

double** solucao(double* x, double* y, int lin, int col, double t){
    double** u = alocMatriz(lin, col);

    for(int i=0; i<lin; i++){
        for (int j=0; j<col; j++){
            u[i][j] = exp((-2)*D*M_PI*M_PI*t) * sin(M_PI*x[i]) * sin(M_PI*y[j]);
        }
    }

    return u;
}

double** diferenca(double** a, double** b, int lin, int col){
    for(int i=0; i<lin; i++){
        for(int j=0; j<col; j++){
            b[i][j] -= a[i][j];
        }
    }
    return b;
}

double** leMatriz(char* nome, int m, int n){
  FILE* arq = fopen(nome, "rt");

  //parametros de tamanho linha e coluna
  //fscanf(arq, "%d %d\n", m, n);

  //alocacao da nova matriz
  double** newMat = malloc((m)*sizeof(double*));
  for(int i=0; i<(m);i++)
    newMat[i] = malloc((n)*sizeof(double*));

  //atribuicao de valores obtidos na matriz do arquivo.dat
  for(int i=0; i<(m); i++)
    for(int j=0; j<(n); j++){
      fscanf(arq, "%lf", &newMat[i][j]);
    }

  fclose(arq);
  return (newMat);
}

double linhaNorma(double* linha, int col) {
    double norma = 0.0;
    for (int i = 0; i < col; i++) {
        norma += linha[i] * linha[i]; // Soma dos quadrados dos elementos
    }
    return sqrt(norma); // Retorna a raiz quadrada da soma
}

double* calcularNormas(double** matriz, int lin, int col) {
    double* norma = alocVector(lin);

    for (int i = 0; i < lin; i++){
        norma[i] = linhaNorma(matriz[i], col);
    }
    return norma;
}

int main(){
//variaveis.
    double dx = Lx/(nx);    //intervalo infinitesimal de x
    double dy = Ly/(ny);    //intervalo infinitesimal de y

//memória necessaria.
    double* x = iniciaVetor(dx, nx);
    double* y = iniciaVetor(dy, ny);

//preenche a matriz de solucao analitica u(x,y,Lt), tempo final.
    double** analitica = solucao(x, y, nx, ny, Lt);
    double** matriz99 = leMatriz("99tempo", nx, ny);

    matriz99 = diferenca(analitica, matriz99, nx, ny);
        //printMatriz("99tempo", matriz99, nx, ny);

    double* norma = calcularNormas(matriz99, nx, ny);
        printVetor("normas\n", norma, nx);
    
    saveVetor(norma, nx, "NORMAS.dat");

//libera memoria previamente alocada.
    liberaMatriz(analitica, nx);
    liberaMatriz(matriz99, nx);
    free(x);
    free(y);
    free(norma);

  return 0;
}