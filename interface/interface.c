#include <stdio.h>
#include <stdlib.h>
#include "interface.h"


//# sao diretivas

void limparBufferEntrada(){
    int c;

    while((c = getchar()) != '\n' && c != EOF){
    }
}

void limparTela(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar(){
    int c;
    limparBufferEntrada(); //limpa o stdin
    printf("\nPressione ENTER para continuar...");
    getchar();                                     //espera enter
}

