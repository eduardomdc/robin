#include <stdio.h>
#include <stdlib.h>
#include "processo.h"

void criarProcessos(char* filename, int MAX_PROCESSOS){

    FILE* f = fopen(filename, "w");
    if (f == NULL){
        printf("Erro abrindo arquivo.");
        exit(4);
    }

    for(int i=0; i< MAX_PROCESSOS; i++){
       //ToDo
    }

    fclose(f);
}

Processo* getProcessos(char* filename, int PID_VAL, int MAX_PROCESSOS){
    FILE* f = fopen(filename, "r");
    if (f == NULL){
        printf("Erro abrindo arquivo.");
        exit(4);
    }

    //ToDo

    fclose(f);
}

