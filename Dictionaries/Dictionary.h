#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct dictTable
{
    struct dictNode** nodes;
    size_t hashmapSize;
} dictTable;



typedef struct dictNode
{
    const char* key;
    size_t keyLen;
    struct dictNode* next;
    struct dictNode* prev;
    int value; 
} dictNode;



size_t HashDJB33X(const char* key, const size_t keylen);
void PrintDict(struct dictTable* table);
dictTable* NewDictTable(const size_t hashmapSize);
void DictAddKey(struct dictTable* table, const char* key, const int value);
dictNode* DictContainsKey(struct dictTable* table, const char* key);
void DictRemoveKey(struct dictTable* table, const char* key);
















