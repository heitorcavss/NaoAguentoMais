#include <stdio.h>
#include "sistema.h"

/* EXEMPLO 
{ 2x + y = 4
{ -x + 3y = 1
*/

void lerSistema(SistemaLinear *s){
    printf("Digite o numero de linhas: ");
    scanf("%d", &s->a.linhas);
    printf("Digite o numero de colunas: ");
    scanf("%d", &s->a.colunas);

    printf("Digite os elementos da matriz dos coeficientes (linha a linha):\n");
    for(int i = 0; i < s->a.linhas; i++){
        printf("EQUAÇÃO %d: \n", i + 1);
        for (int j = 0; j < s->a.colunas; j++) {
            printf("Digite o coeficiente de x%d: ", j + 1);
            scanf("%lf", &s->a.valores[i][j]);
        }
        printf("Digite o termo independente: ");
        scanf("%lf", &s->b[i]);
    }
}

void escreveAumentada(SistemaLinear s){
    for(int i = 0; i < s.a.linhas; i++){
        printf("| ");
        for(int j = 0; j < s.a.colunas; j++){
            printf("%8.2lf ", s.a.valores[i][j]);
        }
        printf("| %8.2lf |\n", s.b[i]);
    }
    printf("\n");
}

void copiaParaAumentada(SistemaLinear s, Matriz *aumentada){
    aumentada->linhas = s.a.linhas;
    aumentada->colunas = s.a.colunas + 1;

    for(int i = 0; i < s.a.linhas; i++){
        for(int j = 0; j < s.a.colunas; j++){
            aumentada->valores[i][j] = s.a.valores[i][j];
        }
        aumentada->valores[i][s.a.colunas] = s.b[i];
    }
}

void resolverSistema(SistemaLinear *s){
    printf("Matriz aumentada:\n");
    escreveAumentada(*s); 
    printf("\n\n");
    Matriz aumentada;
    copiaParaAumentada(*s, &aumentada);

    //2 Escalonar
        for(int i = 0; i < aumentada.linhas; i++){
            for(int k = i + 1; k < aumentada.linhas; k++){
            double fator = aumentada.valores[k][i] / aumentada.valores[i][i]; //oq eu zero/pivo
                for(int l = i; l < aumentada.colunas; l++){
                    aumentada.valores[k][l] -= fator * aumentada.valores[i][l];
                }
            }
        }
    
    printf("Matriz aumentada escalonada:\n");
    escreverMatriz(&aumentada);

    //3 Determinar o tipo do sistema
    s->tipo = SPD;
    for(int i = 0; i < aumentada.linhas; i++){
        int soZeros = 1;
        for(int j = 0; j < aumentada.colunas - 1; j++){
            if(aumentada.valores[i][j] != 0){
                soZeros = 0;
                break;
            }
        }
        if(soZeros && aumentada.valores[i][aumentada.colunas - 1] != 0){
            s->tipo = SI; 
            break;
        }else if(soZeros && aumentada.valores[i][aumentada.colunas - 1] == 0){
            s->tipo = SPI; 
        }
    }
    //4 Resolver o sistema (se possível)

    if(s->tipo == SPD){
        double solucao[s->a.colunas];
        for(int i = aumentada.linhas - 1; i >= 0; i--){
            solucao[i] = aumentada.valores[i][aumentada.colunas - 1];
            for(int j = i + 1; j < aumentada.colunas - 1; j++){
                solucao[i] -= aumentada.valores[i][j] * solucao[j];
            }
            solucao[i] /= aumentada.valores[i][i];
        }
    }

}
