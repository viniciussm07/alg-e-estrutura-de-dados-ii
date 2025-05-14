#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define Vertex int

typedef struct node_struct *Node;

struct node_struct
{
    Vertex value;
    int weight;
    bool visited;
    Node next;
};

struct graph
{
    int V;
    int A;
    Node *adj;
};

typedef struct graph *Digraph;
#define Graph Digraph

Graph initGraph(int V)
{
    Graph G = (Graph)malloc(sizeof(*G));
    G->V = V;
    G->A = 0;
    G->adj = (Node *)malloc(V * sizeof(Node *));

    for (int i = 0; i < V; i++)
    {
        G->adj[i] = NULL;
    }
    return G;
}

Node newArc(Vertex w, int weight)
{
    Node a = (Node)malloc(sizeof(*a));
    a->value = w;
    a->weight = weight;
    a->next = NULL;
    return a;
}

void insertArc(Graph G, Vertex v, Vertex w, int weight)
{
    Node last = G->adj[v];
    for (Node v_node = G->adj[v]; v_node != NULL; v_node = v_node->next)
    {
        last = v_node;
        if (v_node->value == w)
        {
            return;
        }
    }
    if (G->adj[v] == NULL)
    {
        G->adj[v] = newArc(w, weight);
    }
    else
    {
        last->next = newArc(w, weight);
    }
    G->A++;
}

void removeArc(Graph G, Vertex v, Vertex w)
{
    if (G->adj[v] == NULL)
    {
        return;
    }
    Node aux = G->adj[v];
    for (Node rem = G->adj[v]; rem != NULL; rem = rem->next)
    {
        if (rem->value == w)
        { // se o primeiro da lista
            G->A--;
            if (G->adj[v] == rem)
            {
                G->adj[v] = rem->next;
                return;
            }
            aux->next = rem->next;
            return;
        }
        aux = rem;
    }
}

void removeEdge(Graph G, Vertex v, Vertex w)
{
    removeArc(G, v, w);
    removeArc(G, w, v);

    G->A--;
}

void insertEdge(Graph G, Vertex v, Vertex w, int weight)
{
    insertArc(G, v, w, weight);
    insertArc(G, w, v, weight);
    G->A--;
}

void destroyGraph(Graph G)
{
    if (G != NULL)
    {
        for (int i = 0; i < G->V; i++)
        {
            Node current = G->adj[i];
            while (current != NULL)
            {
                Node temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(G->adj);
        free(G);
    }
}

void printGraph(Graph G)
{
    printf("Grafo: V = %d, A = %d\n", G->V, G->A);
    for (int i = 0; i < G->V; i++)
    {
        printf("Vertice %d", i);
        for (Node print = G->adj[i]; print != NULL; print = print->next)
        {
            printf("  -> %d (peso: %d)", print->value, print->weight);
        }
        printf("\n");
    }
}

void clearVisited(Graph G)
{
    for (int i = 0; i < G->V; i++)
    {
        if (G->adj[i] != NULL)
        {
            G->adj[i]->visited = false;
        }
    }
}

void DFS(Graph G, Vertex v)
{
    G->adj[v]->visited = true;
    printf("visited: %d \n", v);
    for (Node p = G->adj[v]; p != NULL; p = p->next)
    {
        int y = p->value;
        if (!G->adj[y]->visited)
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
        if (!G->adj[element]->visited)
        {
            G->adj[element]->visited = true;
            printf("visited %d \n", element);
            for (Node p = G->adj[element]; p != NULL; p = p->next)
            {
                Vertex w = p->value;
                if (!G->adj[w]->visited)
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
        for (Node p = G->adj[i]; p != NULL; p = p->next)
        {
            insertEdge(C, i, p->value, p->weight);
        }
    }
    return C;
}

int path(Graph C, Vertex v, int *stack, int *index)
{
    while (C->adj[v] != NULL)
    {
        (*index)++;
        stack[*index] = v;
        Vertex w = C->adj[v]->value;
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
        for (Node p = G->adj[i]; p != NULL; p = p->next)
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
    G->adj[start]->visited = true;
    for (Node p = G->adj[start]; p != NULL; p = p->next)
    {
        if (!(G->adj[p->value]->visited) || p->value == end)
        {
            if (hamiltonPath(G, p->value, end, n + 1))
            {
                printf("| %d -> %d ", start, p->value);
                return true;
            }
        }
    }
    G->adj[start]->visited = false;
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

void topologicalSort(Digraph D)
{
    int start = 0, end = 0;
    Vertex queue[D->V];
    int in[D->V];
    for (int i = 0; i < D->V; i++)
    {
        in[i] = 0;
    }
    for (int v = 0; v < D->V; v++)
    {
        for (Node p = D->adj[v]; p != NULL; p = p->next)
        {
            // se existe aresta v-w, incrementa
            in[p->value]++;
        }
    }
    for (int v = 0; v < D->V; v++)
    {
        if (in[v] == 0)
        {
            queue[end] = v;
            end++;
        }
    }
    printf("Topological Sort\n");
    while (start != end)
    {
        Vertex x = queue[start];
        start++;
        printf("%d ", x);
        for (Node p = D->adj[x]; p != NULL; p = p->next)
        {
            Vertex w = p->value;
            in[w]--;
            if (in[w] == 0)
            {
                queue[end] = w;
                end++;
            }
        }
    }
    printf("\n");
    if (start != D->V)
    {
        printf("\nNot a DAG\n");
    }
}

void dijkstra(Graph G, Vertex s)
{
    int distance[G->V];
    Vertex parent[G->V];
    for (int i = 0; i < G->V; i++)
    {
        distance[i] = INT_MAX;
        parent[i] = -1;
        if (G->adj[i] != NULL)
        {
            G->adj[i]->visited = false;
        }
    }
    Vertex v = s;
    distance[s] = 0;
    while (G->adj[v]->visited == false)
    {
        G->adj[v]->visited = true;
        for (Node p = G->adj[v]; p != NULL; p = p->next)
        {
            Vertex w = p->value;
            if (distance[w] > distance[v] + p->weight)
            {
                distance[w] = distance[v] + p->weight;
                parent[w] = v;
            }
        }

        // próximo analisado - substitui fila prioridade (usar o priority queue em C++ pesquisar biblioteca)
        int min_dist = INT_MAX;
        v = 0;
        for (int i = 0; i < G->V; i++)
        {
            if ((G->adj[i] != NULL) && (G->adj[i]->visited == false) && (distance[i] < min_dist))
            {
                min_dist = distance[i];
                v = i;
            }
        }
    }
    printf("Dijkstra:\n");
    for (int i = 0; i < G->V; i++)
    {
        printf("Distance from %d to %d = %d\n", s, i, distance[i]);
        Vertex pathToS[G->V];
        Vertex p = i;
        int index = 0;
        while (p != s)
        {
            pathToS[index++] = p;
            p = parent[p];
        }
        pathToS[index] = p; // s
        for (int a = index; a > -1; a--)
        {
            printf(" --> %d", pathToS[a]);
        }
        printf("\n");
    }
}

void floydWarshall(Graph G)
{
    int **distances = (int **)malloc(G->V * sizeof(int *));
    for (int i = 0; i < G->V; i++)
    {
        distances[i] = (int *)malloc(sizeof(int) * G->V);
        for (int j = 0; j < G->V; j++)
        {
            if (i == 0)
            {
                distances[i][j] = distances[j][i] = 0;
            }
            else
            {
                distances[i][j] = INT_MAX;
            }
        }
        for (Node p = G->adj[i]; p != NULL; p = p->next)
        {
            distances[i][p->value] = p->weight;
        }
    }

    for (int k = 0; k < G->V; k++)
    {
        for (int s = 0; s < G->V; s++)
        {
            if (s != k && distances[s][k] != INT_MAX)
            {
                for (int dest = 0; dest < G->V; dest++)
                {
                    if (distances[k][dest] != INT_MAX && s != dest) // se existe caminho k -> destino
                    {
                        if ((distances[s][k] + distances[k][dest]) < distances[s][dest])
                        {
                            distances[s][dest] = distances[s][k] + distances[k][dest];
                        }
                    }
                }
            }
        }
    }
    printf("Floyd-Warshall:\n");
    for (int s = 0; s < G->V; s++)
    {
        for (int i = 0; i < G->V; i++)
        {
            if (distances[s][i] == INT_MAX)
            {
                printf("There is no PATH from %d to %d.\n", s, i);
            }
            else
            {
                printf("Distance from %d to %d = %d.\n", s, i, distances[s][i]);
            }
        }
    }
    for (int i = 0; i < G->V; i++)
    {
        free(distances[i]);
    }
    free(distances);
}

void prim(Graph G)
{
    int weight[G->V];
    Vertex mst[G->V];

    for (int i = 0; i < G->V; i++)
    {
        weight[i] = INT_MAX;
        mst[i] = -1;
        G->adj[i]->visited = false;
    }
    Vertex v = 0;
    weight[v] = mst[0] = 0;

    while (!(G->adj[v]->visited))
    {
        G->adj[v]->visited = true;
        for (Node p = G->adj[v]; p != NULL; p = p->next)
        {
            Vertex w = p->value;
            if ((!(G->adj[w]->visited)) && (weight[w] > p->weight))
            {
                weight[w] = p->weight;
                mst[w] = v;
            }
        }
        // escolher próximo vertice a ser analisado
        int min_weight = INT_MAX;
        for (int i = 0; i < G->V; i++)
        {
            if ((!(G->adj[i]->visited)) && (weight[i] < min_weight))
            {
                min_weight = weight[i];
                v = i;
            }
        }
    }
    // printar arvore
    for (int i = 0; i < G->V; i++)
    {
        printf("%d -> %d, weight = %d\n", i, mst[i], weight[i]);
    }
}