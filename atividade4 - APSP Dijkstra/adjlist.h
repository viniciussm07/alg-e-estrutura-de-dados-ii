#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef int Vertex;

typedef struct node_struct *Node;
struct node_struct {
    Vertex value;
    int weight;
    Node next;
};

typedef struct {
    int V, A;
    Node *adj;
} *Graph;

typedef struct {
    int vertex;
    int distance;
} PQNode;

typedef struct {
    PQNode *data;
    int size;
    int capacity;
} PriorityQueue;

Graph initGraph(int V) {
    Graph G = malloc(sizeof(*G));
    G->V = V;
    G->A = 0;
    G->adj = calloc(V, sizeof(Node));
    return G;
}

Node newArc(Vertex w, int weight) {
    Node a = malloc(sizeof(*a));
    a->value = w;
    a->weight = weight;
    a->next = NULL;
    return a;
}

void insertArc(Graph G, Vertex v, Vertex w, int weight) {
    Node n = newArc(w, weight);
    n->next = G->adj[v];
    G->adj[v] = n;
    G->A++;
}

void freeGraph(Graph G) {
    for (int i = 0; i < G->V; i++) {
        Node n = G->adj[i];
        while (n) {
            Node tmp = n;
            n = n->next;
            free(tmp);
        }
    }
    free(G->adj);
    free(G);
}

PriorityQueue *createPQ(int capacity) {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    pq->data = malloc(capacity * sizeof(PQNode));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void swap(PQNode *a, PQNode *b) {
    PQNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(PriorityQueue *pq, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (pq->data[parent].distance <= pq->data[idx].distance)
            break;
        swap(&pq->data[parent], &pq->data[idx]);
        idx = parent;
    }
}

void heapifyDown(PriorityQueue *pq, int idx) {
    while (1) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;
        if (left < pq->size && pq->data[left].distance < pq->data[smallest].distance)
            smallest = left;
        if (right < pq->size && pq->data[right].distance < pq->data[smallest].distance)
            smallest = right;
        if (smallest == idx)
            break;
        swap(&pq->data[idx], &pq->data[smallest]);
        idx = smallest;
    }
}

void insertPQ(PriorityQueue *pq, int vertex, int distance) {
    pq->data[pq->size].vertex = vertex;
    pq->data[pq->size].distance = distance;
    heapifyUp(pq, pq->size);
    pq->size++;
}

PQNode extractMin(PriorityQueue *pq) {
    PQNode min = pq->data[0];
    pq->data[0] = pq->data[--pq->size];
    heapifyDown(pq, 0);
    return min;
}

bool isEmpty(PriorityQueue *pq) {
    return pq->size == 0;
}

void freePQ(PriorityQueue *pq) {
    free(pq->data);
    free(pq);
}

void printPath(int *parent, int v) {
    if (parent[v] == -1) {
        printf("%d", v);
        return;
    }
    printPath(parent, parent[v]);
    printf(" -> %d", v);
}

void dijkstra(Graph G, Vertex src) {
    int dist[G->V];
    int parent[G->V];
    bool visited[G->V];

    for (int i = 0; i < G->V; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
        visited[i] = false;
    }
    dist[src] = 0;

    PriorityQueue *pq = createPQ(G->V);
    insertPQ(pq, src, 0);

    while (!isEmpty(pq)) {
        PQNode minNode = extractMin(pq);
        int u = minNode.vertex;

        if (visited[u])
            continue;
        visited[u] = true;

        for (Node n = G->adj[u]; n; n = n->next) {
            int v = n->value;
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + n->weight < dist[v]) {
                dist[v] = dist[u] + n->weight;
                parent[v] = u;
                insertPQ(pq, v, dist[v]);
            }
        }
    }

    printf("Node %d:\n", src);
    for (int i = 0; i < G->V; i++) {
        printf("Distance from %d to %d = ", src, i);
        if (dist[i] == INT_MAX) {
            printf("infinity\n");
        } else {
            printf("%d\n", dist[i]);
            if (i != src) {
                printf("Path: ");
                printPath(parent, i);
                printf("\n");
            }
        }
    }
    freePQ(pq);
}

bool bellmanFord(Graph G) {
    int dist[G->V];
    for (int src = 0; src < G->V; src++) {
        for (int i = 0; i < G->V; i++)
            dist[i] = INT_MAX;
        dist[src] = 0;
        for (int i = 1; i < G->V; i++) {
            for (int u = 0; u < G->V; u++) {
                for (Node n = G->adj[u]; n; n = n->next) {
                    int v = n->value;
                    if (dist[u] != INT_MAX && dist[u] + n->weight < dist[v]) {
                        dist[v] = dist[u] + n->weight;
                    }
                }
            }
        }
        for (int u = 0; u < G->V; u++) {
            for (Node n = G->adj[u]; n; n = n->next) {
                int v = n->value;
                if (dist[u] != INT_MAX && dist[u] + n->weight < dist[v]) {
                    return false;
                }
            }
        }
    }
    return true;
}