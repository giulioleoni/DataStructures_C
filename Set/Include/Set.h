#ifndef SET_H
#define SET_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



typedef struct setTable
{
    struct setNode** nodes;
    size_t hashmapSize;
} setTable;

typedef struct setNode
{
    const char* key;
    size_t keyLen;
    struct setNode* next;
    struct setNode* prev;
} setNode;



size_t HashDJB33X(const char* key, const size_t keyLen);
setTable* NewSetTable(const size_t hashmapSize);
int SetInsert(struct setTable* table, const char* key);
setNode* SetSearch(struct setTable* table, const char* key);
void SetRemove(struct setTable* table, const char* key);
void FreeSetNodesMemory(setNode** head);
void FreeSetTable(setTable** table);


#endif