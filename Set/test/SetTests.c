#define CLOVE_SUITE_NAME SetTest
#include "clove-unit.h"
#include "Set.h"

CLOVE_TEST(CreateNewSetTable)
{
    setTable* table = NewSetTable(4);

    CLOVE_NOT_NULL(table);
    free(table);
}

CLOVE_TEST(CreateNewSetTableWhitNegativeSize)
{
    setTable* table = NewSetTable(-4);

    CLOVE_NULL(table);
}

CLOVE_TEST(AddOneKeyToNewSet)
{
    setTable* table = NewSetTable(4);

    const char* string0 = "Word";

    SetInsert(table, string0);

    CLOVE_STRING_EQ(string0, table->nodes[3]->key);
    FreeSetTable(&table);
}

CLOVE_TEST(AddMoreKeyToNewSet)
{
    setTable* table = NewSetTable(4);

    const char* string1 = "abc";
    const char* string2 = "AAAAAA";
    const char* string3 = "pizza";

    SetInsert(table, string1);
    SetInsert(table, string2);
    SetInsert(table, string3);

    CLOVE_STRING_EQ(string2, table->nodes[1]->next->key);
    CLOVE_STRING_EQ(string3, table->nodes[1]->next->next->key);
    FreeSetTable(&table);
}

CLOVE_TEST(AddAnExistingKey)
{
    setTable* table = NewSetTable(4);

    const char* string1 = "abc";
    const char* string2 = "AAAAAA";
    const char* string3 = "pizza";
    const char* string4 = "AAAAAA";

    SetInsert(table, string1);
    SetInsert(table, string2);
    SetInsert(table, string3);
    int insertResult = SetInsert(table, string4);

    CLOVE_INT_EQ(-2, insertResult);
    FreeSetTable(&table);
}

CLOVE_TEST(SetSearchAnExistingKey)
{
    setTable* table = NewSetTable(4);

    const char* string1 = "abc";
    const char* string2 = "AAAAAA";
    const char* string3 = "pizza";

    SetInsert(table, string1);
    SetInsert(table, string2);
    SetInsert(table, string3);

    setNode* nodeToCheck = SetSearch(table, string2);
    CLOVE_NOT_NULL(nodeToCheck);
    FreeSetTable(&table);
}

CLOVE_TEST(SetSearchANotExistingKey)
{
    setTable* table = NewSetTable(4);

    const char* string1 = "abc";
    const char* string2 = "AAAAAA";
    const char* string3 = "pizza";

    SetInsert(table, string1);
    SetInsert(table, string2);
    SetInsert(table, string3);

    setNode* nodeToCheck = SetSearch(table, "dnjsnc");
    CLOVE_NULL(nodeToCheck);
    FreeSetTable(&table);
}

CLOVE_TEST(RemovingTheOnlyElementOfTheSet)
{
    setTable* table = NewSetTable(4);

    const char* string0 = "Word";

    SetInsert(table, string0);

    SetRemove(table, string0);

    CLOVE_NULL(table->nodes[3]);
    FreeSetTable(&table);
}

CLOVE_TEST(RemovingElementInsideSet)
{
    // removing a node, which is inside a list of the set
    setTable* table = NewSetTable(4);

    const char* string1 = "abc";
    const char* string2 = "AAAAAA";
    const char* string3 = "pizza";

    SetInsert(table, string1);
    SetInsert(table, string2);
    SetInsert(table, string3);

    SetRemove(table, string2);
    
    CLOVE_STRING_EQ(string3, table->nodes[1]->next->key);
    FreeSetTable(&table);
}

CLOVE_TEST(RemovingHeadOfSet)
{
    // removing a node, which is head of a list with other elements
    setTable* table = NewSetTable(4);

    const char* string1 = "abc";
    const char* string2 = "AAAAAA";
    const char* string3 = "pizza";

    SetInsert(table, string1);
    SetInsert(table, string2);
    SetInsert(table, string3);

    SetRemove(table, string1);
    
    CLOVE_STRING_EQ(string2, table->nodes[1]->key);
    FreeSetTable(&table);
}

CLOVE_TEST(RemovingLastSetElement)
{
    // removing a node, which is the last element of a list 
    setTable* table = NewSetTable(4);

    const char* string1 = "abc";
    const char* string2 = "AAAAAA";
    const char* string3 = "pizza";

    SetInsert(table, string1);
    SetInsert(table, string2);
    SetInsert(table, string3);

    SetRemove(table, string3);

    CLOVE_NULL(table->nodes[1]->next->next);
    FreeSetTable(&table);
}
