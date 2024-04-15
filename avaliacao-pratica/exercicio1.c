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

void addProduct(TabelaHash* tabelaHash, Produto produto) {
    system("cls");
    int indice = hash(produto.nome);
    
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

void removeProduct(TabelaHash* tabelaHash, char* nome) {
    system("cls");
    int indice = hash(nome);
    
    if (tabelaHash[indice].inicio == NULL) {
        printf("\n\tProduto nao encontrado!\n\n");
        printf("\t"); system("pause");
        return;
    }
    
    No* atual = tabelaHash[indice].inicio;
    No* previous = NULL;
    while (atual != NULL) {
        if (strcmp(atual->produto.nome, nome) == 0) {
            if (previous == NULL) {
                tabelaHash[indice].inicio = atual->proximo;
            } else {
                previous->proximo = atual->proximo;
            }
            free(atual);
            printf("\n\tProduto removido com sucesso!\n\n");
            printf("\t"); system("pause");
            return;
        }
        previous = atual;
        atual = atual->proximo;
    }

    printf("\n\tProduto nao encontrado!\n\n");
    printf("\t"); system("pause");
}

void buscarProduto(TabelaHash* tabelaHash, char* nome) {
    system("cls");
    int indice = hash(nome);
    
    if (tabelaHash[indice].inicio == NULL) {
        printf("\n\tProduto nao encontrado!\n\n");
        printf("\t"); system("pause");
        return;
    }

    No* atual = tabelaHash[indice].inicio;
    while (atual != NULL) {
        if (strcmp(atual->produto.nome, nome) == 0) {
            printf("\n\n\tProduto encontrado:\n\n");
            printf("\tNome: %s\n", atual->produto.nome);
            printf("\tPreco: R$ %.2f\n", atual->produto.preco);
            printf("\tQuantidade: %d\n\n", atual->produto.quantidade);
            printf("\t"); system("pause");
            return;
        }
        atual = atual->proximo;
    }

    printf("\n\tProduto nao encontrado!\n\n");
    printf("\t"); system("pause");
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
                printf("\n\n\tNome do produto: ");
                scanf("%s", nome);
                printf("\tPreco R$: ");
                scanf("%f", &preco);
                printf("\tquantidade: ");
                scanf("%d", &quantidade);

                Produto produto;
                strcpy(produto.nome, nome);
                produto.preco = preco;
                produto.quantidade = quantidade;

                addProduct(tabelaHash, produto);
                printf("\n\tProduto adicionado com sucesso!\n\n");
                break;

            case 2:
                printf("\n\tNome do produto: ");
                scanf("%s", nome);

                removeProduct(tabelaHash, nome);
                break;

            case 3:
                printf("\n\tNome do produto: ");
                scanf("%s", nome);

                buscarProduto(tabelaHash, nome);
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