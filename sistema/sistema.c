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
        for(int i = numVariaveis - 1; i >= 0; i--){
            s->solucao[i] = aumentada.valores[i][aumentada.colunas - 1];
            for(int j = i + 1; j < numVariaveis; j++){
                s->solucao[i] -= aumentada.valores[i][j] * s->solucao[j];
            }
            s->solucao[i] /= aumentada.valores[i][i];
        }
        printf("Solução do sistema:\n");
        for(int i = 0; i < s->a.colunas; i++)
            printf("%c = %.2f\n", s->variaveis[i], s->solucao[i]);
    }else if (s->tipo == SI){
        printf("O sistema é impossível (SI).\n");
    }else if (s->tipo == SPI){
        resolverSPI(s, &aumentada);
    }
}

void resolverSPI(SistemaLinear *s, Matriz *aumentada){
    int numVariaveis = s->a.colunas;
    int numEquacoes = s->a.linhas;

    int colunaPivo[MAX];
    int ehPivo[MAX] = {0};

    s->qtdParametrosSPI = 0;
    for(int i = 0; i < numVariaveis; i++){
        s->constanteSPI[i] = 0.0;
        for(int j = 0; j < numVariaveis; j++)
            s->coefParamSPI[i][j] = 0.0;
    }

    // Inicializa o vetor de colunas pivô
    for(int i = 0; i < MAX; i++){
        colunaPivo[i] = -1;
    }

    // Identifica as colunas que possuem pivô
    for(int i = 0; i < numEquacoes; i++){
        for(int j = 0; j < numVariaveis; j++){
            if(fabs(aumentada->valores[i][j]) > ZERO){
                colunaPivo[i] = j;
                ehPivo[j] = 1;
                break;
            }
        }
    }

    // Variáveis sem pivô viram parâmetros livres
    for(int j = 0; j < numVariaveis; j++){
        if(!ehPivo[j]){
            s->indiceParametroSPI[s->qtdParametrosSPI] = j;
            s->coefParamSPI[j][s->qtdParametrosSPI] = 1.0;
            s->qtdParametrosSPI++;
        }
    }

    // Resolve as variáveis dependentes de baixo para cima
    for(int i = numEquacoes - 1; i >= 0; i--){
        int col = colunaPivo[i];

        if(col == -1){
            continue;
        }

        double pivo = aumentada->valores[i][col];

        s->constanteSPI[col] = aumentada->valores[i][numVariaveis];

        for(int j = col + 1; j < numVariaveis; j++){
            s->constanteSPI[col] -= aumentada->valores[i][j] * s->constanteSPI[j];

            for(int p = 0; p < s->qtdParametrosSPI; p++){
                s->coefParamSPI[col][p] -= aumentada->valores[i][j] * s->coefParamSPI[j][p];
            }
        }

        s->constanteSPI[col] /= pivo;

        for(int p = 0; p < s->qtdParametrosSPI; p++){
            s->coefParamSPI[col][p] /= pivo;
        }
    }

    // Exibe a solução geral
    printf("O sistema e possivel e indeterminado (SPI).\n");
    printf("Solucao geral:\n");

    for(int j = 0; j < numVariaveis; j++){
        printf("%c = ", s->variaveis[j]);

        int escreveuAlgo = 0;

        if(fabs(s->constanteSPI[j]) > ZERO){
            printf("%.2lf", s->constanteSPI[j]);
            escreveuAlgo = 1;
        }

        for(int p = 0; p < s->qtdParametrosSPI; p++){
            double coef = s->coefParamSPI[j][p];

            if(fabs(coef) > ZERO){
                if(escreveuAlgo){
                    if(coef > 0){
                        printf(" + ");
                    }else{
                        printf(" - ");
                    }
                }else{
                    if(coef < 0){
                        printf("-");
                    }
                }

                if(fabs(fabs(coef) - 1.0) > ZERO){
                    printf("%.2lf", fabs(coef));
                }

                printf("%c", s->variaveis[s->indiceParametroSPI[p]]);
                escreveuAlgo = 1;
            }
        }

        if(!escreveuAlgo){
            printf("0");
        }

        printf("\n");
    }

    // Exibe os parâmetros usados
    printf("\nOnde ");

    for(int p = 0; p < s->qtdParametrosSPI; p++){
        printf("%c", s->variaveis[s->indiceParametroSPI[p]]);

        if(p < s->qtdParametrosSPI - 1){
            printf(", ");
        }
    }

    printf(" pertencem aos reais.\n");
}