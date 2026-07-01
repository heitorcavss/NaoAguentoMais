#include <stdio.h>
#include "base.h"

/*
Base é quando satisfaz duas condições:
1. Conjunto tem q ser LI
2. N de vetores == dimensão
*/

void lerConjunto(Matriz *m){
    char coord[3] = {'x', 'y', 'z'};
    do{
        printf("Digite a quantidade de vetores do conjunto: ");
        scanf("%d", &m->linhas);
    }while(m->linhas < 1 || m->linhas > 3);

    do{
        printf("Digite a dimensao dos vetores do conjunto: ");
        scanf("%d", &m->colunas);
    }while(m->colunas < 1 || m->colunas > 3);
    

    for(int i = 0; i < m->linhas; i++) {
        printf("Digite as coordenadas do vetor %d :\n", i + 1);
        for(int j = 0; j < m->colunas; j++) {
            printf("Digite a coordenada %c: ", coord[j]);
            scanf("%lf", &m->valores[i][j]);
        }
    }

}

int ehBase(Matriz *m){ 
    int nVetores = m->linhas;
    int dimensao = m->colunas;
    int posto = calcularPosto(m);

    if(nVetores != dimensao) return 0; //easy
    if(nVetores != posto) return 0; //LI
    return 1;
    
}

void indicarSubconjunto(Matriz *m, int dimensao){
    Matriz n;
    n.linhas = 0;
    n.colunas = dimensao;
    for(int i = 0; i < m->linhas; i++){
        Matriz rascunho = n;
        for(int j = 0; j < m->colunas; j++){
            rascunho.valores[n.linhas][j] = m->valores[i][j];
        }
        rascunho.linhas = n.linhas + 1; //abre espaço para o próximo vetor
        if(calcularPosto(&rascunho) == rascunho.linhas){
            n = rascunho; //copia a matriz rascunho para a matriz valores n, e acrescenta uma linha a mais rasc = 1 e n = 1 (ja que copiou)
        }
    }

    if(n.linhas == dimensao){
        printf("O subconjunto de vetores que forma uma base eh:\n");
        escreverMatriz(&n);
    }else{
        printf("Nao foi possivel encontrar um subconjunto de vetores que forma uma base.\n");
    }
}

void determinarBase(Matriz *m){
    lerConjunto(m);

    if(ehBase(m)) {
        printf("O conjunto de vetores forma uma base.\n");
    } else {
        printf("O conjunto de vetores nao forma uma base.\n");
        indicarSubconjunto(m, m->colunas);
    }
}