//-----------------------------------------------------------------------------
// Abhay Singh, abrsingh
// 2022 Spring CSE101 PA#2
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------
#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_

#include <stdbool.h>
// Exported type --------------------------------------------------------------
typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------
List newList(void);

void freeList(List* pL);

// Access functions -----------------------------------------------------------
int length(List L);

int index(List L);

int front(List L);

int back(List L);

int get(List L);

bool equals(List A, List B);

// Manipulation procedures ----------------------------------------------------
void clear(List L);

void set(List L, int x);

void moveFront(List L);

void moveBack(List L);

void movePrev(List L);

void moveNext(List L);

void prepend(List L, int x);

void append(List L, int x);

void insertBefore(List L, int x);

void insertAfter(List L, int x);

void deleteFront(List L);

void deleteBack(List L);

void delete(List L);

// Other Functions ------------------------------------------------------------
void printList(FILE* out, List L);

List copyList(List L);

List concatList(List A, List B);

#endif










