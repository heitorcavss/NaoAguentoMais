#ifndef BASE_H
#define BASE_H

#include "../matriz/matriz.h"

void lerConjunto(Matriz *m);
int  ehBase(Matriz *m);
void indicarSubconjunto(Matriz *m, int dimensao);
void determinarBase(Matriz *m);

#endif
