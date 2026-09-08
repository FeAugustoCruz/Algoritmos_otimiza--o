#define MAX_NAVIO 60
#define MAX_BERCO 13

#define PES_FEC_BER 5
#define PES_PRAZO_NAV 5

typedef struct fSolucao{
    int fo;
    int qtd_berco[MAX_BERCO];
    int mat_atracacao[MAX_BERCO][MAX_NAVIO];
}Solucao;

int num_navio;
int num_berco;
int fim_barco[MAX_BERCO];
int temp_atendimento[MAX_BERCO][MAX_NAVIO];
int aber_berco[MAX_BERCO];
int fecha_berco[MAX_BERCO];
int temp_chegada[MAX_NAVIO];
int temp_saida[MAX_NAVIO];


void ler_dados(char* arq);
void testa_dados(char* arq);