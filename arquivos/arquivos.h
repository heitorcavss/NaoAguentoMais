#ifndef ARQUIVOS_H
#define ARQUIVOS_H
#include <stdio.h>
#include "../sistema/sistema.h"

FILE *abrirArquivoSaida(const char *nomeArquivo);
void fecharArquivoSaida(FILE *f);
void gravarSistema(SistemaLinear *s, FILE *destino);
int lerSistemaDeArquivo(SistemaLinear *s, const char *nomeArquivo);

#endif
