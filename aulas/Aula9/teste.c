#include "adjlist.h"

int main () {
    int n, x, y, z;

    Graph myGraph;

    if (scanf("%d", &n) == 1){
        myGraph = initGraph(n);
        while(scanf("%d %d %d", &x, &y, &z) != EOF) {
            insertArc(myGraph, x, y, z); // Adicionado o peso (z)
        }
        printGraph(myGraph);
        dijkstra(myGraph, 0);
        destroyGraph(myGraph);
    }
}