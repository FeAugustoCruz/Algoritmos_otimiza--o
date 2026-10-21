#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <memory.h>

#include "p2.h"

#define MAX(X,Y)((X > Y) ? (X) : (Y))
#define MIN(X,Y)((X < Y) ? (X) : (Y))

int main()
{
    srand(time(NULL));
    char arq[50];
    strcpy(arq, "csp100.txt");
    ler_dados(arq);
    // strcpy(arq, "");
    // testar_dados(arq);
    num_tri = 0;
    for (int j = 0; j < num_tar; j++)
        num_tri += vet_hor_ter[j] - vet_hor_ini[j];
    num_tri = (num_tri / tem_nor) * 2;
    
    // printf("\n\nNUM TRIP: %d\n", num_tri);
    //------------------------------------------------------------------------------------------------------

    // UTILIZE ESSA AREA PARA TESTE

    static Solucao sra, srand, smm, spm;
    printf("\n\nSOLUCAO ALEATORIA\n");
    heu_cons_aleatoria(sra);
    calcular_fo(sra);


    printf("orig (fo): %d \n", sra.fo);
    memcpy(&srand, &sra, sizeof(Solucao));
    memcpy(&smm, &sra, sizeof(Solucao));
    memcpy(&spm, &sra, sizeof(Solucao));



    heu_bl_rand(srand, 200 * num_tri * num_tar);
    printf("busca local aleatoria (fo): %d\n", srand.fo);

    heu_bl_mm(smm);
    printf("busca melhor melhor (fo): %d\n", smm.fo);
    
    heu_bl_pm(spm);
    printf("busca primeiro melhor (fo): %d\n", spm.fo);

    return 0;
}

//----------------------------------------------------------------------------------------------------------

// INSIRA SEU CODIGO AQUI

void heu_bl_rand(Solucao& s, const int inter){
    Solucao s_aux;
    INICIO : ;
    for (int i = 0; i < inter; i++)
    {
        memcpy(&s_aux, &s, sizeof(Solucao));
        gerar_vizinha(s_aux);
        calcular_fo(s_aux);
        if (s_aux.fo < s.fo)
        {
            memcpy(&s, &s_aux, sizeof(Solucao));
            goto INICIO;
        }
    }
}

void heu_bl_mm(Solucao& s)
{
    static Solucao a_aux, melhor_sol;
    int melfo, id;
    while (1)
    {
        melfo = s.fo;
        memcpy(&melhor_sol, &s, sizeof(Solucao));

        int flag = 0;
        for(int j = 0; j < num_tri; j ++){
            for (int k = 0; k < s.vet_qtd[j]; k ++){
                id = s.mat_sol[j][k];
                for(int l = 0; l < num_tri; l ++){
                    if (l != j){

                        memcpy(&a_aux, &s, sizeof(Solucao));

                        remover_tarefa(a_aux, j, k);
                        inserir_tarefa(a_aux, l, id);

                        calcular_fo(a_aux);
                        if(a_aux.fo < melfo){
                            flag = 1;
                            melfo = a_aux.fo;
                            memcpy(&melhor_sol, &a_aux, sizeof(Solucao));
                        }
                    }
                }

            }
            
        }
        
        if (flag){
            memcpy(&s, &melhor_sol, sizeof(Solucao));
        }else{
            break;
        }
    }
     
}

void heu_bl_pm(Solucao& s)
{
    static Solucao a_aux;
    int melfo, id;
    
    INICIO:;
    melfo = s.fo;

    for(int j = 0; j < num_tri; j ++){
        for (int k = 0; k < s.vet_qtd[j]; k ++){
            id = s.mat_sol[j][k];
            for(int l = 0; l < num_tri; l ++){
                if (l != j){

                    memcpy(&a_aux, &s, sizeof(Solucao));

                    remover_tarefa(a_aux, j, k);
                    inserir_tarefa(a_aux, l, id);

                    calcular_fo(a_aux);
                    if(a_aux.fo < melfo){
                        melfo = a_aux.fo;
                        memcpy(&s, &a_aux, sizeof(Solucao));
                        goto INICIO;
                    }
                }
            }

        }
        
    }

     
}

void gerar_vizinha(Solucao& s)
{
    int tri_Or, tri_Ds, pos, tar;
    do
        tri_Or = rand() % num_tri;
    while (s.vet_qtd[tri_Or] == 0);
    pos = rand() % s.vet_qtd[tri_Or];
    tar = s.mat_sol[tri_Or][pos];
    do
        tri_Ds = rand() % num_tri;
    while (tri_Ds == tri_Or);
    remover_tarefa(s, tri_Or, pos);
    inserir_tarefa(s, tri_Ds, tar);
}

void heu_cons_aleatoria(Solucao& s)
{
    memset(&s.vet_qtd, 0, sizeof(s.vet_qtd));
    for (int j = 0; j < num_tar; j++)
    {
        int trip = rand() % num_tri;
        inserir_tarefa(s, trip, j);
    }
}

void heu_cons_gulosa_simples(Solucao& s)
{
    memset(&s.vet_qtd, 0, sizeof(s.vet_qtd));
    for (int j = 0; j < num_tar; j++)
    {
        int trip = j % num_tri;
        inserir_tarefa(s, trip, j);
    }
}

void heu_cons_gulosa(Solucao& s)
{
    memset(&s.vet_qtd, 0, sizeof(s.vet_qtd));
    for (int j = 0; j < num_tar; j++)
    {
        int trip = -1;
        for (int i = 0; i < num_tri; i++)
        {
            if (s.vet_qtd[i] == 0)
            {
                trip = i;
                break;
            }
            else
            {
                int pri_tar = s.mat_sol[i][0];
                int ult_tar = s.mat_sol[i][s.vet_qtd[i]-1];
                int hi = vet_hor_ini[pri_tar];
                int ht = vet_hor_ter[ult_tar];
                if ((vet_hor_ini[j] >= ht) && (vet_hor_ter[j] - hi <= tem_max))
                {
                    trip = i;
                    break;  
                }
            }
        }
        if (trip == -1)
        {
            trip = num_tri;
            num_tri++;
        }
        inserir_tarefa(s, trip, j);
    }
}


void heu_cons_ale_gul(Solucao& s, float per_ale)
{
    memset(&s.vet_qtd, 0, sizeof(s.vet_qtd));
    int qtd = MAX(1, per_ale / 100 * num_tar);
    for (int j = 0; j < num_tar; j++)
    {
        int trip = -1;
        for (int i = 0; i < num_tri; i++)
        {
            if (j < qtd)
            {
                trip = rand() % num_tri;
                break;
            }
            else if (s.vet_qtd[i] == 0)
            {
                trip = i;
                break;
            }
            else
            {
                int pri_tar = s.mat_sol[i][0];
                int ult_tar = s.mat_sol[i][s.vet_qtd[i]-1];
                int hi = vet_hor_ini[pri_tar];
                int ht = vet_hor_ter[ult_tar];
                if ((vet_hor_ini[j] >= ht) && (vet_hor_ter[j] - hi <= tem_max))
                {
                    trip = i;
                    break;  
                }
            }
        }
        if (trip == -1)
        {
            trip = num_tri;
            num_tri++;
        }
        inserir_tarefa(s, trip, j);
    }
}

//----------------------------------------------------------------------------------------------------------

void remover_tarefa(Solucao& s, const int& trip, const int& pos)
{
    for (int j = pos; j < s.vet_qtd[trip] - 1; j++)
        s.mat_sol[trip][j] = s.mat_sol[trip][j + 1];
    s.vet_qtd[trip]--;
}

int inserir_tarefa(Solucao& s, const int& trip, const int& tar)
{
    int j;
    for (j = s.vet_qtd[trip] - 1; j >= 0; j--)
    {
        int t = s.mat_sol[trip][j];
        if (vet_hor_ini[t] > vet_hor_ini[tar])
            s.mat_sol[trip][j + 1] = s.mat_sol[trip][j];
        else
            break;
    }
    s.mat_sol[trip][j + 1] = tar;
    s.vet_qtd[trip]++;

    if (j + 1 < s.vet_qtd[trip] - 1)
        return s.mat_sol[trip][j + 2];

    return -1;
}

void calcular_fo(Solucao& s)
{
    s.tri_uti = s.tem_oci = s.hor_ext = s.tem_sob = s.tem_exc = 0;
    for (int i = 0; i < num_tri; i++)
    {
        if (s.vet_qtd[i] == 0)
            continue;
        s.tri_uti++;
        int hi = vet_hor_ini[s.mat_sol[i][0]];
        for (int j = 1; j < s.vet_qtd[i]; j++)
        {
            s.tem_oci += MAX(0, vet_hor_ini[s.mat_sol[i][j]] - vet_hor_ter[s.mat_sol[i][j - 1]]);
            s.tem_sob += MAX(0, vet_hor_ter[s.mat_sol[i][j - 1]] - vet_hor_ini[s.mat_sol[i][j]]);
        }
        int hf = vet_hor_ter[s.mat_sol[i][s.vet_qtd[i] - 1]];
        s.tem_oci += MAX(0, tem_nor - (hf - hi));
        s.hor_ext += MIN((tem_max - tem_nor), MAX(0, (hf - hi) - tem_nor));
        s.tem_exc += MAX(0, (hf - hi) - tem_max);
    }
    s.fo = s.tri_uti * PES_TU + s.hor_ext * PES_HE + s.tem_oci * PES_TO + s.tem_sob * PES_TS + s.tem_exc * PES_TE;
}

void escrever_solucao(const Solucao& s, char* arq)
{
    FILE* f;
    if (strcmp(arq, "") == 0)
        f = stdout;
    else
        f = fopen(arq, "w");
    fprintf(f, "\n\nFO: %d\nTU: %d\nHE: %d\nTO: %d\nTS: %d\nTE: %d\n", s.fo, s.tri_uti, s.hor_ext, s.tem_oci, s.tem_sob, s.tem_exc);
    for (int i = 0; i < num_tri; i++)
    {
        fprintf(f, "\nTrip %-3d:\t", i + 1);
        for (int j = 0; j < s.vet_qtd[i]; j++)
            fprintf(f, "%d\t", s.mat_sol[i][j] + 1);
    }
    if (strcmp(arq, "") != 0)
        fclose(f);
}

void testar_dados(char* arq)
{
    FILE* f;
    if (strcmp(arq, "") == 0)
        f = stdout;
    else
        f = fopen(arq, "w");
    fprintf(f, "%d %d %d\n", num_tar, tem_nor, tem_max);
    for(int j = 0; j < num_tar; j++)
        fprintf(f, "%d\t%d\n", vet_hor_ini[j], vet_hor_ter[j]);
    if (strcmp(arq, "") != 0)
        fclose(f);
}

void ler_dados(char* arq)
{
    FILE* f = fopen(arq, "r");
    fscanf(f, "%d %d %d", &num_tar, &tem_nor, &tem_max);
    for(int j = 0; j < num_tar; j++)
        fscanf(f, "%d %d", &vet_hor_ini[j], &vet_hor_ter[j]);
    fclose(f);
}
