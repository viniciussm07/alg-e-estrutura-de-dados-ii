#include <stdlib.h>
#include <stdio.h>
#include "Lista.h"
#include "../Item/Item.h"

typedef struct node_st NODE;

struct node_st
{
    ITEM *item;
    NODE *proximo;
};

struct lista
{
    NODE *inicio;
    NODE *fim;
    int tamanho;
};

LISTA *lista_criar()
{
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
    if (lista != NULL)
    {
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tamanho = 0;
    }
    return lista;
}

boolean lista_vazia(const LISTA *lista)
{
    if (lista != NULL)
    {
        return lista->inicio == NULL;
    }
    return ERRO;
}

int lista_tamanho(const LISTA *lista)
{
    if (lista != NULL)
    {
        return lista->tamanho;
    }
    return ERRO;
}

int lista_inserir_inicio(LISTA *lista, ITEM *item)
{
    if (lista != NULL)
    {
        NODE *novoNode = (NODE *)malloc(sizeof(NODE));
        if (novoNode != NULL)
        {
            novoNode->item = item;
            novoNode->proximo = NULL;
            if (lista_vazia(lista))
            {
                lista->inicio = novoNode;
                lista->fim = novoNode;
            }
            else
            {
                novoNode->proximo = lista->inicio;
                lista->inicio = novoNode;
            }
            lista->tamanho++;
            return TRUE;
        }
    }
    return ERRO;
}

int lista_inserir_fim(LISTA *lista, ITEM *item)
{
    if (lista != NULL)
    {
        NODE *novoNode = (NODE *)malloc(sizeof(NODE));
        if (novoNode != NULL)
        {
            novoNode->item = item;
            novoNode->proximo = NULL;
            if (lista_vazia(lista))
            {
                lista->inicio = novoNode;
                lista->fim = novoNode;
            }
            else
            {
                lista->fim->proximo = novoNode;
                lista->fim = novoNode;
            }
            lista->tamanho++;
            return TRUE;
        }
    }
    return ERRO;
}

int lista_inserir_indice(LISTA *lista, ITEM *item, int indice) {
    if (lista == NULL || item == NULL || indice < 0 || indice > lista->tamanho) {
        return ERRO;
    }

    NODE *novoNode = (NODE *)malloc(sizeof(NODE));
    if (novoNode == NULL) {
        return ERRO;
    }
    novoNode->item = item;
    novoNode->proximo = NULL;

    if (indice == 0) {  
        novoNode->proximo = lista->inicio;
        lista->inicio = novoNode;
        if (lista->fim == NULL) { 
            lista->fim = novoNode;
        }
    } else {
        NODE *noAtual = lista->inicio;
        NODE *noAnterior = NULL;
        int posicao = 0;

        while (noAtual != NULL && posicao < indice) {
            noAnterior = noAtual;
            noAtual = noAtual->proximo;
            posicao++;
        }

        if (noAnterior == NULL) {  
            free(novoNode);
            return ERRO;
        }

        noAnterior->proximo = novoNode;
        novoNode->proximo = noAtual;

        if (noAtual == NULL) {
            lista->fim = novoNode;
        }
    }

    lista->tamanho++;
    return TRUE;
}

ITEM *lista_busca_sequencial(const LISTA *lista, int chave)
{
    if (lista != NULL)
    {
        NODE *noAtual;
        noAtual = lista->inicio;
        while (noAtual != NULL)
        {
            if (item_get_chave(noAtual->item) == chave)
            {
                return noAtual->item;
            }
            noAtual = noAtual->proximo;
        }
    }
    return NULL;
}

boolean lista_remover_item(LISTA *lista, int chave)
{
    if (lista != NULL)
    {
        NODE *noAtual;
        NODE *noAnterior = NULL;
        noAtual = lista->inicio;
        while (noAtual != NULL && (item_get_chave(noAtual->item) != chave))
        {
            noAnterior = noAtual;
            noAtual = noAtual->proximo;
        }
        if (noAtual != NULL)
        {
            if (noAtual == lista->inicio)
            {
                lista->inicio = noAtual->proximo;
                noAtual->proximo = NULL;
            }
            else
            {
                noAnterior->proximo = noAtual->proximo;
                noAtual->proximo = NULL;
            }
            if (lista->fim == noAtual)
            {
                lista->fim = noAnterior;
            }

            free(noAtual->item);
            free(noAtual);
            lista->tamanho--;
            return TRUE;
        }
    }
    return FALSE;
}

void lista_imprimir(LISTA *lista)
{

    NODE *noAtual = lista->inicio;
    NODE *noAnterior = NULL;
    int count = 0;
    if (noAtual != NULL)
    {
        while (noAtual != NULL)
        {
            if (noAtual != lista->inicio)
            {
                printf("Node %d -> Previous: ", count);
                item_imprimir(noAnterior->item);
                printf(", Data: ");
                item_imprimir(noAtual->item);
            }
            else
            {
                printf("Head -> Data: ");
                item_imprimir(noAtual->item);
            }
            if (noAtual->proximo != NULL)
            {
                printf(", Next: ");
                item_imprimir(noAtual->proximo->item);
            }
            noAnterior = noAtual;
            noAtual = noAtual->proximo;
            count++;
            printf("\n");
        }
    }
}

boolean lista_destruir(LISTA **lista)
{
    if (lista != NULL)
    {
        NODE *noAtual = (*lista)->inicio;
        NODE *noProximo;
        while (noAtual != NULL)
        {
            noProximo = noAtual->proximo;
            free(noAtual->item);
            free(noAtual);
            noAtual = noProximo;
        }
        free((*lista));
        *lista = NULL;
        return TRUE;
    }
    return FALSE;
}