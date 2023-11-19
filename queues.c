#include <stdlib.h>
#include "queues.h"

int inserirProcesso(Queue* q, Processo* p){
    if(q->tamanho + 1 > q->max_size){
        return 0; //fila cheia
    }

    ProcessoFila* pf = (ProcessoFila*) malloc(sizeof(ProcessoFila));
    
    pf->p = p;

    if (q->head == NULL){
        q->head = pf;
        q->tail = pf;
        pf->prox = pf;
        pf->prev = pf;
    }

    pf->prox = q->head; 
    pf->prev = q->tail;
    q->tail->prox = pf;
    q->tail = pf;

    q->tamanho += 1;

    return 1; //sucesso
}


Processo* popProcesso(Queue* q){

    if(q->head == NULL) return NULL;

    ProcessoFila* old_head = q->head;
    q->tail->prox = q->head->prox;
    q->head->prox->prev = q->tail;
    q->head = q->head->prox;

    Processo* p = old_head->p;
    free(old_head);

    q->tamanho -= 1;

    if(q->tamanho == 0){
        q->head = q->tail = NULL;
    }

    return p;
    
}


Queue* criarQueue(int max_size, int prioridade){
    

    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->max_size = max_size; //checar valor válido
    q->prioridade = prioridade; //checar valor válido
    q->head = NULL;
    q->tail = NULL;
    q->tamanho = 0;

    return q;
}