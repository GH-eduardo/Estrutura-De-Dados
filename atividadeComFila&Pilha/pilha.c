#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void empilhar(Tarefa *tarefa, Pilha *pilha) {
    tarefa->proximo = pilha->topo;
    pilha->topo = tarefa;
}

void desempilhar(Pilha *pilha) {
    if(pilha->topo == NULL) {
        printf("Nao foi possivel desempilhar, a pilha esta vazia!");
        sleep(1);
        return;
    }
    else{
        Tarefa *aux = pilha->topo;
        pilha->topo = pilha->topo->proximo; 
        free(aux);
    }
}

void exibirPilha(Tarefa *tarefaEmpilhada) {
    textcolor(10);
    printf("\n\t\tTopo da Pilha\n\n"); textcolor(15);
    printf("\n-----------------------------------------------\n");
    while(tarefaEmpilhada) {
        exibirTarefa(tarefaEmpilhada);
        printf("\n-----------------------------------------------\n");
        tarefaEmpilhada = tarefaEmpilhada->proximo;
    }
    textcolor(4);
    printf("\n\t\tFim da Pilha\n\n"); textcolor(15);
}