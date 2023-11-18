#ifndef QUEUES
#define QUEUES

#include "processo.h"

typedef struct _ProcessoFila{
    Processo* p;
    struct _ProcessoFila* prev;
    struct _ProcessoFila* prox;
    int TempoFila; // tempo nessa fila
}ProcessoFila; 

/* tipo diferente para a head vai dar erros de conversão de ponteiro
typedef struct _HeadNode{
    ProcessoFila* prox;
    ProcessoFila* prev;
}HeadNode;
*/

typedef struct _Queue{
    int max_size;
    ProcessoFila* head; // chegou sua vez!
    ProcessoFila* tail; // final da fila, vc é o último
    int prioridade;
    int tamanho;
}Queue;

#endif