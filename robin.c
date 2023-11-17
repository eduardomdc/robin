#include <printf.h>
#include "robin.h"

int PID_VAL = 100; //Valor Base do PID
int t=0;

const int quantum = 5;
const int MAX_PROCESSOS = 20;

int main(){
    Robin robin = makeRobin();
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