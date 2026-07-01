#ifndef LER_H
#define LER_H

#include "../sistema/sistema.h"
#include "../matriz/matriz.h"

int indiceVariavel(SistemaLinear *s, char variavel);
int variavelJaCadastrada(SistemaLinear *s, char variavel, int limite);
void limparBufferEntrada();
int parseEquacao(char linha[], SistemaLinear *s, int linhaSistema);

int parseExpressaoLinear(char expr[], char variaveis[], int qtdVariaveis, double coeficientes[]);

int parseMatrizTexto(char linha[], Matriz *m, int linhasEsperadas, int colunasEsperadas);
void lerMatrizPorParsing(Matriz *m, int linhas, int colunas);

#endif