#include "tarefa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

Tarefa *criarTarefa(char descricao[], int prioridade) {
    Tarefa *novaTarefa = (Tarefa*)malloc(sizeof(Tarefa));
    if (novaTarefa){
        strcpy(novaTarefa->descricao, descricao);
        novaTarefa->prioridade = prioridade;
        novaTarefa->proximo = NULL;
        printf("\nNova tarefa criada com sucesso!");
        sleep(1);
        return novaTarefa;
    }
    else{
        printf("Impossível alocar memoria para criar uma nova tarefa!\n");
        return NULL;
    }
}

void exibirTarefa(Tarefa *tarefa) {
    printf("Descricao da tarefa: %s\n\nPrioridade da tarefa: %d\n\n", tarefa->descricao, tarefa->prioridade);
}