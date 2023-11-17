#ifndef QUEUES
#define QUEUES

#include "processo.h"

typedef struct _ProcessoFila{
    Processo* p;
    struct _ProcessoFila* prev;
    struct _ProcessoFila* prox;
    int TempoFila;
}ProcessoFila; 

typedef struct _HeadNode{
    ProcessoFila* prox;
    ProcessoFila* prev;
}HeadNode;

typedef struct _Queue{
    int max_size;
    HeadNode* head;
    int prioridade;
    int tamanho;

}Queue;

#endif