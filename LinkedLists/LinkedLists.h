#include <stdlib.h>
#include <stdio.h>

typedef struct listItem
{
    struct listItem* next;
    int value;
} listItem ;



int RemoveValueFromList(listItem** head, int value);
listItem* ListAppend(listItem** head, int value);
listItem* GetTail(listItem* head);
void PrintList(listItem* head);
void FreeListMemory(listItem** head);
void ReverseList(listItem** head);
















