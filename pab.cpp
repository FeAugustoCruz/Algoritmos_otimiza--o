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
        solucao.qtd_berco[i] = num_navio;
        for(int j = 0; j < num_navio; j ++){
            solucao.t_atracacao[i][j] = rand() % num_navio;
        }
    }


    strcpy(arq, "");
    testar_dados(arq);
    calcular_FO(solucao);
    //escrever_FO(solucao);

    printf("\n\nsolucao.qtd_berco\n");
    for(int i = 0; i < num_berco; i ++){
        printf("%d ", solucao.qtd_berco[i]);
    }
    printf("\n");
    printf("solucao.t_atracacao\n");
    for(int i = 0; i < num_berco; i ++){
        for(int j = 0; j < num_navio; j ++){
            printf("%d ", solucao.t_atracacao[i][j]);
        }
        printf("\n");
    }
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
    fprintf(f,"\033[1mQtd Navios\tQtd de bercos\033[0m\n");
    fprintf(f, "%d\t%d\n", num_navio, num_berco);

    fprintf(f,"\033[1mTempo de cada embarcacao em cada berco: (t_atracacao)\033[0m\n");
    for (int i = 0; i < num_berco; i++){
        for (int j = 0; j < num_navio; j ++){
            fprintf(f, "%d ", temp_atedimento[i][j]);
        }
        fprintf(f, "\n");
    }


    fprintf(f, "\033[1mAbertura do berco x fechamento do berco (aber_berco, fecha_berco)\033[0m\n");
    for(int i = 0; i < num_berco; i ++){
        fprintf(f, "%d  %d\n", aber_berco[i], fecha_berco[i]);
    }

    fprintf(f, "\033[1mtempo chegada de cada embarcacao:(temp_chegada)\033[0m\n");
    for(int i = 0; i < num_navio; i ++){
        fprintf(f, "%d ", temp_chegada[i]);
    }

    fprintf(f, "\n");
    fprintf(f, "\033[1mtempo saida de cada embarcacao:(temp_saida)\033[0m\n");
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
                printf("\n ->ENTROU NA CONDIÇÃO!\n");
                hora = temp_chegada[navio];
            }
            
            // CORREÇÃO: Matriz acessada na ordem correta [berço][navio]
            hora += temp_atedimento[b][navio];
            printf("\nHora nesse momento berco (%d) | navio (%d) | hora (%d)\n", b, navio, hora);
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

