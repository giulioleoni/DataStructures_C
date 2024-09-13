#include "LinkedLists.h"

void FreeListMemory(listItem** head)
{
    if (!(*head))
    {
        return;
    }
    
    listItem* currentItem = *head;
    while (currentItem)
    {
        listItem* itemToFree = currentItem;
        currentItem = currentItem->next;
        free(itemToFree);
    }

    *head = NULL;
}

listItem* ListGetTail(listItem* head)
{
    if (!head)
    {
        return NULL;
    }

    listItem* currentItem = head;
    listItem* tail = NULL;
    
    while (currentItem)
    {
        tail = currentItem;
        currentItem = currentItem->next;
    }

    return tail;
}

listItem* ListAppend(listItem** head, int value)
{
    listItem* item = malloc(sizeof(listItem));

    if (!item)
    {
        return NULL;
    }
    
    listItem* tail = ListGetTail(*head);
    
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
    return item;
}

void ListRemoveValue(listItem** head, int value)
{
    if (!*head)
    {
        return;
    }   
        
    listItem* itemToRemove = NULL;

    if ((*head)->value == value)
    {
        // head is the item to remove
        itemToRemove = *head;
        *head = (*head)->next;
        free(itemToRemove);
        return;
    }

    if ((*head)->next)
    {
        listItem* currentItem = *head;

        while (currentItem->next->value != value)
        {
            currentItem = currentItem->next;
            if (!currentItem->next)
            {
                return;
            }
        }    

        itemToRemove = currentItem->next;
        currentItem->next = currentItem->next->next;
        free(itemToRemove);
    }
}

void ListReverse(listItem** head)
{
    if (!(*head))
    {
        return;
    }

    listItem* currentItem = *head;
    listItem* previousItem = NULL;

    while (currentItem)
    {
        listItem* nextItem = currentItem->next;
        currentItem->next = previousItem;
        previousItem = currentItem;
        currentItem = nextItem;
    }
    
    *head = previousItem;
}









