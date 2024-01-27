#ifndef DOUBLYLINKEDLISTS_H
#define DOUBLYLINKEDLISTS_H
#include <stdlib.h>
#include <stdio.h>

typedef struct doublyListItem
{
    struct doublyListItem* next;
    struct doublyListItem* prev;
    int value;
} doublyListItem;



doublyListItem* DoublyListGetTail(doublyListItem* head);
void PrintDoublyList(doublyListItem* head);
void FreeDoublyListMemory(doublyListItem** head);
doublyListItem* DoublyListAppend(doublyListItem** head, int value);
void DoublyListAddValueAfterItem(doublyListItem* item, int value);
void DoublyListAddValueBeforeItem(doublyListItem** item, int value);
int DoublyListRemoveValue(doublyListItem** head, int value);
doublyListItem* DoublyListFindItem(doublyListItem* head, int value);
void DoublyListRemoveItem(doublyListItem** head, doublyListItem* item);

#endif