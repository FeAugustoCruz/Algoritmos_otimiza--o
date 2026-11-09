#ifndef DARP_H
#define DARP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_VEICULOS 100
#define MAX_REQUISICOES 100
#define MAX_LOCAIS (2 * MAX_REQUISICOES + 2) // 2 garagens + embarque/desembarque de cada requisição

// Pesos da Função Objetivo (conforme descrição)
#define W1 10.0 // Peso número de veículos
#define W2 1.0  // Peso distância/tempo de deslocamento
#define W3 1.0  // Peso duração da rota (HC - HS)
#define W4 1.0  // Peso tempo de viagem das PPNEs (HD - HE)
#define W5 1.0  // Peso tempo de espera das PPNEs
#define PENALIDADE 10000.0 // Penalidade para violação de restrições

// PROVA I - Questão 2: Estrutura de dados para armazenamento de uma solução
typedef struct fSolucao {
    double fo;
    int rotas[MAX_VEICULOS][MAX_LOCAIS]; // Matriz contendo a sequência de locais visitados por cada veículo
    int tamanho_rota[MAX_VEICULOS];      // Quantidade de locais visitados por cada veículo
} Solucao;

// PROVA I - Questão 1: Variáveis globais para armazenar os dados do problema
extern int num_veiculos;
extern int num_requisicoes;
extern int num_locais; 
extern double duracao_max_rota;
extern double tempo_max_viagem;
extern double tempo_max_espera;

extern int capacidade_veiculos[MAX_VEICULOS];
extern int assentos_local[MAX_LOCAIS];
extern double tempo_servico[MAX_LOCAIS];
extern double inicio_janela[MAX_LOCAIS];
extern double fim_janela[MAX_LOCAIS];
extern double tempo_deslocamento[MAX_LOCAIS][MAX_LOCAIS];

// Assinaturas PROVA I
void ler_dados(const char* arq);
void escrever_solucao(Solucao &s, const char* arq);
void calcular_fo(Solucao &s);

// Assinaturas PROVA II
void gerar_vizinho(Solucao &s);
void construtiva_aleatoria(Solucao &s);
void construtiva_gulosa(Solucao &s);
void construtiva_aleatoria_gulosa(Solucao &s);

void heu_bl_rand(Solucao& s, const int& inter);

#endif