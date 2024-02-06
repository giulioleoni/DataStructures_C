#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <stdio.h>

typedef struct listItem
{
    struct listItem* next;
    int value;
} listItem ;



int ListRemoveValue(listItem** head, int value);
listItem* ListAppend(listItem** head, int value);
listItem* ListGetTail(listItem* head);
void PrintList(listItem* head);
void FreeListMemory(listItem** head);
void ListReverse(listItem** head);


#endif













