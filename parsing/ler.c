#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ler.h"
#include "../interface/interface.h"


void limparQuebraDeLinha(char str[]){
    int tam = strlen(str);

    if(tam > 0 && str[tam - 1] == '\n'){
        str[tam - 1] = '\0';
    }
}

void trocarVirgulaPorPonto(char str[]){
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] == ','){
            str[i] = '.';
        }
    }
}

int indiceVariavel(SistemaLinear *s, char variavel){
    for(int i = 0; i < s->a.colunas; i++){
        if(s->variaveis[i] == variavel){
            return i;
        }
    }

    return -1;
}

int variavelJaCadastrada(SistemaLinear *s, char variavel, int limite){
    for(int i = 0; i < limite; i++){
        if(s->variaveis[i] == variavel){
            return 1;
        }
    }

    return 0;
}

int parseLado(char expr[], SistemaLinear *s, int linhaSistema, int lado){
    int i = 0;

    while(expr[i] != '\0'){

        while(expr[i] == ' ' || expr[i] == '\t'){
            i++;
        }

        if(expr[i] == '\0'){
            break;
        }

        int sinal = 1;

        if(expr[i] == '+'){
            sinal = 1;
            i++;
        }else if(expr[i] == '-'){
            sinal = -1;
            i++;
        }

        while(expr[i] == ' ' || expr[i] == '\t'){
            i++;
        }

        if(expr[i] == '\0'){
            printf("Erro: sinal sem termo depois.\n");
            return 0;
        }

        double coeficiente = 1.0;
        int temNumero = 0;

        if(isdigit((unsigned char)expr[i]) || expr[i] == '.'){
            char *fimNumero;

            coeficiente = strtod(&expr[i], &fimNumero);

            if(fimNumero == &expr[i]){
                printf("Erro ao converter numero.\n");
                return 0;
            }

            i = fimNumero - expr;
            temNumero = 1;
        }

        while(expr[i] == ' ' || expr[i] == '\t'){
            i++;
        }

        if(expr[i] == '*'){
            if(!temNumero){
                printf("Erro: operador '*' sem coeficiente antes.\n");
                return 0;
            }

            i++;

            while(expr[i] == ' ' || expr[i] == '\t'){
                i++;
            }
        }

        if(isalpha((unsigned char)expr[i])){
            char variavel = expr[i];
            i++;

            int coluna = indiceVariavel(s, variavel);

            if(coluna == -1){
                printf("Erro: variavel '%c' nao foi cadastrada.\n", variavel);
                return 0;
            }

            s->a.valores[linhaSistema][coluna] += lado * sinal * coeficiente;

        }else if(temNumero){
            double constante = sinal * coeficiente;

            s->b[linhaSistema] -= lado * constante;

        }else{
            printf("Erro de sintaxe perto de '%c'.\n", expr[i]);
            return 0;
        }

        while(expr[i] == ' ' || expr[i] == '\t'){
            i++;
        }

        if(expr[i] != '\0' && expr[i] != '+' && expr[i] != '-'){
            printf("Erro de sintaxe perto de '%c'.\n", expr[i]);
            return 0;
        }
    }

    return 1;
}

int parseEquacao(char linha[], SistemaLinear *s, int linhaSistema){
    limparQuebraDeLinha(linha);
    trocarVirgulaPorPonto(linha);

    char *igual = strchr(linha, '=');

    if(igual == NULL){
        printf("Erro: a equacao precisa ter o sinal '='.\n");
        return 0;
    }

    *igual = '\0';

    char *ladoEsquerdo = linha;
    char *ladoDireito = igual + 1;

    for(int j = 0; j < s->a.colunas; j++){
        s->a.valores[linhaSistema][j] = 0.0;
    }

    s->b[linhaSistema] = 0.0;

    if(!parseLado(ladoEsquerdo, s, linhaSistema, 1)){
        return 0;
    }

    if(!parseLado(ladoDireito, s, linhaSistema, -1)){
        return 0;
    }

    return 1;
}

void lerSistemaPorEquacoes(SistemaLinear *s){
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
    printf("Exemplo: 2x + y - z = 4\n\n");

    for(int i = 0; i < s->a.linhas; i++){
        printf("Equacao %d: ", i + 1);

        fgets(linha, sizeof(linha), stdin);

        if(!parseEquacao(linha, s, i)){
            printf("Digite novamente a equacao %d.\n\n", i + 1);
            i--;
        }
    }
}

int parseExpressaoLinear(char expr[], char variaveis[], int qtdVariaveis, double coeficientes[]){
    int i = 0;

    limparQuebraDeLinha(expr);
    trocarVirgulaPorPonto(expr);

    for(int j = 0; j < qtdVariaveis; j++){
        coeficientes[j] = 0.0;
    }

    while(expr[i] != '\0'){

        while(expr[i] == ' ' || expr[i] == '\t'){
            i++;
        }

        if(expr[i] == '\0'){
            break;
        }

        int sinal = 1;

        if(expr[i] == '+'){
            sinal = 1;
            i++;
        }else if(expr[i] == '-'){
            sinal = -1;
            i++;
        }

        while(expr[i] == ' ' || expr[i] == '\t'){
            i++;
        }

        if(expr[i] == '\0'){
            printf("Erro: sinal sem termo depois.\n");
            return 0;
        }

        double coeficiente = 1.0;
        int temNumero = 0;

        if(isdigit((unsigned char)expr[i]) || expr[i] == '.'){
            char *fimNumero;

            coeficiente = strtod(&expr[i], &fimNumero);

            if(fimNumero == &expr[i]){
                printf("Erro ao converter numero.\n");
                return 0;
            }

            i = fimNumero - expr;
            temNumero = 1;
        }

        while(expr[i] == ' ' || expr[i] == '\t'){
            i++;
        }

        if(expr[i] == '*'){
            if(!temNumero){
                printf("Erro: operador '*' sem coeficiente antes.\n");
                return 0;
            }

            i++;

            while(expr[i] == ' ' || expr[i] == '\t'){
                i++;
            }
        }

        if(isalpha((unsigned char)expr[i])){
            char variavel = expr[i];
            int coluna = -1;

            i++;

            for(int j = 0; j < qtdVariaveis; j++){
                if(variaveis[j] == variavel){
                    coluna = j;
                    break;
                }
            }

            if(coluna == -1){
                printf("Erro: variavel '%c' nao foi cadastrada.\n", variavel);
                return 0;
            }

            coeficientes[coluna] += sinal * coeficiente;

        }else if(temNumero){
            printf("Erro: transformacao linear nao deve ter termo constante.\n");
            return 0;

        }else{
            printf("Erro de sintaxe perto de '%c'.\n", expr[i]);
            return 0;
        }

        while(expr[i] == ' ' || expr[i] == '\t'){
            i++;
        }

        if(expr[i] != '\0' && expr[i] != '+' && expr[i] != '-'){
            printf("Erro de sintaxe perto de '%c'.\n", expr[i]);
            return 0;
        }
    }

    return 1;
}

static int ehSeparadorMatriz(char c) {
    return c == ' ' || c == '\t' || c == '\n' ||
           c == ',' ||
           c == '[' || c == ']' ||
           c == '(' || c == ')' ||
           c == '{' || c == '}' ||
           c == '|';
}

int parseMatrizTexto(char linha[], Matriz *m, int linhasEsperadas, int colunasEsperadas) {
    char *p = linha;
    int linhaAtual = 0;
    int colunaAtual = 0;

    m->linhas = linhasEsperadas;
    m->colunas = colunasEsperadas;
    inicializarMatriz(m);

    while (*p != '\0') {
        while (*p != '\0' && ehSeparadorMatriz(*p)) {
            p++;
        }

        if (*p == '\0') {
            break;
        }

        if (*p == ';') {
            if (colunaAtual != colunasEsperadas) {
                printf("Erro: linha %d deveria ter %d valores.\n",
                       linhaAtual + 1, colunasEsperadas);
                return 0;
            }

            linhaAtual++;
            colunaAtual = 0;
            p++;
            continue;
        }

        if (colunaAtual == colunasEsperadas) {
            linhaAtual++;
            colunaAtual = 0;
        }

        if (linhaAtual >= linhasEsperadas) {
            printf("Erro: matriz tem mais linhas do que o esperado.\n");
            return 0;
        }

        char *fimNumero;
        double valor = strtod(p, &fimNumero);

        if (fimNumero == p) {
            printf("Erro de sintaxe perto de '%c'.\n", *p);
            return 0;
        }

        m->valores[linhaAtual][colunaAtual] = valor;
        colunaAtual++;

        p = fimNumero;
    }

    if (colunaAtual > 0) {
        if (colunaAtual != colunasEsperadas) {
            printf("Erro: linha %d deveria ter %d valores.\n",
                   linhaAtual + 1, colunasEsperadas);
            return 0;
        }

        linhaAtual++;
    }

    if (linhaAtual != linhasEsperadas) {
        printf("Erro: matriz deveria ter %d linhas, mas foram lidas %d.\n",
               linhasEsperadas, linhaAtual);
        return 0;
    }

    return 1;
}

void lerMatrizPorParsing(Matriz *m, int linhas, int colunas) {
    char linha[TAM_LINHA];

    limparBufferEntrada();

    printf("\nDigite a matriz %dx%d em uma unica linha.\n", linhas, colunas);
    printf("Exemplos aceitos:\n");
    printf("1 2; 3 4\n");
    printf("[[1,2],[3,4]]\n\n");

    while (1) {
        printf("Matriz: ");

        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            printf("Erro ao ler matriz.\n");
            return;
        }

        if (parseMatrizTexto(linha, m, linhas, colunas)) {
            break;
        }

        printf("Digite novamente.\n\n");
    }
}