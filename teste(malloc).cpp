#include <stdio.h>
#include <stdlib.h>//<- busca no diretório de instalção
#include <time.h>
#include "teste.h"//<- Busca no diretório do arquivo

#include <memory.h>

#define MOSTRAR_PRINTF

int main(void){

    //teste_alocacao();

    Solucao Sol1, Sol2;
    Sol1.fo = 1;
    Sol2.fo = 2;
    testar_estrutura(&Sol1, Sol2);// Usar * para alucação estática 


    //---------------------------------------------

    int mat3 [3][3];

    memset();


    //int aux

    for(int i = 0; i < 1000; i ++){
        int vet_sol[TAMANHO];//Para variavies primitivas como essa, é viável colocar a sua criação dentro do for!


    }

    return 0;
}


void teste_instalacao(){ 


    clock_t h;
    double tempo;

    h = clock();
    int **mat_a = (int**)malloc(TAMANHO * sizeof(int*));
    for (int i = 0; i < TAMANHO; i++){
        mat_a[i] = (int*)malloc(TAMANHO*sizeof(int*));
    }

    #ifdef MOSTRAR_PRINTF//if em tempo de execulção importante para otimização!


    for(int i  = 0; i < TAMANHO; i++){

        for(int j = 0; j < TAMANHO; j++){
            printf("%d", mat_a[i][j]);
        }
        printf("\n");
    }

    #endif

    for(int i = 0; i < TAMANHO; i++){

        free(mat_a[i]);

    }
    free(mat_a);
    tempo = ((double) clock() - h)/ CLOCKS_PER_SEC;// se a divisão não for exata perdemos precisão, logo devemos fazer um type casting para double
    printf("TEMPO M> %.5f\n", tempo);

}
void testar_estrutura(Solucao* s1, Solucao s2){

    //s1.fo = 10;
    //s2.fo = 20;

    s1 = s2;//ERRADO Não se pode fazer atribuição dessa forma para tipo composto.
    s1->fo = 50;
}

