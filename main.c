#include <stdio.h>
#include "matriz/matriz.h"
#include "sistema/sistema.h"
#include "transformacao/transformacao.h"
#include "base/base.h"
#include "autovalores/autovalores.h"
#include "diagonalizacao/diagonalizacao.h"

/* ════════════════════════════════════════════════════
   MAIN
   ════════════════════════════════════════════════════ */
int main(void) {
    Matriz A, B, C;
    int op;

    do {
        printf("\n╔════════════════════════════════════════╗\n");
        printf("║          ALGEBRA LINEAR                ║\n");
        printf("╠════════════════════════════════════════╣\n");
        printf("║  --- Entrada / Saida ---               ║\n");
        printf("║  1 - Ler Matriz A                      ║\n");
        printf("║  2 - Exibir Matriz A                   ║\n");
        printf("║  --- Operacoes ---                     ║\n");
        printf("║  3 - Resolucao de Sistema Linear       ║\n");
        printf("║  4 - Injetividade / Sobrejetividade    ║\n");
        printf("║  5 - Determinacao de Base              ║\n");
        printf("║  6 - Autovalores e Autovetores         ║\n");
        printf("║  7 - Diagonalizacao de Matriz          ║\n");
        printf("║  0 - Sair                              ║\n");
        printf("╚════════════════════════════════════════╝\n");
        printf("Opcao: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("Linhas de A (max %d): ", MAX);
                scanf("%d", &A.linhas);
                printf("Colunas de A (max %d): ", MAX);
                scanf("%d", &A.colunas);
                inicializarMatriz(&A);
                lerMatriz(&A);
                break;

            case 2:
                printf("\nMatriz A (%dx%d):\n", A.linhas, A.colunas);
                escreverMatriz(&A);
                break;

            case 3: {
                SistemaLinear s;
                lerSistema(&s);
                resolverSistema(&s);
                break;
            }

            case 4:
                verificarInjetividade(&A);
                break;

            case 5:
                determinarBase(&A);
                break;

            case 6:
                if (A.linhas != A.colunas) {
                    printf("Erro: A nao e quadrada (%dx%d).\n",
                           A.linhas, A.colunas);
                } else {
                    calcularAutovaloresAutovetores(&A);
                }
                break;

            case 7:
                if (A.linhas != A.colunas) {
                    printf("Erro: A nao e quadrada (%dx%d).\n",
                           A.linhas, A.colunas);
                } else {
                    diagonalizarMatriz(&A);
                }
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while (op != 0);

    return 0;
}
