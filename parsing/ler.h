#ifndef LER_H
#define LER_H

#include "sistema.h"

int indiceVariavel(SistemaLinear *s, char variavel);
int variavelJaCadastrada(SistemaLinear *s, char variavel, int limite);
void limparBufferEntrada();
int parseEquacao(char linha[], SistemaLinear *s, int linhaSistema);

#endif