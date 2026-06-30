#include <stdio.h>
#include "diagonalizacao.h"

void diagonalizarMatriz(Matriz *m){
    double autovalores[2];
    m->linhas = 2;
    m->colunas = 2;

    lerMatriz(m);  

    TipoAutovalor tipo = calcularAutovalores(m, autovalores);

    if(tipo == DOIS_AUTOVALORES_DISTINTOS){
        printf("A matriz é diagonalizavel.\n");

        Matriz D;
        formarMatrizDiagonal(&D, autovalores);

        printf("Matriz diagonal D:\n");
        escreverMatriz(&D);   /* reusa sua função do modulo matriz */
    }
    else {
        printf("A matriz NAO e diagonalizavel em R.\n");
    }
}

void formarMatrizDiagonal(Matriz *m, double autovalores[2]){

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            if(i == j){
                m->valores[i][j] = autovalores[i];
            } else {
                m->valores[i][j] = 0.0;
            }
        }
    }
}