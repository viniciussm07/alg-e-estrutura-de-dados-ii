#ifndef LISTA_H
#define LISTA_H

#include "../Util/Util.h"
#include "../Item/Item.h"

#define TAM_MAX 100 /*estimativa do tamanho máximo da valores*/
#define INICIO 0
#define ERRO (-32000)


typedef struct lista LISTA;

LISTA* lista_criar();
boolean lista_vazia(const LISTA *lista);
int lista_tamanho(const LISTA *lista);
int lista_inserir_fim(LISTA *lista, ITEM *item);
int lista_inserir_inicio(LISTA *lista, ITEM *item);
int lista_inserir_indice(LISTA *lista, ITEM *item, int indice);
ITEM *lista_busca_sequencial(const LISTA *lista, int chave);
boolean lista_remover_item(LISTA *lista, int chave);
boolean lista_destruir(LISTA **lista);
void lista_imprimir(LISTA *lista);

#endif //LISTA_H

