#define MAX_CONFLI 4000
#define MAX_PONTOS 1000
#define MAX_REGI 4
#define ALFA 2

typedef struct fSolucao{
    int fo;
    int vet_posi[MAX_PONTOS];
}Solucao;

int num_pontos;
int num_regiao;
int mat_regiao[MAX_PONTOS*MAX_REGI][MAX_CONFLI];
int vet_num_conflitos[MAX_PONTOS*MAX_REGI];

void ler_dados(char* arq);
void testa_dados(char* arq);
void calcular_FO(Solucao& s);
void escrever_FO(Solucao& s);

void gerar_vizinha(Solucao& s);
void heuristica_aleatoria(Solucao& s);
void heuristica_gulosa(Solucao& s);
void heuristica_aleatoria_gulosa(Solucao& s);

void heu_bl_rand(Solucao& s, const int inter);
void heu_bl_mm(Solucao& s);
void heu_bl_pm(Solucao& s);
void heu_bl_nd_pm(Solucao& s);
