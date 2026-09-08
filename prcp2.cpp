#include <stdio.h>
#include "prcp2.h"
#include <time.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    srand(time(NULL));

    char arq[50];
    strcpy(arq, "inst1.txt");
    ler_dados(arq);
    
    Solucao solucao;
    for(int i = 0; i < num_pontos; i ++){
        solucao.vet_posi[i] = rand() % num_regiao;
    }

    strcpy(arq, "");
    testa_dados(arq);

    calcular_FO(solucao);
    escrever_FO(solucao);

    return 0;
}

void ler_dados(char* arq){
    FILE* f = fopen(arq, "r");

    memset(&mat_regiao, 0, sizeof(mat_regiao));

    fscanf(f,"%d", &num_pontos);
    fscanf(f, "%d", &num_regiao);
    for(int i = 0; i < num_pontos*num_regiao; i++){
        fscanf(f,"%d", &vet_num_conflitos[i]);
        for(int j = 0; j < vet_num_conflitos[i]; j ++){
            fscanf(f,"%d", &mat_regiao[i][j]);
        }
    }

    fclose(f);
}

void testa_dados(char* arq){
    FILE *f;
    
    if(strcmp(arq, "") == 0){
        f = stdout;
    }else{
        f = fopen(arq, "w");
    }
    fprintf(f,"%d\n", num_pontos);

    fprintf(f,"%d\n", num_regiao);
    for(int i = 0; i < num_pontos*num_regiao; i ++){
        fprintf(f,"%d\n", vet_num_conflitos[i]);
        for(int j = 0; j < vet_num_conflitos[i]; j ++){
            fprintf(f, "%d ", mat_regiao[i][j]);
        }
        fprintf(f, "\n");

    }

    if (strcmp(arq, "") != 0){
        fclose(f);
    }
}

void calcular_FO(Solucao& s){
    s.fo = 0;
    
    for(int i = 0; i< num_pontos; i ++){
        int regiao_i = i * num_regiao + s.vet_posi[i];

        bool conflito = 0;

        for (int k = 0; k < vet_num_conflitos[regiao_i]; k ++){
            int regiao_conf = mat_regiao[regiao_i][k];
            
            int ponto_conf    = regiao_conf / num_regiao;
            int posicao_conf  = regiao_conf % num_regiao;

            if(s.vet_posi[ponto_conf] == posicao_conf){
                conflito = 1;
            }

            //flag break
            if(conflito == 1){
                break;
            }
        }
        
        if(conflito){
            s.fo ++;
        }
    }
}

void escrever_FO(Solucao& s){
    printf("FO:%d\n", s.fo);
    for(int i = 0; i < num_pontos; i ++){
        printf("%d ", s.vet_posi[i]);
    }
}