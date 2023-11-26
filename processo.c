#include <stdio.h>
#include <stdlib.h>
#include "processo.h"
#include "robin.h"

ProcList* criarProcessos(char* filename, int MAX_PROCESSOS){

    FILE* f = fopen(filename, "w");
    if (f == NULL){
        printf("Erro abrindo arquivo.");
        exit(4);
    }

    //A primeira informação do arquivo é o número de processos que ele tem
    int nProcessos;
    fscanf(f, "%d", &nProcessos);

    //Limite de leitura
    int n = (nProcessos >= MAX_PROCESSOS)? MAX_PROCESSOS:nProcessos;

    //Criando a lista de processos vazia
    ProcList* plist = (ProcList*)malloc(sizeof(ProcList));
    Processo** procs = (Processo**)malloc(n * sizeof(Processo*));

    //Criando cada processo e alocando na lista
    for (int i = 0; i < n; i++){
        Processo* proc = (Processo*)malloc(sizeof(Processo));
        //status* s = (status*)malloc(sizeof(status));
        IOreqs* ioreqs = (IOreqs*)malloc(sizeof(IOreqs));

        //Todas as informações do processo exceto as de IO
        fscanf(f, "%d %d %d %d", &proc->PID, &proc->tempoExecucao, &proc->tempoInicio, &ioreqs->size);
        IO** ios = (IO**)malloc(ioreqs->size * sizeof(IO*));

        //Informações de IO
        if(ioreqs->size > 0){
            for(int i = 0; i < ioreqs->size; i++){
                IO* io = (IO*)malloc(sizeof(IO));
                int iotipo;
                fscanf(f, "%d %d", &io->tempoInicio, &iotipo);
                io->tipo = iotipo;
                ios[i] = io;
            }
            ioreqs->reqs = ios;
        }
        else if(ioreqs->size == 0){
            ioreqs->reqs = NULL;
        }
        proc->PPID = 0;
        proc->IO = ioreqs;
        proc->status = PRONTO;
        procs[i] = proc;
    }

    plist->procs = procs;
    plist->size = n;
    fclose(f);   

    return plist; 
}

IO* checarIORequests(Processo* p, int t){
    //Itera pelos IO's do processo e retornar true se existir um que comece no tempo t
    if(p->IO == NULL) return NULL;
    for(int i = 0; i < p->IO->size; i++){
        if(p->IO->reqs[i]->tempoInicio == t) return p->IO->reqs[i];
    }
    return NULL;
}
