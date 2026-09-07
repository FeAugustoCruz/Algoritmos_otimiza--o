#include <stdio.h>
#include "pab.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>

int main(void){
    srand(time(NULL));
    char arq[50];
    Solucao solucao;
    memset(&solucao, 0, sizeof(Solucao));

    strcpy(arq, "i01.txt");
    ler_dados(arq);
    for(int i = 0; i < num_berco; i ++){
        solucao.qtd_berco[i] = rand() % num_berco;
        for(int j = 0; j < num_navio; j ++){
            solucao.t_atracacao[i][j] = rand() % MAX_NAVIOS;
        }
    }


    strcpy(arq, "");
    //testar_dados(arq);
    calcular_FO(solucao);
    escrever_FO(solucao);
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
  
void calcular_FO(Solucao& s){
    s.fo = 0;
    
    for(int b = 0; b < num_berco; b++){
        int hora = aber_berco[b];

        for(int i = 0; i < s.qtd_berco[b]; i++){
            int navio = s.t_atracacao[b][i];

            // Proteção: Berço incompatível (Tempo = 0)
            if(temp_atedimento[b][navio] == 0) {
                s.fo += 100000; // Penalidade pesada por atracação impossível
                continue;
            }

            if(temp_chegada[navio] > hora){
                hora = temp_chegada[navio];
            }
            
            // CORREÇÃO: Matriz acessada na ordem correta [berço][navio]
            hora += temp_atedimento[b][navio];
            
            // Adiciona o tempo de serviço daquele navio à FO total
            s.fo += hora - temp_chegada[navio];
            
            // CORREÇÃO: Subtração usando temp_saida, sem duplicação de MAX()
            if(hora > temp_saida[navio]){
                s.fo += PES_PRAZO_NAV * (hora - temp_saida[navio]);
            }
        }
        
        // CORREÇÃO: Apenas um check simples para fechamento, sem duplicação de MAX()
        if(hora > fecha_berco[b]){
            s.fo += PES_FEC_BER * (hora - fecha_berco[b]);
        }
    }
}

void escrever_FO(Solucao& s){
    printf("Funcao Objetivo: %d\n", s.fo);
    printf("Matriz de Atracacao:\n");

    for(int i = 0; i < num_berco; i++){
        for(int j = 0; j < s.qtd_berco[i]; j ++){
            printf("[%d] ", s.t_atracacao[i][j]);
        }
        printf("\n");
    }
}

