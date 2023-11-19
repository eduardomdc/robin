#ifndef PROCESSO
#define PROCESSO

typedef enum tiposIO{
    impressora,
    disco,
    fita_magnetica
}tiposIO;

typedef struct IO {
    int tempoInicio;
    tiposIO tipo; // {impressora: i, disco: d, fita magnetica: f}
}IO;

typedef struct IOreqs {
    IO* reqs;
    int size;
}IOreqs;

typedef struct Processo{
    int PID;
    int PPID; //Parent Process ID
    char status; //{pronto: p, bloqueado: q, executando: e} ???{saida: s, pronto_suspenso: ps, bloqueado_suspenso: bs}???
    int tempoExecucao; 
    int tempoInicio;
    IOreqs IO;   
    
}Processo;

typedef struct ProcList{
    Processo* procs; // lista de processos dinamicamente alocados após leitura
    int size;
}ProcList;

#endif