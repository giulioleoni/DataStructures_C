#include "Set.h"

size_t HashDJB33X(const char* key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

setTable* NewSetTable(const size_t hashmapSize)
{
    if (hashmapSize <= 0)
    {
        return NULL;
    }

    struct setTable* table = malloc(sizeof(struct setTable));

    if (!table)
    {
        return NULL;
    }

    table->hashmapSize = hashmapSize;
    table->nodes = calloc(table->hashmapSize, sizeof(struct setNode *));

    if (!table->nodes)
    {
        return NULL;
    }

    return table;
}

int SetInsert(struct setTable* table, const char* key)
{
    const size_t keyLen = strlen(key);
    const size_t hash = HashDJB33X(key, keyLen);
    const size_t index = hash % table->hashmapSize;

    struct setNode* head = table->nodes[index];

    if (!head)
    {
        table->nodes[index] = malloc(sizeof(struct setNode));

        if (!table->nodes[index])
        {
            return -1;
        }

        table->nodes[index]->key = key;
        table->nodes[index]->keyLen = keyLen;
        table->nodes[index]->next = NULL;
        table->nodes[index]->prev = NULL;

        return 0;
    }

    struct setNode* newItem = malloc(sizeof(struct setNode));
    if (!newItem)
    {
        return -1;
    }

    newItem->key = key;
    newItem->keyLen = keyLen;
    newItem->next = NULL;

    struct setNode* tail;

    while (head)
    {
        if (newItem->keyLen == head->keyLen && !memcmp(head->key, newItem->key, keyLen))
        {
            free(newItem);
            return -2;
        }

        tail = head;
        head = head->next;
    }

    tail->next = newItem;
    newItem->prev = tail;
    return 0;
}

setNode* SetSearch(struct setTable* table, const char* key)
{
    const size_t keyLen = strlen(key);
    const size_t hash = HashDJB33X(key, keyLen);
    const size_t index = hash % table->hashmapSize;

    if (!table->nodes[index])
    {
        return NULL;
    }

    setNode* currentNode = table->nodes[index];

    while (currentNode)
    {
        if (currentNode->keyLen == keyLen && !memcmp(currentNode->key, key, keyLen))
        {
            return currentNode;
        }

        currentNode = currentNode->next;
    }

    return NULL;
}

void SetRemove(struct setTable* table, const char* key)
{
    setNode* nodeToRemove = SetSearch(table, key);

    if (nodeToRemove)
    {
        if (!nodeToRemove->prev)
        {
            // case nodeToRemove is a head, table->nodes[index]
            const size_t keyLen = strlen(key);
            const size_t hash = HashDJB33X(key, keyLen);
            const size_t index = hash % table->hashmapSize;

            table->nodes[index] = table->nodes[index]->next;
            if (table->nodes[index])
            {
                // case the head have elements in his list
                table->nodes[index]->prev = NULL;
            }

            free(nodeToRemove);
            return;
        }
        else
        {
            nodeToRemove->prev->next = nodeToRemove->next;
            if (nodeToRemove->next)
            {
                // if it is not the last element of the list
                nodeToRemove->next->prev = nodeToRemove->prev;
            }

            free(nodeToRemove);
            return;
        }
    }

}