#ifndef FILA
#define FILA

#include <stdio.h>
#include "tarefa.h"

typedef struct Fila{
Tarefa *inicio;
Tarefa *fim;
} Fila;

void entrarNaFila(Tarefa *tarefa, Fila *fila);
void sairDaFila(Fila *fila);
void exibirFila(Tarefa *tarefaEnfileirada);

#endif