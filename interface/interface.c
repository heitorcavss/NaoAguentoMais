#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

//# sao diretivas

void limparTela(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  //limpa o stdin
    printf("\nPressione ENTER para continuar...");
    getchar();                                     //espera enter
}

