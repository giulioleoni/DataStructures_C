#include "Set.h"
// some tests for the main functionalities


int main(int argc, char** argv)
{
    setTable* table = NewSetTable(4);
    
    const char* string0 = "Word";
    const char* string1 = "abc";
    const char* string2 = "AAAAAA";
    const char* string3 = "pizza";
    const char* string5 = "AAAAAA";

    printf("Case of an Empty Set\n");
    SetSearch(table, string1);

    SetInsert(table, string0);
    SetInsert(table, string1);
    SetInsert(table, string2);
    SetInsert(table, string3);
    SetInsert(table, string5);
    
    PrintSet(table);

    printf("searching a set element\n");
    SetSearch(table, string1);
    printf("\n");
    
    printf("searching a key which is not in the set\n");
    SetSearch(table, "dcsjn");
    printf("\n");

    printf("removing a set element, which is a head of a doubly linked list without other elements\n");
    SetRemove(table, string0);
    printf("\n");
    PrintSet(table);

    printf("removing a set element, which is inside a doubly linked list\n");
    SetRemove(table, string5);
    printf("\n");
    PrintSet(table);

    printf("removing a set element, which is head of a doubly linked list with other elements\n");
    SetRemove(table, string1);
    printf("\n");
    PrintSet(table);

    return 0;
}





