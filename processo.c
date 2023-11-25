#include <stdio.h>
#include <stdlib.h>
#include "processo.h"

ProcList* criarProcessos(char* filename, int MAX_PROCESSOS){

    FILE* f = fopen(filename, "w");
    if (f == NULL){
        printf("Erro abrindo arquivo.");
        exit(4);
    }


    int nProcessos;
    fscanf(f, "%d", &nProcessos);
    //Limite de leitura
    int n = (nProcessos >= MAX_PROCESSOS)? MAX_PROCESSOS:nProcessos;

    //Criando a lista de processos vazia
    ProcList* plist = (ProcList*)malloc(sizeof(ProcList));
    Processo** procs = (Processo**)malloc(n * sizeof(Processo*));

    //Criando cada processo e alocando na lista
    for (int i = 0; i < n; i++){
        Processo *proc = (Processo *)malloc(sizeof(Processo));
        status *s = (status *)malloc(sizeof(status));
        IOreqs *ioreqs = (IOreqs *)malloc(sizeof(IOreqs));
        IO *io = (IO *)malloc(sizeof(IO));

        fscanf(f, "%d, %d, %s, %d, %d, %d, %s, %d", proc->PID, proc->PPID, proc->tempoExecucao, proc->tempoInicio,
               io->tempoInicio, io->tipo, ioreqs->size);

        ioreqs->reqs = io;
        proc->IO = ioreqs;
        procs[i] = proc;
    }

    plist->procs = procs;
    plist->size = n;
    fclose(f);   

    return plist; 
}

int checarIORequests(Processo* p, int t){
    //ToDo: Iterar pelos IO's do processo e retornar true se existir um que comece no tempo t
    return 0;
}