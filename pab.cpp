#include <stdio.h>
#include "pab.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void){
    srand(time(NULL));
    char arq[50];
    Solucao solucao;


    strcpy(arq, "i01.txt");
    ler_dados(arq);

    for(int i = 0; i < num_berco; i ++){
        for(int j = 0; i < num_navio; j ++){
            solucao.t_atracacao[i][j] = rand() % MAX_NAVIOS;
        }
    }

    strcpy(arq, "");
    testar_dados(arq);

    return 0;
}

int ler_dados(char* arq){
    FILE *f = fopen(arq, "r");
    fscanf(f, "%d  %d", &num_navio, &num_berco);

    for (int i = 0; i < num_berco; i++){
        for (int j = 0; j < num_navio; j ++){
            fscanf(f, "%d", &temp_atedimento[i][j]);
        }
    }

    for(int i = 0; i < num_berco; i ++){
        fscanf(f, "%d  %d", &aber_berco[i], &fecha_berco[i]);
    }

    for(int i = 0; i < num_navio; i ++){
        fscanf(f, "%d", &temp_chegada[i]);
    }

    for(int i = 0; i < num_navio; i ++){
        fscanf(f, "%d", &temp_saida[i]);
    }

    fclose(f);
}

int testar_dados(char* arq){
    FILE *f;
    if(strcmp(arq, "") == 0){
        f = stdout;
    }else{
        f = fopen(arq, "w");
    }

    fprintf(f, "%d\t%d\n", num_navio, num_berco);

    for (int i = 0; i < num_berco; i++){
        for (int j = 0; j < num_navio; j ++){
            fprintf(f, "%d ", temp_atedimento[i][j]);
        }
        fprintf(f, "\n");
    }

    for(int i = 0; i < num_berco; i ++){
        fprintf(f, "%d  %d\n", aber_berco[i], fecha_berco[i]);
    }

    for(int i = 0; i < num_navio; i ++){
        fprintf(f, "%d ", temp_chegada[i]);
    }

    fprintf(f, "\n");

    for(int i = 0; i < num_navio; i ++){
        fprintf(f, "%d ", temp_saida[i]);
    }

    fprintf(f, "\n");

    if(strcmp(arq, "") != 0){
        fclose(f);
    }   

}
  
int calcular_FO(Solucao& s){
    s.fo = 0;
    for(int b = 0;b < ; b++){
        int hora = temp_chegada[];
        for(){

        }
    }
}