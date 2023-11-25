#include <stdio.h>
#include <stdlib.h>
#include "queues.h"
#include "robin.h"
#include "processo.h"

int PID_VAL = 100; //Valor Base do PID
int t=0;

const int QUANTUM = 5;
const int MAX_PROCESSOS = 10;

int criarPID(){
    static int PID = 100;
    PID++;
    return PID;
}

//Debugging
ProcList* criarProcessosHardcoded(){
    ProcList* pl = (ProcList*) malloc(sizeof(ProcList));
    pl->size  = 2;
    pl->procs = (Processo**) malloc(pl->size*sizeof(Processo*));

    IOreqs placeholder = {NULL, 0};
    Processo* p1 = (Processo*) malloc(sizeof(Processo));
    p1->PID = criarPID();
    p1->PPID = 0;
    p1->status = PRONTO;
    p1->tempoExecucao = 10;
    p1->tempoInicio = 5;    
    p1->IO = placeholder;

    Processo* p2 = (Processo*) malloc(sizeof(Processo));
    p2->PID = criarPID();
    p2->PPID = 0;
    p2->status = PRONTO;
    p2->tempoExecucao = 12;
    p2->tempoInicio = 2;    
    p2->IO = placeholder;

    pl->procs[0] = p1;
    pl->procs[1] = p2;

    return pl;
}

int main(){

    Robin robin = criarRobin(QUANTUM, MAX_PROCESSOS);
    //ToDo: ProcList* pl = criaProcessos();
    ProcList* pl = criarProcessosHardcoded(); 


    while(!verificarFim(&robin, pl)){
        if(robin.em_execucao != NULL){
            printf("quantum no tempo %d :%d\n", t, robin.quantum_atual);
            printf("em_execucao: %d\n", robin.em_execucao->PID);
        } 

        updateSimulacao(&robin, pl);
    }

    return 0;
}

void entradaProcessos(Robin* r, ProcList* pl, int t){
    printf("entradaProcessos\n");
    if(pl==NULL){
        printf("entradaProcessos:: lista é NULL\n");
        return;
    } //lista vazia

    for (int i=0; i< pl->size;i++){
        if (pl->procs[i] == NULL) continue;
        if((pl->procs[i])->tempoInicio == t){
            printf("entradaProcessos:: entrar processo %d\n", pl->procs[i]->PID);
            inserirProcesso(r->qalto, (pl->procs)[i]);
        }
    }
}

void verificarIO(Queue* qIO){
    printf("VerificarIO\n");
    //ToDo: Iterar pela fila de io e colocar os finalizados na fila de pronto os que acabam no tempo t
    //Não esquecer de considerar filas diferentes para cada IO
    return;
}

int verificarFim(Robin* r, ProcList* pl){
    printf("verificamFim::\n");
    // checa se todos os processos já saíram da lista de processos
    // e se todos queues estão vazios
    // e se não tem nada executando
    // return 0 caso não seja o fim
    // return 1 caso fim
    for (int i=0; i<pl->size; i++){
        if (pl->procs[i] != NULL){
            printf("proclist n está vazia\n");
            return 0;
        } // ainda tem proc na lista
    }
    if (r->qalto->head != NULL){
        printf("queue alto não está vazio\n");
        return 0;
    } // ainda tem proc no queue alto
    if (r->qbaixo->head != NULL){
        printf("queue baixo não está vazio\n");
        return 0;
    } // ainda tem proc no queue baixo
    if (r->em_execucao != NULL){
        printf("ainda tem processo em execução\n");
        return 0;
    }
    printf("Fim!\n");
    return 1; // fim
}

void updateSimulacao(Robin* r, ProcList* pl){
    printf("Update!\n");
    t++;

    //Alterações no processo executado
    if(r->em_execucao != NULL){
        printf("em_execucao != NULL\n");
        r->em_execucao->tempoExecucao -= 1;
        r->quantum_atual++;
    }
    //Organizar Filas

    entradaProcessos(r, pl, t); 
    verificarIO(r->qIO);

    //Nenhum processo executando
    if(r->em_execucao == NULL){
        printf("Nada em execução\n");
        executarNovoProcesso(r);
    }
    //Acabou o processo 
    else if(r->em_execucao->tempoExecucao == 0){
        finalizarProcesso(pl, r->em_execucao->PID);

        executarNovoProcesso(r);
    }

    //Saiu por preempção. Volta para a fila 2
    else if((r->quantum_atual) % QUANTUM == 0){
        
        r->em_execucao->status = PRONTO;
        inserirProcesso(r->qbaixo, r->em_execucao); 

        executarNovoProcesso(r);
    }
    //O processo possui um io request
    else if (checarIORequests(r->em_execucao, t)){
        //ToDo
        executarNovoProcesso(r);
    }
}

void executarNovoProcesso(Robin* r){
    printf("executarNovoProcesso\n");
    r->em_execucao = NULL;
    r->quantum_atual = 0;

    Processo* proc = popProcesso(r->qalto);
    if(proc == NULL){ //Fila com prioridade 1 vazia
        printf("Fila alta vazia\n");
        proc = popProcesso(r->qbaixo);

    }

    if(proc != NULL){
        printf("Novo processo agora executando\n");
        proc->status = EXECUTANDO;
        r->em_execucao = proc;
    }
    return;
}


void finalizarProcesso(ProcList* pl, int PID){
    printf("finalizarProcesso\n");
    for (int i=0; i < pl->size; i++){
        if (pl->procs[i] == NULL) continue;
        if (pl->procs[i]->PID == PID){
            pl->procs[i] = NULL;
        }
    }
    return;
}


Robin criarRobin(int quantum, int max_proc){
    Robin robin;
    robin.quantum_atual = 0;
    robin.maxProcessos = max_proc;
    robin.em_execucao = NULL;
    robin.qalto = criarQueue(max_proc, 1);
    robin.qbaixo = criarQueue(max_proc, 2);
    robin.qIO = criarQueue(max_proc, 0); //Isso ta esquisito
    
    return robin;
}
