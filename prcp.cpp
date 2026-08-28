#include <stdio.h>
#include "prcp.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main(void){
    srand(time(NULL));

    //nome do arquivo
    char arq[50];
    strcpy(arq, "inst1.txt");
    ler_dados(arq);

    Solucao solucao;
    //Obtendo uma solução aleatória
    for(int i = 0; i < num_pont; i ++){
        solucao.vet_posi[i] = rand() % qtd_posi;
        printf("%d", solucao.vet_posi[i]);
    }

    //strcpy(arq, "");
    //testar_dados(arq);


    return 0;
}

void ler_dados(char* arq){
    FILE *f = fopen(arq, "r");
    fscanf(f, "%d", &num_pont);
    fscanf(f, "%d", &qtd_posi);

    for(int i = 0; i < MAX_REGIAO; i ++){
        fscanf(f, "%d", &conflitos[i].num_conflito);
        for(int j = 0; j < conflitos[i].num_conflito; j ++){
            fscanf(f, "%d", &conflitos[i].vet_id[j]);
            conflitos[i].vet_id[j]--;
        }
    }

}

void testar_dados(char* arq){
    FILE* f; 
    if (strcmp(arq, "") == 0){

        //-> saida no terminal
        f = stdout;
    }else{
        f = fopen(arq, "w");
    }

    fprintf(f, "%d\n", num_pont);
    fprintf(f, "%d\n", qtd_posi);

    for(int i = 0; i < MAX_REGIAO; i ++){
        fprintf(f,"%d\n", conflitos[i].num_conflito);
        for (int j = 0; j < conflitos[i].num_conflito; j++)
        {
            fprintf(f,"%d ", conflitos[i].vet_id[j] + 1);
        }
        printf("\n");
        
    }

    if (strcmp(arq, "") != 0){
        fclose(f);
    }
}

void calcula_FO(Solucao& s){
    s.fo = 0;
    for (int i = 0; i < num_pont; i++){
        int regiao_i = i * qtd_posi + s.vet_posi[i];

        bool livre = true;

        for (int k = 0; k < conflitos[regiao_i].num_conflito && livre; k++){
            int regiao_conf = conflitos[regiao_i].vet_id[k];

            int ponto_conf    = regiao_conf / qtd_posi;
            int posicao_conf  = regiao_conf % qtd_posi;

            if (s.vet_posi[ponto_conf] == posicao_conf){
                livre = false;
            }
        }

        if (livre){
            s.fo++;
        }
    }
}

void escrever_sol(Solucao& s){
    
}