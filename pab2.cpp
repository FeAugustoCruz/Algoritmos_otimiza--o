#include <stdio.h>
#include "pab2.h"
#include <stdlib.h>
#include <memory.h>
#include <time.h>

int main(void){
    srand(time(NULL));

    //nome do arquivo

    char arq[50];
    strcpy(arq, "i01.txt");
    ler_dados(arq);
    strcpy(arq, "");
    testa_dados(arq);
}


void ler_dados(char* arq){
    FILE* f = fopen(arq, "r");
    fscanf(f, "%d  %d", &num_navio, &num_berco);

    for(int i = 0; i < num_berco; i ++){
        for(int j = 0; j < num_navio; j ++){
            fscanf(f, "%d", &temp_atendimento[i][j]);
        }
    }

    for(int i = 0; i < num_berco; i ++){
        fscanf(f, "%d   %d", &aber_berco[i], &fecha_berco[i]);
    }

    for(int i = 0; i < num_navio; i ++){
        fscanf(f, "%d", &temp_chegada[i]);
    }

    for(int i = 0; i < num_navio; i ++){
        fscanf(f, "%d", &temp_saida[i]);
    }
    
}

void testa_dados(char* arq){
    FILE *f;
    
    if(strcmp(arq, "") == 0){
        f = stdout;
    }else{
        f = fopen(arq, "w");
    }

    fprintf(f, "%d\n", num_navio);
    fprintf(f, "%d\n", num_berco);

    for(int i = 0; i < num_berco; i ++){
        for(int j = 0; j < num_navio; j ++){
            fprintf(f, "%d ", temp_atendimento[i][j]);
        }
        fprintf(f,"\n");
    }

    fprintf(f,"\n");
    for(int i = 0; i < num_berco; i ++){
        fprintf(f, "%d   %d\n", aber_berco[i], fecha_berco[i]);
    }
    fprintf(f,"\n");
    for(int i = 0; i < num_navio; i ++){
        fprintf(f, "%d ", temp_chegada[i]);
    }
    fprintf(f,"\n");
    for(int i = 0; i < num_navio; i ++){
        fprintf(f, "%d ", temp_saida[i]);
    }
}