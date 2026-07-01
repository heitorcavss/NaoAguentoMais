#include <stdio.h>
#include <math.h>
#include "autovalores.h"
#include "../parsing/ler.h"

void calcularAutovaloresAutovetores(Matriz *m){
    double autovalores[2];
    double autovetor[2];
    
    lerMatrizPorParsing(m, 2, 2);

    TipoAutovalor tipo = calcularAutovalores(m, autovalores);

    if(tipo == SEM_AUTOVALORES_REAL){
        printf("A matriz nao tem autovalores reais (complexos).\n");
        return;   /* não tem autovetor real pra calcular, encerra aqui */
    }else if(tipo == UM_AUTOVALOR_REPETIDO){
        /* ===== EXEMPLO PRONTO: um autovalor só ===== */
        printf("Autovalor (repetido): %.2f\n", autovalores[0]);
        calcularAutovetor(m, autovalores[0], autovetor);
        printf("Autovetor: (%.2f, %.2f)\n\n", autovetor[0], autovetor[1]);
    }else{   /* DOIS_AUTOVALORES_DISTINTOS */
        for(int i = 0; i < 2; i++){
            printf("Autovalor: %.2f\n", autovalores[i]);
            calcularAutovetor(m, autovalores[i], autovetor);
            printf("Autovetor: (%.2f, %.2f)\n\n", autovetor[0], autovetor[1]);
        }
    }
}

TipoAutovalor calcularAutovalores(Matriz *m, double autovalores[2]) {

    //pra n virar bagunça
    double a = m->valores[0][0];   
    double b = m->valores[0][1];   
    double c = m->valores[1][0];  
    double d = m->valores[1][1];   

    double f = -(a + d); // coef do lambda
    double g = (a * d) - (b * c); // termo constante

    double delta = (f*f) - (4 * 1 * g);

    if(delta <-ZERO){
        return SEM_AUTOVALORES_REAL;
    }else if(delta < ZERO){
        autovalores[0] = -f / (2 * 1);
        return UM_AUTOVALOR_REPETIDO;
    }else{
        autovalores[0] = (-f + sqrt(delta)) / (2 * 1);
        autovalores[1] = (-f - sqrt(delta)) / (2 * 1);
        return DOIS_AUTOVALORES_DISTINTOS;
    }
}

void montarMatrizLambdaI(Matriz *A, double lambda, Matriz *resultado){

    resultado->linhas  = A->linhas;
    resultado->colunas = A->colunas;

    for(int i = 0; i < A->linhas; i++){
        for(int j = 0; j < A->colunas; j++){
            //copiar valores
            resultado->valores[i][j] = A->valores[i][j];

            if(i == j){
                //diminui lambda se diagonal
                resultado->valores[i][j] -= lambda;
            }
        }
    }
}

void calcularAutovetor(Matriz *m, double lambda, double autovetor[2]){
    Matriz v;
    montarMatrizLambdaI(m, lambda, &v);

    double p = v.valores[0][0];   // 1ª linha [p, q]
    double q = v.valores[0][1];

    if(fabs(p) > ZERO){
        autovetor[0] = -q/p;
        autovetor[1] = 1; // y vou setar em 1
    }else{
        autovetor[0] = 1; // x agr
        autovetor[1] = 0;
    }
}