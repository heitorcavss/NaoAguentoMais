#include <stdio.h>
#include <math.h>
#include "../sistema/sistema.h"

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
    for(int i = 0; i < a->linhas; i++)
        for(int j = 0; j < b->colunas; j++)
            for(int k = 0; k < a->colunas; k++)
                c->valores[i][j] += a->valores[i][k] * b->valores[k][j];
}

int escalonarMatriz(Matriz *m){
    int trocas = 0;
    int linhaPivo = 0;
    int colPivo = 0;

    while(linhaPivo < m->linhas && colPivo < m->colunas){
        //acha o maior elemento da coluna, para evitar problemas de precisão e div por 0
        int maxLin = linhaPivo;
        for(int k = linhaPivo + 1; k < m->linhas; k++)
            if(fabs(m->valores[k][colPivo]) > fabs(m->valores[maxLin][colPivo]))
                maxLin = k;

        // anda coluna se o pivo == 0
        if(fabs(m->valores[maxLin][colPivo]) < ZERO){
            colPivo++;
            continue;
        }

        //pivoteamento
        if(maxLin != linhaPivo){
            for (int j = 0; j < m->colunas; j++){
                double temp = m->valores[linhaPivo][j];
                m->valores[linhaPivo][j] = m->valores[maxLin][j];
                m->valores[maxLin][j] = temp;
            }
            trocas++;
        }

        //escalonamento
        for(int k = linhaPivo + 1; k < m->linhas; k++){
            double fator = m->valores[k][colPivo] / m->valores[linhaPivo][colPivo];
            for (int l = colPivo; l < m->colunas; l++)
                m->valores[k][l] -= fator * m->valores[linhaPivo][l];
        }

        linhaPivo++;
        colPivo++;
    }
    return trocas;
}

double calcularDeterminante(Matriz *m){
    Matriz cop = *m;
    int trocas = escalonarMatriz(&cop);

    double det = (trocas % 2 == 0) ? 1.0 : -1.0;
    for (int i = 0; i < cop.linhas; i++){
        if (fabs(cop.valores[i][i]) < ZERO){
            m->determinante = 0.0;
            return 0.0;
        }
        det *= cop.valores[i][i];
    }

    m->determinante = det;
    return det;
}

int contarPivos(Matriz *m){
    int pivos = 0;
    for(int i = 0; i < m->linhas; i++){
        int temPivo = 0;
        for(int j = 0; j < m->colunas; j++){
            if(fabs(m->valores[i][j]) > ZERO){ 
                temPivo = 1;
                break;
            }
        }
        pivos += temPivo;
    }
    return pivos;
}

int calcularPosto(Matriz *m){ 
    Matriz cop = *m;
    escalonarMatriz(&cop);
    return contarPivos(&cop);
}

 
