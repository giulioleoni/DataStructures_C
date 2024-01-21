#include "DoublyLinkedLists.h"


doublyListItem* DoublyListGetTail(doublyListItem* head)
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

void FreeDoublyListMemory(doublyListItem** head)
{
    if (!(*head))
    {
        return;
    }

    doublyListItem* currentItem = *head;

    while (currentItem->next != NULL)
    {
        printf("curr val: %d\n", currentItem->value);

        currentItem = currentItem->next;

        printf("next curr val: %d\n", currentItem->value);
        printf("prev val: %d\n", currentItem->prev->value);

        free(currentItem->prev);

        printf("fa il free\n");
    }

    printf("esce dal ciclo\n");
    free(currentItem);
}

doublyListItem* DoublyListAppend(doublyListItem** head, int value)
{
    doublyListItem* item = malloc(sizeof(doublyListItem));

    if (!item)
    {
        return NULL;
    }
    
    doublyListItem* tail = DoublyListGetTail(*head);
    
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

void DoublyListAddValueAfterItem(doublyListItem* item, int value)
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

void DoublyListAddValueBeforeItem(doublyListItem** item, int value)
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



int DoublyListRemoveValue(doublyListItem** head, int value)
{
    if (!*head)
    {
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








