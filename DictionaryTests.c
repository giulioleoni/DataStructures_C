#include "Dictionary.h"
// some tests for the main functionalities

int main(int argc, char** argv)
{
    dictTable* table = NewDictTable(4);
    
    const char* string0 = "Word";
    const char* string1 = "abc";
    const char* string2 = "AAAAAA";
    const char* string3 = "pizza";
    const char* string5 = "AAAAAA";

    const int value0 = 0;
    const int value1 = 1;
    const int value2 = 2;
    const int value3 = 3;
    const int value4 = 4;

    printf("Case of an empty Dictionary\n");
    DictContainsKey(table, string3);



    DictAddKey(table, string0, value0);
    DictAddKey(table, string1, value1);
    DictAddKey(table, string2, value2);
    DictAddKey(table, string3, value3);
    DictAddKey(table, string5, value4);
    
    PrintDict(table);

    printf("Control if the key is already in the dictionary\n");
    DictContainsKey(table, string3);
    printf("\n");
    DictContainsKey(table, "dknwjkvnjsdhf");
    printf("\n");

    printf("removing a key, which is a head of a list without other elements\n");
    DictRemoveKey(table, string0);
    PrintDict(table);
    printf("\n");

    printf("removing a key, which is inside a list\n");
    DictRemoveKey(table, string2);
    PrintDict(table);
    printf("\n");

    printf("removing a key, which is head of a list with other elements\n");
    DictRemoveKey(table, string1);
    PrintDict(table);
    printf("\n");

    return 0;
}
