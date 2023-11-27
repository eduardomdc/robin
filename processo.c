#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processo.h"
#include "robin.h"
#include "tui.h"

ProcList* criarProcessos(char* filename, int MAX_PROCESSOS){

    FILE* f = fopen(filename, "r");
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
        fscanf(f, "%d %d %d %d", &proc->PID, &proc->tempoExecucao, &proc->tempoEntrada, &ioreqs->size);

        //Informações de IO
        if(ioreqs->size > 0){
            IO** ios = (IO**)malloc(ioreqs->size * sizeof(IO*));
            for(int i = 0; i < ioreqs->size; i++){
                IO* io = (IO*)malloc(sizeof(IO));
                char iotipo[100];
                tiposIO enumtipo;
                fscanf(f, "%d %s", &io->tempoInicio, iotipo);
                if (strcmp(iotipo, "FITA")==0 
                || strcmp(iotipo, "FITA_MAGNETICA")==0){
                    enumtipo = FITA_MAGNETICA;
                }
                else if (strcmp(iotipo, "DISCO")==0){
                    enumtipo = DISCO;
                }
                else if (strcmp(iotipo, "IMPRESSORA")==0){
                    enumtipo = IMPRESSORA;
                } else {
                    red();printf("CriarProcessos:: !! Erro: Tipo de IO %s inválido !!", iotipo);reset();
                }
                io->tipo = enumtipo;
                ios[i] = io;
            }
            ioreqs->reqs = ios;
        }
        else if(ioreqs->size == 0){
            ioreqs->reqs = NULL;
        }
        proc->IO = ioreqs;
        proc->status = PRONTO;
        proc->tempoRestante = proc->tempoExecucao;
        procs[i] = proc;
    }

    plist->procs = procs;
    plist->size = n;
    fclose(f);   

    return plist; 
}

IO* checarIORequests(Processo* p){
    #ifdef DEBUG
    printf("checarIORequests::\n");
    #endif
    //Itera pelos IO's do processo e retornar true se existir um que comece no tempo t
    if(p->IO->size == 0){
        #ifdef DEBUG
        printf("checarIORequests::processo sem IO\n");
        #endif
        return NULL;
    }
    for(int i = 0; i < p->IO->size; i++){
        if(p->IO->reqs[i]->tempoInicio == p->tempoExecucao - p->tempoRestante){
            #ifdef DEBUG
            printf("checarIORequests::processo tem IO %d\n", p->IO->reqs[i]->tipo);
            #endif
            return p->IO->reqs[i];
        } else {
            #ifdef DEBUG
            printf("checarIORequests::IO->reqs[%d] não está na hora de executar\n",i);
            printf("    pois ele começa no t=%d\n", p->IO->reqs[i]->tempoInicio);
            printf("    e agora é t=%d\n", p->tempoExecucao - p->tempoRestante);
            #endif
        }
    }
    
    #ifdef DEBUG
    printf("checarIORequests::processo tem lista de IO size=%d\n", p->IO->size);
    #endif
    return NULL;
}
