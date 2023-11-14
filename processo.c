#include <stdio.h>
#include <stdlib.h>


typedef struct _IO {
    int tempoInicio;
    char type; // {impressora: i, disco: d, fita magnetica: f}
}IO;



typedef struct _Processo{
    int PID;
    int PPID; //Parent Process ID (-1 como inválido?)
    char status; //{pronto: p, bloqueado: q, executando: e} ???{saida: s, pronto_suspenso: ps, bloqueado_suspenso: bs}???
    int tempoExecucao; 
    int tempoInicio;
    IO IO_access;   
    
}Processo;



void createProcessos(char* filename, int MAX_PROCESSOS){

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

