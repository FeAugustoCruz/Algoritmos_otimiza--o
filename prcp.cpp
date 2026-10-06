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

    printf("=== Heuristica aleatoria ===\n");
    heuristica_aleatoria(solucao);
    calcular_FO(solucao);
    escrever_FO(solucao);

    printf("\n\n=== Heuristica gulosa ===\n");
    heuristica_gulosa(solucao);
    calcular_FO(solucao);
    escrever_FO(solucao);

    printf("\n\n=== Heuristica aleatoria gulosa (alfa = %.2f) ===\n", ALFA);
    heuristica_aleatoria_gulosa(solucao);
    calcular_FO(solucao);
    escrever_FO(solucao);

    printf("\n\n=== Vizinha da solucao anterior ===\n");
    gerar_vizinha(solucao);
    calcular_FO(solucao);
    escrever_FO(solucao);
    printf("\n");

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
            mat_regiao[i][j]--;   // o arquivo numera as regioes de 1 a N; internamente usamos 0 a N-1
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

// ---------------------------------------------------------------------------
// PROVA II
// ---------------------------------------------------------------------------


void gerar_vizinha(Solucao& s){
    if(num_regiao < 2){
        return;
    }

    int ponto = rand() % num_pontos;
    int nova  = rand() % (num_regiao - 1);

    // garante que a nova posicao e diferente da atual
    if(nova >= s.vet_posi[ponto]){
        nova ++;
    }
    s.vet_posi[ponto] = nova;
}


void heuristica_aleatoria(Solucao& s){
    for(int i = 0; i < num_pontos; i ++){
        s.vet_posi[i] = rand() % num_regiao;
    }
    calcular_FO(s);
}


static int conflitos_parciais(Solucao& s, int p, int pos){
    int regiao_p = p * num_regiao + pos;
    int qtd = 0;

    for(int k = 0; k < vet_num_conflitos[regiao_p]; k ++){
        int regiao_conf  = mat_regiao[regiao_p][k];
        int ponto_conf   = regiao_conf / num_regiao;
        int posicao_conf = regiao_conf % num_regiao;

        if(ponto_conf < p && s.vet_posi[ponto_conf] == posicao_conf){
            qtd ++;
        }
    }
    return qtd;
}

void heuristica_gulosa(Solucao& s){
    for(int i = 0; i < num_pontos; i ++){
        int melhor_pos = 0;
        int melhor_custo = conflitos_parciais(s, i, 0);

        for(int pos = 1; pos < num_regiao; pos ++){
            int custo = conflitos_parciais(s, i, pos);
            if(custo < melhor_custo){
                melhor_custo = custo;
                melhor_pos = pos;
            }
        }
        s.vet_posi[i] = melhor_pos;
    }
    calcular_FO(s);
}

void heuristica_aleatoria_gulosa(Solucao& s){
    int custo[MAX_REGI];
    int lrc[MAX_REGI];

    for(int i = 0; i < num_pontos; i ++){
        int cmin = 0, cmax = 0;

        for(int pos = 0; pos < num_regiao; pos ++){
            custo[pos] = conflitos_parciais(s, i, pos);
            if(pos == 0 || custo[pos] < cmin) cmin = custo[pos];
            if(pos == 0 || custo[pos] > cmax) cmax = custo[pos];
        }

        double limite = cmin + ALFA * (cmax - cmin);
        int tam = 0;
        for(int pos = 0; pos < num_regiao; pos ++){
            if(custo[pos] <= limite){
                lrc[tam ++] = pos;
            }
        }

        s.vet_posi[i] = lrc[rand() % tam];
    }
    calcular_FO(s);
}