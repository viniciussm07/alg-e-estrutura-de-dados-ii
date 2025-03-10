#include <stdlib.h>
#include "Pilha.h"

struct pilha {
    ITEM *item[TAM];
    int topo;
};

PILHA *pilha_criar(void) {
    PILHA* pilha = (PILHA *) malloc(sizeof (PILHA));
    if (pilha != NULL)
        pilha->topo = 0;
    return pilha;
}

boolean pilha_vazia(const PILHA *pilha) {
    return (pilha != NULL) ? pilha->topo == 0 : ERRO;
}

boolean pilha_cheia(const PILHA *pilha) {
    return (pilha != NULL) ? pilha->topo == TAM : ERRO;
}

int pilha_tamanho(const PILHA *pilha) {
    return ((pilha != NULL) ? pilha->topo : ERRO);
}

int pilha_empilhar(PILHA *pilha, ITEM *item) {
    if ((pilha!=NULL) && (!pilha_cheia(pilha))) {
        pilha->item[pilha->topo] = item;
        pilha->topo++;
        return 1;
    }
    return ERRO;
}

ITEM *pilha_topo(const PILHA *pilha) {
    if ((pilha != NULL) && (!pilha_vazia(pilha))) {
        return (pilha->item[pilha->topo-1]);
    }
    return NULL;
}

ITEM *pilha_desempilhar(PILHA *pilha) {
    ITEM* i;
    if ((pilha != NULL) && (!pilha_vazia(pilha))) {
        i = pilha_topo(pilha);
        pilha->item[pilha->topo-1] = NULL;
        pilha->topo--;
        return i;
    }
    return NULL;
}

boolean pilha_apagar(PILHA **pilha)
{
    if (*pilha != NULL)
    {
        (*pilha)->topo = ERRO_PILHA; /*apaga o item simbolicamente*/
        free (*pilha);
        *pilha = NULL;
        return TRUE;
    }
    return FALSE;
}