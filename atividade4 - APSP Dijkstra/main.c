#include "adjlist.h"

int main() {
    int V, u, v, w;
    if (scanf("%d", &V) != 1)
        return 1;

    Graph G = initGraph(V);
    while (scanf("%d %d %d", &u, &v, &w) == 3) {
        insertArc(G, u, v, w);
    }

    // Detecta ciclo negativo (loop infinito)
    if (!bellmanFord(G)) {
        printf("Infinity Loop\n");
        freeGraph(G);
        return 0;
    }

    // Caso não haja ciclo, pode prosseguir com demais lógicas
    for (int i = 0; i < G->V; i++) {
        dijkstra(G, i);
        if (i != G->V - 1)
            printf("\n");
    }

    freeGraph(G);
    return 0;
}