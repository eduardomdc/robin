#ifndef ROBIN
#define ROBIN

#include "queues.h"
#include "processo.h"

typedef struct Robin {
    int quantum_atual;
    int maxProcessos;
    Queue* q1;
    Queue* q2;
    Queue* qIO;
    Processo* em_execucao;
} Robin;

Robin criarRobin(int quantum, int max_proc); // inicializa struct robin
void updateSimulacao(Robin* r, ProcList* pl);
void executarNovoProcesso(Robin* r);
void verificarIO(Queue* qIO);
void entradaProcessos(Robin* r, ProcList* pl, int t);
void finalizarProcesso(ProcList* pl, int PID);

#endif