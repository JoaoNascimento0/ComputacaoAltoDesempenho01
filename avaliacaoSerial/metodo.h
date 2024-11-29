#ifndef METODOS_H
#define METODOS_H

//controla a difusao entre os valores do arrays 2d princial.
double f(double, double, double);

//faz a troca de uma linha de 'a' para 'b'.
void troca(double** a, double** b, int lin, int col);

//preeche o array 2d principal com as condicoes iniciais, que podem ser depender das posicoes x e y.
void condicaoInicial(double**, double*, double*, int, int);

//faz o controle do arrays 2d principal para que as condicoes de Dirichlet sejam obedecidas.
void condicaoContorno(double**, int, int);

//Solucao para o sistema linear dentro do metodo de diferencas finitas.
void gaussSiedel(double**, double**, double, double, double, double (*f)(double, double, double), double*, double*, double*, int, int, int);

//encontra os valores para o proximo passo de tempo no array 2d principal. 
void diferencasFinitas(double**, double**, double, double, double, double (*f)(double, double, double), double*, double*, double*, int, int, int);

#endif