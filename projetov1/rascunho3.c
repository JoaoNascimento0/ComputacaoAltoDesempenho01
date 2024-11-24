// segundo rascunho para projeto de diffusion equation 2d.
// data: 20/11

//gostaria de testar o editor m
/*  -----   du/dt - D*(d²u/d²x + d²u/d²y) = f(x,y,t)   -----  */

// Bibliotecas, possiveis .h entrarao na jogada.
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Parâmetros do problema.
#define CondicaoInicial 100.0
#define CondicaoContorno 0.0
#define tol 1e-6

#define D  1.0       // Coeficiente de difusão
#define nx 100        // Numero de pontos em x
#define ny 100        // Número de pontos em y
#define nt 100        // Número de passos de tempo
#define Lx 1.0       // dimensao do dominio em x
#define Ly 1.0       // dimensao do dominio em y
#define Tmax 0.1     // Tempo máximo

void printMatriz(char* msg, double** mat, int m, int n){
  puts(msg);
  for(int i=0; i<m; i++){
    for(int j=0; j<n; j++){
      printf("%g\t", mat[i][j]);
    }
    puts("");
  }
}
double f(double x, double y, double t){
    // Exemplo: uma fonte que depende de x, y e do tempo t => return sin(x * y) * exp(-t);
    return 0.0;
}

void liberaMatriz(double** mat, int lin){
  //liberar a memoria alocada pelo programa para armazenar a matriz
  for(int i=0; i<lin; i++)
    free(mat[i]);
  free(mat);
}
double** alocMatriz(int lin, int col){
    double** mat = (double**)malloc(lin*sizeof(double*));
    for(int i=0; i<lin; i++){
        mat[i] = (double*)malloc(col*sizeof(double));
    }

    return mat;
}
double* alocVector(int lin){
    double* vet = (double*)malloc(lin*sizeof(double));
return vet;
}

void sistemaLinear(double** a, double** b, double r, double s, double dt, double (*f)(double, double, double), double* x, double* y, double* t, int n){
    double max_diff;
    int iter = 0;
    do{
        max_diff = 0.0;

        for (int i=1; i<nx-1; i++){
            for (int j=1; j<ny-1; j++){
                double old = b[i][j];

                // AQUI: adicione o termo f(x[i], y[j], t[n]) na fórmula
                b[i][j] = (a[i][j]
                       + r * (b[i+1][j] + b[i-1][j])
                       + s * (b[i][j+1] + b[i][j-1])
                       + dt * f(x[i], y[j], t[n]) )  // termo da fonte
                       / (1 + 2 * r + 2 * s);

                // Calcular a diferença para ver se o método convergiu
                max_diff = fmax(max_diff, fabs(b[i][j] - old));
            }
        }

        //printf("\niter : %d", iter);
        iter++;
    }while(max_diff > tol);
    printf("\titer: %d", iter);
}

void salvarMatriz(double** mat, int lin, int col, const char* nome){
    FILE* arq = fopen(nome, "w");

    // Escrever os dados da matriz no arquivo
    for (int i=0; i<lin; i++) {
        for (int j=0; j<col; j++) {
            fprintf(arq, "%g\t", mat[i][j]); // Escreve um valor da matriz no arquivo
        }
        fprintf(arq, "\n"); // Nova linha após cada linha da matriz
    }

    // Fechar o arquivo
    fclose(arq);
    printf("\n\nMatriz salva em %s\n", nome);
}

int main(){
// Variaveis.
    double** u = alocMatriz(nx, ny);    //declaração para arrays
    double** u_new = alocMatriz(nx, ny); // Armazena o próximo estado
    double* x = alocVector(nx);
    double* y = alocVector(nx);
    double* t = alocVector(nx);

// Inicializar a matriz u com condições iniciais e de contorno.
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            u[i][j] = CondicaoInicial; // Condição inicial
        }
    }
    //printMatriz("inicio", u, nx, ny);

// Cálculo dos passos.
    double dx = Lx/(nx-1);      // Intervalo infinitesimal de x
    double dy = Ly/(ny-1);      // Intervalo infinitesimal de y
    double dt = Tmax/nt;        // Intervalo infinitesimal de tempo
    double r = D*dt/(dx*dx);    // contribuicao do coeficiente de difusao em x  
    double s = D*dt/(dy*dy);    // contribuicao do coeficiente de difusao em y

// Loop no tempo.
    for(int n = 0; n < nt; n++){
        // Copiar u para u_new para começar a iteração.
        for(int i = 0; i < nx; i++){
            for(int j = 0; j < ny; j++){
                u_new[i][j] = u[i][j];
            }
        }

        sistemaLinear(u, u_new, r, s, dt, f, x, y, t, n);

        // Aplicar condições de contorno.
        for (int i = 0; i < nx; i++){
            u_new[i][0] = CondicaoContorno;          // Exemplo: contorno inferior
            u_new[i][ny-1] = CondicaoContorno;       // Exemplo: contorno superior
        }
        for(int j = 0; j < ny; j++){
            u_new[0][j] = CondicaoContorno;          // Exemplo: contorno esquerdo
            u_new[nx-1][j] = CondicaoContorno;       // Exemplo: contorno direito
        }

        // Atualizar u para o próximo passo de tempo.
        for (int i = 0; i < nx; i++) {
            for (int j = 0; j < ny; j++) {
                u[i][j] = u_new[i][j];
            }
        }
        // Opcional: salvar ou visualizar `u` a cada k passos
        // Uma opcao de otimizacao para grandes matrizes e implementar a funcao troca, ao inves de trocar todos os valores apenas passar um novo ponteiro.
    
    //printf("\n\ntempo: %d", n);   //fim do laco temporal.
    }
    salvarMatriz(u, nx, ny, "resultadoRascunho3.dat");

    liberaMatriz(u_new, nx);
    liberaMatriz(u, nx);
    puts("");

return 0;
}
