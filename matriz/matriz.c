#include <stdio.h>
#include <math.h>
#include "matriz.h"

void inicializarMatriz(Matriz *m) {
    for (int i = 0; i < m->linhas; i++)
        for (int j = 0; j < m->colunas; j++)
            m->valores[i][j] = 0.0;
    m->determinante = 0.0;
}

void lerMatriz(Matriz *m) {
    printf("Digite os elementos (linha a linha):\n");
    for (int i = 0; i < m->linhas; i++)
        for (int j = 0; j < m->colunas; j++) {
            printf("  m[%d][%d] = ", i + 1, j + 1);
            scanf("%lf", &m->valores[i][j]);
        }
}

void escreverMatriz(Matriz *m) {
    for (int i = 0; i < m->linhas; i++) {
        printf("|");
        for (int j = 0; j < m->colunas; j++)
            printf(" %8.2lf|", m->valores[i][j]);
        printf("\n");
    }
}

void multiplicarMatrizes(Matriz *a, Matriz *b, Matriz *c) {
    c->linhas  = a->linhas;
    c->colunas = b->colunas;
    inicializarMatriz(c);
    for (int i = 0; i < a->linhas; i++)
        for (int j = 0; j < b->colunas; j++)
            for (int k = 0; k < a->colunas; k++)
                c->valores[i][j] += a->valores[i][k] * b->valores[k][j];
}

double calcularDeterminante(Matriz *m) {
    double tmp[MAX][MAX];
    double det = 1.0;
    int n = m->linhas;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            tmp[i][j] = m->valores[i][j];

    for (int col = 0; col < n; col++) {

        int pivotLin = col;
        for (int i = col + 1; i < n; i++)
            if (fabs(tmp[i][col]) > fabs(tmp[pivotLin][col]))
                pivotLin = i;

        if (pivotLin != col) {
            for (int j = 0; j < n; j++) {
                double aux        = tmp[col][j];
                tmp[col][j]       = tmp[pivotLin][j];
                tmp[pivotLin][j]  = aux;
            }
            det *= -1.0;
        }

        if (fabs(tmp[col][col]) < 1e-12) {
            m->determinante = 0.0;
            return 0.0;
        }

        det *= tmp[col][col];

        for (int i = col + 1; i < n; i++) {
            double fator = tmp[i][col] / tmp[col][col];
            for (int j = col; j < n; j++)
                tmp[i][j] -= fator * tmp[col][j];
        }
    }

    m->determinante = det;
    return det;
}

int calcularPosto(Matriz *m) { return 0; /* TODO */ }
