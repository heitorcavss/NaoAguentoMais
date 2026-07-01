#include <stdio.h>
#include "matriz/matriz.h"
#include "sistema/sistema.h"
#include "transformacao/transformacao.h"
#include "base/base.h"
#include "autovalores/autovalores.h"
#include "diagonalizacao/diagonalizacao.h"
#include "parsing/ler.h"
#include "arquivos/arquivos.h"
#include "interface/interface.h"

int main() {
    Matriz A = {0};  // Inicializa a matriz A com zeros
    int op;

    do {
        limparTela();
        printf("╔════════════════════════════════════════╗\n");
        printf("║        ALGEBRA LINEAR - MENU           ║\n");
        printf("╠════════════════════════════════════════╣\n");
        printf("║  [ Matriz ]                            ║\n");
        printf("║  1 - Ler Matriz A                      ║\n");
        printf("║  2 - Exibir Matriz A                   ║\n");
        printf("╠════════════════════════════════════════╣\n");
        printf("║  [ Operacoes ]                         ║\n");
        printf("║  3 - Sistema Linear                    ║\n");
        printf("║  4 - Transformacao Linear              ║\n");
        printf("║  5 - Base de Espaco Vetorial           ║\n");
        printf("║  6 - Autovalores e Autovetores         ║\n");
        printf("║  7 - Diagonalizacao (2x2)              ║\n");
        printf("╠════════════════════════════════════════╣\n");
        printf("║  0 - Sair                              ║\n");
        printf("╚════════════════════════════════════════╝\n");
        printf("Opcao: ");
        scanf("%d", &op);

        switch (op){
            case 1:
                printf("Linhas de A (max %d): ", MAX);
                scanf("%d", &A.linhas);
                printf("Colunas de A (max %d): ", MAX);
                scanf("%d", &A.colunas);
                inicializarMatriz(&A);
                lerMatriz(&A);
                pausar();
                break;

            case 2:
                printf("\nMatriz A (%dx%d):\n", A.linhas, A.colunas);
                escreverMatriz(&A);
                pausar();
                break;

            case 3: {
                SistemaLinear s;
                int origem;
                printf("Origem do sistema: 1 - Teclado  2 - Arquivo: ");
                scanf("%d", &origem);
                if (origem == 2) {
                    char nomeArq[256];
                    printf("Nome do arquivo: ");
                    scanf(" %255s", nomeArq);
                    if (!lerSistemaDeArquivo(&s, nomeArq))
                        break;
                } else if( origem == 1) {
                    lerSistema(&s);
                } else {
                    printf("Opcao invalida!\n");
                    pausar();
                    break;
                }
                resolverSistema(&s);
                char resp;
                printf("\nDeseja salvar o resultado em arquivo? (s/n): ");
                scanf(" %c", &resp);
                if (resp == 's' || resp == 'S') {
                    FILE *arq = abrirArquivoSaida("resultados.txt");
                    if (arq) {
                        gravarSistema(&s, arq);
                        fecharArquivoSaida(arq);
                        printf("Resultado foi salvo!\n");
                    }
                } else if (resp != 'n' || resp == 'N'){
                    printf("Opcao Invalida!\n");
                    pausar();
                    break;
                }
                pausar();
                break;
            }

            case 4: {
                Matriz m;
                lerTransformacao(&m);
                relatorioTransformacao(&m);
                pausar();
                break;
            }

            case 5:
            {
                
                determinarBase(&A);
                pausar();
                break;
            }

            case 6: {
                Matriz m;
                calcularAutovaloresAutovetores(&m);
                pausar();
                break;
            }

            case 7: {
                Matriz m;
                diagonalizarMatriz(&m);
                pausar();
                break;
            }

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida.\n");
                pausar();
        }
    } while (op != 0);

    return 0;
}
