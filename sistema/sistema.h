#ifndef SISTEMA_H
#define SISTEMA_H
#include "../matriz/matriz.h"
#include <stdio.h>

#define TAM_LINHA 300

typedef enum{
   SI=0,
   SPI,
   SPD
}TipoSistema;

typedef struct{
   Matriz a;
   double b[MAX];
   char variaveis[MAX];
   TipoSistema tipo;
   double solucao[MAX];
   double constanteSPI[MAX];
   double coefParamSPI[MAX][MAX]; 
   int indiceParametroSPI[MAX];
   int qtdParametrosSPI;
}SistemaLinear;

void resolverSistema(SistemaLinear *s);
void lerSistema(SistemaLinear *s);
void escreveAumentada(SistemaLinear s);
void copiaParaAumentada(SistemaLinear s, Matriz *aumentada);
void resolverSPI(SistemaLinear *s, Matriz *aumentada);
void escreverNumeroFormatado(FILE *saida, double valor);
void escreverResultadoFormatado(FILE *saida, char variavel, double valor);

#endif
