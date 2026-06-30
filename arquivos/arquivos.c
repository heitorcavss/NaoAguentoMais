#include "arquivos.h"
#include <stdio.h>
#include <math.h>
#include "../parsing/ler.h"

FILE *abrirArquivoSaida(const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "a");
    if (!f)
        printf("Erro: nao foi possivel abrir o arquivo '%s'.\n", nomeArquivo);
    return f;
}

void fecharArquivoSaida(FILE *f) {
    fclose(f);
}

int lerSistemaDeArquivo(SistemaLinear *s, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro: nao foi possivel abrir o arquivo '%s'.\n", nomeArquivo);
        return 0;
    }

    fscanf(arquivo, "%d", &s->a.linhas);
    fscanf(arquivo, "%d", &s->a.colunas);

    for (int j = 0; j < s->a.colunas; j++)
        fscanf(arquivo, " %c", &s->variaveis[j]);

    int c;
    while ((c = fgetc(arquivo)) != '\n' && c != EOF);

    char linha[TAM_LINHA];
    for (int i = 0; i < s->a.linhas; i++) {
        if (!fgets(linha, TAM_LINHA, arquivo)) {
            printf("Erro: linhas insuficientes no arquivo.\n");
            fclose(arquivo);
            return 0;
        }
        if (!parseEquacao(linha, s, i)) {
            printf("Erro ao interpretar equacao %d do arquivo.\n", i + 1);
            fclose(arquivo);
            return 0;
        }
    }

    fclose(arquivo);
    return 1;
}

void gravarSistema(SistemaLinear *s, FILE *destino) {
    if (s->tipo == SPD) {
        for (int i = 0; i < s->a.colunas; i++)
            fprintf(destino, "%c = %.2f\n", s->variaveis[i], s->solucao[i]);
    } else if (s->tipo == SI) {
        fprintf(destino, "O sistema e impossivel (SI).\n");
    } else {
        int numVariaveis = s->a.colunas;
        fprintf(destino, "O sistema e possivel e indeterminado (SPI).\n");
        fprintf(destino, "Solucao geral:\n");

        for (int j = 0; j < numVariaveis; j++) {
            fprintf(destino, "%c = ", s->variaveis[j]);

            int escreveuAlgo = 0;

            if (fabs(s->constanteSPI[j]) > ZERO) {
                fprintf(destino, "%.2lf", s->constanteSPI[j]);
                escreveuAlgo = 1;
            }

            for (int p = 0; p < s->qtdParametrosSPI; p++) {
                double coef = s->coefParamSPI[j][p];

                if (fabs(coef) > ZERO) {
                    if (escreveuAlgo) {
                        if (coef > 0)
                            fprintf(destino, " + ");
                        else
                            fprintf(destino, " - ");
                    } else {
                        if (coef < 0)
                            fprintf(destino, "-");
                    }

                    if (fabs(fabs(coef) - 1.0) > ZERO)
                        fprintf(destino, "%.2lf", fabs(coef));

                    fprintf(destino, "%c", s->variaveis[s->indiceParametroSPI[p]]);
                    escreveuAlgo = 1;
                }
            }

            if (!escreveuAlgo)
                fprintf(destino, "0");

            fprintf(destino, "\n");
        }

        fprintf(destino, "\nOnde ");
        for (int p = 0; p < s->qtdParametrosSPI; p++) {
            fprintf(destino, "%c", s->variaveis[s->indiceParametroSPI[p]]);
            if (p < s->qtdParametrosSPI - 1)
                fprintf(destino, ", ");
        }
        fprintf(destino, " pertencem aos reais.\n");
    }

    fprintf(destino, "==============================================================\n");
    fprintf(destino, "\n");
}
