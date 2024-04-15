#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100
#define MAX_NOME 50

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

int hash(char* nome) {
    int valorHash = 0;
    int tamanhoNome = strlen(nome);
    for (int i = 0; i < tamanhoNome; i++) {
        valorHash += nome[i];
    }
    return valorHash % MAX_PRODUTOS;
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
        printf("\t4. Sair\n\n\n");
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
                printf("\n\tProduto adicionado com sucesso!\n\n");
                break;

            case 2:
                printf("\n\tDigite o nome do produto a ser removido: ");
                scanf("%s", nome);

                buscarProduto(tabelaHash, nome);

                printf("\n\tDigite a quantidade a ser removida ou 't' para 'tudo': ");
                char entrada[10];
                scanf("%s", entrada);

                int quantidade;
                if (strcmp(entrada, "t") == 0) {
                    quantidade = -1;
                } else {
                    quantidade = atoi(entrada);
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
                printf("\tSaindo...\n");
                break;

            default:
                printf("\n\tEscolha invalida! tente novamente.\n\n");
                break;
        }
    } while (opcao != 4);

    return 0;
}