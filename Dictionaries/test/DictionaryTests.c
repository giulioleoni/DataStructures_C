#define CLOVE_SUITE_NAME DictionaryTest
#include "clove-unit.h"
#include "Dictionary.h"

CLOVE_TEST(CreateNewDictTable)
{
    dictTable* table = NewDictTable(4);

    CLOVE_NOT_NULL(table);
    free(table);
}

CLOVE_TEST(CreateNewDictTableWhitNegativeSize)
{
    dictTable* table = NewDictTable(-4);

    CLOVE_NULL(table);
}

CLOVE_TEST(AddOneKeyValuePairToNewDictTable)
{
    dictTable* table = NewDictTable(4);

    const char* string0 = "Word";
    int value0 = 1;

    DictAddKey(&table, string0, &value0);

    CLOVE_STRING_EQ(string0, table->nodes[3]->key);
    CLOVE_INT_EQ(value0, *(int*)table->nodes[3]->value);
    FreeDictTable(&table);
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

    DictAddKey(&table, string1, &value1);
    DictAddKey(&table, string2, &value2);
    DictAddKey(&table, string3, &value3);

    CLOVE_STRING_EQ(string2, table->nodes[1]->next->key);
    CLOVE_INT_EQ(value2, *(int*)table->nodes[1]->next->value);

    CLOVE_STRING_EQ(string3, table->nodes[1]->next->next->key);
    CLOVE_INT_EQ(value3, *(int*)table->nodes[1]->next->next->value);
    FreeDictTable(&table);
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

    DictAddKey(&table, string1, &value1);
    DictAddKey(&table, string2, &value2);
    DictAddKey(&table, string3, &value3);
    int addResult = DictAddKey(&table, string4, &value4);

    CLOVE_INT_EQ(-2, addResult);
    FreeDictTable(&table);
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

    DictAddKey(&table, string1, &value1);
    DictAddKey(&table, string2, &value2);
    DictAddKey(&table, string3, &value3);

    dictNode* nodeToCheck = DictContainsKey(table, string2);

    CLOVE_NOT_NULL(nodeToCheck);
    FreeDictTable(&table);
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

    DictAddKey(&table, string1, &value1);
    DictAddKey(&table, string2, &value2);
    DictAddKey(&table, string3, &value3);

    dictNode* nodeToCheck = DictContainsKey(table, "pasta");

    CLOVE_NULL(nodeToCheck);
    FreeDictTable(&table);
}

CLOVE_TEST(RemovingKeyWhichIsTheOnlyElement)
{
    dictTable* table = NewDictTable(4);

    const char* string0 = "Word";
    int value0 = 1;

    DictAddKey(&table, string0, &value0);

    DictRemoveKey(table, string0);
    
    CLOVE_NULL(table->nodes[3]);
    free(table);
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

    DictAddKey(&table, string1, &value1);
    DictAddKey(&table, string2, &value2);
    DictAddKey(&table, string3, &value3);

    DictRemoveKey(table, string2);

    CLOVE_STRING_EQ(string3, table->nodes[1]->next->key);
    CLOVE_INT_EQ(value3, *(int*)table->nodes[1]->next->value);
    FreeDictTable(&table);
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

    DictAddKey(&table, string1, &value1);
    DictAddKey(&table, string2, &value2);
    DictAddKey(&table, string3, &value3);

    DictRemoveKey(table, string1);

    CLOVE_STRING_EQ(string2, table->nodes[1]->key);
    FreeDictTable(&table);
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

    DictAddKey(&table, string1, &value1);
    DictAddKey(&table, string2, &value2);
    DictAddKey(&table, string3, &value3);

    DictRemoveKey(table, string3);

    CLOVE_NULL(table->nodes[1]->next->next);
    FreeDictTable(&table);
}

CLOVE_TEST(RecreateTable)
{
    dictTable* table = NewDictTable(6);

    const char* string1 = "abc";
    const char* string2 = "AAAAAA";
    const char* string3 = "pizza";
    const char* string4 = "developer";
    const char* string5 = "pasta";
    const char* string6 = "printer";

    int value1 = 1;
    int value2 = 2;
    int value3 = 3;
    int value4 = 4;
    int value5 = 5;
    int value6 = 6;

    DictAddKey(&table, string1, &value1);
    DictAddKey(&table, string2, &value2);
    DictAddKey(&table, string3, &value3);
    DictAddKey(&table, string4, &value4);
    DictAddKey(&table, string5, &value5);
    DictAddKey(&table, string6, &value6);

    CLOVE_NOT_NULL(table);
    CLOVE_INT_EQ(12, table->hashmapSize);
    CLOVE_STRING_EQ("abc", DictContainsKey(table, "abc")->key);
    CLOVE_STRING_EQ("AAAAAA", DictContainsKey(table, "AAAAAA")->key);
    CLOVE_STRING_EQ("pizza", DictContainsKey(table, "pizza")->key);
    CLOVE_STRING_EQ("developer", DictContainsKey(table, "developer")->key);
    CLOVE_STRING_EQ("pasta", DictContainsKey(table, "pasta")->key);
    CLOVE_STRING_EQ("printer", DictContainsKey(table, "printer")->key);
    
    FreeDictTable(&table);
}