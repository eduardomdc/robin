#include <stdio.h>
#include <stdlib.h>
#include "processo.h"

Processo* criarProcessos(char* filename, int MAX_PROCESSOS){

    FILE* f = fopen(filename, "w");
    if (f == NULL){
        printf("Erro abrindo arquivo.");
        exit(4);
    }

    for(int i=0; i< MAX_PROCESSOS; i++){
       Processo* proc = (Processo*)malloc(sizeof(Processo));
       status* s = (status*)malloc(sizeof(status));
       IOreqs* ioreqs = (IOreqs*)malloc(sizeof(IOreqs));
       IO* io = (IO*)malloc(sizeof(IO));

       fscanf(f, "%d, %d, %s, %d, %d, %d, %s, %d", proc->PID, proc->PPID, proc->tempoExecucao, proc->tempoInicio,
       io->tempoInicio, io->tipo, ioreqs->size);
       
       ioreqs->reqs = io;
       proc->IO = ioreqs;
       return proc;
    }
    
    fclose(f);
    
}

ProcList* getProcessos(char* filename, int PID_VAL, int MAX_PROCESSOS){
    FILE* f = fopen(filename, "r");
    if (f == NULL){
        printf("Erro abrindo arquivo.");
        exit(4);
    }
    // criar lista de processos lidos
    ProcList* proclist = (ProcList*)malloc(sizeof(ProcList));
    proclist->size = 0;
    // acomodar espaço para MAX_PROCESSOS
    proclist->procs = (Processo**)malloc(sizeof(Processo*)*MAX_PROCESSOS);
    //ToDo

    fclose(f);
    return proclist;
}


int checarIORequests(Processo* p, int t){
    //ToDo: Iterar pelos IO's do processo e retornar true se existir um que comece no tempo t
    return 0;
}

