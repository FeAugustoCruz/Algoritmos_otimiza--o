#include <stdio.h>
#include <string.h>
#include <memory.h>
#include "pnm.h"
#include <time.h>
#include <stdlib.h>

#define MAX(X, Y) ((X > Y) ? X : Y)//condição ternária (mais rápida de ser execultada)

int main(void){
    srand(time(NULL));//colocar apenas uma vez no main!


    char arq[50];
    strcpy(arq, "pmm3.txt");//Vai copiar o texto pnm1 para o array arq!
    //OBS caso de erro coloque "..//" para sair do diretório e entrar em outro
    ler_dados(arq);
    //strcpy(arq, "");
    //testar_dados(arq);

    SolucaoBIN solB;
    memset(&solB, 0, sizeof(SolucaoBIN));//Vai zerar a matriz inteira! função conhecida como (zero-biting)
    for(int i = 0; i < num_moc; i ++){
        for(int j = 0; j < num_obj; j++){
            solB.mat_sol[i][j] = rand() % 2;
        }
    }

    clock_t h1;
    h1 = clock();
    for (int r = 0; r < 100; r++){
        calcular_FOBIN(solB);
    }

    double tempo1 = ((double)(clock() - h1)) / CLOCKS_PER_SEC;
    printf("FO %d\tTempo: %.5f\n", solB.fo, tempo1);
    //escrever_solBIN(solB);
    printf("\n");

    Solucao sol;
    for(int j = 0; j < num_obj; j ++){
        sol.vet_sol[j] = rand() % (num_moc + 1) - 1;
    }

    clock_t h;
    h = clock();
    for (int r = 0; r < 100; r++){
        calcular_FO(sol);
    }

    double tempo = ((double)(clock() - h)) / CLOCKS_PER_SEC;
    printf("FO %d\tTempo: %.5f\n", sol.fo, tempo);
    return 0;

    escrever_sol(sol);
}

void calcular_FOBIN(SolucaoBIN& s){

    s.fo = 0;
    for(int i = 0; i < num_moc; i ++){
        int peso = 0;
        for (int j = 0; j < num_obj; j ++){
            /*if(s.mat_sol[i][j] == 1){
                s.fo += vet_val_obj[j];
            }*/

            s.fo += vet_val_obj[j] * s.mat_sol[i][j];//-> Mais rápido do que a condicional!
            peso += vet_pes_obj[j] * s.mat_sol[i][j];
        }

        s.fo -= PESO_CAP * MAX(0, peso - vet_cap_moc[i]);
        //Essa condição max, retorna ZERO se o valor não passar da capacidade isso é se pesso < vet_..
        //Essa condição max, retorna um valor > 0 se o valor passar da capacidade isso é pesso > vet_..
        /*if (peso > vet_cap_moc[i])
        {
            s.fo -= PESO_CAP * (peso - vet_cap_moc[i]);//-> Pesso que passa em relação a capacidade da mochila 
        }*/

    }
    for (int j = 0; j < num_obj; j ++){
        int qtd = 0;
        for(int i = 0; i < num_moc; i ++){
            qtd += s.mat_sol[i][j];
        }
        s.fo -= PESO_DUP * MAX(0, qtd - 1);//-> Nessa parte verificamos se o obj esta em mais de uma se qtd for 2 (maximo possivel pois temos duas mochilas) qtd - 1é maior que 0 logo a multiplicação vai acontecer e o valor será inflado!
    }
}

void escrever_solBIN(SolucaoBIN& s){
    printf("\n\nFO: %d\n", s.fo);

    for(int i = 0; i < num_moc; i ++){

        for(int j = 0; j < num_obj; j ++){
            printf("%d ", s.mat_sol[i][j]);
        }
        printf("\n");
    }

}

void ler_dados(char* arq){
    FILE* f = fopen(arq, "r");
    fscanf(f, "%d %d", &num_obj, &num_moc);//-> Le os dois primeiros inteiros 
    for(int j = 0;  j < num_obj; j++){
        fscanf(f, "%d", &vet_val_obj[j]);//Lê a primeira linha do vetor (pula automaticamente para  aproxima linha! o flag espera um inteiro e pula)
    }

    for(int j = 0;  j < num_obj; j++){
        fscanf(f, "%d", &vet_pes_obj[j]);
    }

    for(int i = 0;  i < num_moc; i++){
        fscanf(f, "%d", &vet_cap_moc[i]);
    }

    fclose(f);
}

void testar_dados(char* arq){
    FILE* f; 
    if (strcmp(arq, "") == 0){//-> strcmp compara duas strings
        f = stdout;//vai endereçar a sua tela primp para análise, ou seja, os dados o aqruivo vão ser direicionados para a tela. Isso é um "tast flag"

    }else{
        f = fopen(arq, "w");//"w" para leitura
    }
    fprintf(f, "%d %d\n", num_obj, num_moc);//-> Le os dois primeiros inteiros 
    for(int j = 0;  j < num_obj; j++){
        fprintf(f, "%d ", vet_val_obj[j]);//Le 
    }
    fprintf(f, "\n");

    for(int j = 0;  j < num_obj; j++){
        fprintf(f, "%d ", vet_pes_obj[j]);
    }
    fprintf(f, "\n");

    for(int i = 0;  i < num_moc; i++){
        fprintf(f, "%d ", vet_cap_moc[i]);
    }

    if (strcmp(arq, "") != 0){//-> vai verificar se é um arquivo ou a tela, se for != "" temos um arquivo texto logo temos que fechar
        fclose(f);
    }
}

void calcular_FO(Solucao& s){

    s.fo = 0;
    memset(&s.vet_pesos, 0, sizeof(s.vet_pesos));
    for(int j = 0; j < num_obj; j ++){
        
        int moc = s.vet_sol[j];
        if (moc == -1){
            continue;//Pula tudo e vai para próxima iteração do laço!

        }
        s.fo += vet_val_obj[j];
        s.vet_pesos[moc] += vet_pes_obj[j];
    }
    for(int i = 0; i < num_moc; i ++){
        s.fo -= PESO_CAP * MAX(0, s.vet_pesos[i] - vet_cap_moc[i]);
    }
}

void escrever_sol(Solucao& s){
    printf("\n\nFO: %d\n", s.fo);

    for(int j = 0; j < num_obj; j ++){
        printf("%d ", s.vet_sol[j]);
    }

}