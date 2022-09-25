//-----------------------------------------------------------------------------
// Abhay Singh, abrsingh
// 2022 Spring CSE101 PA#2
// Graph.c
// Implementation of the Graph ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Graph.h"

#define White 5
#define Grey 10
#define Black 15


// structs --------------------------------------------------------------------
typedef struct GraphObj{
    List *array;
    int *color;
    int *parent;
    int *distance;
    int order;
    int size;
    int label;
} GraphObj;

// Constructors - Destructors -------------------------------------------------

//returns a Graph pointing to a newly createed GraphObj
//representing a graph having n vertices sand no edges
Graph newGraph(int n) {
    Graph G;
    G = malloc(sizeof(GraphObj));
    G->array = malloc((n + 1) * sizeof(List));
    for (int i = 1; i <= n; i += 1) {
        G->array[i] = newList();
    }
    G->color = (int*)malloc((n + 1) * sizeof(int));
    G->parent = (int*)malloc((n + 1) * sizeof(int));
    G->distance = (int*)malloc((n + 1) * sizeof(int));
    G->order = n;
    G->size = 0;
    G->label = 0;
    return G;
}


//frees all heap memory associated with the Graph
void freeGraph(Graph* pG){
    if (pG != NULL && *pG != NULL) {
        makeNull(*pG);
        free((*pG)->array);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
        free(*pG);
        *pG = NULL;
    }
}

// Access Functions ------------------------------------------------------------

//return number of vertices of the graph
int getOrder(Graph G) {
    return G->order;
}

//return number of edges of the graph
int getSize(Graph G) {
    return G->size;
}

//return source vertex most recently used in BFS
//Pre: BFS must be called
int getSource(Graph G) {
    if (G == NULL) {
        printf("Graph Error: calling getSource() on NULL Graph reference\n");
        freeGraph(&G);
        exit(EXIT_FAILURE);
    }
    if (G->label != 0) {
        return G->label;
    } else {
        return NIL;
    }
}

//return parent vertex of u in BFS tree
//Pre: BFS must be called, 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: calling getParent() on NULL Graph reference\n");
        freeGraph(&G);
        exit(EXIT_FAILURE);
    }
    if (u >= 1 && u <= getOrder(G)) {
        if (G->label != 0) {
            return G->parent[u];
        } else {
            return NIL;
        }
    }
     else {
        printf("Graph Error: 'u' does not meet preconditions");
        freeGraph(&G);
        exit(EXIT_FAILURE);
    }
}


//returns distance from most recent BFS source to vertex u
//Pre: BFS must be called, 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: calling getDist() on NULL Graph reference\n");
        freeGraph(&G);
        exit(EXIT_FAILURE);
    }
    if (u >= 1 && u <= getOrder(G)) {
        if (G->label != 0) {
            return G->distance[u];
        } else {
            return INF;
        }
    } 
    else {
        printf("Graph Error: 'u' does not meet preconditions");
        freeGraph(&G);
        exit(EXIT_FAILURE);
    }
}

//appends to L the vertices of the shortest path
//in G from source to u or appends
//NIL if no such path exits
//Pre: getsource(G) != NIL, BFS must be called, 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u){
    if (G == NULL) {
        printf("Graph Error: calling getPath() on NULL Graph reference\n");
        freeGraph(&G);
        exit(EXIT_FAILURE);
    }
    if (u >= 1 && u <= getOrder(G) && getSource(G) != NIL &&  G->label != 0) {
        if (getSource(G) == u) {
            append(L, getSource(G));
        } else if (G->parent[u] == NIL) {
            append(L, NIL);
        } else {
            getPath(L, G, G->parent[u]);
            append(L, u);
        }
    } else {
        printf("Graph Error: Preconditions Failed");
        freeGraph(&G);
        freeList(&L);
        exit(EXIT_FAILURE);
    }
}
// Manipulation Procedures ------------------------------------------------------

//deletes all edges of G, restoring the no edge state
void makeNull(Graph G) {
    for(int i = 1; i <= G->order; i += 1){
        freeList(&G->array[i]);
        G->size = 0;
    }
}

//insert new edge joining u to v
//Pre: int u and int v must be in range from 1 to getOrder(G)
void addEdge(Graph G, int u, int v) {
    if (u >= 1 && v >= 1 && u <= getOrder(G) && v <= getOrder(G)) {
        if (length(G->array[v]) == 0) {
            append(G->array[v], u);
        } else {
            moveBack(G->array[v]);
            int j = get(G->array[v]);
            while (u < j) {
                movePrev(G->array[v]);
                if (index(G->array[v]) == -1) {
                    prepend(G->array[v], u);
                    break;
                }
                j = get(G->array[v]);
            }
            if (index(G->array[v]) >= 0) {
                insertAfter(G->array[v], u);
            }
        }    
        if (length(G->array[u]) == 0) {
            append(G->array[u], v);
        } else {
            moveBack(G->array[u]);
            int j = get(G->array[u]);
            while (v < j) {
                movePrev(G->array[u]);
                if (index(G->array[u]) == -1) {
                    prepend(G->array[u], v);
                    break;
                }
                j = get(G->array[u]);
            }
            if (index(G->array[u]) >= 0) {
                insertAfter(G->array[u], v);
            }
        }  
        G->size += 1;
    } else {
        printf("Graph Error: Ints are not in the correct range");
        freeGraph(&G);
        exit(EXIT_FAILURE);
    }
}

//insert a new directed edge from u to v
//Pre: int u and int v must be in range from 1 to getOrder(G)
void addArc(Graph G, int u, int v){
    if (u >= 1 && v >= 1 && u <= getOrder(G) && v <= getOrder(G)) {
        if (length(G->array[u]) == 0) {
            append(G->array[u], v);
        } else {
            moveBack(G->array[u]);
            int j = get(G->array[u]);
            while (v < j) {
                movePrev(G->array[u]);
                if (index(G->array[u]) == -1) {
                    prepend(G->array[u], v);
                    break;
                }
                j = get(G->array[u]);
            }
            if (index(G->array[u]) >= 0) {
                insertAfter(G->array[u], v);

            }
        }
        G->size += 1;
    } else {
        printf("Graph Error: Ints are not in the correct range");
        freeGraph(&G);
        exit(EXIT_FAILURE);
    }
}

//runs BFS algorithm on Graph G with source s
void BFS(Graph G, int s){
    G->label = s;
    for (int i = 1; i <= G->order; i += 1) {
        if (i != s) {
            G->color[i] = White;
            G->parent[i] = NIL;
            G->distance[i] = INF;
        }
    }
    G->color[s] = Grey;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List Queue = newList();
    append(Queue, s);
    while(length(Queue) != 0){
        moveFront(Queue);
        int x = get(Queue);
        deleteFront(Queue);
        for(moveFront(G->array[x]); index(G->array[x]) >= 0; moveNext(G->array[x])){
            int y = get(G->array[x]);
            if (G->color[y] == White) {
                G->color[y] = Grey;
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                append(Queue, y);
            }
        }
        G->color[x] = Black;
    }
    freeList(&Queue);
}

        

// Other Operations --------------------------------------------------------------

//print adjacency list of G to outfile
void printGraph(FILE* out, Graph G) {
    for (int i = 1; i <= G->order; i += 1) {
        fprintf(out, "%d: ", i );
        printList(out, G->array[i]);
        fprintf(out, "\n");
    }

}