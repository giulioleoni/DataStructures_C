#include <stdlib.h>
#include <stdio.h>

typedef struct doublyListItem
{
    struct doublyListItem* next;
    struct doublyListItem* prev;
    int value;
} doublyListItem ;


doublyListItem* GetTail(doublyListItem* head);
void PrintDoublyList(doublyListItem* head);
void PrintDoublyListReverse(doublyListItem* head);
void FreeDoublyListMemory(doublyListItem** head);
doublyListItem* DoublyListAppend(doublyListItem** head, int value);
void AddValueAfterItem(doublyListItem* item, int value);
void AddValueBeforeItem(doublyListItem** item, int value);
int RemoveValueFromDoublyList(doublyListItem** head, int value);







