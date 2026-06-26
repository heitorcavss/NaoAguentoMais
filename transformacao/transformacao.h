#ifndef TRANSFORMACAO_H
#define TRANSFORMACAO_H

#include "../matriz/matriz.h"

int verificarInjetividade(Matriz *m);
int verificarSobrejetividade(Matriz *m);
int verificaBijetividade(Matriz *m);
void relatorioTransformacao(Matriz *m);
void lerTransformacao(Matriz *m);

#endif
