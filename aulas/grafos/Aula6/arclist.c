#include "adjlist.h"

int main () {
    int n, x, y;

    Graph myGraph;

    if (scanf("%d", &n) == 1){
        myGraph = initGraph(n);
        while(scanf("%d %d", &x, &y) != EOF) {
            insertEdge(myGraph, x, y);
        }
        // printGraph(myGraph);
        // startBFS(myGraph, 0);
        checkEulerPath(myGraph);
        destroyGraph(myGraph);
    }
}