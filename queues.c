#include "processo.c"
#include <stdlib.h>

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



int inserirProcesso(Queue* q, Processo* p){
    if(q->tamanho + 1 > q->max_size){
        return 0; //fila cheia
    }

    ProcessoFila* pf = (ProcessoFila*) malloc(sizeof(ProcessoFila));
    
    pf->p = p;
    pf->prox = q->head; 
    pf->prev = q->head->prev;
    q->head->prev->prox = pf;
    q->head->prev = pf;

    q->tamanho += 1;

    return 1; //sucesso
}


Processo* removerProcesso(Queue* q, int PID){
    ProcessoFila* pf = q->head->prox;
    while(pf != q->head){
        if (pf->p->PID == PID){
            
            pf->prev->prox = pf->prox;
            pf->prox->prev = pf->prev;
            return pf->p;
        }

        pf = pf->prox;
    }
    return NULL; //PID não encontrado 
}


Queue* criarQueue(int max_size, int prioridade){
    //Cabeça
    HeadNode* head = (HeadNode*) malloc(sizeof(HeadNode));
    head->prev = head->prox = head;

    //Info da queue
    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->max_size = max_size; //checar valor válido
    q->prioridade = prioridade; //checar valor válido
    q->head = head;
    q->tamanho = 0;

    return q;
}
