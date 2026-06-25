#ifndef SISTEMA_H
#define SISTEMA_H

#include "../matriz/matriz.h"

typedef enum{
   SI=0,
   SPI,
   SPD
}TipoSistema;

typedef struct{
   Matriz a;
   double b[MAX];
   //int nomeDasVAR[MAX]; // 0 = x, 1 = y, 2 = z
   TipoSistema tipo;
}SistemaLinear;

void resolverSistema(SistemaLinear *s);
void lerSistema(SistemaLinear *s);
void escreveAumentada(SistemaLinear s);
void copiaParaAumentada(SistemaLinear s, Matriz *aumentada);

#endif
