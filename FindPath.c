//-----------------------------------------------------------------------------
// Abhay Singh, abrsingh
// 2022 Spring CSE101 PA#1
// FindPath.c
// File that will reflect the executable that will print the paths using BFS
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Graph.h"

int main(int argc, char* argv[]) {
    FILE *in, *out;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    char buffer[16384];
    int vertex = 0;


    fgets(buffer, 16384, in);

    sscanf(buffer, "%d", &vertex);

    Graph G = newGraph(vertex);

    int left = 0;
    int right = 0;

    do {
        fgets(buffer, 16384, in);
        sscanf(buffer, "%d %d", &left, &right);
        if (left == 0 && right == 0) {
            break;
        } else {
            addEdge(G, left, right);
        }
    } while (left != 0 && right != 0);

    printGraph(out, G);
    fprintf(out, "\n");

    int source = 0;
    int destin = 0;

    List L = newList();

    do {
        fgets(buffer, 16384, in);
        sscanf(buffer, "%d %d", &source, &destin);
        if (source == 0 && destin == 0) {
            break;
        } else {
            BFS(G, source);
            if (getDist(G, destin) != INF) {
                fprintf(out, "The distance from %d to %d is %d\n", source, destin, getDist(G, destin));
                getPath(L, G, destin);
                fprintf(out, "A shortest %d-%d path is: ", source, destin);
                printList(out, L);
                fprintf(out, "\n\n");
                clear(L);
            } else {
                fprintf(out, "The distance from %d to %d is infinity\n", source, destin);
                fprintf(out, "No %d-%d path exists\n", source, destin);
                fprintf(out, "\n");
            }
        }
    } while (source != 0 && destin != 0);

    freeList(&L);
    freeGraph(&G);

    fclose(out);
    fclose(in); 
}