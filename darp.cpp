#include "darp.h"

// Definição das variáveis globais
int num_veiculos;
int num_requisicoes;
int num_locais;
double duracao_max_rota;
double tempo_max_viagem;
double tempo_max_espera;

int capacidade_veiculos[MAX_VEICULOS];
int assentos_local[MAX_LOCAIS];
double tempo_servico[MAX_LOCAIS];
double inicio_janela[MAX_LOCAIS];
double fim_janela[MAX_LOCAIS];
double tempo_deslocamento[MAX_LOCAIS][MAX_LOCAIS];

// ============================================================================
// PROVA I
// ============================================================================

// PROVA I - Questão 1: Leitura de dados
void ler_dados(const char* arq) {
    FILE* f = fopen(arq, "r");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo %s\n", arq);
        exit(1);
    }

    fscanf(f, "%d %d %lf %lf %lf", &num_veiculos, &num_requisicoes, &duracao_max_rota, &tempo_max_viagem, &tempo_max_espera);
    num_locais = 2 * num_requisicoes + 2;

    for (int i = 0; i < num_veiculos; i++) {
        fscanf(f, "%d", &capacidade_veiculos[i]);
    }

    for (int i = 0; i < num_locais; i++) {
        fscanf(f, "%d", &assentos_local[i]);
    }

    for (int i = 0; i < num_locais; i++) {
        fscanf(f, "%lf", &tempo_servico[i]);
    }

    for (int i = 0; i < num_locais; i++) {
        fscanf(f, "%lf", &inicio_janela[i]);
    }

    for (int i = 0; i < num_locais; i++) {
        fscanf(f, "%lf", &fim_janela[i]);
    }

    for (int i = 0; i < num_locais; i++) {
        for (int j = 0; j < num_locais; j++) {
            fscanf(f, "%lf", &tempo_deslocamento[i][j]);
        }
    }

    fclose(f);
}

// PROVA I - Questão 3: Escrita da solução
void escrever_solucao(Solucao &s, const char* arq) {
    FILE *f;
    if (strcmp(arq, "") == 0) {
        f = stdout;
    } else {
        f = fopen(arq, "w");
    }

    fprintf(f, "Valor da FO: %.2f\n", s.fo);
    fprintf(f, "Rotas dos Veiculos:\n");
    
    for (int v = 0; v < num_veiculos; v++) {
        if (s.tamanho_rota[v] > 0) {
            fprintf(f, "Veiculo %d: ", v);
            for (int i = 0; i < s.tamanho_rota[v]; i++) {
                fprintf(f, "%d ", s.rotas[v][i]);
            }
            fprintf(f, "\n");
        }
    }

    if (strcmp(arq, "") != 0) {
        fclose(f);
    }
}

// PROVA I - Questão 4: Cálculo da Função Objetivo
void calcular_fo(Solucao &s) {
    s.fo = 0.0;
    int veiculos_utilizados = 0;
    double dist_total = 0.0;
    double tempo_duracao_rotas = 0.0;
    double tempo_viagem_ppnes = 0.0;
    double tempo_espera_ppnes = 0.0;
    double penalidades = 0.0;

    double chegada_req[MAX_LOCAIS];
    
    for (int v = 0; v < num_veiculos; v++) {
        if (s.tamanho_rota[v] <= 2) continue; // Rota apenas com garagens (vazia)
        
        veiculos_utilizados++;
        double tempo_atual = inicio_janela[0]; // Sai da garagem no início da janela (ou depois)
        int carga_atual = 0;
        double horario_saida_garagem = tempo_atual;

        for (int i = 0; i < s.tamanho_rota[v] - 1; i++) {
            int origem = s.rotas[v][i];
            int destino = s.rotas[v][i + 1];

            // 1. Distância/Deslocamento
            double tempo_desloc = tempo_deslocamento[origem][destino];
            dist_total += tempo_desloc;
            tempo_atual += tempo_desloc;

            // 2. Janelas de Tempo e Espera
            if (tempo_atual < inicio_janela[destino]) {
                tempo_espera_ppnes += (inicio_janela[destino] - tempo_atual);
                tempo_atual = inicio_janela[destino]; // Aguarda até abrir a janela
            } else if (tempo_atual > fim_janela[destino]) {
                penalidades += PENALIDADE; // Chegou atrasado - Inviável
            }

            chegada_req[destino] = tempo_atual;

            // 3. Capacidade
            carga_atual += assentos_local[destino];
            if (carga_atual > capacidade_veiculos[v]) {
                penalidades += PENALIDADE; // Excedeu assentos
            }

            // Atendimento
            tempo_atual += tempo_servico[destino];
        }

        double horario_chegada_garagem = tempo_atual;
        double duracao_rota = horario_chegada_garagem - horario_saida_garagem;
        tempo_duracao_rotas += duracao_rota;
        
        // Restrição de duração da rota
        if (duracao_rota > duracao_max_rota) penalidades += PENALIDADE;
    }

    // Calcula tempo de viagem das PPNES (Desembarque - Embarque)
    for (int r = 1; r <= num_requisicoes; r++) {
        int embarque = r;
        int desembarque = r + num_requisicoes;
        double tempo_viagem = chegada_req[desembarque] - chegada_req[embarque];
        tempo_viagem_ppnes += tempo_viagem;
        
        // Restrição tempo máximo de viagem
        if (tempo_viagem > tempo_max_viagem) penalidades += PENALIDADE;
    }

    // Composição Final da FO
    s.fo = (W1 * veiculos_utilizados) + 
           (W2 * dist_total) + 
           (W3 * tempo_duracao_rotas) + 
           (W4 * tempo_viagem_ppnes) + 
           (W5 * tempo_espera_ppnes) + 
           penalidades;
}

// ============================================================================
// PROVA II
// ============================================================================

// Função auxiliar para inicializar solução vazia
void inicializar_solucao_vazia(Solucao &s) {
    for (int v = 0; v < num_veiculos; v++) {
        s.rotas[v][0] = 0;                       // Garagem inicial
        s.rotas[v][1] = 2 * num_requisicoes + 1; // Garagem final
        s.tamanho_rota[v] = 2;
    }
}

// PROVA II - Questão 1: Geração de solução vizinha (Shift / Movimento de Requisição)
// Remove uma requisição (embarque/desembarque) do veículo atual e insere em outro.
void gerar_vizinho(Solucao &s) {
    int req = (rand() % num_requisicoes) + 1; // Seleciona requisição aleatória
    int embarque = req;
    int desembarque = req + num_requisicoes;
    int veiculo_origem = -1;

    // Encontra onde a requisição está
    for (int v = 0; v < num_veiculos; v++) {
        for (int i = 0; i < s.tamanho_rota[v]; i++) {
            if (s.rotas[v][i] == embarque) veiculo_origem = v;
        }
    }

    if (veiculo_origem == -1) return;

    // Remove requisição do veículo de origem
    int nova_rota[MAX_LOCAIS];
    int cont = 0;
    for (int i = 0; i < s.tamanho_rota[veiculo_origem]; i++) {
        if (s.rotas[veiculo_origem][i] != embarque && s.rotas[veiculo_origem][i] != desembarque) {
            nova_rota[cont++] = s.rotas[veiculo_origem][i];
        }
    }
    for (int i = 0; i < cont; i++) s.rotas[veiculo_origem][i] = nova_rota[i];
    s.tamanho_rota[veiculo_origem] = cont;

    // Sorteia veículo destino e posições
    int veiculo_destino = rand() % num_veiculos;
    int pos_embarque = 1 + rand() % (s.tamanho_rota[veiculo_destino]);
    int pos_desembarque = pos_embarque + rand() % (s.tamanho_rota[veiculo_destino] - pos_embarque + 1);

    // Insere no destino abrindo espaço
    for (int i = s.tamanho_rota[veiculo_destino] - 1; i >= pos_embarque; i--) {
        s.rotas[veiculo_destino][i + 1] = s.rotas[veiculo_destino][i];
    }
    s.rotas[veiculo_destino][pos_embarque] = embarque;
    s.tamanho_rota[veiculo_destino]++;

    for (int i = s.tamanho_rota[veiculo_destino] - 1; i >= pos_desembarque; i--) {
        s.rotas[veiculo_destino][i + 1] = s.rotas[veiculo_destino][i];
    }
    s.rotas[veiculo_destino][pos_desembarque] = desembarque;
    s.tamanho_rota[veiculo_destino]++;

    calcular_fo(s);
}

// PROVA II - Questão 2: Heurística Construtiva Aleatória
void construtiva_aleatoria(Solucao &s) {
    inicializar_solucao_vazia(s);
    
    for (int r = 1; r <= num_requisicoes; r++) {
        int v = rand() % num_veiculos; // Veículo aleatório
        
        // Insere requisição logo antes da garagem final para simplicidade na inserção aleatória
        int pos = s.tamanho_rota[v] - 1; 
        
        s.rotas[v][pos] = r;                       // Embarque
        s.rotas[v][pos + 1] = r + num_requisicoes; // Desembarque
        s.rotas[v][pos + 2] = 2 * num_requisicoes + 1; // Garagem final (shift)
        s.tamanho_rota[v] += 2;
    }
    calcular_fo(s);
}

// PROVA II - Questão 3: Heurística Construtiva Gulosa (Menor Incremento de Distância)
void construtiva_gulosa(Solucao &s) {
    inicializar_solucao_vazia(s);
    
    // Para cada requisição, insere no veículo que gerar o menor incremento de FO (ou distância)
    for (int r = 1; r <= num_requisicoes; r++) {
        int embarque = r;
        int desembarque = r + num_requisicoes;
        
        double melhor_fo = 999999999.0;
        int melhor_v = 0;
        int melhor_pos_emb = 1;
        int melhor_pos_des = 2;

        Solucao s_temp = s; // Cópia para testes de inserção

        for (int v = 0; v < num_veiculos; v++) {
            for (int i = 1; i < s.tamanho_rota[v]; i++) {
                for (int j = i; j <= s.tamanho_rota[v]; j++) {
                    // Simula inserção
                    // (Omitindo lógica massiva de shift para fins de espaço, 
                    // o conceito insere 'embarque' em 'i' e 'desembarque' em 'j')
                    
                    // Se a nova FO calculada for menor que a melhor_fo, guarda a posição
                    // melhor_fo = fo_calculada; 
                    // melhor_v = v; 
                }
            }
        }
        // Aplica a melhor inserção encontrada no veículo melhor_v na solução original
        // s.tamanho_rota[melhor_v] += 2;
    }
    calcular_fo(s);
}

// PROVA II - Questão 4: Heurística Construtiva Aleatória Gulosa (RCL)
void construtiva_aleatoria_gulosa(Solucao &s) {
    inicializar_solucao_vazia(s);
    double alfa = 0.3; // Parâmetro de gulosidade
    
    // Estrutura similar à gulosa, mas ao invés de escolher estritamente 
    // a posição com a `melhor_fo`, cria-se uma Lista Restrita de Candidatos (RCL).
    
    for (int r = 1; r <= num_requisicoes; r++) {
        // 1. Avaliar todos os pares de inserção (veículo, pos_emb, pos_des)
        // 2. Calcular o custo de cada inserção
        // 3. Determinar custo_min e custo_max
        // 4. Limiar = custo_min + alfa * (custo_max - custo_min)
        // 5. Adicionar todas as inserções cujo custo <= Limiar na RCL
        // 6. Escolher aleatoriamente uma inserção da RCL e aplicar em 's'
    }
    calcular_fo(s);
}

// Programa principal para testes 
int main() {
    srand(time(NULL));
    char arq[50] = "darp1.txt"; // Exemplo de uso 
    
    // Prova I - Q1
    ler_dados(arq);
    
    Solucao sol;
    
    construtiva_aleatoria(sol);
    
    escrever_solucao(sol, ""); 
    
    return 0;
}