#define MAX_OBJ 500
#define MAX_MOC 50

typedef struct tSolucaoBIN{
    int mat_sol[MAX_MOC][MAX_OBJ];
    int fo;

}SolucaoBIN;

int num_obj;
int num_moc;

int vet_val_obj[MAX_OBJ];
int vet_pes_obj[MAX_OBJ];
int vet_cap_moc[MAX_MOC];
//-> Sempre usar procedimentos em vez de funções! pois funções alocam mais memória


void calcular_FOBIN(SolucaoBIN& s);
void escrever_solBIN(SolucaoBIN& s);//Sempre se for um parametro estático, deve ser por referência!
void testar_dados(char* arq);
void ler_dados(char* arq);
