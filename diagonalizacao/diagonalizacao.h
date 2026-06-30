#ifndef DIAGONALIZACAO_H
#define DIAGONALIZACAO_H

#include "../matriz/matriz.h"
#include "../autovalores/autovalores.h"

void diagonalizarMatriz(Matriz *m);
void formarMatrizDiagonal(Matriz *m, double autovalores[2]);

#endif
