//Número total de possíveis conflitos de cada região.
#define MAX_CONFLI 99
//Numero total de regiões (num_pont * num_posi)
#define MAX_REGIAO 100

typedef struct tSolucao{
    //posições da solução
    int vet_posi[25];
    int fo;
}Solucao;

typedef struct tConflito{
    //Número de comflitos para cada região de cada ponto.
    int num_conflito;
    int vet_id[MAX_CONFLI];
    
}Conflito;

Conflito conflitos[MAX_REGIAO];
//Quantidade de pontos no mapa. 
int num_pont;
//Quantodade de posições possíveis no caso 4.
int qtd_posi;


void ler_dados(char* arq);
void testar_dados(char* arq);
void escrever_solucao(Solucao& s);
void calcula_FO(Solucao& s);
void escrever_sol(Solucao& s);