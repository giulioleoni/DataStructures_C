#include "LinkedLists.h"
#include "LinkeListUnitTest.h"

AIVUNIT_TEST(GetTailTest)
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

    listItem* tail = GetTail(&head);

    AIVUNIT_IS_TRUE(tail != NULL)
    AIVUNIT_INT_EQ(tail->value, third.value)
}

AIVUNIT_TEST(CreateListHeadWithAppend)
{
    listItem* head = NULL;
    ListAppend(&head, 10);
    AIVUNIT_IS_TRUE(head != NULL)
    AIVUNIT_INT_EQ(head->value, 10)

    FreeListMemory(&head);
}

AIVUNIT_TEST(AppendAfterTheHead)
{
    listItem* head = NULL;
    ListAppend(&head, 10);
    ListAppend(&head, 20);
    ListAppend(&head, 30);

    AIVUNIT_IS_TRUE(head->next != NULL)
    AIVUNIT_IS_TRUE(head->next->next != NULL)

    AIVUNIT_INT_EQ(head->next->value, 20)
    AIVUNIT_INT_EQ(head->next->next->value, 30)

    FreeListMemory(&head);
}

AIVUNIT_TEST(ReverseListTest)
{
    listItem* head = NULL;
    ListAppend(&head, 10);
    ListAppend(&head, 20);
    ListAppend(&head, 30);

    ReverseList(&head);

    AIVUNIT_INT_EQ(head->value, 30)
    AIVUNIT_INT_EQ(head->next->value, 20)
    AIVUNIT_INT_EQ(head->next->next->value, 10)

    FreeListMemory(&head);
}

AIVUNIT_TEST(RemoveValueWhichIsNotInTheList)
{
    listItem* head = NULL;
    ListAppend(&head, 10);
    ListAppend(&head, 20);
    ListAppend(&head, 30);

    int removed = RemoveValueFromList(&head, 3);

    AIVUNIT_INT_EQ(removed, -1)

    FreeListMemory(&head);
}

AIVUNIT_TEST(RemoveHead)
{
    listItem* head = NULL;
    ListAppend(&head, 10);
    ListAppend(&head, 20);
    ListAppend(&head, 30);

    int removed = RemoveValueFromList(&head, head->value);

    AIVUNIT_INT_EQ(removed, 10)
    AIVUNIT_INT_EQ(head->value, 20)

    FreeListMemory(&head);
}

AIVUNIT_TEST(RemoveValueInsideList)
{
    listItem* head = NULL;
    ListAppend(&head, 10);
    ListAppend(&head, 20);
    ListAppend(&head, 30);

    int removed = RemoveValueFromList(&head, head->next->value);

    AIVUNIT_INT_EQ(removed, 20)

    FreeListMemory(&head);
}

AIVUNIT_TEST(RemoveLastValue)
{
    listItem* head = NULL;
    ListAppend(&head, 10);
    ListAppend(&head, 20);
    ListAppend(&head, 30);

    int removed = RemoveValueFromList(&head, head->next->next->value);

    AIVUNIT_INT_EQ(removed, 30)

    FreeListMemory(&head);
}

AIVUNIT_RUNNER(GetTailTest, 
               CreateListHeadWithAppend, 
               AppendAfterTheHead, 
               ReverseListTest, 
               RemoveValueWhichIsNotInTheList, 
               RemoveHead, 
               RemoveValueInsideList,
               RemoveLastValue);


