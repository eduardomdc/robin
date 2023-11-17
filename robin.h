#ifndef ROBIN
#define ROBIN

#include "queues.h"

typedef struct Robin {
    char fim;
    Queue queue;
} Robin;

Robin makeRobin(); // inicializa struct robin
void simulationUpdate();
void checarProcessoFim(); //Processo acabou antes do quantum
void checarQuantumFim(); //Quantum terminou
void escalonar();

#endif