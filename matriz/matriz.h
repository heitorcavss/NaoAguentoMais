#ifndef MATRIZ_H
#define MATRIZ_H
#define ZERO 0.000000001
#define MAX 4

typedef struct {
    int linhas;
    int colunas;
    double valores[MAX][MAX];
    double determinante;
} Matriz;

void inicializarMatriz(Matriz *m);
void lerMatriz(Matriz *m);
void escreverMatriz(Matriz *m);
double calcularDeterminante(Matriz *m);
int calcularPosto(Matriz *m); //retorna posto
int escalonarMatriz(Matriz *m); //retorna o numero de trocas de linha para calculo do det.
int contarPivos(Matriz *m);
int calcularPosto(Matriz *m);



#endif
