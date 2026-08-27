#define MAX_CONFLI 99
//Numero total de regiões (num_pont * num_posi)
#define MAX_PONTS 100

typedef struct tSolucao{
    
    int fo;
}Solucao;

typedef struct tConflito{
    //Número de comflitos para cada região de cada ponto.
    int num_conflito;
    int vet_id[MAX_CONFLI];
    
}Conflito;

Conflito conflitos[MAX_PONTS]; 
int num_pont;
int num_posi;


void ler_dados(char* arq);
void testar_dados(char* arq);
void escrever_solucao(Solucao& s);