#include "array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void printVetor(char* msg, double* vet, int m){
  puts(msg);
  for(int i=0; i<m; i++){
      printf("%g\t", vet[i]);
  }
}

double* alocVector(int lin){
    double* vet = (double*)malloc(lin*sizeof(double));
return vet;
}

double* iniciaVetor(double passo, int n){
    double* vet = alocVector(n);
    for(int i=0; i<n; i++){
        vet[i] = i*passo; //preenche o array
    }
return (vet);
}

void printMatriz(char* msg, double** mat, int m, int n){
  puts(msg);
  for(int i=0; i<m; i++){
    for(int j=0; j<n; j++){
      printf("%g\t", mat[i][j]);
    }
    puts("");
  }
}

double** alocMatriz(int lin, int col){
    double** mat = (double**)malloc(lin*sizeof(double*));
    for(int i=0; i<lin; i++){
        mat[i] = (double*)malloc(col*sizeof(double));
    }

    return mat;
}

void liberaMatriz(double** mat, int lin){
  //liberar a memoria alocada pelo programa para armazenar a matriz
  for(int i=0; i<lin; i++)
    free(mat[i]);
  free(mat);
}

void salvarMatriz(double** mat, int lin, int col, const char* nome){
    const char* diretorio = "dados";
    
    // Verifica se o diretório existe e cria caso não exista
    struct stat st = {0};
    if (stat(diretorio, &st) == -1) {
        if (mkdir(diretorio, 0777) != 0) {
            perror("Erro ao criar o diretório");
            return;
        }
    }

    // Concatena o diretório com o nome do arquivo
    char caminho[64];  // Buffer para o caminho completo
    snprintf(caminho, sizeof(caminho), "%s/%s", diretorio, nome);

    // Abre o arquivo no caminho especificado
    FILE* arq = fopen(caminho, "w");
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    // Escreve os dados da matriz no arquivo
    for (int i = 0; i < lin; i++){
        for (int j = 0; j < col; j++){
            fprintf(arq, "%g\t", mat[i][j]); // Escreve um valor da matriz
        }
        fprintf(arq, "\n"); // Nova linha após cada linha da matriz
    }

    // Fecha o arquivo
    fclose(arq);
    //printf("\n\nMatriz salva em %s\n", caminho);
}
