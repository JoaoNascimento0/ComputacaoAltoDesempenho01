#ifndef ARRAY_H
#define ARRAY_H

//mostra o array 1d e uma mensagem para identificar o vetor.
void printVetor(char*, double*, int);

//aloca dinamicamente um array 1d.
double* alocVector(int);

//inicia o array 1d com a discretizacao uniforme do espaco [0, passo].
double* iniciaVetor(double, int);

//mostra o array 2d e uma mensagem para identifcar a matriz.
void printMatriz(char*, double**, int, int);

//aloca dinamicamente um array 2d.
double** alocMatriz(int, int);

//libera a memoria alocada dinamicamente para o array 2d.
void liberaMatriz(double**, int);

//salva o array 2d em um arquivo '.dat'.
void salvarMatriz(double**, int, int, const char*);

#endif