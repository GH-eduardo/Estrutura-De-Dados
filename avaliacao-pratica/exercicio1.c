#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100
#define MAX_NOME 50
#define A 0.6180339887  // constante multiplicativa

// Lucas Augusto Covaltchuk Calixto RA: 22000109-2, Leonardo Demetrio
// Franchini RA: 22014274-2, Eduardo Thomé RA: 22110037-2

typedef struct {
    char nome[MAX_NOME];
    float preco;
    int quantidade;
} Produto;

typedef struct No {
    Produto produto;
    struct No* proximo;
} No;

typedef struct {
    No* inicio;
} TabelaHash;

typedef struct NoPilha {
    int operacao;
    Produto produto;
    struct NoPilha* proximo;
}NoPilha;

typedef struct Pilha {
    NoPilha* topo;
} Pilha;

void push(Pilha* pilha, Produto produto, int operacao, char* nome, int quantidade) {
    NoPilha* novo = (NoPilha*) malloc(sizeof(NoPilha));

    if (novo == NULL) {
        printf("\n\tFalha na alocação de memória!\n\n");
        return;
    }
    if (operacao == -1) {
        strcpy(novo->produto.nome, nome);
        novo->produto.quantidade = quantidade;
    }
    else {
        novo->produto = produto;
        novo->operacao = operacao;
    }
    novo->proximo = pilha->topo;
    pilha->topo = novo;
}

Produto pop(Pilha* pilha) {
    if (pilha->topo == NULL) {
        printf("\n\tPilha vazia!\n\n");
        Produto produtoVazio;
        return produtoVazio;
    }
    NoPilha* temp = pilha->topo;
    Produto produtoRemovido = pilha->topo->produto;
    pilha->topo = pilha->topo->proximo;
    free(temp);
    return produtoRemovido;
}

void imprimirPilha(Pilha* pilha) {
    NoPilha* atual = pilha->topo;
    while (atual != NULL) {
        printf("\n###############################################\n\n\tOperacao: %s\n", atual->operacao == 1 ? "Adicionar" : "Remover");
        printf("\n\tNome: %s\n", atual->produto.nome);
        atual->operacao == 1 ? printf("\tPreco: R$ %.2f\n", atual->produto.preco) : printf("");
        printf("\tQuantidade: %d\n\n", atual->produto.quantidade);
        atual = atual->proximo;
    }
}

unsigned int hash(char* nome) {
    int valorHash = 0;
    int tamanhoNome = strlen(nome);
    for (int i = 0; i < tamanhoNome; i++) {
        valorHash += nome[i];
    }
    double valor = valorHash * A;
    valor = valor - (int)valor;  // descarta a parte inteira
    return (unsigned int)(MAX_PRODUTOS * valor);  // multiplica pelo tamanho da tabela e retorna a parte inteira
}

void inicializarTabelaHash(TabelaHash* tabelaHash) {
    for (int i = 0; i < MAX_PRODUTOS; i++) {
        tabelaHash[i].inicio = NULL;
    }
}

void adicionarProduto(TabelaHash* tabelaHash, Produto produto) {
    int indice = hash(produto.nome);
    
    No* atual = tabelaHash[indice].inicio;
    while (atual != NULL) {
        if (strcmp(atual->produto.nome, produto.nome) == 0) {
            atual->produto.quantidade += produto.quantidade;
            atual->produto.preco = produto.preco;
            printf("\n\tQuantidade do produto atualizada com sucesso!\n\n");
            printf("\t"); system("pause");
            return;
        }
        atual = atual->proximo;
    }

    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->produto = produto;
    novoNo->proximo = NULL;
    
    if (tabelaHash[indice].inicio == NULL) {
        tabelaHash[indice].inicio = novoNo;
    } else {
        novoNo->proximo = tabelaHash[indice].inicio;
        tabelaHash[indice].inicio = novoNo;
    }
    printf("\n\tProduto adicionado com sucesso!\n\n");
    printf("\t"); system("pause");
}

void removerProduto(TabelaHash* tabela, char* nome, int quantidade) {
    int indice = hash(nome);
    No* atual = tabela[indice].inicio;
    No* anterior = NULL;

    while (atual != NULL && strcmp(atual->produto.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Produto não encontrado.\n");
        return;
    }

    if (quantidade >= atual->produto.quantidade || quantidade == -1) {
        if (anterior == NULL) {
            tabela[indice].inicio = atual->proximo;
        } else {
            anterior->proximo = atual->proximo;
        }
        free(atual);
    } else {
        atual->produto.quantidade -= quantidade;
    }
}


void buscarProduto(TabelaHash* tabelaHash, char* nome) {
    int indice = hash(nome);
    
    if (tabelaHash[indice].inicio == NULL) {
        printf("\n\tProduto nao encontrado!\n\n");
        return;
    }

    No* atual = tabelaHash[indice].inicio;
    while (atual != NULL) {
        if (strcmp(atual->produto.nome, nome) == 0) {
            printf("\n\tProduto encontrado:\n\n");
            printf("\tNome: %s\n", atual->produto.nome);
            printf("\tPreco: R$ %.2f\n", atual->produto.preco);
            printf("\tQuantidade: %d\n\n", atual->produto.quantidade);
            return;
        }
        atual = atual->proximo;
    }
    printf("\n\tProduto nao encontrado!\n\n");
}

int main() {
    TabelaHash tabelaHash[MAX_PRODUTOS];
    inicializarTabelaHash(tabelaHash);
    Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));
    pilha->topo = NULL;

    int opcao;
    char nome[MAX_NOME];
    float preco;
    int quantidade;

    do {
        system("cls");
        printf("\n--- Sistema de Gerenciamento de Estoque ---\n\n");
        printf("\t1. Adicionar produto\n");
        printf("\t2. Remover produto\n");
        printf("\t3. Buscar produto\n");
        printf("\t4. Imprimir historico\n");
        printf("\t5. Sair\n\n\n");
        printf("\tEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n\tNome do produto: ");
                scanf("%s", nome);

                buscarProduto(tabelaHash, nome);

                printf("\tDefinir/Atualizar Preco R$: ");
                scanf("%f", &preco);
                printf("\tAdicionar quantidade(un): ");
                scanf("%d", &quantidade);

                Produto produto;
                strcpy(produto.nome, nome);
                produto.preco = preco;
                produto.quantidade = quantidade;

                adicionarProduto(tabelaHash, produto);
                push(pilha, produto, 1, "", 0);
                printf("\n\tProduto adicionado com sucesso!\n\n");
                break;

            case 2:
                printf("\n\tDigite o nome do produto a ser removido: ");
                scanf("%s", nome);

                buscarProduto(tabelaHash, nome);

                printf("\n\tDigite a quantidade a ser removida ou 't' para 'tudo': ");
                char entrada[5];
                scanf("%s", entrada);

                quantidade = atoi(entrada);
                push(pilha, produto, -1, nome, quantidade);

                if (strcmp(entrada, "t") == 0) {
                    quantidade = -1;
                }
                removerProduto(tabelaHash, nome, quantidade);
                break;

            case 3:
                printf("\n\tNome do produto: ");
                scanf("%s", nome);

                buscarProduto(tabelaHash, nome);
                printf("\t"); system("pause");
                break;

            case 4:
                imprimirPilha(pilha);
                printf("\t"); system("pause");
                break;

            case 5:
                printf("\tSaindo...\n");
                break;

            default:
                printf("\n\tEscolha invalida! tente novamente.\n\n");
                break;
        }
    } while (opcao != 5);

    free(pilha);

    return 0;
}