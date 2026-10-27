#ifndef PROVA3_H_INCLUDED
#define PROVA3_H_INCLUDED

#define MAX_NOS 250
typedef struct tSolucao
{
    int vet_sol[MAX_NOS]; // [num_hub | num_nos - num_hub]
    double fo;
}Solucao;

int num_nos;
int num_hub;
double mat_distancias[MAX_NOS][MAX_NOS];
double mat_custo[MAX_NOS][MAX_NOS];

//----------------------------------------------------------------------------------------------------------

void heu_bl_rand(Solucao& s, const int inter);
void heu_bl_mm(Solucao& s);
void heu_bl_pl(Solucao& s);
void heu_bl_pm_nd(Solucao& s);

//----------------------------------------------------------------------------------------------------------

void criar_solucao(Solucao& s);
void calcular_fo(Solucao& s);
void escrever_solucao(Solucao& s);
void testar_dados(char* arq);
void ler_dados(char* arq);

#endif
