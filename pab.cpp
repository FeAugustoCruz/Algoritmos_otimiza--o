#include <stdio.h>
#include "pab.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>

int main(void){
    srand(time(NULL));
    char arq[50];
    Solucao solucao;
    memset(&solucao, 0, sizeof(Solucao));

    strcpy(arq, "i01.txt");
    ler_dados(arq);
    for(int i = 0; i < num_berco; i ++){
        solucao.qtd_berco[i] = num_navio;
        for(int j = 0; j < num_navio; j ++){
            solucao.t_atracacao[i][j] = rand() % num_navio;
        }
    }


    //strcpy(arq, "");
    //testar_dados(arq);
    //calcular_FO(solucao);
    escrever_FO(solucao);

    /*printf("\n\nsolucao.qtd_berco\n");
    for(int i = 0; i < num_berco; i ++){
        printf("%d ", solucao.qtd_berco[i]);
    }
    printf("\n");
    printf("solucao.t_atracacao\n");
    for(int i = 0; i < num_berco; i ++){
        for(int j = 0; j < num_navio; j ++){
            printf("%d ", solucao.t_atracacao[i][j]);
        }
        printf("\n");
    }*/
    return 0;
}

int ler_dados(char* arq){
    FILE *f = fopen(arq, "r");
    fscanf(f, "%d  %d", &num_navio, &num_berco);

    for (int i = 0; i < num_berco; i++){
        for (int j = 0; j < num_navio; j ++){
            fscanf(f, "%d", &temp_atedimento[i][j]);
        }
    }

    for(int i = 0; i < num_berco; i ++){
        fscanf(f, "%d  %d", &aber_berco[i], &fecha_berco[i]);
    }

    for(int i = 0; i < num_navio; i ++){
        fscanf(f, "%d", &temp_chegada[i]);
    }

    for(int i = 0; i < num_navio; i ++){
        fscanf(f, "%d", &temp_saida[i]);
    }

    fclose(f);
}

int testar_dados(char* arq){
    FILE *f;
    if(strcmp(arq, "") == 0){
        f = stdout;
    }else{
        f = fopen(arq, "w");
    }
    fprintf(f,"\033[1mQtd Navios\tQtd de bercos\033[0m\n");
    fprintf(f, "%d\t%d\n", num_navio, num_berco);

    fprintf(f,"\033[1mTempo de cada embarcacao em cada berco: (t_atracacao)\033[0m\n");
    for (int i = 0; i < num_berco; i++){
        for (int j = 0; j < num_navio; j ++){
            fprintf(f, "%d ", temp_atedimento[i][j]);
        }
        fprintf(f, "\n");
    }


    fprintf(f, "\033[1mAbertura do berco x fechamento do berco (aber_berco, fecha_berco)\033[0m\n");
    for(int i = 0; i < num_berco; i ++){
        fprintf(f, "%d  %d\n", aber_berco[i], fecha_berco[i]);
    }

    fprintf(f, "\033[1mtempo chegada de cada embarcacao:(temp_chegada)\033[0m\n");
    for(int i = 0; i < num_navio; i ++){
        fprintf(f, "%d ", temp_chegada[i]);
    }

    fprintf(f, "\n");
    fprintf(f, "\033[1mtempo saida de cada embarcacao:(temp_saida)\033[0m\n");
    for(int i = 0; i < num_navio; i ++){
        fprintf(f, "%d ", temp_saida[i]);
    }

    fprintf(f, "\n");

    if(strcmp(arq, "") != 0){
        fclose(f);
    }   
}
  
void calcular_FO(Solucao& s){
    s.fo = 0;
    
    for(int b = 0; b < num_berco; b++){
        int hora = aber_berco[b];

        for(int i = 0; i < s.qtd_berco[b]; i++){
            int navio = s.t_atracacao[b][i];

            // Proteção: Berço incompatível (Tempo = 0)
            if(temp_atedimento[b][navio] == 0) {
                s.fo += 100000; // Penalidade pesada por atracação impossível
                continue;
            }

            if(temp_chegada[navio] > hora){
                printf("\n ->ENTROU NA CONDIÇÃO!\n");
                hora = temp_chegada[navio];
            }
            
            // CORREÇÃO: Matriz acessada na ordem correta [berço][navio]
            hora += temp_atedimento[b][navio];
            printf("\nHora nesse momento berco (%d) | navio (%d) | hora (%d)\n", b, navio, hora);
            // Adiciona o tempo de serviço daquele navio à FO total
            s.fo += hora - temp_chegada[navio];
            
            // CORREÇÃO: Subtração usando temp_saida, sem duplicação de MAX()
            if(hora > temp_saida[navio]){
                s.fo += PES_PRAZO_NAV * (hora - temp_saida[navio]);
            }
        }
        
        // CORREÇÃO: Apenas um check simples para fechamento, sem duplicação de MAX()
        if(hora > fecha_berco[b]){
            s.fo += PES_FEC_BER * (hora - fecha_berco[b]);
        }
    }
}

void escrever_FO(Solucao& s){
    printf("Funcao Objetivo: %d\n", s.fo);
    printf("Matriz de Atracacao:\n");

    for(int i = 0; i < num_berco; i++){
        for(int j = 0; j < s.qtd_berco[i]; j ++){
            printf("[%d] ", s.t_atracacao[i][j]);
        }
        printf("\n");
    }
}

void gerar_vizinha(Solucao& s){
    int b1, b2;
    do{
        b1 = rand() % num_berco;
    }while (s.qtd_berco[b1] == 0);
    

    int i1 = rand() % s.qtd_berco[b1];//sorteia a partir da quntidade de navios no berço

    int navio = s.t_atracacao[b1][i1];

    for(int k = i1; k < s.qtd_berco[b1] - 1; k ++){
        s.t_atracacao[b1][k] = s.t_atracacao[b1][k + 1];
    }
    s.qtd_berco[b1]--;

    int b2 = rand() % num_berco;
    int pos = rand() % (s.qtd_berco[b2] + 1);
    for(int k = s.qtd_berco[b2]; k > pos; k --){
        s.t_atracacao[b2][k] = s.t_atracacao[b2][k-1];
    }

    s.t_atracacao[b2][pos] = navio;
    s.qtd_berco[b2]++;
}

void heuristica_aleatoria(Solucao& s){
    memset(&s, 0, sizeof(Solucao));
 
    for(int n = 0; n < num_navio; n ++){
        int cand[MAX_BERCOS];
        int tam = 0;
        for(int b = 0; b < num_berco; b ++){
            if(temp_atedimento[b][n] != 0){
                cand[tam ++] = b;
            }
        }
 
        int b = (tam > 0) ? cand[rand() % tam] : rand() % num_berco;
        s.t_atracacao[b][s.qtd_berco[b] ++] = n;
    }
 
    calcular_FO(s);
}

static void ordenar_por_chegada(int* ordem){
    for(int i = 0; i < num_navio; i ++){
        ordem[i] = i;
    }
    for(int i = 1; i < num_navio; i ++){
        int x = ordem[i];
        int j = i - 1;
        while(j >= 0 && temp_chegada[ordem[j]] > temp_chegada[x]){
            ordem[j + 1] = ordem[j];
            j --;
        }
        ordem[j + 1] = x;
    }
}

void heuristica_gulosa(Solucao& s){
    memset(&s, 0, sizeof(Solucao));
 
    int ordem[MAX_NAVIOS];
    ordenar_por_chegada(ordem);
 
    for(int k = 0; k < num_navio; k ++){
        int n = ordem[k];
        int melhor_b = -1;
 
        for(int b = 0; b < num_berco; b ++){
            if(temp_atedimento[b][n] == 0) continue;     // berco incompativel
 
            if(melhor_b == -1 || temp_atedimento[b][n] < temp_atedimento[melhor_b][n]){
                melhor_b = b;                            // empate: fica o primeiro berco
            }
        }
 
        if(melhor_b == -1){
            melhor_b = rand() % num_berco;               // nenhum berco compativel
        }
        s.t_atracacao[melhor_b][s.qtd_berco[melhor_b] ++] = n;
    }
 
    calcular_FO(s);
}

void heuristica_aleatoria_gulosa(Solucao& s){
    memset(&s, 0, sizeof(Solucao));

    int ordem[MAX_NAVIOS];
    ordenar_por_chegada(ordem);

    for(int k = 0; k < num_navio; k ++){
        int n = ordem[k];

        // 1) menor e maior tempo de atendimento entre os berços compatíveis
        int tmin = 0, tmax = 0, qtd = 0;
        for(int b = 0; b < num_berco; b ++){
            int t = temp_atedimento[b][n];
            if(t == 0) continue;                         // berço incompatível

            if(qtd == 0 || t < tmin) tmin = t;
            if(qtd == 0 || t > tmax) tmax = t;
            qtd ++;
        }

        int escolhido;
        if(qtd == 0){
            escolhido = rand() % num_berco;              // nenhum berço compatível
        }else{
            // 2) monta a LRC: berços compatíveis "bons o suficiente"
            double limite = tmin + ALFA * (tmax - tmin);
            int lrc[MAX_BERCOS];
            int tam = 0;
            for(int b = 0; b < num_berco; b ++){
                int t = temp_atedimento[b][n];
                if(t != 0 && t <= limite){
                    lrc[tam ++] = b;
                }
            }
            // 3) sorteia um berço da LRC
            escolhido = lrc[rand() % tam];
        }

        s.t_atracacao[escolhido][s.qtd_berco[escolhido] ++] = n;
    }

    calcular_FO(s);
}