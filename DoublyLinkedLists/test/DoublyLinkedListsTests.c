#define CLOVE_SUITE_NAME DoublyLinkedListTest
#include "clove-unit.h"
#include "DoublyLinkedLists.h"

CLOVE_TEST(DoublyListGetTailTest)
{
    doublyListItem head;
    head.value = 1;
    doublyListItem second;
    second.value = 2;
    doublyListItem third;
    third.value = 3;

    head.next = &second;
    head.prev = NULL;
    second.next = &third;
    second.prev = &head;
    third.next = NULL;
    third.prev = &second;

    doublyListItem *tail = DoublyListGetTail(&head);

    CLOVE_IS_TRUE(tail != NULL);
    CLOVE_INT_EQ(tail->value, third.value);
}

CLOVE_TEST(CreateListHeadWithAppend)
{
    doublyListItem *head = NULL;
    DoublyListAppend(&head, 10);

    CLOVE_NOT_NULL(head);
    CLOVE_INT_EQ(10, head->value);
    CLOVE_NULL(head->prev);

    FreeDoublyListMemory(&head);
}

CLOVE_TEST(AddingMoreElementsToDoublyList)
{
    doublyListItem *head = NULL;
    DoublyListAppend(&head, 10);
    DoublyListAppend(&head, 20);
    DoublyListAppend(&head, 30);

    CLOVE_NOT_NULL(head->next);
    CLOVE_NOT_NULL(head->next->next);
    CLOVE_INT_EQ(20, head->next->value);
    CLOVE_INT_EQ(30, head->next->next->value);
    CLOVE_PTR_EQ(head, head->next->prev);
    CLOVE_PTR_EQ(head->next, head->next->next->prev);

    FreeDoublyListMemory(&head);
}

CLOVE_TEST(DoublyListFind)
{
    doublyListItem *head = NULL;
    DoublyListAppend(&head, 10);
    doublyListItem* itemToFind = DoublyListAppend(&head, 20);
    DoublyListAppend(&head, 30);

    doublyListItem* itemFound = DoublyListFindItem(head, 20);
    CLOVE_PTR_EQ(itemToFind, itemFound);

    FreeDoublyListMemory(&head);
}

CLOVE_TEST(RemoveElementNotInTheDoublyList)
{
    doublyListItem *head = NULL;
    DoublyListAppend(&head, 10);
    DoublyListAppend(&head, 20);
    DoublyListAppend(&head, 30);

    int removeResult = DoublyListRemoveValue(&head, 1234);

    CLOVE_INT_EQ(-1, removeResult);

    FreeDoublyListMemory(&head);
}

CLOVE_TEST(RemoveHeadOfTheDoublyList)
{
    doublyListItem *head = NULL;
    DoublyListAppend(&head, 10);
    DoublyListAppend(&head, 20);
    DoublyListAppend(&head, 30);

    int removeResult = DoublyListRemoveValue(&head, 10);
    
    CLOVE_INT_EQ(0, removeResult);
    CLOVE_INT_EQ(20, head->value);
    CLOVE_NULL(head->prev);

    FreeDoublyListMemory(&head);
}

CLOVE_TEST(RemoveElementInsideTheDoublyList)
{
    doublyListItem *head = NULL;
    DoublyListAppend(&head, 10);
    DoublyListAppend(&head, 20);
    DoublyListAppend(&head, 30);

    int removeResult = DoublyListRemoveValue(&head, 20);

    CLOVE_INT_EQ(0, removeResult);
    CLOVE_PTR_EQ(head->next->prev, head);
    CLOVE_INT_EQ(30, head->next->value);

    FreeDoublyListMemory(&head);
}

CLOVE_TEST(RemoveLastElementOfTheDoublyList)
{
    doublyListItem *head = NULL;
    DoublyListAppend(&head, 10);
    DoublyListAppend(&head, 20);
    DoublyListAppend(&head, 30);

    int removeResult = DoublyListRemoveValue(&head, 30);

    CLOVE_INT_EQ(0, removeResult);
    CLOVE_NULL(head->next->next);

    FreeDoublyListMemory(&head);
}

CLOVE_TEST(AddValueBeforeAnItem)
{
    doublyListItem *head = NULL;
    DoublyListAppend(&head, 10);
    DoublyListAppend(&head, 20);
    DoublyListAppend(&head, 30);
    doublyListItem* item = head->next->next;

    DoublyListAddValueBeforeItem(&item, 40);

    CLOVE_INT_EQ(40, head->next->next->value);
    CLOVE_PTR_EQ(head->next->next->prev, head->next);
    CLOVE_INT_EQ(30, head->next->next->next->value);

    FreeDoublyListMemory(&head);
}

CLOVE_TEST(AddValueBeforeHead)
{
    doublyListItem *head = NULL;
    DoublyListAppend(&head, 10);
    DoublyListAppend(&head, 20);
    DoublyListAppend(&head, 30);
    doublyListItem* item = head->next->next;

    DoublyListAddValueBeforeItem(&head, 40);

    CLOVE_INT_EQ(40, head->value);
    CLOVE_NULL(head->prev);
    CLOVE_INT_EQ(10, head->next->value);

    FreeDoublyListMemory(&head);
}

CLOVE_TEST(AddValueAfterAnItem)
{
    doublyListItem *head = NULL;
    DoublyListAppend(&head, 10);
    DoublyListAppend(&head, 20);
    DoublyListAppend(&head, 30);

    DoublyListAddValueAfterItem(head, 40);

    CLOVE_INT_EQ(40, head->next->value);
    CLOVE_PTR_EQ(head->next->prev, head);
    CLOVE_INT_EQ(20, head->next->next->value);

    FreeDoublyListMemory(&head);
}

CLOVE_TEST(AddValueAfterLastItem)
{
    doublyListItem *head = NULL;
    DoublyListAppend(&head, 10);
    DoublyListAppend(&head, 20);
    DoublyListAppend(&head, 30);
    doublyListItem* item = head->next->next;

    DoublyListAddValueAfterItem(item, 40);
    doublyListItem* itemAdded = head->next->next->next;

    CLOVE_INT_EQ(40, itemAdded->value);
    CLOVE_PTR_EQ(itemAdded->prev, item);
    CLOVE_INT_EQ(30, itemAdded->prev->value);

    FreeDoublyListMemory(&head);
}


