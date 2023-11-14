#include <printf.h>

int PID_VAL = 100 //Valor Base do PID
int t=0;

const quantum = 5;
const MAX_PROCESSOS = 20;

int main(){

    while(!fim){
        simulationUpdate()
    }

    return 0;
}



void simulationUpdate(){
    t++;
    checarProcessoFim(); //Processo acabou antes do quantum
    checarQuantumFim(); //Quantum terminou
    escalonar();
    
}