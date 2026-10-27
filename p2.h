#define MAX_TAR 500 // maximo de tarefas

#define PES_TU 100   // peso para tripulacao utilizada
#define PES_HE 5     // peso para hora extra
#define PES_TO 1     // peso para tempo ocioso
#define PES_TS 1000  // peso para tempo de sobreposicao
#define PES_TE 1000  // peso para tempo excessivo

typedef struct tSolucao{
    int tri_uti;
    int hor_ext;
    int tem_oci;
    int tem_sob;
    int tem_exc;
    int mat_sol[MAX_TAR][MAX_TAR]; // matriz com a sequencia de tarefas (colunas) de cada tripulacao (linha)
    int vet_qtd[MAX_TAR];          // vetor com a quantidade de tarefas atendidas por cada tripulacao
    int fo;
}Solucao;

int num_tri;              // numero de tripulacoes (nao e dado como entrada, deve ser estimado)
int num_tar;              // numero de tarefas
int tem_nor;              // tempo normal de trabalho
int tem_max;              // tempo maximo de trabalho
int vet_hor_ini[MAX_TAR]; // vetor com o horario de inicio das tarefas
int vet_hor_ter[MAX_TAR]; // vetor com o horario de termino das tarefas
//----------------------------------------------------------------------------------------------------------

// INSIRA SEU CODIGO AQUI

void gerar_vizinha(Solucao& s);
void heu_cons_aleatoria(Solucao& s);
void heu_cons_gulosa_simples(Solucao& s);
void heu_cons_gulosa(Solucao& s);
void heu_cons_ale_gul(Solucao& s, float per_ale);

//----------------------------------------------------------------------------------------------------------
void remover_tarefa(Solucao& s, const int& trip, const int& pos); // remove a tarefa que esta na posicao pos da tripulacao trip
int inserir_tarefa(Solucao& s, const int& trip, const int& tar); // insere a tarefa tar na tripulacao trip (de forma ordenada)
void calcular_fo(Solucao& s);                                     // calcula a FO da solucao s
void escrever_solucao(const Solucao& s, char* arq);
void testar_dados(char* arq);
void ler_dados(char* arq);

//Heurística busca local aleatoria
void heu_bl_rand(Solucao& s, const int iter);
//Heurística busca local melhor dos melhor
void heu_bl_mm(Solucao& s);
//Heurística busca local primeiro melhor
void heu_bl_pm(Solucao& s);
void heu_bl_pm_nd(Solucao& s);
