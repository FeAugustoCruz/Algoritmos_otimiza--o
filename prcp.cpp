#include <stdio.h>
#include "prcp.h"
#include <time.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    srand(time(NULL));

    char arq[50];
    strcpy(arq, "inst3.txt");
    ler_dados(arq);
    
    /*Solucao solucao;
    for(int i = 0; i < num_pontos; i ++){
        solucao.vet_posi[i] = rand() % num_regiao;
    }

    strcpy(arq, "");
    testa_dados(arq);

    calcular_FO(solucao);
    escrever_FO(solucao);*/

    Solucao sra, srand, smm, spm, snd;
    heuristica_aleatoria(sra);
    memcpy(&srand, &sra, sizeof(Solucao));
    memcpy(&smm, &sra, sizeof(Solucao));
    memcpy(&spm, &sra, sizeof(Solucao));
    memcpy(&snd, &sra, sizeof(Solucao));

    printf("\n\nheuristica aleatoria (REF): %d\t", sra.fo);

    heu_bl_rand(srand, 10 * (num_pontos * num_regiao));
    printf("\n\nheuristica busca aleatoria (fo): %d\t", srand.fo);

    heu_bl_mm(smm);
    printf("\n\nheuristica melhor melhor (fo): %d\t", smm.fo);

    heu_bl_pm(spm);
    printf("\n\nheuristica primeiro melhor (fo): %d\t", spm.fo);

    heu_bl_nd_pm(snd);
    printf("\n\nheuristica primeiro melhor nao deterministico (fo): %d\t", snd.fo);


    return 0;
}

void heu_bl_rand(Solucao& s, const int inter)
{
    static Solucao s_aux; 

    INICIO:;

    for(int j = 0; j < inter; j ++){
        memcpy(&s_aux, &s, sizeof(Solucao));

        gerar_vizinha(s_aux);

        calcular_FO(s_aux);
        if (s_aux.fo < s.fo){
            memcpy(&s, &s_aux, sizeof(Solucao));
            goto INICIO;
        }

    }
}

void heu_bl_mm(Solucao& s)
{    
    int mel_fo, mel_pont, mel_regi;
    mel_fo = s.fo;
    while (1)
    {
        int flag = 0;
        for (int i = 0; i < num_pontos; i++)
        {
            int regi_ori = s.vet_posi[i];
            int fo_ori = s.fo;

            for(int j = 0; j < num_regiao; j ++){
                if(j != regi_ori){
                    s.vet_posi[i] = j;
                    calcular_FO(s);
                    if (s.fo < mel_fo){
                        mel_fo = s.fo;
                        mel_pont = i;
                        mel_regi = j;
                        flag = 1;
                    }
                }
            }
            s.vet_posi[i] = regi_ori;
            s.fo = fo_ori;
        }
        if (flag)
        {
            s.vet_posi[mel_pont] = mel_regi;
            s.fo = mel_fo;
        }else
        {
            break;
        }   
    }
    
    
}

void heu_bl_pm(Solucao& s)
{
    int mel_fo;
    INICIO:;
    
    mel_fo = s.fo;
    
    for (int i = 0; i < num_pontos; i++)
    {
        int regi_ori = s.vet_posi[i];
        int fo_ori = s.fo;

        for(int j = 0; j < num_regiao; j ++){
            if(j != regi_ori){
                s.vet_posi[i] = j;
                calcular_FO(s);
                if (s.fo < mel_fo){
                    s.vet_posi[i] = j;
                    goto INICIO;
                }
            }
        }
        s.vet_posi[i] = regi_ori;
        s.fo = fo_ori;
    }
}

void heu_bl_nd_pm(Solucao& s)
{
    int mel_fo, vet_aux[MAX_PONTOS];

    for(int i = 0; i < num_pontos; i ++)
    {
        vet_aux[i] = i;
    }

    INICIO:;
    
    mel_fo = s.fo;
    
    for (int i = 0; i < num_pontos; i++)
    {
        int pos = i + rand() % (num_pontos - i);
        int ponto = vet_aux[pos];

        int regi_ori = s.vet_posi[ponto];
        int fo_ori = s.fo;
        for(int j = 0; j < num_regiao; j ++){
            if(j != regi_ori){
                s.vet_posi[ponto] = j;
                calcular_FO(s);
                if (s.fo < mel_fo){
                    goto INICIO;
                }
            }
        }
        s.vet_posi[ponto] = regi_ori;
        s.fo = fo_ori;


        int aux = vet_aux[i];
        vet_aux[i] = vet_aux[pos];
        vet_aux[pos] = aux;

    }
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
