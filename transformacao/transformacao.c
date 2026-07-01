#include <stdio.h>
#include "transformacao.h"
#include "../parsing/ler.h"
#include "../interface/interface.h"
#include <ctype.h>

/*
logica de resolucao de questoes
1-  Ler dimensao do dominio e contradominio
2-  Ler matriz associada
3-  Escalonar a matriz associada
4-  Contar posto
5-  verificar comportamento

    Deve reponder:
    nucleo, imagem, (injetiva  sobrejetiva bijetiva)
*/

void lerTransformacao(Matriz *m) {
    char variaveis[MAX];
    char linha[TAM_LINHA];

    printf("\n--- Transformacao Linear  T: R^n -> R^m ---\n");

    printf("Sai de R^n  (n = dominio, max %d): ", MAX);
    scanf("%d", &m->colunas);

    if(m->colunas < 1 || m->colunas > MAX){
        printf("Erro: dimensao do dominio invalida.\n");
        return;
    }

    printf("Vai para R^m  (m = contradominio, max %d): ", MAX);
    scanf("%d", &m->linhas);

    if(m->linhas < 1 || m->linhas > MAX){
        printf("Erro: dimensao do contradominio invalida.\n");
        return;
    }

    inicializarMatriz(m);

    printf("\nInforme uma letra para cada variavel do dominio.\n");
    printf("Exemplo: x, y, z\n\n");

    for(int i = 0; i < m->colunas; i++){
        char variavel;

        printf("Nome da variavel %d: ", i + 1);
        scanf(" %c", &variavel);

        if(!isalpha((unsigned char)variavel)){
            printf("Erro: a variavel precisa ser uma letra.\n");
            i--;
            continue;
        }

        int repetida = 0;

        for(int j = 0; j < i; j++){
            if(variaveis[j] == variavel){
                repetida = 1;
                break;
            }
        }

        if(repetida){
            printf("Erro: a variavel '%c' ja foi cadastrada.\n", variavel);
            i--;
            continue;
        }

        variaveis[i] = variavel;
    }

    limparBufferEntrada();

    printf("\nDigite cada coordenada da transformacao.\n");
    printf("Exemplo para T(x,y,z) = (2x + y - z, x + 3z):\n");
    printf("Coordenada 1: 2x + y - z\n");
    printf("Coordenada 2: x + 3z\n\n");

    for(int i = 0; i < m->linhas; i++){
        printf("Coordenada %d: ", i + 1);

        fgets(linha, sizeof(linha), stdin);

        if(!parseExpressaoLinear(linha, variaveis, m->colunas, m->valores[i])){
            printf("Digite novamente a coordenada %d.\n\n", i + 1);
            i--;
        }
    }
}


int verificarInjetividade(Matriz *m){
    if(calcularPosto(m) == m->colunas) return 1;
    
    return 0;
}

int verificarSobrejetividade(Matriz *m){
    if(calcularPosto(m) == m->linhas) return 1;
    
    return 0; 
}


int verificaBijetividade(Matriz *m){
    if(verificarInjetividade(m) && verificarSobrejetividade(m)) return 1;

    return 0;
}

void relatorioTransformacao(Matriz *m){
    int posto = calcularPosto(m);
    
    printf("Relatorio da Transformacao Linear:\n");
    printf("Dimensao do nucleo: %d\n", m->colunas - posto);
    printf("Dimensao da imagem: %d\n", posto);
    printf("Matriz Associada:\n");
    escreverMatriz(m);
    printf("Injetiva: %s\n", verificarInjetividade(m) ? "Sim" : "Nao");
    printf("Sobrejetiva: %s\n", verificarSobrejetividade(m) ? "Sim" : "Nao");
    printf("Bijetiva: %s\n", verificaBijetividade(m) ? "Sim" : "Nao");

}


