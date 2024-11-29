#include "metodo.h"

//bibliotecas utilizadas.
#include <stdio.h>
#include <math.h>
#include <string.h>

//parametros do problema.
#define CondicaoContorno 0.0
#define tol 1e-6

#define fonte 0.0

double f(double x, double y, double t){
    // Exemplo: uma fonte que depende de x, y e do tempo t => return sin(x * y) * exp(-t);
    return 0.0;
}

void troca(double** a, double** b, int lin, int col){
    for(int i=0; i<lin; i++){
        memcpy(a[i], b[i], col*sizeof(double)); //copia inha de 'b' para 'a'
    }
}

void condicaoInicial(double** u, double* x, double* y, int lin, int col){
    for(int i=0; i<lin; i++){    
        for (int j=0; j<col; j++){
            u[i][j] = sin(M_PI*x[i]) * sin(M_PI*y[j]);  //u(x,y,0) = sin(pi*x)sin(pi*y)
        }
    }
}

void condicaoContorno(double** a, int lin, int col){

    for (int i=0; i<lin; i++){
        a[i][0] = CondicaoContorno;          //contorno inferior
        a[i][lin-1] = CondicaoContorno;      //contorno superior
    }
    for(int j=0; j<col; j++){
        a[0][j] = CondicaoContorno;          //contorno esquerdo
        a[col-1][j] = CondicaoContorno;      //contorno direito
    }
}

void gaussSiedel(double** a, double** b, double r, double s, double dt, double (*f)(double, double, double), double* x, double* y, double* t, int n, int lin, int col){

    double max_diff;
    int iter = 0;
    do{
        max_diff = 0.0;

        for (int i=1; i<lin-1; i++){
            for (int j=1; j<col-1; j++){
                double old = b[i][j];

                b[i][j] = (a[i][j]
                       + r * (b[i+1][j] + b[i-1][j])
                       + s * (b[i][j+1] + b[i][j-1])
                       + dt * fonte /*f(x[i], y[j], t[n])*/ )  // termo da fonte
                       / (1 + 2 * r + 2 * s);

                // Calcular a diferença para ver se o método convergiu
                max_diff = fmax(max_diff, fabs(b[i][j] - old));
            }
        }

        //printf("\niter : %d", iter);
        iter++;
    }while(max_diff > tol);
    //printf("\titer: %d", iter);
}

void diferencasFinitas(double** a, double** b, double r, double s, double dt, double (*f)(double, double, double), double* x, double* y, double* t, int n, int lin, int col){
    //copiar u para u_new para começar a iteração.
    troca(b, a, lin, col);

    //encontra os proximos valores para a matriz.
    gaussSiedel(a, b, r, s, dt, f, x, y, t, n, lin, col);

    //aplicar condicoes de contorno.
    condicaoContorno(b, lin, col);

    //atualizar u para o próximo passo de tempo.
    troca(a, b, lin, col);
}