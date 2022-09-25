# Find Shortest Path

Abhay Singh

## Files

List.c:
    Contains the module for the List ADT as well as all of its functions

List.h:
    Header file for List.c that contains the interface

Graph.c:
    Contains the module for the Graph ADT as well as all of its functions

Graph.h:
    Header file for Graph.c that contains the interface

GraphTest.c:
    Contains the test harness for the Graph.c ADT. Includes the GraphClient test as well as 
    some of my own tests.

FindPath.c:
    Contains my implementation of the BFS Find Path Algorithm. Will compile into an executable
    that will print out the adjacency list representation of the graph as well as the shortest 
    path from a source to a destination.

Makefile:
    The file that will be used to run the "make" command. Will compile FindPath and GraphTest 
    and will also run valgrind on the files.

README:
    The current file that outlines each file to be used in the final project.
    
Note: This project was created in CSE101 Spring 2022 at UCSC
