#include <stdlib.h>
#include <stdio.h>
#include "queues.h"
#include "robin.h"

// HEAD PROX == TAIL
// TAIL PREV == HEAD

int inserirProcesso(Queue* q, Processo* p){
    if(q->tamanho + 1 > q->max_size){
        return 0; //fila cheia
    }

    ProcessoFila* pf = (ProcessoFila*) malloc(sizeof(ProcessoFila));
    
    pf->p = p;
    pf->TempoFila = 0;

    if (q->head == NULL){
        q->head = pf;
        q->tail = pf;
    }

    pf->prev = q->head; 
    pf->prox = q->tail;
    q->head->prox = pf;
    q->tail->prev = pf;
    q->tail = pf;

    q->tamanho += 1;

    return 1; //sucesso
}


Processo* popProcesso(Queue* q){
    #ifdef DEBUG
    printf("popProcesso\n");
    #endif
    ProcessoFila* bighead = q->head;
    if(bighead == NULL){
        #ifdef DEBUG
        printf("popProcessos:: head = NULL\n");
        #endif
        return NULL;
    }

    ProcessoFila* old_head = q->head;

    q->tail->prev = q->head->prev;
    q->head->prev->prox = q->tail;
    q->head = q->head->prev;
    Processo* p = old_head->p;
    free(old_head);
    #ifdef DEBUG
    printf("popProcesso:: fred old_head\n");
    #endif

    q->tamanho -= 1;

    if(q->tamanho == 0){
        q->head = q->tail = NULL;
    }

    return p;
    
}


Queue* criarQueue(int max_size, int prioridade){
    
    
    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->max_size = max_size; 
    q->prioridade = prioridade; 
    q->head = NULL;
    q->tail = NULL;
    q->tamanho = 0;

    return q;
}
