#include "LinkedLists.h"


void FreeListMemory(listItem** head)
{
    if (!(*head))
    {
        printf("The head is NULL\n");
        return;
    }
    
    listItem* currentItem = *head;
    while (currentItem)
    {
        listItem* itemToFree = currentItem;
        currentItem = currentItem->next;
        free(itemToFree);
    }

    printf("Freed memory\n");
}

void PrintList(listItem* head)
{
    if (!head)
    {
        printf("The head is NULL\n");
        return;
    }
    
    listItem* currentItem = head;
    int index = 0;
    while (currentItem)
    {
        printf("Value at index %d: %d\n", index, currentItem->value);
        currentItem = currentItem->next;
        index++;
    }
}

listItem* GetTail(listItem* head)
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
    
    listItem* tail = GetTail(*head);
    
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

int RemoveValueFromList(listItem** head, int value)
{
    if (!*head)
    {
        printf("The head is NULL\n");
        return -1;
    }   
    
    int removedValue;      // variable for debug purposes
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
                printf("\nThis value is not in the list\n");
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



void ReverseList(listItem** head)
{
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





