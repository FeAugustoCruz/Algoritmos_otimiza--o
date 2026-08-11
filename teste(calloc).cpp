#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

#include "teste.h"

int main(void) {
    teste_instalacao();
    return 0;
}

void teste_instalacao() {

    int REP = 1000;
    clock_t h;
    double tempo;

    h = clock();

    int **mat_a = (int**)calloc(TAMANHO, sizeof(int *));

    for (int i = 0; i < TAMANHO; i++) {
        mat_a[i] = (int*)calloc(TAMANHO, sizeof(int));
    }

    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", mat_a[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < TAMANHO; i++) {
        free(mat_a[i]);
    }

    free(mat_a);

    tempo = ((double)(clock() - h)) / CLOCKS_PER_SEC;

    printf("TEMPO M> %.5f\n", tempo);


    clock_t h;
    double tempo;

    h = clock();

    for(int r = 0; r < REP; r ++){

        int mat_e[TAMANHO][TAMANHO];
        memset(&mat_e, 0, sizeof(mat_e));//-> vai zerar sequencialmente da posição de memória da váriavel até o bit terminador (funciona apenas para terinadores 0 ou -1 para limpar)
        
    }

    tempo = ((double)(clock() - h)) / CLOCKS_PER_SEC;

    printf("TEMPO M> %.5f\n", tempo);
}