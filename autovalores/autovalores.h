#ifndef AUTOVALORES_H
#define AUTOVALORES_H

#include "../matriz/matriz.h"

typedef enum {
    SEM_AUTOVALORES_REAL,
    UM_AUTOVALOR_REPETIDO,
    DOIS_AUTOVALORES_DISTINTOS,
} TipoAutovalor;   

void calcularAutovaloresAutovetores(Matriz *m);
void montarMatrizLambdaI(Matriz *m, double lambda, Matriz *resultado);
TipoAutovalor calcularAutovalores(Matriz *m, double autovalores[2]);
void calcularAutovetor(Matriz *m, double lambda, double autovetor[2]);
#endif
