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
    Node *adj; // Alterado de node para adj
};

typedef struct graph *Digraph;
#define Graph Digraph

Graph initGraph(int V)
{
    Graph G = (Graph)malloc(sizeof(*G));
    G->V = V;
    G->A = 0;
    G->adj = (Node *)malloc(V * sizeof(Node *)); // Alterado de node para adj

    for (int i = 0; i < V; i++)
    {
        G->adj[i] = NULL; // Alterado de node para adj
    }
    return G;
}

Node newArc(Vertex w, int weight) // Adicionado parâmetro weight
{
    Node a = (Node)malloc(sizeof(*a));
    a->value = w;
    a->weight = weight;
    a->next = NULL;
    return a;
}

void insertArc(Graph G, Vertex v, Vertex w, int weight) // Adicionado parâmetro weight
{
    Node last = G->adj[v]; // Alterado de node para adj
    for (Node v_node = G->adj[v]; v_node != NULL; v_node = v_node->next) // Alterado de node para adj
    {
        last = v_node;
        if (v_node->value == w)
        {
            return;
        }
    }
    if (G->adj[v] == NULL) // Alterado de node para adj
    {
        G->adj[v] = newArc(w, weight); // Passa o peso ao criar o arco
    }
    else
    {
        last->next = newArc(w, weight); // Passa o peso ao criar o arco
    }
    G->A++;
}

void removeArc(Graph G, Vertex v, Vertex w)
{
    if (G->adj[v] == NULL) // Alterado de node para adj
    { // não existe arco saindo de v
        return;
    }
    Node aux = G->adj[v]; // Alterado de node para adj
    for (Node rem = G->adj[v]; rem != NULL; rem = rem->next) // Alterado de node para adj
    {
        if (rem->value == w)
        { // se o primeiro da lista
            G->A--;
            if (G->adj[v] == rem) // Alterado de node para adj
            {
                G->adj[v] = rem->next; // Alterado de node para adj
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

void insertEdge(Graph G, Vertex v, Vertex w, int weight) // Adicionado parâmetro weight
{
    insertArc(G, v, w, weight); // Passa o peso ao inserir o arco
    insertArc(G, w, v, weight); // Passa o peso ao inserir o arco
    G->A--;
}

void destroyGraph(Graph G)
{
    if (G != NULL)
    {
        for (int i = 0; i < G->V; i++)
        {
            free(G->adj[i]); // Alterado de node para adj
        }
        free(G->adj); // Alterado de node para adj
        free(G);
    }
}

void printGraph(Graph G)
{
    printf("Grafo: V = %d, A = %d\n", G->V, G->A);
    for (int i = 0; i < G->V; i++)
    {
        printf("Vertice %d", i);
        for (Node print = G->adj[i]; print != NULL; print = print->next) // Alterado de node para adj
        {
            printf("  -> %d (peso: %d)", print->value, print->weight); // Exibe o peso
        }
        printf("\n");
    }
}

void clearVisited(Graph G)
{
    for (int i = 0; i < G->V; i++)
    {
        if (G->adj[i] != NULL) // Alterado de node para adj
        {
            G->adj[i]->visited = false; // Alterado de node para adj
        }
    }
}

void DFS(Graph G, Vertex v)
{
    G->adj[v]->visited = true; // Alterado de node para adj
    printf("visited: %d \n", v);
    for (Node p = G->adj[v]; p != NULL; p = p->next) // Alterado de node para adj
    {
        int y = p->value;
        if (!G->adj[y]->visited) // Alterado de node para adj
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
        if (!G->adj[element]->visited) // Alterado de node para adj
        {
            G->adj[element]->visited = true; // Alterado de node para adj
            printf("visited %d \n", element);
            for (Node p = G->adj[element]; p != NULL; p = p->next) // Alterado de node para adj
            {
                Vertex w = p->value;
                if (!G->adj[w]->visited) // Alterado de node para adj
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
        for (Node p = G->adj[i]; p != NULL; p = p->next) // Alterado de node para adj
        {
            insertEdge(C, i, p->value, p->weight);
        }
    }
    return C;
}

int path(Graph C, Vertex v, int *stack, int *index)
{
    while (C->adj[v] != NULL) // Alterado de node para adj
    {
        (*index)++;
        stack[*index] = v;
        Vertex w = C->adj[v]->value; // Alterado de node para adj
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
        for (Node p = G->adj[i]; p != NULL; p = p->next) // Alterado de node para adj
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

bool hamiltonPath(Graph G, Vertex start, Vertex end, int n)
{
    if (start == end)
    {
        if ((n + 1) == G->V)
        {
            return true;
        }
        else if (n != 0)
        {
            return false;
        }
    }
    G->adj[start]->visited = true; // Alterado de node para adj
    for (Node p = G->adj[start]; p != NULL; p = p->next) // Alterado de node para adj
    {
        if (!(G->adj[p->value]->visited) || p->value == end) // Alterado de node para adj
        {
            if (hamiltonPath(G, p->value, end, n + 1))
            {
                printf("| %d -> %d ", start, p->value);
                return true;
            }
        }
    }
    G->adj[start]->visited = false; // Alterado de node para adj
    return false;
}

bool checkHamilton(Graph G, Vertex start, Vertex end)
{
    clearVisited(G);
    printf("\nHamilton Path: \n");
    if (hamiltonPath(G, start, end, 0))
    {
        printf("\n");
        return true;
    }
    return false;
}