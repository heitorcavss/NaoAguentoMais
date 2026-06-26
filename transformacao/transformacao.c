#include <stdio.h>
#include "transformacao.h"

/*
1-  Ler dimensao do dominio e contradominio
2-  Ler matriz associada
3-  Escalonar a matriz associada
4-  Contar posto
5-  nulidades
6-  verificar comportamento

    Deve reponder:
    nucleo, imagem, (injetiva  sobrejetiva bijetiva)
*/

void lerTransformacao(Matriz *m) {
    printf("\n--- Transformacao Linear  T: R^n -> R^m ---\n");

    printf("Sai de R^n  (n = dominio): ");
    scanf("%d", &m->colunas);     /* n -> COLUNAS */

    printf("Vai para R^m  (m = contradominio, max %d): ", MAX);
    scanf("%d", &m->linhas);      /* m -> LINHAS  */

    inicializarMatriz(m);

    printf("\nDigite os coeficientes (0 onde a variavel nao aparece):\n");
    for (int i = 0; i < m->linhas; i++) {
        printf("Coordenada de saida %d:\n", i + 1);
        for (int j = 0; j < m->colunas; j++) {
            printf("  coeficiente da variavel %d: ", j + 1);
            scanf("%lf", &m->valores[i][j]);
        }
    }
}


int verificarInjetividade(Matriz *m) {
    if(calcularPosto(m) == m->colunas){
        return 1;
    }
    return 0;
}

int verificarSobrejetividade(Matriz *m) {
    if(calcularPosto(m) == m->linhas){
        return 1;
    }
    return 0; 
}


int verificaBijetividade(Matriz *m){
    
    if(verificarInjetividade(m) && verificarSobrejetividade(m)) return 1;

    return 0;
    
    
}

void relatorioTransformacao(Matriz *m) {
    int posto = calcularPosto(m);
    
    printf("Relatório da Transformação Linear:\n");
    printf("Dimensão do núcleo: %d\n", m->colunas - posto);
    printf("Dimensão da imagem: %d\n", posto);
    printf("Matriz Associada:\n");
    escreverMatriz(m);
    printf("Injetiva: %s\n", verificarInjetividade(m) ? "Sim" : "Não");
    printf("Sobrejetiva: %s\n", verificarSobrejetividade(m) ? "Sim" : "Não");
    printf("Bijetiva: %s\n", verificaBijetividade(m) ? "Sim" : "Não");

}


