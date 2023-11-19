#ifndef QUEUES
#define QUEUES

#include "processo.h"

typedef struct ProcessoFila{
    Processo* p;
    struct ProcessoFila* prev;
    struct ProcessoFila* prox;
    int TempoFila; // tempo nessa fila
}ProcessoFila; 


typedef struct Queue{
    int max_size;
    ProcessoFila* head; // chegou sua vez!
    ProcessoFila* tail; // final da fila, vc é o último
    int prioridade;
    int tamanho;
}Queue;


int inserirProcesso(Queue* q, Processo* p);
Processo* popProcesso(Queue* q);
Queue* criarQueue(int max_size, int prioridade);
#endif