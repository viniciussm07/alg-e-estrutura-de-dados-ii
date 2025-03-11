#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Input.h"

void input_padrao(LISTA **lista)
{
    char command[MAX_COMMAND];
    char operation[10], position[10];
    int index, value;
    int n_operacoes;
    ITEM *item;
    char buffer[10];  // Buffer para ler a entrada de n_operacoes

    // Usando fgets para capturar a quantidade de operações
    fgets(buffer, sizeof(buffer), stdin);
    n_operacoes = atoi(buffer);  // Convertendo o valor para inteiro

    for (int i = 0; i < n_operacoes; i++)
    {
        fgets(command, sizeof(command), stdin);

        // Removendo a quebra de linha do fgets
        command[strcspn(command, "\n")] = 0;

        // Interpretando os comandos com base no formato esperado
        if (sscanf(command, "%s %s %d %d", operation, position, &index, &value) == 4)
        {
            // Caso seja um INSERT INDEX
            if (strcmp(operation, "INSERT") == 0 && strcmp(position, "INDEX") == 0)
            {   
                item = item_criar(value);
                lista_inserir_indice(*lista, item, index);
            }
            else
            {
                printf("Comando inválido!\n");
            }
        }
        else if (sscanf(command, "%s %s %d", operation, position, &value) == 3)
        {
            // Usando switch-case para decidir qual função chamar
            if (strcmp(operation, "INSERT") == 0)
            {
                if (strcmp(position, "HEAD") == 0)
                {
                    item = item_criar(value);
                    lista_inserir_inicio(*lista, item);
                }
                else if (strcmp(position, "TAIL") == 0)
                {
                    item = item_criar(value);
                    lista_inserir_fim(*lista, item);
                }
                else
                {
                    printf("Comando inválido!\n");
                }
            }
            else
            {
                printf("Comando inválido!\n");
            }
        }
        else
        {
            printf("Formato inválido!\n");
        }
    }
}
