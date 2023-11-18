#ifndef PROCESSO
#define PROCESSO

typedef struct _IO {
    int tempoInicio;
    char type; // {impressora: i, disco: d, fita magnetica: f}
}IO;

typedef struct _Processo{
    int PID;
    int PPID; //Parent Process ID (-1 como inválido?)
    char status; //{pronto: p, bloqueado: q, executando: e} ???{saida: s, pronto_suspenso: ps, bloqueado_suspenso: bs}???
    int tempoExecucao; 
    int tempoInicio;
    IO IO_access;   
    
}Processo;

typedef struct ProcList{
    Processo* procs; // lista de processos dinamicamente alocados após leitura
    int size;
}ProcList;

#endif