#ifndef ROBIN
#define ROBIN

//#define DEBUG
#include "queues.h"
#include "processo.h"

typedef struct Robin {
    int quantum_atual;
    int t;
    int maxProcessos;
    Queue* qalto;
    Queue* qbaixo;
    Queue** qIO;
    Processo* em_execucao;
} Robin;

Robin criarRobin(int quantum, int max_proc, int numeroIO); // inicializa struct robin
void updateSimulacao(Robin* r, ProcList* pl);
void executarNovoProcesso(Robin* r);
void verificarIO(Robin* r);
void entradaProcessos(Robin* r, ProcList* pl);
void finalizarProcesso(ProcList* pl, int PID);
int verificarFim(Robin* r, ProcList* pl);
#endif
