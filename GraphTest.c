//-----------------------------------------------------------------------------
// Abhay Singh, abrsingh
// 2022 Spring CSE101 PA#1
// GraphTest.c
// Test Harness for Graph ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){

   //GraphClient Test----------------------------------------------------------

   int i, s, max, min, d, n=35;
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
   Graph G = NULL;

   // Build graph G 
   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);

   // Print adjacency list representation of G
   printGraph(stdout, G);

   // Calculate the eccentricity of each vertex 
   for(s=1; s<=n; s++){
      BFS(G, s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }

   // Determine the Radius and Diameter of G, as well as the Central and 
   // Peripheral vertices.
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveFront(E);
   moveNext(E);
   for(i=2; i<=n; i++){
      d = get(E);
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }

   // Print results 
   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");

   // Free objects 
   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeGraph(&G);

   //My Tests-------------------------------------------------------------

   printf("\n");

   Graph A = newGraph(50);
   for(i=1; i<n; i++){
      if( i%20!=0 ) addEdge(A, i, i+1);
      if( i<= 40) addEdge(A, i, i+7);
   }

   addArc(A, 10, 5);
   addArc(A, 48, 50);
   addArc(A, 32, 45);
   addArc(A, 22, 34);

   printGraph(stdout, A);

   printf("\n");

   List F = newList();

   BFS(A, 10);

   getPath(F, A, 5);

   printf("Order of A: %d\n", getOrder(A));
   printf("Size of A: %d\n", getSize(A));
   printf("Source of A: %d\n", getSource(A));
   printf("Parent of 5: %d\n", getParent(A, 5));
   printf("Distance from source(%d) to %d is: %d\n\n", 10, 5, getDist(A, 5));

   freeList(&F);
   freeGraph(&A);


   return(0);
}