#ifndef PROCESSO
#define PROCESSO

typedef enum tiposIO{
    DISCO = 3,
    FITA_MAGNETICA = 6,
    IMPRESSORA = 10
}tiposIO;

typedef enum status{
    PRONTO,
    BLOQUEADO,
    EXECUTANDO
}status;

typedef struct IO{
    int tempoInicio;
    tiposIO tipo;
}IO;

typedef struct IOreqs{
    IO** reqs;
    int size;
}IOreqs;

typedef struct Processo{
    int PID;
    int PPID; //Parent Process ID
    status status; 
    int tempoExecucao; 
    int tempoInicio;
    IOreqs* IO;   
    
}Processo;

typedef struct ProcList{
    Processo** procs; // lista de processos dinamicamente alocados após leitura
    int size;
}ProcList;

ProcList* criarProcessos(char* filename, int MAX_PROCESSOS);
IO* checarIORequests(Processo* p, int t);

#endif 