#include <stdio.h>
#include "prcp.h"
#include <string.h>


int main(void){
    
    //nome do arquivo
    char arq[50];
    strcpy(arq, "inst1.txt");
    ler_dados(arq);
    strcpy(arq, "");
    testar_dados(arq);


    return 0;
}

void ler_dados(char* arq){
    FILE *f = fopen(arq, "r");
    fscanf(f, "%d", &num_pont);
    fscanf(f, "%d", &num_posi);

    for(int i = 0; i < MAX_PONTS; i ++){
        fscanf(f, "%d", &conflitos[i].num_conflito);
        for(int j = 0; j < conflitos[i].num_conflito; j ++){
            fscanf(f, "%d", &conflitos[i].vet_id[j]);
        }
    }

}

void testar_dados(char* arq){
    FILE* f; 
    if (strcmp(arq, "") == 0){

        //-> saida no terminal
        f = stdout;
    }else{
        f = fopen(arq, "w");
    }

    fprintf(f, "%d\n", num_pont);
    fprintf(f, "%d\n", num_posi);

    /*for(int i = 0; i < MAX_PONTS; i ++){
        fprintf(f,"%d\n", conflitos[i].num_conflito);
        for (int j = 0; j < conflitos[i].num_conflito; j++)
        {
            fprintf(f,"%d\t", conflitos[i].vet_id[j]);
        }
        printf("\n");
        
    }*/

    if (strcmp(arq, "") != 0){
        fclose(f);
    }
}

