#include "tui.h"
#include "processo.h"
#include "queues.h"
#include "robin.h"



void printWelcome(){
    green();
    printf("|| S . E . R || v0.1\n");
    blue();
    printf("Simulador de Escalonamento Round Robin\n");
    reset();
}

void printAll(Robin* r){
    printf("\n");
    green();
    printf("***********\n");
    printf("Tempo Atual %d\n", r->t);
    printf("Quantum Atual %d\n", r->quantum_atual);reset();
    printCurrent(r);
    green();printf("FILA | Alta Prioridade\n");
    printQueue(r->qalto);reset();
    blue();printf("FILA | Baixa prioridade\n");
    printQueue(r->qbaixo);reset();
    magenta();printf("FILA | IO\n");
    printQueue(r->qIO);reset();
}

void printProc(Processo* proc){
    if (proc == NULL){
        return;
    }
    yellow();
    printf("----| PID %d |----\n", proc->PID);
    printf("| PPID %d\n", proc->PPID);
    printf("| STATUS ");
    switch (proc->status){
        case PRONTO:
            printf("PRONTO\n");
            break;
        case BLOQUEADO:
            printf("BLOQUEADO\n");
            break;
        case EXECUTANDO:
            printf("EXECUTANDO\n");
            break;
    }
    printf("| Tempo de Início %d\n", proc->tempoInicio);
    printf("| Tempo Restante de Execução %d\n", proc->tempoExecucao);
    reset();
}

void printQueue(Queue* queue){
    printf("|");
    ProcessoFila* start = queue->head;
    ProcessoFila* iterator = start;
    if (start == NULL){
        printf(" Vazia...\n");
        return;
    }
    do {
        Processo* proc = iterator->p;
        printf("<- %d ", proc->PID);
        iterator = iterator->prev;
    } while(iterator != start);
    printf("\n");
}

void printCurrent(Robin* r){
    
    if (r->em_execucao == NULL){
        magenta();
        printf("!--Nenhum processo em execução--!\n");
        reset();
        return;
    }
    green();
    printf("Processo Atual\n");
    reset();
    printProc(r->em_execucao);
    
}

void red(){
    printf("\x1b[0;31m");
}
void green(){
    printf("\x1b[0;32m");
}
void yellow(){
    printf("\x1b[0;33m");
}
void blue(){
    printf("\x1b[0;34m");
}
void magenta(){
    printf("\x1b[0;35m");
}
void cyan(){
    printf("\x1b[0;36m");
}
void white(){
    printf("\x1b[0;37m");
}
void reset(){
    printf("\x1b[0;0m");
}