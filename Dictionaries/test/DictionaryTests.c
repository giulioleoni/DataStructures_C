#define CLOVE_SUITE_NAME DictionaryTest
#include "clove-unit.h"
#include "Dictionary.h"

CLOVE_TEST(CreateNewDictTable)
{
    dictTable* table = NewDictTable(4);

    CLOVE_NOT_NULL(table);
}

CLOVE_TEST(CreateNewDictTableWhitNegativeSize)
{
    dictTable* table = NewDictTable(-4);

    CLOVE_NULL(table);
}

CLOVE_TEST(AddOneKeyValuePairToNewDictTable)
{
    dictTable* table = NewDictTable(4);

    const char *string0 = "Word";
    int value0 = 1;

    DictAddKey(table, string0, &value0);

    CLOVE_STRING_EQ(string0, table->nodes[3]->key);
    CLOVE_INT_EQ(value0, *(int*)table->nodes[3]->value);
}

CLOVE_TEST(AddMoreKeyValuePairAfterAnExistingElement)
{
    // Adding more key at the same index, one after the other
    dictTable* table = NewDictTable(4);

    const char* string1 = "abc";
    const char* string2 = "AAAAAA";
    const char* string3 = "pizza";

    int value1 = 1;
    int value2 = 2;
    int value3 = 3;

    DictAddKey(table, string1, &value1);
    DictAddKey(table, string2, &value2);
    DictAddKey(table, string3, &value3);

    CLOVE_STRING_EQ(string2, table->nodes[1]->next->key);
    CLOVE_INT_EQ(value2, *(int*)table->nodes[1]->next->value);

    CLOVE_STRING_EQ(string3, table->nodes[1]->next->next->key);
    CLOVE_INT_EQ(value3, *(int*)table->nodes[1]->next->next->value);
}

CLOVE_TEST(AddAnExistingKey)
{
    dictTable* table = NewDictTable(4);

    const char* string1 = "abc";
    const char* string2 = "AAAAAA";
    const char* string3 = "pizza";
    const char* string4 = "pizza";

    int value1 = 1;
    int value2 = 2;
    int value3 = 3;
    int value4 = 4;

    DictAddKey(table, string1, &value1);
    DictAddKey(table, string2, &value2);
    DictAddKey(table, string3, &value3);
    int addResult = DictAddKey(table, string4, &value4);

    CLOVE_INT_EQ(-2, addResult);
}

CLOVE_TEST(DictionaryContainsKey)
{
    dictTable* table = NewDictTable(4);

    const char* string1 = "abc";
    const char* string2 = "AAAAAA";
    const char* string3 = "pizza";

    int value1 = 1;
    int value2 = 2;
    int value3 = 3;

    DictAddKey(table, string1, &value1);
    DictAddKey(table, string2, &value2);
    DictAddKey(table, string3, &value3);

    dictNode* nodeToCheck = DictContainsKey(table, string2);

    CLOVE_NOT_NULL(nodeToCheck);
}

CLOVE_TEST(DictionaryNotContainsKey)
{
    dictTable* table = NewDictTable(4);

    const char* string1 = "abc";
    const char* string2 = "AAAAAA";
    const char* string3 = "pizza";

    int value1 = 1;
    int value2 = 2;
    int value3 = 3;

    DictAddKey(table, string1, &value1);
    DictAddKey(table, string2, &value2);
    DictAddKey(table, string3, &value3);

    dictNode* nodeToCheck = DictContainsKey(table, "pasta");

    CLOVE_NULL(nodeToCheck);
}

CLOVE_TEST(RemovingKeyWhichIsTheOnlyElement)
{
    dictTable* table = NewDictTable(4);

    const char* string0 = "Word";
    int value0 = 1;

    DictAddKey(table, string0, &value0);

    int removeResult = DictRemoveKey(table, string0);

    CLOVE_INT_EQ(0, removeResult);
    CLOVE_NULL(table->nodes[3]);
}

CLOVE_TEST(RemovingKeyInsideDictionary)
{
    // removing a key, which is inside a list of the dictionary
    dictTable* table = NewDictTable(4);

    const char* string1 = "abc";
    const char* string2 = "AAAAAA";
    const char* string3 = "pizza";

    int value1 = 1;
    int value2 = 2;
    int value3 = 3;

    DictAddKey(table, string1, &value1);
    DictAddKey(table, string2, &value2);
    DictAddKey(table, string3, &value3);

    int removeResult = DictRemoveKey(table, string2);

    CLOVE_INT_EQ(0, removeResult);
    CLOVE_STRING_EQ(string3, table->nodes[1]->next->key);
    CLOVE_INT_EQ(value3, *(int*)table->nodes[1]->next->value);
}

CLOVE_TEST(RemovingKeyHeadOfList)
{
    // removing a key, which is head of a list with other elements
    dictTable* table = NewDictTable(4);

    const char* string1 = "abc";
    const char* string2 = "AAAAAA";
    const char* string3 = "pizza";

    int value1 = 1;
    int value2 = 2;
    int value3 = 3;

    DictAddKey(table, string1, &value1);
    DictAddKey(table, string2, &value2);
    DictAddKey(table, string3, &value3);

    int removeResult = DictRemoveKey(table, string1);

    CLOVE_INT_EQ(0, removeResult);
    CLOVE_STRING_EQ(string2, table->nodes[1]->key);
}

CLOVE_TEST(RemovingKeyAtEndOfList)
{
    // removing a key, which is the last element of a list 
    dictTable* table = NewDictTable(4);

    const char* string1 = "abc";
    const char* string2 = "AAAAAA";
    const char* string3 = "pizza";

    int value1 = 1;
    int value2 = 2;
    int value3 = 3;

    DictAddKey(table, string1, &value1);
    DictAddKey(table, string2, &value2);
    DictAddKey(table, string3, &value3);

    int removeResult = DictRemoveKey(table, string3);

    CLOVE_INT_EQ(0, removeResult);
    CLOVE_NULL(table->nodes[1]->next->next);
}

