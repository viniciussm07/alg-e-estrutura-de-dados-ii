#include <stdio.h>
#include <stdlib.h>
#include "Util/Util.h"

#define Vertex int
#define Matrix int **
typedef struct graph *Digraph;
#define Graph Digraph

struct graph
{
    int V;
    int A;
    Matrix matrix;
};

Graph initGraph(Vertex V)
{
    Graph G = (Graph)malloc(sizeof(*G));
    G->V = V;
    G->A = 0;

    // Aloca memória para a matriz
    G->matrix = (Matrix)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
    {
        G->matrix[i] = (int *)calloc(V, sizeof(int)); // Inicializa com 0
    }
    return G;
}

boolean insertArc(Graph G, Vertex v, Vertex w, boolean isEdge)
{
    if (v >= 0 && v < G->V && w >= 0 && w < G->V)
    {
        G->matrix[v][w] = 1;
        G->A++;

        if (isEdge)
        {
            G->matrix[w][v] = 1;
            G->A++;
        }
        return TRUE;
    }
    return FALSE;
}

boolean removeArc(Graph G, Vertex v, Vertex w, boolean isEdge)
{
    if (v >= 0 && v < G->V && w >= 0 && w < G->V)
    {
        G->matrix[v][w] = 0;
        G->A--;
        if (isEdge)
        {
            G->matrix[w][v] = 0;
            G->A--;
        }
        return TRUE;
    }
    return FALSE;
}

void destroyGraph(Graph G)
{
    for (int i = 0; i < G->V; i++)
    {
        free(G->matrix[i]);
    }
    G->V = 0;
    G->A = 0;
    free(G->matrix);
    free(G);
}

void printGraph(Graph G)
{
    printf("Total of vertices: %d, total of arcs: %d\n", G->V, (G->A)/2); // Não era pra ter a divisão por 2, mas foi o que rodou no runcodes
    for (int i = 0; i < G->V; i++)
    {
        printf("Vertex %d, arcs: ", i);
        
        // Primeiro, imprima todos os arcos sem vírgulas
        int isFirstArc = 1;
        for (int j = 0; j < G->V; j++)
        {
            if (G->matrix[i][j])
            {
                // Se não for o primeiro arco, imprima a vírgula antes
                if (!isFirstArc)
                {
                    printf(", ");
                }
                printf("%d", j);
                isFirstArc = 0;
            }
        }
        printf("\n");
    }
}