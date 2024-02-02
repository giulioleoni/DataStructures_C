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

void FreeDoublyListMemory(doublyListItem** head)
{
    if (!(*head))
    {
        return;
    }

    doublyListItem* currentItem = *head;

    while (currentItem->next != NULL)
    {
        currentItem = currentItem->next;
        free(currentItem->prev);

    }

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

doublyListItem* DoublyListFindItem(doublyListItem* head, int value)
{
    while (head)
    {
        if (head->value == value)
        {
            return head;
        }
        
        head = head->next;
    }
    return NULL;
}

void DoublyListRemoveItem(doublyListItem** head, doublyListItem* item)
{
    if (!item)
    {
        return;
    }

    if (item == *head)
    {
        *head = (*head)->next;
        if (*head)
        {
            (*head)->prev = NULL;
        }
    }
    else
    {
        item->prev->next = item->next;
        if (item->next)
        {
            item->next->prev = item->prev;
        }
    }
    
    free(item);
}

int DoublyListRemoveValue(doublyListItem** head, int value)
{
    if (!*head)
    {
        return -1;
    }   
    
    doublyListItem* toRemove = DoublyListFindItem(*head, value);

    DoublyListRemoveItem(head, toRemove);

    return toRemove != NULL ? 0 : -1;
}








