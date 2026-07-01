#include <stdio.h>
#include <math.h>
#include "diagonalizacao.h"
#include "../parsing/ler.h"

void diagonalizarMatriz(Matriz *m){
    double autovalores[2];

    if(!lerOperadorR2PorParsing(m)){
        return;
    }

    TipoAutovalor tipo = calcularAutovalores(m, autovalores);

    int diagonalizavel = 0;

    if(tipo == DOIS_AUTOVALORES_DISTINTOS){
        diagonalizavel = 1;
    }
    else if(tipo == UM_AUTOVALOR_REPETIDO){
        double b = m->valores[0][1];
        double c = m->valores[1][0];

        // matriz escalar
        if(fabs(b) < ZERO && fabs(c) < ZERO){
            diagonalizavel = 1;
            autovalores[1] = autovalores[0]; // preenche o 2o lambda pra nao sair zuado
        }
    }
    
    if(diagonalizavel){
        printf("A matriz e diagonalizavel.\n");

        Matriz D;
        formarMatrizDiagonal(&D, autovalores);

        printf("Matriz diagonal D:\n");
        escreverMatriz(&D);
    }
    else {
        printf("A matriz NAO e diagonalizavel em R.\n");
    }
}

void formarMatrizDiagonal(Matriz *m, double autovalores[2]){
    m->linhas = 2;
    m->colunas = 2;

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
