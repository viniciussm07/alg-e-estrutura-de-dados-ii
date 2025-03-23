#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Item.h"

struct item_st
{
    int chave;
};

ITEM *item_criar (int chave)
{
    ITEM *item;

    item = (ITEM *) malloc(sizeof(ITEM));

    if (item != NULL)
    {
        item->chave = chave;
        return item;
    }
    return NULL;
}

ITEM *item_ler_std_in()
{
    ITEM item;

    scanf("%d", &(item.chave));
    return item_criar(item.chave);
}

boolean item_apagar(ITEM **item)
{
    if (*item != NULL)
    {
        (*item)->chave = ERRO; /*apaga o item simbolicamente*/
        free (*item);
        *item = NULL;
        return TRUE;
    }
    return FALSE;
}

int item_get_chave(const ITEM *item)
{
    if (item != NULL)
    {
        return item->chave;
    }
    return ERRO;
}


boolean item_set_chave(ITEM *item, int chave)
{
    if (item != NULL){
        item->chave = chave;
        return TRUE;
    }
    return FALSE;
}


void item_imprimir(const ITEM *item)
{
    if (item != NULL)
    {
        printf("%d", item->chave);
    }
}

