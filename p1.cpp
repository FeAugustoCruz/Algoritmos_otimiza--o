#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "p1.h"

#define MAX(X,Y) ((X > Y) ? X : Y)

int main()
{
    srand(time(NULL));

    char arq[50];
    strcpy(arq, "instancia-toy.txt");
    ler_dados(arq);

    /*Solucao sol;
    sol.mat_sol[0][0] = 1;
    sol.mat_sol[0][1] = 3;
    sol.mat_sol[0][2] = 5;
    sol.vet_qtd[0] = 3;

    sol.mat_sol[1][0] = 2;
    sol.mat_sol[1][1] = 4;
    sol.vet_qtd[1] = 2;

    heu_con_gul(sol);
    calcular_fo(sol);
    strcpy(arq, "");
    escrever(sol, arq);
    

    gerar_vizinha(sol);
    calcular_fo(sol);
    escrever(sol, arq);*/
    static Solucao sra, srand, smm, spm, snd;
    printf("SOLUCAO ALEATORIA:\n");
    heuristica_aleatoria(sra);
    calcular_fo(sra);


    printf("orig (fo): %.2f\n", sra.fo);
    memcpy(&srand, &sra, sizeof(Solucao));
    memcpy(&smm, &sra, sizeof(Solucao));
    memcpy(&spm, &sra, sizeof(Solucao));
    memcpy(&snd, &sra, sizeof(Solucao));

    heu_bl_rand(srand, 3 * (num_cli * num_vei));
    printf("Solucao aleatoria (fo): %.2f\n", srand.fo);

    heu_bl_mm(smm);
    printf("Solucao melhor melhor (fo): %.2f\n", smm.fo);

    

    return 0;
}

void heu_bl_rand(Solucao& s, const int inter)
{   
    Solucao s_aux;

    INICIO:;

    for(int i = 0; i < inter; i++){
        memcpy(&s_aux, &s, sizeof(Solucao));
        gerar_vizinha(s_aux);

        calcular_fo(s_aux);
        if (s_aux.fo < s.fo){
            memcpy(&s, &s_aux, sizeof(Solucao));
            goto INICIO;

        }

    }

}

void heu_bl_mm(Solucao &s){
    static Solucao s_melhor, s_aux;

    double mel_fo;

    while (1)
    {
        int flag = 0;
        mel_fo = s.fo;

        memcpy(&s_melhor, &s, sizeof(Solucao));

        for(int i = 0; i < num_vei; i ++)
        {
            for(int j = 0; j < s.vet_qtd[i]; j ++)
            {
                int id = s.mat_sol[i][j];

                for(int l = 0; l < num_vei; l ++){
                    for (int k = 0; k < s.vet_qtd[i]; k++)
                    {
                        memcpy(&s_aux, &s, sizeof(Solucao));

                        remover_cli(s_aux, i, j);
                        inserir_cli_det(s_aux, l, k, id);
                        calcular_fo(s_aux);
                        if(s_aux.fo < mel_fo)
                        {
                            mel_fo = s_aux.fo;
                            flag = 1;
                            memcpy(&s_melhor, &s_aux, sizeof(Solucao));
                        }

                    }
                    
                }
            }
        }

        if (flag)
        {
            memcpy(&s, &s_melhor, sizeof(Solucao));
        }else
        {
            break;
        }
        
        
    }
    
}

void heu_bl_pm(Solucao& s)
{
    static Solucao s_melhor, s_aux;

    double mel_fo;

    int flag = 0;
    mel_fo = s.fo;

    INICIO:;

    memcpy(&s_melhor, &s, sizeof(Solucao));

    for(int i = 0; i < num_vei; i ++)
    {
        for(int j = 0; j < s.vet_qtd[i]; j ++)
        {
            int id = s.mat_sol[i][j];

            for(int l = 0; l < num_vei; l ++){
                for (int k = 0; k < s.vet_qtd[i]; k++)
                {
                    memcpy(&s_aux, &s, sizeof(Solucao));

                    remover_cli(s_aux, i, j);
                    inserir_cli_det(s_aux, l, k, id);
                    calcular_fo(s_aux);
                    if(s_aux.fo < mel_fo)
                    {
                        mel_fo = s_aux.fo;
                        memcpy(&s_melhor, &s_aux, sizeof(Solucao));
                        goto INICIO;
                    }

                }
                
            }
        }
    }
}

void heu_con_gul(Solucao& s){
    memset(&s.vet_qtd, 0, sizeof(s.vet_qtd));
    int vei = 0;
    for(int i = 0; i < num_cli; i ++){
        s.mat_sol[vei][s.vet_qtd[vei]] = i + 1;//->TAVA ERRADO
        s.vet_qtd[vei]++;
        vei++;
        if(vei == num_vei){
            vei = 0;
        }
    }
}

void gerar_vizinha(Solucao& s){//Escolhe um objeto e troque ele de mochila
    int op = rand() % 2;
    if(op == 0){
        int vOr, vDs;
        do{
            vOr = rand() % num_vei;
        }while (s.vet_qtd[vOr] == 0);
        int pos  = rand() % s.vet_qtd[vOr];//pegando uma cliente 
        int cli = s.mat_sol[vOr][pos];
        vDs = rand() % num_vei;
        //retirar cli de vOr e inserir em vDs
        remover_cli(s,vOr, pos);
        inserir_cli(s,vDs, cli);
    }else{
        int vOr, vDs;
        do
        {
            vOr = rand() % num_vei;
        } while (s.vet_qtd[vOr] == 0);
        do
        {
            vDs = rand() % num_vei;
        } while (s.vet_qtd[vDs] == 0);
        int pos_Or = rand() % s.vet_qtd[vOr];
        int pos_Ds = rand() % s.vet_qtd[vDs];
        int aux = s.mat_sol[vOr][pos_Or];
        s.mat_sol[vOr][pos_Or] = s.mat_sol[vDs][pos_Ds];
        s.mat_sol[vDs][pos_Ds] = aux;
        
    }

}

void remover_cli(Solucao& s, const int& vei, const int& pos){
    for(int i = pos; i < s.vet_qtd[vei] - 1; i++){
        s.mat_sol[vei][i] = s.mat_sol[vei][i + 1];
    }
    s.vet_qtd[vei]--;
}
void inserir_cli(Solucao& s, const int& vei, const int& cli){
    int pos = rand() % (s.vet_qtd[vei] + 1);
    for(int i = s.vet_qtd[vei]; i > pos; i --){
        s.mat_sol[vei][i] = s.mat_sol[vei][i-1];
    }
    s.mat_sol[vei][pos] = cli;
    s.vet_qtd[vei]++;

}
void calcular_fo(Solucao& s)
{
    s.fo = 0;
    for (int k = 0; k < num_vei; k++)
    {
        if (s.vet_qtd[k] == 0)
            continue;
        int carga = vet_demandas[0] + vet_demandas[s.mat_sol[k][0]];
        s.fo += mat_custo[0][s.mat_sol[k][0]];
        for (int i = 1; i < s.vet_qtd[k]; i++)
        {
            s.fo += mat_custo[s.mat_sol[k][i-1]][s.mat_sol[k][i]];
            carga += vet_demandas[s.mat_sol[k][i]];
        }
        s.fo += mat_custo[s.mat_sol[k][s.vet_qtd[k]-1]][0];
        //if (carga > vet_cap_vei[k])
        //    s.fo += PESO_CAP * (carga - vet_cap_vei[k]);
        s.fo += PESO_CAP * MAX(0, carga - vet_cap_vei[k]);
    }
}

void escrever(Solucao&s, char* arq)
{
    FILE* f;
    if (strcmp(arq, "") == 0)
        f = stdout;
    else
        f = fopen(arq, "w");
    fprintf(f, "FO: %.2f\n", s.fo);
    for (int k = 0; k < num_vei; k++)
    {
        int carga = vet_demandas[0];
        fprintf(f, "V %d -> 0 -> ", k + 1);
        for (int i = 0; i < s.vet_qtd[k]; i++)
        {
            fprintf(f, "%d -> ", s.mat_sol[k][i]);
            carga += vet_demandas[s.mat_sol[k][i]];
        }
        fprintf(f, "0\tCarga: %d\n", carga);
    }
    if (strcmp(arq, "") != 0)
        fclose(f);
}

void ler_dados(char* arq)
{
    int aux;
    int vet_X[MAX_CLI];
    int vet_Y[MAX_CLI];
    FILE* f = fopen(arq, "r");
    fscanf(f, "%d %d", &num_cli, &num_vei);
    for (int i = 0; i <= num_cli; i++)
        fscanf(f, "%d %d %d %d", &aux, &vet_X[i], &vet_Y[i], &vet_demandas[i]);
    for (int k = 0; k < num_vei; k++)
        fscanf(f, "%d", &vet_cap_vei[k]);
    fclose(f);
    //---
    for (int i = 0; i <= num_cli; i++)
        for (int j = 0; j <= num_cli; j++)
            mat_custo[i][j] = sqrt(
                (vet_X[i] - vet_X[j]) * (vet_X[i] - vet_X[j]) +
                (vet_Y[i] - vet_Y[j]) * (vet_Y[i] - vet_Y[j])
            );
	// Teste
    printf("%d %d\n", num_cli, num_vei);
    for (int i = 0; i <= num_cli; i++)
    {
        for (int j = 0; j <= num_cli; j++)
            printf("%.2f ", mat_custo[i][j]);
        printf("\n");
    }
}