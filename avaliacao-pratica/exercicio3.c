#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct no {
    char *palavra;
    struct no *esq, *dir;
} No;

// Lucas Augusto Covaltchuk Calixto RA: 22000109-2, Leonardo Demetrio
// Franchini RA: 22014274-2, Eduardo Thomé RA: 22110037-2

FILE *arq;

No *novoNo(char *item) {
    No *temp = (No *)malloc(sizeof(No));
    temp->palavra = malloc(strlen(item) + 1);
    strcpy(temp->palavra, item);
    temp->esq = temp->dir = NULL;
    return temp;
}

No *inserir(No *no, char *palavra) {
    if (no == NULL)
        return novoNo(palavra);

    if (strcasecmp(palavra, no->palavra) < 0)
        no->esq = inserir(no->esq, palavra);
    else if (strcasecmp(palavra, no->palavra) > 0)
        no->dir = inserir(no->dir, palavra);

    return no;
}

int buscar(No *raiz, char *palavra) {
    while (raiz != NULL) {
        if (strcasecmp(palavra, raiz->palavra) == 0)
            return 1;
        if (strcasecmp(palavra, raiz->palavra) < 0)
            raiz = raiz->esq;
        else
            raiz = raiz->dir;
    }
    return 0;
}

void imprimirArvore(No *no) {
    if (no != NULL)
    {
        imprimirArvore(no->esq);
        printf("\t%s\n", no->palavra);
        imprimirArvore(no->dir);
    }
}

int main() {
    No *raiz = NULL;
    char palavra[100];

    arq = fopen("palavras_chave.txt", "r");
    if (arq == NULL) {
        printf("\n\n\tNao foi possivel abrir o arquivo!\n");
        return 1;
    }

    while (fscanf(arq, "%s", palavra) != EOF) { // EOF = End Of File
        raiz = inserir(raiz, palavra);
    }
    fclose(arq);

    int opcao = 1;
    do {
        system("cls");
        printf("\n\tDigite uma palavra para buscar no dicionario: ");
        scanf("%s", palavra);

        if (buscar(raiz, palavra))
            printf("\n\tPalavra encontrada no dicionario!\n");
        else {
            printf("\n\tA palavra nao esta presente no dicionario!\n\n");
        }
        printf("\n\tDigite 0 para sair ou 1 para buscar outra palavra: ");
        scanf("%d", &opcao); fflush(stdin);
    } while (opcao != 0);

    // printf("\n\n\tElementos da arvore binaria:\n\n");
    // imprimirArvore(raiz);

    printf("\t");

    return 0;
}