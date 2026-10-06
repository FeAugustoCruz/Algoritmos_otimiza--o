#define MAX_NAVIOS 60
#define MAX_BERCOS 13
#define ALFA 10
#define PES_FEC_BER 5
#define PES_PRAZO_NAV 5

#define MAX(X, Y) ((X > Y) ? X : Y)

typedef struct fSolucao
{
    int fo;
    int t_atracacao[MAX_BERCOS][MAX_NAVIOS];
    //quantidade de navios em cada berço
    int qtd_berco[MAX_BERCOS];
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
void calcular_FO(Solucao& s);
void escrever_FO(Solucao& s);
void gerar_vizinha(Solucao& s);
void heuristica_aleatoria(Solucao& s);
static void ordenar_por_chegada(int* ordem);
void heuristica_aleatoria_gulosa(Solucao& s);