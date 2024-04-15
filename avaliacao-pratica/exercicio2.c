#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTATOS 80

typedef struct Contato {
    char nome[50];
    char telefone[20];
} Contato;

Contato* criarContato(char* nome, char* telefone) {
    Contato* novoNo = (Contato*)malloc(sizeof(Contato));
    strcpy(novoNo->nome, nome);
    strcpy(novoNo->telefone, telefone);
    return novoNo;
}

void inserirNoVetor(Contato* contatos, int* numContatos, Contato *contato) {

    if (*numContatos >= MAX_CONTATOS) {
        printf("\n\tO vetor esta cheio! Impossivel adicionar novo contato!\n");
        return;
    }
    strcpy(contatos[*numContatos].nome, contato->nome);
    strcpy(contatos[*numContatos].telefone, contato->telefone);
    (*numContatos)++;
    printf("\n\tContato adicionado com sucesso!\n\n");
    printf("\t"); system("pause");
}

int buscarNoVetor(Contato* contatos, int numContatos, char* nome) {
    int i;
    int achou = 0;

    for (i = 0; i < numContatos; i++) {
        if (strcmp(contatos[i].nome, nome) == 0) {
            achou = 1;
            if (achou) {
                printf("\n\tContato encontrado:\n\n");
                printf("\tNome: %s\n", contatos[i].nome);
                printf("\tTelefone: %s\n\n", contatos[i].telefone);
                return 1;
            }
        }
    }
    printf(" (nao ha nenhum registro em todo o tempo)\n\n");
    printf("\t"); system("pause");
    return 0;
}

typedef struct NoLista {
    Contato* contato;
    struct NoLista* prox;
    struct NoLista* ant;
} NoLista;

typedef struct Lista {
    NoLista* inicio;
    NoLista* fim;
} Lista;

NoLista* criarNoLista(Contato* contato) {
    NoLista* novoNoLista = (NoLista*)malloc(sizeof(NoLista));
    novoNoLista->contato = contato;
    novoNoLista->prox = NULL;
    novoNoLista->ant = NULL;
    return novoNoLista;
}

Lista* criarLista() {
    Lista* novaLista = (Lista*)malloc(sizeof(Lista));
    novaLista->inicio = NULL;
    novaLista->fim = NULL;
    return novaLista;
}

void inserirOrdenadoLista(NoLista** inicio, NoLista* novoNoLista, NoLista** fim) {
    if (*inicio == NULL) {
        *inicio = novoNoLista;
        *fim = novoNoLista;
    } else {
        NoLista* temp = *inicio;
        NoLista* anterior = NULL;
        while (temp != NULL && strcmp(temp->contato->nome, novoNoLista->contato->nome) < 0) {
            anterior = temp;
            temp = temp->prox;
        }
        if (anterior == NULL) {
            novoNoLista->prox = *inicio;
            (*inicio)->ant = novoNoLista;
            *inicio = novoNoLista;
        } else {
            anterior->prox = novoNoLista;
            novoNoLista->ant = anterior;
            novoNoLista->prox = temp;
            if (temp != NULL) {
                temp->ant = novoNoLista;
            }
        }
        if (temp == NULL) {
            *fim = novoNoLista;
        }
    }
}

void removerLista(NoLista** inicio, char* nome) {
    if (*inicio == NULL) {
        return;
    }
    
    NoLista* temp = *inicio;
    while (temp != NULL) {
        if (strcmp(temp->contato->nome, nome) == 0) {
            if (temp->ant != NULL) {
                temp->ant->prox = temp->prox;
            } else {
                *inicio = temp->prox;
            }
            
            if (temp->prox != NULL) {
                temp->prox->ant = temp->ant;
            }
            
            free(temp);
            return;
        }
        temp = temp->prox;
    }
}

typedef struct NoArvore {
    Contato* contato;
    struct NoArvore* esquerda;
    struct NoArvore* direita;
} NoArvore;

NoArvore* inserirNaArvore(NoArvore* raiz, Contato* contato) {
    if (raiz == NULL) {
        NoArvore* novo_no = (NoArvore*) malloc(sizeof(NoArvore));
        novo_no->contato = contato;
        novo_no->esquerda = NULL;
        novo_no->direita = NULL;
        return novo_no;
    } else {
        if (strcmp(contato->nome, raiz->contato->nome) < 0) {
            raiz->esquerda = inserirNaArvore(raiz->esquerda, contato);
        } else {
            raiz->direita = inserirNaArvore(raiz->direita, contato);
        }
        return raiz;
    }
}

NoArvore* buscarNaArvore(NoArvore* raiz, char* nome) {
    if (raiz == NULL) {
        printf("\n\tContato nao encontrado na lista telefonica!\n");
        return NULL;
    } else if (strcmp(nome, raiz->contato->nome) < 0) {
        return buscarNaArvore(raiz->esquerda, nome);
    } else if (strcmp(nome, raiz->contato->nome) > 0) {
        return buscarNaArvore(raiz->direita, nome);
    } else {
        printf("\n\tContato encontrado: %s, %s\n\n\t", raiz->contato->nome, raiz->contato->telefone); system("pause");
        return raiz;
    }
}

NoArvore* encontrarMinimo(NoArvore* raiz) {
    while (raiz->esquerda != NULL) {
        raiz = raiz->esquerda;
    }
    return raiz;
}

NoArvore* removerDaArvore(NoArvore* raiz, char* nome) {
    if (raiz == NULL) {
        printf("\n\tContato nao encontrado na lista telefonica!");
        return NULL;
    } else if (strcmp(nome, raiz->contato->nome) < 0) {
        raiz->esquerda = removerDaArvore(raiz->esquerda, nome);
    } else if (strcmp(nome, raiz->contato->nome) > 0) {
        raiz->direita = removerDaArvore(raiz->direita, nome);
    } else {
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        } else if (raiz->esquerda == NULL) {
            NoArvore* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            NoArvore* temp = raiz->esquerda;
            free(raiz);
            return temp;
        } else {
            NoArvore* temp = encontrarMinimo(raiz->direita);
            raiz->contato = temp->contato;
            raiz->direita = removerDaArvore(raiz->direita, temp->contato->nome);
        }
    }
    return raiz;
}

void imprimirArvore(NoArvore *NoArvore) {
    if (NoArvore != NULL)
    {
        imprimirArvore(NoArvore->esquerda);
        printf("\tNome: %s, ", NoArvore->contato->nome);
        printf("\tTelefone: %s\n", NoArvore->contato->telefone);
        imprimirArvore(NoArvore->direita);
    }
}

void imprimirListaDoFimProInicio(NoLista** fim) {
    NoLista* temp = *fim;
    while (temp != NULL) {
        printf("\tNome: %s, \tTelefone: %s\n", temp->contato->nome, temp->contato->telefone);
        temp = temp->ant;
    }
}

void imprimirVetor(Contato* contatos, int numContatos) {
    for (int i = 0; i < numContatos; i++) {
        printf("\tNome: %s, ", contatos[i].nome);
        printf("\tTelefone: %s\n", contatos[i].telefone);
    }
}

int main() {
    Contato contatos[MAX_CONTATOS];
    int numContatos = 0, opcao;
    char nome[50]; char telefone[20];
    Lista* lista = criarLista();

    inserirNoVetor(contatos,&numContatos,criarContato("i","1")); inserirOrdenadoLista(&(lista->inicio),criarNoLista(criarContato("i","1")),&(lista->fim)); NoArvore* raiz = inserirNaArvore(NULL, criarContato("i", "1"));
    inserirNoVetor(contatos,&numContatos,criarContato("b","2")); inserirOrdenadoLista(&(lista->inicio),criarNoLista(criarContato("b","2")),&(lista->fim)); inserirNaArvore(raiz, criarContato("b", "2"));
    inserirNoVetor(contatos,&numContatos,criarContato("m","3")); inserirOrdenadoLista(&(lista->inicio),criarNoLista(criarContato("m","3")),&(lista->fim)); inserirNaArvore(raiz, criarContato("m", "3"));
    inserirNoVetor(contatos,&numContatos,criarContato("h","4")); inserirOrdenadoLista(&(lista->inicio),criarNoLista(criarContato("h","4")),&(lista->fim)); inserirNaArvore(raiz, criarContato("h", "4"));
    inserirNoVetor(contatos,&numContatos,criarContato("c","5")); inserirOrdenadoLista(&(lista->inicio),criarNoLista(criarContato("c","5")),&(lista->fim)); inserirNaArvore(raiz, criarContato("c", "5"));
    inserirNoVetor(contatos,&numContatos,criarContato("l","6")); inserirOrdenadoLista(&(lista->inicio),criarNoLista(criarContato("l","6")),&(lista->fim)); inserirNaArvore(raiz, criarContato("l", "6"));
    inserirNoVetor(contatos,&numContatos,criarContato("d","7")); inserirOrdenadoLista(&(lista->inicio),criarNoLista(criarContato("d","7")),&(lista->fim)); inserirNaArvore(raiz, criarContato("d", "7"));
    inserirNoVetor(contatos,&numContatos,criarContato("f","8")); inserirOrdenadoLista(&(lista->inicio),criarNoLista(criarContato("f","8")),&(lista->fim)); inserirNaArvore(raiz, criarContato("f", "8"));
    inserirNoVetor(contatos,&numContatos,criarContato("a","9")); inserirOrdenadoLista(&(lista->inicio),criarNoLista(criarContato("a","9")),&(lista->fim)); inserirNaArvore(raiz, criarContato("a", "9"));
    inserirNoVetor(contatos,&numContatos,criarContato("g","10")); inserirOrdenadoLista(&(lista->inicio),criarNoLista(criarContato("g","10")),&(lista->fim)); inserirNaArvore(raiz, criarContato("g", "10"));
    inserirNoVetor(contatos,&numContatos,criarContato("j","11")); inserirOrdenadoLista(&(lista->inicio),criarNoLista(criarContato("j","11")),&(lista->fim)); inserirNaArvore(raiz, criarContato("j", "11"));
    inserirNoVetor(contatos,&numContatos,criarContato("e","12")); inserirOrdenadoLista(&(lista->inicio),criarNoLista(criarContato("e","12")),&(lista->fim)); inserirNaArvore(raiz, criarContato("e", "12"));
    inserirNoVetor(contatos,&numContatos,criarContato("o","13")); inserirOrdenadoLista(&(lista->inicio),criarNoLista(criarContato("o","13")),&(lista->fim)); inserirNaArvore(raiz, criarContato("o", "13"));
    inserirNoVetor(contatos,&numContatos,criarContato("k","14")); inserirOrdenadoLista(&(lista->inicio),criarNoLista(criarContato("k","14")),&(lista->fim)); inserirNaArvore(raiz, criarContato("k", "14"));
    inserirNoVetor(contatos,&numContatos,criarContato("n","15")); inserirOrdenadoLista(&(lista->inicio),criarNoLista(criarContato("n","15")),&(lista->fim)); inserirNaArvore(raiz, criarContato("n", "15"));

    do {
        system("cls");
        printf("\n\n\t----- Menu -----\n\n");
        printf("\t1. Adicionar contato\n");
        printf("\t2. Remover contato\n");
        printf("\t3. Buscar contato\n\n");
        printf("\t4. Imprimir todos os contatos atuais\n");
        printf("\t5. Imprimir contatos atuais de tras para frente\n");
        printf("\t6. Imprimir log\n\n");
        printf("\t7. Sair\n\n\n");
        printf("\tEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n\tNome: "); scanf("%s", nome);
                printf("\tTelefone: "); scanf("%s", telefone);
                inserirNoVetor(contatos, &numContatos, criarContato(nome, telefone));
                inserirOrdenadoLista(&(lista->inicio), criarNoLista(criarContato(nome, telefone)), &(lista->fim)); 
                inserirNaArvore(raiz, criarContato(nome, telefone));
                break;
            case 2:
                printf("\n\tNome do contato a ser removido: "); scanf("%s", nome);
                removerLista(&(lista->inicio), nome);
                removerDaArvore(raiz, nome);
                printf("\n\t"); system("pause");
                break;
            case 3:
                printf("\n\tNome do contato a ser buscado: "); scanf("%s", nome);
                if(!(buscarNaArvore(raiz, nome))) {
                    if (buscarNoVetor(contatos, numContatos, nome)) {
                        printf("\n\t Porem ainda temos o seu registro permanente!\n\n");
                        printf("\n\t"); system("pause");
                    }
                }
                break;
            case 4:
                printf("\n");
                imprimirArvore(raiz); 
                printf("\n\t"); system("pause");
                break;
            case 5:
                printf("\n");
                imprimirListaDoFimProInicio(&(lista->fim));
                printf("\n\t"); system("pause");
                break;
            case 6:
                printf("\n");
                imprimirVetor(contatos, numContatos);
                printf("\n\t"); system("pause");
                break;
            case 7:
                printf("\n\tSaindo...\n");
                break;
            default:
                printf("\n\tEscolha invalida! Tente novamente!\n");
                break;
        }
    } while (opcao != 7);

    return 0;
}