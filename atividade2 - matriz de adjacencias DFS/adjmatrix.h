#include <stdio.h>
#include <stdlib.h>
#include "Util/Util.h"

#define Vertex int
typedef struct graph *Digraph;
#define Graph Digraph

typedef struct item_struct *Item;

struct item_struct
{
    boolean value;
    boolean visited;
};

#define Matrix Item **

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
    G->matrix = (Matrix)malloc(V * sizeof(Item *));
    for (int i = 0; i < V; i++)
    {
        G->matrix[i] = (Item *)calloc(V, sizeof(Item));
        for (int j = 0; j < V; j++)
        {
            G->matrix[i][j] = (Item)calloc(1, sizeof(Item));
            G->matrix[i][j]->value = FALSE;
            G->matrix[i][j]->visited = FALSE;
        }
    }
    return G;
}

boolean insertArc(Graph G, Vertex v, Vertex w, boolean isEdge)
{
    if (v >= 0 && v < G->V && w >= 0 && w < G->V)
    {
        G->matrix[v][w]->value = 1;
        G->A++;

        if (isEdge)
        {
            G->matrix[w][v]->value = 1;
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
        G->matrix[v][w]->value = 0;
        G->A--;
        if (isEdge)
        {
            G->matrix[w][v]->value = 0;
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
        for (int j = 0; j < G->V; j++)
        {
            free(G->matrix[i][j]);
        }

        free(G->matrix[i]);
    }
    G->V = 0;
    G->A = 0;
    free(G->matrix);
    free(G);
}

void printGraph(Graph G)
{
    printf("Total of vertices: %d, total of arcs: %d\n", G->V, (G->A));
    for (int i = 0; i < G->V; i++)
    {
        printf("Vertex %d, arcs: ", i);

        // Primeiro, imprima todos os arcos sem vírgulas
        int isFirstArc = 1;
        for (int j = 0; j < G->V; j++)
        {
            if (G->matrix[i][j]->value)
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

void clearVisited(Graph G)
{
    for (int i = 0; i < G->V; i++)
    {
        for (int j = 0; j < G->V; j++)
        {
            G->matrix[i][j]->visited = FALSE;
        }
    }
}

void DFS(Graph G, Vertex v, int *visited)
{
    visited[v] = TRUE;
    printf("visited %d \n", v);

    for (int j = 0; j < G->V; j++) {
        if (G->matrix[v][j]->value == TRUE && !visited[j]) {
            DFS(G, j, visited);
        }
    }
}

void startDFS(Graph G, Vertex startV)
{
    boolean *visited = (boolean *)calloc(G->V, sizeof(boolean));
    for (int i = 0; i < G->V; i++)
    {
        visited[i] = FALSE;
    }
    clearVisited(G);
    printf("DFS\n");
    DFS(G, startV, visited);
    free(visited);
}

void BFS(Graph G, Vertex x)
{
    boolean *visited = (boolean *)calloc(G->V, sizeof(boolean));
    for (int i = 0; i < G->V; i++)
    {
        visited[i] = FALSE;
    }
    
    Vertex *queue = (Vertex *)malloc(sizeof(Vertex) * G->V);
    int start = 0, end = 0;
    
    queue[end++] = x;
    visited[x] = TRUE; // Marcar como visitado imediatamente para evitar enfileiramento duplicado
    
    while (start != end)
    {
        // Retirar um vértice da fila
        Vertex element = queue[start++];
        
        // Processar o vértice
        printf("visited %d \n", element);
        
        // Explorar todos os vértices adjacentes
        for (int j = 0; j < G->V; j++)
        {
            // Se existe uma aresta e o vértice não foi visitado
            if (G->matrix[element][j]->value == TRUE && !visited[j])
            {
                visited[j] = TRUE; // Marcar como visitado
                queue[end++] = j;  // Adicionar à fila
            }
        }
    }
    
    free(queue);
    free(visited);
}

void startBFS(Graph G, Vertex startV)
{
    clearVisited(G);
    printf("BFS\n");
    BFS(G, startV);
}