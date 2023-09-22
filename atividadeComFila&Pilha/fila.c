#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.c>
#include <unistd.h>

void entrarNaFila(Tarefa *tarefa, Fila *fila) {
    if (fila->inicio == NULL) {
        fila->inicio = fila->fim = tarefa;
    } else {
        fila->fim->proximo = tarefa;
        fila->fim = tarefa;
    }
}

void sairDaFila(Fila *fila) {
    if (fila->inicio == NULL) {
        printf("Nao foi possivel tirar da fila, a fila esta vazia!");
        sleep(1);
        return; // Fila vazia
    }
    Tarefa *tarefa = fila->inicio;
    fila->inicio = tarefa->proximo;
    free(tarefa);
    if (fila->inicio == NULL) {
        fila->fim = NULL; // A fila está vazia agora
    }
}

void exibirFila(Tarefa *tarefaEnfileirada) {
    textcolor(10);
    printf("\n\t\tInicio da Fila\n\n"); textcolor(15);
    printf("\n-----------------------------------------------\n");
    while(tarefaEnfileirada != NULL) {
        exibirTarefa(tarefaEnfileirada);
        printf("\n-----------------------------------------------\n");
        tarefaEnfileirada = tarefaEnfileirada->proximo;
    }
    textcolor(4);
    printf("\n\t\tFim da Fila\n\n"); textcolor(15);
}