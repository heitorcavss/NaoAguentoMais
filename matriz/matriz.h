#ifndef MATRIZ_H
#define MATRIZ_H

#define MAX 4

typedef struct {
    int linhas;
    int colunas;
    double valores[MAX][MAX];
    double determinante;
} Matriz;

void inicializarMatriz(Matriz *m);
void lerMatriz(Matriz *m);
void escreverMatriz(Matriz *m);
void multiplicarMatrizes(Matriz *a, Matriz *b, Matriz *c);
double calcularDeterminante(Matriz *m);
int calcularPosto(Matriz *m); /* retorna o número de pivôs após escalonamento */

#endif
