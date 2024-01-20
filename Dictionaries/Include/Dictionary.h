#ifndef DICTIONARY_H
#define DICTIONARY_H
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
    void* value; 
} dictNode;



size_t HashDJB33X(const char* key, const size_t keylen);
void PrintDict(struct dictTable* table);
dictTable* NewDictTable(const size_t hashmapSize);
int DictAddKey(struct dictTable* table, const char* key, void* value);
dictNode* DictContainsKey(struct dictTable* table, const char* key);
int DictRemoveKey(struct dictTable* table, const char* key);



#endif












