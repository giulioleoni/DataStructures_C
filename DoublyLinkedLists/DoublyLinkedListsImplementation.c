#include "DoublyLinkedLists.h"


doublyListItem* GetTail(doublyListItem* head)
{
    if (!head)
    {
        return NULL;
    }

    doublyListItem* currentItem = head;
    doublyListItem* tail = NULL;
    
    while (currentItem)
    {
        tail = currentItem;
        currentItem = currentItem->next;
    }

    return tail;
}



void PrintDoublyList(doublyListItem* head)
{
    if (!head)
    {
        printf("The head is NULL\n");
        return;
    }

    doublyListItem* currentItem = head;
    int index = 0;
    while (currentItem)
    {
        printf("Value at index %d: %d\n", index, currentItem->value);
        currentItem = currentItem->next;
        index++;
    }
}

void PrintDoublyListReverse(doublyListItem* head)
{
    if (!head)
    {
        printf("The head is NULL\n");
        return;
    }
    
    doublyListItem* tail = GetTail(head);

    int index = 0;
    while (tail)
    {
        printf("Value at index %d: %d\n", index, tail->value);
        tail = tail->prev;
        index--;
    }
}

void FreeDoublyListMemory(doublyListItem** head)
{
    if (!(*head))
    {
        printf("The head is NULL");
        return;
    }

    doublyListItem* currentItem = *head;

    while (currentItem->next)
    {
        currentItem = currentItem->next;
        free(currentItem->prev);
    }

    free(currentItem);

    printf("Freed memory\n");
}

doublyListItem* DoublyListAppend(doublyListItem** head, int value)
{
    doublyListItem* item = malloc(sizeof(doublyListItem));

    if (!item)
    {
        return NULL;
    }
    
    doublyListItem* tail = GetTail(*head);
    
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }

    item->value = value;
    item->next = NULL;
    item->prev = tail;
    return item;
}

void AddValueAfterItem(doublyListItem* item, int value)
{
    doublyListItem* newItem = malloc(sizeof(doublyListItem));

    if (!newItem)
    {
        return;
    }

    newItem->value = value;

    if (!item->next)
    {
        newItem->prev = item;
        newItem->next = NULL;
        item->next = newItem;
    }
    else
    {
        newItem->next = item->next;
        newItem->prev = item;
        item->next->prev = newItem;
        item->next = newItem;
    }  
}

void AddValueBeforeItem(doublyListItem** item, int value)
{
    doublyListItem* newItem = malloc(sizeof(doublyListItem));

    if (!newItem)
    {
        return;
    }

    newItem->value = value;

    if (!(*item)->prev)
    {
        newItem->prev = NULL;
        newItem->next = *item;
        (*item)->prev = newItem;
        *item = newItem;
    }
    else
    {
        newItem->next = (*item)->prev->next;
        newItem->prev = (*item)->prev;
        newItem->prev->next = newItem;
        (*item)->prev = newItem;
    }  
}



int RemoveValueFromDoublyList(doublyListItem** head, int value)
{
    if (!*head)
    {
        printf("Head is NULL\n");
        return -1;
    }   
    int removedValue;    

    if ((*head)->value == value)
    {
        removedValue = (*head)->value;
        
        if ((*head)->next)
        {
            *head = (*head)->next;
            (*head)->prev = NULL;
        }
        else
        {
            *head = NULL;
        }
        
        free(*head);
        return removedValue;
    }

    doublyListItem* currentItem = *head;

    if (currentItem->next)
    {
        
        while (currentItem->value != value)
        {
            currentItem = currentItem->next;
            if (currentItem == NULL)
            {
                printf("\nThis value is not in the list\n");
                return -1;
            }
        }    

        removedValue = currentItem->value;

        currentItem->prev->next = currentItem->next;
        if (currentItem->next)
        {
            currentItem->next->prev = currentItem->prev;
        }
        
        free(currentItem);

        return removedValue;
    }

    return -1;
}








