#include "adjmatrix.h"

int main () {
    int n, x, y;

    Graph myGraph;
    boolean isEdge = TRUE;

    if (scanf("%d", &n) == 1){
        myGraph = initGraph(n);
        while(scanf("%d %d", &x, &y) != EOF) {
            insertArc(myGraph, x, y, isEdge);
        }
        startDFS(myGraph, 0);
        startBFS(myGraph, 0);
        destroyGraph(myGraph);
    }
}