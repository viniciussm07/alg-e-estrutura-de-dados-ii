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
        printGraph(myGraph);
        destroyGraph(myGraph);
    }
}