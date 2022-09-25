//-----------------------------------------------------------------------------
// Abhay Singh, abrsingh
// 2022 Spring CSE101 PA#2
// Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------

#pragma once 

#include "List.h"
#include <stdbool.h>

#define INF -5
#define NIL -1

// Exported type --------------------------------------------------------------
typedef struct GraphObj* Graph;

// Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n);

void freeGraph(Graph* pG);

// Access Functions ------------------------------------------------------------
int getOrder(Graph G);

int getSize(Graph G);

int getSource(Graph G);

int getParent(Graph G, int u);

int getDist(Graph G, int u);

void getPath(List L, Graph G, int u);

// Manipulation Procedures ------------------------------------------------------
void makeNull(Graph G);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void BFS(Graph G, int s);

// Other Operations --------------------------------------------------------------
void printGraph(FILE* out, Graph G);



