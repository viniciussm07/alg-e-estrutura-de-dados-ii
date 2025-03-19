#include <stdlib.h>
#include <stdio.h>

#define Vertex int

// um Arco é um par de vértices v, w
typedef struct
{
    Vertex v;
    Vertex w;
} Arc;

struct arclist
{
    int size;
    Arc *arcs;
};

typedef struct arclist *Graph;

Graph initGraph()
{
    Graph G = (Graph)malloc(sizeof(*G));
    G->size = 0;
    G->arcs = NULL;
    return G;
}

void destructGraph(Graph G){
    free(G->arcs);
    G->size = 0;
}

Arc newArc(Vertex v, Vertex w)
{
    Arc a;
    a.v = v;
    a.w = w;

    return a;
}

void insertArc(Graph G, Vertex v, Vertex w)
{
    Arc newa = newArc(v, w);
    G->size++;
    G->arcs = (Arc *)realloc(G->arcs, G->size * sizeof(Arc));
    G->arcs[G->size - 1] = newa;
}

void insertEdge(Graph G, Vertex v, Vertex w) {
    insertArc(G, v, w);
    insertArc(G, w, v);
}

void printGraph(Graph G){
    for (int i = 0; i < (G->size); i++){
        printf("Arco %d -- %d\n", G->arcs[i].v, G->arcs[i].w);
    }
}

void removeArc(Graph G, Vertex v, Vertex w){
    for (int i = 0; i < G->size; i++){
        if ((G->arcs[i].v == v) && (G->arcs[i].w == w)){
            G->arcs[i] = G->arcs[G->size - 1];
            G->size --;
        }
    }
}

void removeEdge(Graph G, Vertex v, Vertex w){
    removeArc(G, v, w);
    removeArc(G, w, v);
}