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

int ListRemoveValue(listItem** head, int value)
{
    if (!*head)
    {
        return -1;
    }   
    
    int removedValue;      
    listItem* itemToRemove = NULL;

    if ((*head)->value == value)
    {
        removedValue = (*head)->value;
        itemToRemove = *head;
        *head = (*head)->next;
        free(itemToRemove);
        return removedValue;
    }

    if ((*head)->next)
    {
        listItem* currentItem = *head;

        while (currentItem->next->value != value)
        {
            currentItem = currentItem->next;
            if (currentItem->next == NULL)
            {
                return -1;
            }
        }    

        removedValue = currentItem->next->value;
        itemToRemove = currentItem->next;
        currentItem->next = currentItem->next->next;
        free(itemToRemove);
        return removedValue;
    }
    
    return -1;
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









