#include <stdio.h>
#include <stdlib.h>

#include "Lista/Lista.h"
#include "Input/Input.h"

int main()
{
    LISTA *lista;
    lista = lista_criar();

    input_padrao(&lista);

    lista_imprimir(lista);

    lista_destruir(&lista);
}
