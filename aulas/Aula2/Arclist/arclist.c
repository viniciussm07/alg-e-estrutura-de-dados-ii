#include "arclist.h"

int main () {
    int n, x, y;

    Graph myGDigaph;

    if (scanf("%d", &n) == 1){
        myGDigaph = initGraph();
        printf("Vértices %d\n", n);
        while(scanf("%d %d", &x, &y) != EOF) {
            insertArc(myGDigaph, x, y);
        }
        removeArc(myGDigaph, 2, 5);
        printGraph(myGDigaph);
        destructGraph(myGDigaph);
    }
}