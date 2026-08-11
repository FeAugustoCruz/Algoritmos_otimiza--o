#include <stdio.h>
#include <stdlib.h>//<- busca no diretório de instalção
#include <vector>
#include <time.h>

#include "teste.h"//<- Busca no diretório do arquivo

int main(void){

    clock_t h;
    double tempo;
    h = clock();


    std::vector<std::vector<int>
    tempo = ((double) clock() - h)/ CLOCKS_PER_SEC;// se a divisão não for exata perdemos precisão, logo devemos fazer um type casting para double
    printf("TEMPO M> %.5f\n", tempo);
}
