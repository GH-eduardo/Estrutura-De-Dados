#ifndef TAREFA
#define TAREFA

typedef struct Tarefa{
char descricao[100];
int prioridade;
struct Tarefa *proximo;
} Tarefa;

Tarefa *criarTarefa(char descricao[], int prioridade);
void exibirTarefa(Tarefa *tarefa);

#endif