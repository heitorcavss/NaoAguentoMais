#include <stdio.h>
#include "sistema.h"
#include "../parsing/ler.h"
#include <math.h>
#include <ctype.h>


/* EXEMPLO 
{ 2x + y = 4
{ -x + 3y = 1
*/

void lerSistema(SistemaLinear *s){
    char linha[TAM_LINHA];

    printf("Digite o numero de equacoes: ");
    scanf("%d", &s->a.linhas);

    printf("Digite o numero de variaveis: ");
    scanf("%d", &s->a.colunas);

    printf("\nInforme uma letra para cada variavel.\n");
    printf("Exemplo: x, y, z ou a, b, c\n\n");

    for(int i = 0; i < s->a.colunas; i++){
        char variavel;

        printf("Nome da variavel %d: ", i + 1);
        scanf(" %c", &variavel);

        if(!isalpha((unsigned char)variavel)){
            printf("Erro: a variavel precisa ser uma letra.\n");
            i--;
            continue;
        }

        if(variavelJaCadastrada(s, variavel, i)){
            printf("Erro: a variavel '%c' ja foi cadastrada.\n", variavel);
            i--;
            continue;
        }

        s->variaveis[i] = variavel;
    }

    limparBufferEntrada();

    printf("\nDigite as equacoes.\n");
    printf("Exemplo: 2x + y - z = 4\n");
    printf("Tambem aceita: x + y = z + 5\n\n");

    for(int i = 0; i < s->a.linhas; i++){
        printf("Equacao %d: ", i + 1);

        fgets(linha, sizeof(linha), stdin);

        if(!parseEquacao(linha, s, i)){
            printf("Digite novamente a equacao %d.\n\n", i + 1);
            i--;
        }
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
    escalonarMatriz(&aumentada);
    
    printf("Matriz aumentada escalonada:\n");
    escreverMatriz(&aumentada);

    //3 Determinar o tipo do sistema
    int numVariaveis = s->a.colunas;
    int postoA = calcularPosto(&s->a);
    int postoAumentada = calcularPosto(&aumentada);
    
    if(postoA < postoAumentada){
        s->tipo = SI; //"tem solução?"
    }else if(postoA == numVariaveis){
        s->tipo = SPD; 
    }else{
        s->tipo = SPI;
    }
    //4 Resolver o sistema (se possível)

    if(s->tipo == SPD){
        double solucao[s->a.colunas];
        for(int i = numVariaveis - 1; i >= 0; i--){
            solucao[i] = aumentada.valores[i][aumentada.colunas - 1];
            for(int j = i + 1; j < numVariaveis; j++){
                solucao[i] -= aumentada.valores[i][j] * solucao[j];
            }
            solucao[i] /= aumentada.valores[i][i];
        }
        printf("Solução do sistema:\n");
        for(int i = 0; i < s->a.colunas; i++)
            printf("x%d = %.2f\n", i + 1, solucao[i]);
    }else if (s->tipo == SI){
        printf("O sistema é impossível (SI).\n");
    }else if (s->tipo == SPI){
        printf("O sistema é possível e indeterminado (SPI).\n");
    }
    
//Roger, faz o parsing na entrada a lógica do SPI, pra sair a expressão "universal"
//Vou tocar nas transf. lineares.
}
