#include <stdio.h>
#include <string.h>
#include <memory.h>
#include "pnm.h"

int main(void){
    char arq[50];
    strcpy(arq, "pmm1.txt");//Vai copiar o texto pnm1 para o array arq!
    //OBS caso de erro coloque "..//" para sair do diretório e entrar em outro
    ler_dados(arq);
    //strcpy(arq, "");
    //testar_dados(arq);

    SolucaoBIN solB;
    memset(&solB, 0, sizeof(SolucaoBIN));//Vai zerar a matriz inteira! função conhecida como (zero-biting)
    solB.mat_sol[0][0] = 1;
    solB.mat_sol[0][1] = 1;
    solB.mat_sol[1][0] = 1;
    solB.mat_sol[1][2] = 1;
    calcular_FOBIN(solB);
    escrever_solBIN(solB);
    return 0;
}

void calcular_FOBIN(SolucaoBIN& s){

    s.fo = 0;
    for(int i = 0; i < num_moc; i ++){
        for (int j = 0; j < num_obj; j ++){
            /*if(s.mat_sol[i][j] == 1){
                s.fo += vet_val_obj[j];
            }*/

            s.fo += vet_val_obj[j] * s.mat_sol[i][j];//-> Mais rápido do que a condicional!
        }

    }
}

void escrever_solBIN(SolucaoBIN& s){
    printf("\n\nFO: %d\n", s.fo);

    for(int i = 0; i < num_moc; i ++){

        for(int j = 0; j < num_obj; j ++){
            printf("%d ", s.mat_sol[i][j]);
        printf("\n");
        }
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