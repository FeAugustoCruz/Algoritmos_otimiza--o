#define MAX_CONFLI 99
#define MAX_PONTOS 25
#define MAX_REGI 4

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