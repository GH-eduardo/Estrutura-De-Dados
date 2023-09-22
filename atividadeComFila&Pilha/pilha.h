#ifndef PILHA
#define PILHA

#include "tarefa.h"

typedef struct Pilha{
Tarefa *topo;
} Pilha;

void empilhar(Tarefa *tarefa, Pilha *pilha);
void desempilhar(Pilha *pilha);
void exibirPilha(Tarefa *tarefaEmpilhada);

#endif