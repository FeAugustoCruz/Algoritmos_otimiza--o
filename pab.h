#define MAX_NAVIOS 60
#define MAX_BERCOS 13

typedef struct fSolucao
{
    int fo;
    int t_atracacao[MAX_BERCOS][MAX_NAVIOS];
    int qtd_berco[MAX_NAVIOS];
}Solucao;


int num_navio;
int num_berco;
int fim_barco[MAX_BERCOS];

int temp_atedimento[MAX_BERCOS][MAX_NAVIOS];
int aber_berco[MAX_BERCOS];
int fecha_berco[MAX_BERCOS];
int temp_chegada[MAX_NAVIOS];
int temp_saida[MAX_NAVIOS];

int ler_dados(char* arq);
int testar_dados(char* arq);
int calcular_FO(Solucao& s);