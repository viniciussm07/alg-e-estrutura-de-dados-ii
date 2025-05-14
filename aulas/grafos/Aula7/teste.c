#include "adjlist.h"

int main () {
    int n, x, y, z;

    Graph myGraph;

    if (scanf("%d", &n) == 1){
        myGraph = initGraph(n);
        while(scanf("%d %d %d", &x, &y, &z) != EOF) {
            insertEdge(myGraph, x, y, z); // Adicionado o peso (z)
        }
        printGraph(myGraph);
        // startBFS(myGraph, 0);
        checkEulerPath(myGraph);
        checkHamilton(myGraph, 0, 7);
        destroyGraph(myGraph);
    }
}