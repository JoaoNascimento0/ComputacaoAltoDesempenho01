// primeiro rascunho para projeto de diffusion equation 2d.
// data: 07/11

/*  -----   du/dt - D*(d²u/d²x + d²u/d²y) = f(x,y,t)   -----  */

// Bibliotecas, possiveis .h entrarao na jogada.
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Parâmetros do problema.
#define CondicaoInicial 0.0

#define D  1.0       // Coeficiente de difusão
#define nx 50        // Numero de pontos em x
#define ny 50        // Número de pontos em y
#define nt 100       // Número de passos de tempo
#define Lx 1.0       // dimensao do dominio em x
#define Ly 1.0       // dimensao do dominio em y
#define Tmax 0.1     // Tempo máximo

double f(double x, double y, double t){
    // Exemplo: uma fonte que depende de x, y e do tempo t => return sin(x * y) * exp(-t);
    return 0.0;
}

int main(){
// Variaveis.
    double u[nx][ny] = {0.0}; 

// Cálculo dos passos.
    double dx = Lx / (nx - 1);      // Intervalo infinitesimal de x
    double dy = Ly / (ny - 1);      // Intervalo infinitesimal de y
    double dt = Tmax / nt;          // Intervalo infinitesimal de tempo
    double r = D * dt / (dx * dx);  // contribuicao do coeficiente de difusao em x  
    double s = D * dt / (dy * dy);  // contribuicao do coeficiente de difusao em y

// Inicializar a matriz u com condições iniciais e de contorno.
    double u[nx][ny];
    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            u[i][j] = CondicaoInicial; // Condição inicial
        }
    }

// Loop no tempo.
    for (int n = 0; n < nt; n++){
        double u_new[nx][ny]; // Armazena o próximo estado

// Copiar u para u_new para começar a iteração.
        for (int i = 0; i < nx; i++) {
            for (int j = 0; j < ny; j++) {
                u_new[i][j] = u[i][j];
            }
        }

// Resolver o sistema linear com método iterativo de Gauss-Seidel.
        for (int iter = 0; iter < 1000; iter++) { // Máximo de iterações
            double max_diff = 0.0;

            for (int i = 1; i < nx - 1; i++) {
                for (int j = 1; j < ny - 1; j++) {
                    // Calcular o novo valor para u_new[i][j] usando o esquema implícito e adicionando f(x, y, t)
                    double u_old = u_new[i][j];

                    // AQUI: adicione o termo f(x[i], y[j], t[n]) na fórmula
                    u_new[i][j] = (u[i][j] 
                           + r * (u_new[i+1][j] + u_new[i-1][j])
                           + s * (u_new[i][j+1] + u_new[i][j-1])
                           + dt * f(x[i], y[j], t[n]) )  // termo da fonte
                           / (1 + 2 * r + 2 * s);

                    // Calcular a diferença para ver se o método convergiu
                    max_diff = fmax(max_diff, fabs(u_new[i][j] - u_old));
                }
            }

            // Condição de parada para o método iterativo
            if (max_diff < 1e-6) {
                break;
            }
        }

        // Aplicar condições de contorno.
        for (int i = 0; i < nx; i++) {
            u_new[i][0] = 0.0;          // Exemplo: contorno inferior
            u_new[i][ny-1] = 0.0;       // Exemplo: contorno superior
        }
        for (int j = 0; j < ny; j++) {
            u_new[0][j] = 0.0;          // Exemplo: contorno esquerdo
            u_new[nx-1][j] = 0.0;       // Exemplo: contorno direito
        }

        // Atualizar u para o próximo passo de tempo.
        for (int i = 0; i < nx; i++) {
            for (int j = 0; j < ny; j++) {
                u[i][j] = u_new[i][j];
            }
        }
        // Opcional: salvar ou visualizar `u` a cada k passos
        // Uma opcao de otimizacao para grandes matrizes e implementar a funcao troca, ao inves de trocar todos os valores apenas passar um novo ponteiro.

    }//fim do laco temporal.


return 0;
}