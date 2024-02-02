#define CLOVE_SUITE_NAME LinkedListTest
#include "clove-unit.h"
#include "LinkedLists.h"

CLOVE_TEST(ListGetTailTest)
{
    listItem head;
    head.value = 1;
    listItem second;
    second.value = 2;
    listItem third;
    third.value = 3;

    head.next = &second;
    second.next = &third;
    third.next = NULL;

    listItem* tail = ListGetTail(&head);

    CLOVE_NOT_NULL(tail);
    CLOVE_INT_EQ(tail->value, third.value);
}

CLOVE_TEST(CreateListHeadWithAppend)
{
    listItem* head = NULL;
    ListAppend(&head, 10);
    CLOVE_NOT_NULL(head);
    CLOVE_INT_EQ(10, head->value);

    FreeListMemory(&head);
}

CLOVE_TEST(AppendAfterTheHead)
{
    listItem* head = NULL;
    ListAppend(&head, 10);
    ListAppend(&head, 20);
    ListAppend(&head, 30);

    CLOVE_NOT_NULL(head->next);
    CLOVE_NOT_NULL(head->next->next);

    CLOVE_INT_EQ(20, head->next->value);
    CLOVE_INT_EQ(30, head->next->next->value);

    FreeListMemory(&head);
}

CLOVE_TEST(ReverseListTest)
{
    listItem* head = NULL;
    ListAppend(&head, 10);
    ListAppend(&head, 20);
    ListAppend(&head, 30);

    ListReverse(&head);

    CLOVE_INT_EQ(30, head->value);
    CLOVE_INT_EQ(20, head->next->value);
    CLOVE_INT_EQ(10, head->next->next->value);

    FreeListMemory(&head);
}

CLOVE_TEST(RemoveValueWhichIsNotInTheList)
{
    listItem* head = NULL;
    ListAppend(&head, 10);
    ListAppend(&head, 20);
    ListAppend(&head, 30);

    int removed = ListRemoveValue(&head, 3);

    CLOVE_INT_EQ(-1, removed);

    FreeListMemory(&head);
}

CLOVE_TEST(RemoveHead)
{
    listItem* head = NULL;
    ListAppend(&head, 10);
    ListAppend(&head, 20);
    ListAppend(&head, 30);

    int removedResult = ListRemoveValue(&head, head->value);

    CLOVE_INT_EQ(0, removedResult);
    CLOVE_INT_EQ(20, head->value);

    FreeListMemory(&head);
}

CLOVE_TEST(RemoveValueInsideList)
{
    listItem* head = NULL;
    ListAppend(&head, 10);
    ListAppend(&head, 20);
    ListAppend(&head, 30);

    int removedResult = ListRemoveValue(&head, head->next->value);

    CLOVE_INT_EQ(0, removedResult);
    CLOVE_INT_EQ(30, head->next->value);

    FreeListMemory(&head);
}

CLOVE_TEST(RemoveLastValue)
{
    listItem* head = NULL;
    ListAppend(&head, 10);
    ListAppend(&head, 20);
    ListAppend(&head, 30);

    int removedResult = ListRemoveValue(&head, head->next->next->value);

    CLOVE_INT_EQ(0, removedResult);
    CLOVE_NULL(head->next->next);

    FreeListMemory(&head);
}







