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

void saveMatriz(double** mat, int lin, int col, const char* nome){
    FILE* arq = fopen(nome, "wt");
 
    // Escreve os dados da matriz no arquivo
    for(int i=0; i<lin; i++){
        for(int j=0; j<col; j++){
            fprintf(arq, "%g\t", mat[i][j]);
        }
        fprintf(arq, "\n");
    }

    fclose(arq);
    //printf("\n\nMatriz salva em %s\n", nome);
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

int main(){
//variaveis.
    double dx = Lx/(nx);    //intervalo infinitesimal de x
    double dy = Ly/(ny);    //intervalo infinitesimal de y

//memória necessaria.
    double* x = iniciaVetor(dx, nx);
    double* y = iniciaVetor(dy, ny);

//preenche a matriz de solucao analitica u(x,y,Lt), tempo final.
    double **analitica = solucao(x, y, nx, ny, Lt);

//salva a matriz em um arquivo '.dat'.
    saveMatriz(analitica, nx, ny, "solucaoAnalitica.dat");

//libera memoria previamente alocada.
    liberaMatriz(analitica, nx);
    free(x);
    free(y);

  return 0;
}