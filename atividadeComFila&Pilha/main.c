#include "tarefa.h"
#include "pilha.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main () {

    int opcao = 1;
    int prioridade;
    char descricao[100];
    Tarefa *tarefa;
    Pilha pilha;
    Fila fila;
    pilha.topo = NULL;
    fila.inicio = fila.fim = NULL;

    Tarefa *tarefaPilha;
    Tarefa *tarefaFila;

    Tarefa *tarefa1 = criarTarefa("Desenvolver recurso A", 2);
    Tarefa *tarefa2 = criarTarefa("Corrigir bug B", 1);
    Tarefa *tarefa3 = criarTarefa("Fazer a documentacao do sistema C", 6);
    Tarefa *tarefa4 = criarTarefa("Implementar D", 7);

    entrarNaFila(tarefa1, &fila);
    entrarNaFila(tarefa2, &fila);
    empilhar(tarefa3, &pilha);
    empilhar(tarefa4, &pilha);

    do {
    
        system("cls");
        printf("Escolha um opcao abaixo: \n"); 
        printf("\n0) Para sair\n");
        printf("1) Para inserir uma nova tarefa\n");
        printf("2) Para visualizar a Pilha de tarefas de alta prioridade\n");
        printf("3) Para visualizar a fila de tarefas gerais\n");
        printf("4) Para definir uma tarefa da Pilha como concluida\n");
        printf("5) Para definir uma tarefa da Fila como concluida\n");

        printf("\n---------> ");
        scanf("%d",&opcao);
        fflush(stdin);

        switch(opcao) {
        
            case 0: printf("\nSaindo...\n"); exit(0); break;

            case 1: 
                printf("\nDigite a descricao da tarefa: ");
                scanf("%s",&descricao); fflush(stdin);
                printf("\nDigite a prioridade da tarefa de 1 (muito baixa) ate 10 (muito alta): ");
                scanf("%d",&prioridade); fflush(stdin);
                tarefa = criarTarefa(descricao, prioridade);
                if(tarefa->prioridade > 5) {
                    empilhar(tarefa, &pilha);
                }
                else {
                    entrarNaFila(tarefa, &fila);
                }
            break;

            case 2: tarefaPilha = pilha.topo; exibirPilha(tarefaPilha); system("pause"); break;
    
            case 3: tarefaFila = fila.inicio; exibirFila(tarefaFila); system("pause"); break;

            case 4:  desempilhar(&pilha); break;

            case 5:  sairDaFila(&fila); break;
        
            default: printf("\nOpcao invalida!\n"); sleep(1);
        } 

    } while(opcao != 0);

}