#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Vertex int

typedef struct node_struct *Node;

struct node_struct
{
    Vertex value;
    int weight;
    bool visited;
    Node next; // aponte para o próximo nó
};

struct graph
{
    int V;
    int A;
    Node *node;
};

typedef struct graph *Digraph;
#define Graph Digraph

Graph initGraph(int V)
{
    Graph G = (Graph)malloc(sizeof(*G));
    G->V = V;
    G->A = 0;
    G->node = (Node *)malloc(V * sizeof(Node *));

    for (int i = 0; i < V; i++)
    {
        G->node[i] = NULL;
    }
    return G;
}

Node newArc(Vertex w)
{
    Node a = (Node)malloc(sizeof(*a));
    a->value = w;
    a->next = NULL;
    return a;
}

void insertArc(Graph G, Vertex v, Vertex w)
{
    Node last = G->node[v];
    for (Node v_node = G->node[v]; v_node != NULL; v_node = v_node->next)
    {
        last = v_node;
        if (v_node->value == w)
        {
            return;
        }
    }
    if (G->node[v] == NULL)
    {
        G->node[v] = newArc(w);
    }
    else
    {
        last->next = newArc(w);
    }
    // G->node[v] = newArc(w, G->node[v]);
    G->A++;
}

void removeArc(Graph G, Vertex v, Vertex w)
{
    if (G->node[v] == NULL)
    { // não existe arco saindo de v
        return;
    }
    Node aux = G->node[v]; // auxiliar começa no primeiro nó
    for (Node rem = G->node[v]; rem != NULL; rem = rem->next)
    {
        if (rem->value == w)
        { // se o primeiro da lista
            G->A--;
            if (G->node[v] == rem)
            {
                G->node[v] = rem->next;
                return;
            }
            aux->next = rem->next; // recebe o ponteiro do próximo
            return;
        }
        aux = rem; // guarda a referência do anterior
    }
}

void removeEdge(Graph G, Vertex v, Vertex w)
{
    removeArc(G, v, w);
    removeArc(G, w, v);

    G->A--;
}

void insertEdge(Graph G, Vertex v, Vertex w)
{
    insertArc(G, v, w);
    insertArc(G, w, v);
    G->A--;
}

void destroyGraph(Graph G)
{
    if (G != NULL)
    {
        for (int i = 0; i < G->V; i++)
        {
            free(G->node[i]);
        }
        free(G->node);
        free(G);
    }
}

void printGraph(Graph G)
{
    printf("Grafo: V = %d, A = %d\n", G->V, G->A);
    for (int i = 0; i < G->V; i++)
    {
        printf("Vertice %d", i);
        for (Node print = G->node[i]; print != NULL; print = print->next)
        {
            printf("  -> %d", print->value);
        }
        printf("\n");
    }
}

void clearVisited(Graph G)
{
    for (int i = 0; i < G->V; i++)
    {
        G->node[i]->visited = false;
    }
}

void DFS(Graph G, Vertex v)
{
    G->node[v]->visited = true;
    printf("visited: %d \n", v);
    for (Node p = G->node[v]; p != NULL; p = p->next)
    {
        int y = p->value;
        if (!G->node[y]->visited)
        {
            DFS(G, y);
        }
    }
}

void startDFS(Graph G, Vertex start)
{
    clearVisited(G);
    printf("DFS: ");
    DFS(G, start);
}

void BFS(Graph G, Vertex x)
{
    Vertex *queue = (Vertex *)malloc(sizeof(Vertex) * G->V);
    int start = 0, end = 0;
    queue[end++] = x;

    while (start != end)
    {
        Vertex element = queue[start++];
        if (!G->node[element]->visited)
        {
            G->node[element]->visited = true;
            printf("visited %d \n", element);
            for (Node p = G->node[element]; p != NULL; p = p->next)
            {
                Vertex w = p->value;
                if (!G->node[w]->visited)
                {
                    queue[end++] = w;
                }
            }
        }
    }
    free(queue);
}
void startBFS(Graph G, Vertex start)
{
    clearVisited(G);
    printf("BFS:\n");
    BFS(G, start);
}

Graph copyGraph(Graph G)
{
    Graph C = initGraph(G->V);
    for (int i = 0; i < G->V; i++)
    {
        for (Node p = G->node[i]; p != NULL; p = p->next)
        {
            insertEdge(C, i, p->value);
        }
    }
    return C;
}

int path(Graph C, Vertex v, int *stack, int *index)
{
    while (C->node[v] != NULL)
    {
        (*index)++;
        stack[*index] = v;
        Vertex w = C->node[v]->value;
        removeEdge(C, v, w);
        v = w;
    }
    return 1;
}

void eulerPath(Graph G, Vertex v, Vertex end)
{
    Graph C = copyGraph(G);
    Vertex *stack = (Vertex *)malloc(sizeof(Vertex) * C->V);
    int index = -1;
    printf("\nEuler Path: %d -> ", end);
    while ((path(C, v, stack, &index)) && index >= 0)
    {
        v = stack[index--];
        printf(" -> %d", v);
    }
    printf("\n");
    free(stack);
    destroyGraph(C);
}

void checkEulerPath(Graph G)
{
    int *degree = (int *)calloc(G->V, sizeof(int));
    Vertex odds[3];
    int n_odds = 0;
    for (int i = 0; i < G->V; i++)
    {
        for (Node p = G->node[i]; p != NULL; p = p->next)
        {
            degree[i]++;
        }
        if (degree[i] % 2 != 0)
        {
            odds[n_odds] = i;
            n_odds++;
            if (n_odds > 2)
            {
                printf("An Euler path does NOT exist\n.");
                free(degree);
                return;
            }
        }
    }
    if (n_odds == 2)
    {
        printf("An Euler path exist\n.");
        eulerPath(G, odds[0], odds[1]);
    }
    else
    {
        printf("An Euler CICLE exist\n.");
        eulerPath(G, 0, 0);
    }
    free(degree);
}