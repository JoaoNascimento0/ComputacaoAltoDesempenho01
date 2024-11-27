#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//headers
#include "array.h"
#include "metodo.h"

#define D  1.0       //coeficiente de difusão
#define nx 100       //numero de pontos em x
#define ny 100       //numero de pontos em y
#define nt 100       //numero de passos de tempo
#define Lx 1.0       //dimensao do dominio em x
#define Ly 1.0       //dimensao do dominio em y
#define Lt 0.3       //tempo máximo

int main(){
//tempo de execucao.
    clock_t start, end;
    double cpu_time_used;
    start = clock(); // Início da medição

//calculo dos passos.
    double dx = Lx/(nx);        //intervalo infinitesimal de x
    double dy = Ly/(ny);        //intervalo infinitesimal de y
    double dt = Lt/nt;          //intervalo infinitesimal de tempo
    double r = D*dt/(dx*dx);    //contribuicao do coeficiente de difusao em x  
    double s = D*dt/(dy*dy);    //contribuicao do coeficiente de difusao em y
    char* str;

//memória necessaria.
    double** u = alocMatriz(nx, ny);    //declaração para arrays.
    double** u_new = alocMatriz(nx, ny); // Armazena o próximo estado.

    double* x = iniciaVetor(dx, nx);
    double* y = iniciaVetor(dy, ny);
    double* t = iniciaVetor(dt, nt);

//inicializar a matriz u com condicoes iniciais e de contorno.
    condicaoInicial(u, x, y, nx, ny);

//loop no tempo.
    for(int n=0; n<nt; n++){
        //metodo principal para encontrar os valores de u para o proximo passo de tempo.
        diferencasFinitas(u, u_new, r, s, dt, f, x, y, t, n, nx, ny);

        snprintf(str,sizeof(str),"%d",n);
        strcat(str, "tempo");
        salvarMatriz(u, nx, ny, str);
    }

    liberaMatriz(u_new, nx);
    liberaMatriz(u, nx);
    free(x);
    free(y);
    free(t);

    end = clock(); // Fim da medição
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", cpu_time_used);

return 0;
}
