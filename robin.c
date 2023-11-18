#include <printf.h>
#include "queues.h"
#include "robin.h"

int PID_VAL = 100; //Valor Base do PID
int t=0;

const int quantum = 5;
const int MAX_PROCESSOS = 20;

int main(){
    Robin robin = criarRobin();
    while(!robin.fim){
        simulationUpdate();
    }

    return 0;
}



void simulationUpdate(){
    t++;
    checarProcessoFim(); //Processo acabou antes do quantum
    checarQuantumFim(); //Quantum terminou
    escalonar();
}

void checarProcessoFim(){
    return;
}

void checarQuantumFim(){
    return;
}

void escalonar(){
    return;
}

Robin criarRobin(){
    Robin robin;
    robin.fim = 0;
    return robin;
}