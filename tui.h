#ifndef TUI
#define TUI

#include <stdio.h>
#include "robin.h"
#include "processo.h"
// terminal user interface

void printWelcome();
void printAll(Robin* r);
void printProc(Processo* proc);
void printCurrent(Robin* r);
void printQueue(Queue* queue);
void printIOQueues(Queue** queues);


void red();
void green();
void yellow();
void blue();
void magenta();
void cyan();
void white();
void reset();

#endif