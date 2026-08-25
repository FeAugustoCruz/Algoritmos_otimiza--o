#define MAX_OBJ 500
#define MAX_MOC 50

#define PESO_CAP 10//-> alfa da FO como (FO = FO alfa*4)
#define PESO_DUP 100

typedef struct tSolucaoBIN{
    int mat_sol[MAX_MOC][MAX_OBJ];
    int fo;

}SolucaoBIN;

typedef struct tSolucao{
    int vet_pesos[MAX_MOC];
    int vet_sol[MAX_OBJ];
    int fo;

}Solucao;

int num_obj;
int num_moc;

int vet_val_obj[MAX_OBJ];
int vet_pes_obj[MAX_OBJ];
int vet_cap_moc[MAX_MOC];
//-> Sempre usar procedimentos em vez de funções! pois funções alocam mais memória


void calcular_FO(Solucao& s);
void escrever_sol(Solucao& s);
void calcular_FOBIN(SolucaoBIN& s);
void escrever_solBIN(SolucaoBIN& s);//Sempre se for um parametro estático, deve ser por referência!
void testar_dados(char* arq);
void ler_dados(char* arq);
