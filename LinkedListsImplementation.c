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
    
    listItem* CurrentItem = head;
    int index = 0;
    while (CurrentItem)
    {
        printf("Value at index %d: %d\n", index, CurrentItem->value);
        CurrentItem = CurrentItem->next;
        index++;
    }
}

listItem* GetTail(listItem* head)
{
    if (!head)
    {
        return NULL;
    }

    listItem* CurrentItem = head;
    listItem* tail = NULL;
    
    while (CurrentItem)
    {
        tail = CurrentItem;
        CurrentItem = CurrentItem->next;
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
        listItem* CurrentItem = *head;
        while (CurrentItem->next->value != value)
        {
            CurrentItem = CurrentItem->next;
            if (CurrentItem->next == NULL)
            {
                printf("\nThis value is not in the list\n");
                return -1;
            }
            
        }    

        removedValue = CurrentItem->next->value;

        itemToRemove = CurrentItem;
        CurrentItem->next = CurrentItem->next->next;

        free(itemToRemove);

        return removedValue;
    }
    
    return -1;
}









