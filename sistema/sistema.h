#ifndef SISTEMA_H
#define SISTEMA_H
#include "../matriz/matriz.h"

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
}SistemaLinear;

void resolverSistema(SistemaLinear *s);
void lerSistema(SistemaLinear *s);
void escreveAumentada(SistemaLinear s);
void copiaParaAumentada(SistemaLinear s, Matriz *aumentada);

#endif
