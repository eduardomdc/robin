#include <stdio.h>
#include <stdlib.h>
#include "queues.h"
#include "robin.h"
#include "processo.h"
#include "tui.h"


const int QUANTUM = 5;
const int MAX_PROCESSOS = 10;


//Debugging
ProcList* criarProcessosHardcoded(){
    ProcList* pl = (ProcList*) malloc(sizeof(ProcList));
    pl->size  = 2;
    pl->procs = (Processo**) malloc(pl->size*sizeof(Processo*));

    IO** array1IO = (IO**) malloc(sizeof(IO*));
    IO* io1 = (IO*) malloc(sizeof(IO));
    io1->tempoInicio = 3;
    io1->tipo = IMPRESSORA;
    array1IO[0] = io1;

    
    IO** array2IO = (IO**) malloc(sizeof(IO*));
    IO* io2 = (IO*) malloc(sizeof(IO));
    io2->tempoInicio = 2;
    io2->tipo = DISCO;
    array2IO[0] = io2;


    IOreqs* placeholder1 = (IOreqs*)malloc(sizeof(IOreqs*));
    placeholder1->reqs = array1IO;
    placeholder1->size = 1;

    IOreqs* placeholder2 = (IOreqs*)malloc(sizeof(IOreqs*));
    placeholder2->reqs = array2IO;
    placeholder2->size = 1;


    Processo* p1 = (Processo*) malloc(sizeof(Processo));
    p1->PID = 101;
    p1->status = PRONTO;
    p1->tempoExecucao = 10;
    p1->tempoEntrada = 5;    
    p1->IO = placeholder1;
    p1->tempoRestante = p1->tempoExecucao;

    Processo* p2 = (Processo*) malloc(sizeof(Processo));
    p2->PID = 102;
    p2->status = PRONTO;
    p2->tempoExecucao = 12;
    p2->tempoEntrada = 2;    
    p2->IO = placeholder2;
    p2->tempoRestante = p2->tempoExecucao;

    pl->procs[0] = p1;
    pl->procs[1] = p2;

    return pl;
}

int main(){
    printWelcome();
    Robin robin = criarRobin(QUANTUM, MAX_PROCESSOS, 3);
    ProcList* pl = criarProcessos("inputs.txt", MAX_PROCESSOS);
    //ProcList* pl = criarProcessosHardcoded(); 


    while(!verificarFim(&robin, pl)){
        if(robin.em_execucao != NULL){
            #ifdef DEBUG
            printf("quantum no tempo %d :%d\n", robin.t, robin.quantum_atual);
            printf("em_execucao: %d\n", robin.em_execucao->PID);
            #endif
        } 

        updateSimulacao(&robin, pl);
        printAll(&robin);
        robin.t++;
    }

    return 0;
}

void entradaProcessos(Robin* r, ProcList* pl){
    #ifdef DEBUG
    printf("entradaProcessos\n"); 
    #endif
    if(pl==NULL){
        #ifdef DEBUG
        printf("entradaProcessos:: lista é NULL\n");
        #endif
        return;
    } //lista vazia

    for (int i=0; i< pl->size;i++){
        if(pl->procs[i] != NULL && (pl->procs[i])->tempoEntrada == r->t){
            #ifdef DEBUG
            printf("entradaProcessos:: entrar processo %d\n", pl->procs[i]->PID);
            #endif
            inserirProcesso(r->qalto, (pl->procs)[i]);
        }
    }
}

void verificarIO(Robin* r){
    #ifdef DEBUG
    printf("VerificarIO\n");
    #endif
    for (int i=0; i< 3; i++){

        if(r->qIO[i]->head != NULL){
            #ifdef DEBUG
            printf("VerificarIO:: tem IO %d atualmente\n", i);
            #endif
            r->qIO[i]->head->TempoFila += 1;

            if(r->qIO[i]->head->TempoFila == r->qIO[i]->prioridade){

                Processo* p = popProcesso(r->qIO[i]);
                p->status = PRONTO;

                if (i % 2) inserirProcesso(r->qbaixo, p);
                else inserirProcesso(r->qalto, p);

            }
        }
    }
    return;
    }

int verificarFim(Robin* r, ProcList* pl){
    #ifdef DEBUG
    printf("verificamFim::\n");
    #endif
    // checa se todos os processos já saíram da lista de processos
    // e se todos queues estão vazios
    // e se não tem nada executando
    // return 0 caso não seja o fim
    // return 1 caso fim
    for (int i=0; i<pl->size; i++){
        if (pl->procs[i] != NULL){
            #ifdef DEBUG
            printf("proclist n está vazia\n");
            #endif
            return 0;
        } // ainda tem proc na lista
    }
    if (r->qalto->head != NULL){
        #ifdef DEBUG
        printf("queue alto não está vazio\n");
        #endif
        return 0;
    } // ainda tem proc no queue alto
    if (r->qbaixo->head != NULL){
        #ifdef DEBUG
        printf("queue baixo não está vazio\n");
        #endif
        return 0;
    } // ainda tem proc no queue baixo
    if (r->em_execucao != NULL){
        #ifdef DEBUG
        printf("ainda tem processo em execução\n");
        #endif
        return 0;
    }
    for (int i = 0; i<3; i++){
        if (r->qIO[i]->head != NULL){
            #ifdef DEBUG
            printf("ainda tem IO\n");
            #endif
            return 0;
        }
    }
    #ifdef DEBUG
    printf("Fim!\n");
    #endif
    return 1; // fim
}

void updateSimulacao(Robin* r, ProcList* pl){
    #ifdef DEBUG
    printf("Update!\n");
    #endif

    IO* req = NULL; //Possivel requisição do processo em execução

    //Alterações no processo executado
    if(r->em_execucao != NULL){
        #ifdef DEBUG
        printf("em_execucao != NULL\n");
        #endif
        r->em_execucao->tempoRestante -= 1;
        r->quantum_atual++;
        req = checarIORequests(r->em_execucao);
    }
    //Organizar Filas

    entradaProcessos(r, pl); 
    verificarIO(r);

    //Nenhum processo executando
    if(r->em_execucao == NULL){
        #ifdef DEBUG
        printf("Nada em execução\n");
        #endif
        executarNovoProcesso(r);
    }
    //Acabou o processo 
    else if(r->em_execucao->tempoRestante == 0){
        #ifdef DEBUG
        printf("Acabou o processo\n");
        #endif
        finalizarProcesso(pl, r->em_execucao->PID);

        executarNovoProcesso(r);
    }

    //Saiu por preempção. Volta para a fila 2
    else if((r->quantum_atual) % QUANTUM == 0){
        #ifdef DEBUG
        printf("Saiu por preempção, volta pra fila 2\n");
        #endif
        r->em_execucao->status = PRONTO;
        inserirProcesso(r->qbaixo, r->em_execucao); 

        executarNovoProcesso(r);
    }
    //O processo possui um io request
    else if (req){
        #ifdef DEBUG
        printf("Processo possui um IO\n");
        #endif
        r->em_execucao->status = BLOQUEADO;
        if(req->tipo == IMPRESSORA) inserirProcesso(r->qIO[0], r->em_execucao);
        else if (req->tipo == DISCO) inserirProcesso(r->qIO[1], r->em_execucao);
        else if (req->tipo == FITA_MAGNETICA) inserirProcesso(r->qIO[2], r->em_execucao);
        executarNovoProcesso(r);
    }
}

void executarNovoProcesso(Robin* r){
    #ifdef DEBUG
    printf("executarNovoProcesso\n");
    #endif
    r->em_execucao = NULL;
    r->quantum_atual = 0;

    Processo* proc = popProcesso(r->qalto);
    if(proc == NULL){ //Fila com prioridade 1 vazia
        #ifdef DEBUG
        printf("Fila alta vazia\n");
        #endif
        proc = popProcesso(r->qbaixo);

    }

    if(proc != NULL){
        #ifdef DEBUG
        printf("Novo processo agora executando\n");
        #endif
        proc->status = EXECUTANDO;
        r->em_execucao = proc;
    }
    return;
}


void finalizarProcesso(ProcList* pl, int PID){
    #ifdef DEBUG
    printf("finalizarProcesso\n");
    #endif
    for (int i=0; i < pl->size; i++){
        if (pl->procs[i] != NULL){
            if (pl->procs[i]->PID == PID){
                pl->procs[i] = NULL;
            }
        }
    }
    return;
}


Robin criarRobin(int quantum, int max_proc, int numeroIO){
    Robin robin;
    robin.t = 0;
    robin.quantum_atual = 0;
    robin.maxProcessos = max_proc;
    robin.em_execucao = NULL;
    robin.qalto = criarQueue(max_proc, 1);
    robin.qbaixo = criarQueue(max_proc, 2);
    robin.qIO = (Queue**) malloc(numeroIO*sizeof(Queue*));
    
    //Não sei iterar por enum em C .-.
    robin.qIO[0] = criarQueue(max_proc, IMPRESSORA);
    robin.qIO[1] = criarQueue(max_proc, DISCO);
    robin.qIO[2] = criarQueue(max_proc, FITA_MAGNETICA);
    
    return robin;
}
