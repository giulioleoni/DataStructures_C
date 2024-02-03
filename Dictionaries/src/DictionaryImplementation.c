#include "Dictionary.h"

size_t HashDJB33X(const char* key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    
    return hash;
}

dictTable* NewDictTable(const size_t hashmapSize)
{
    if (hashmapSize <= 0)
    {
        return NULL;
    }

    struct dictTable* table = malloc(sizeof(struct dictTable));

    if(!table)
    {
        return NULL;
    }

    table->hashmapSize = hashmapSize;
    table->nodes = calloc(table->hashmapSize, sizeof(struct dictNode*));

    if (!table->nodes)
    {
        return NULL;
    }
    
    return table;
}



int DictAddKey(struct dictTable* table, const char* key, void* value)
{
    const size_t keyLen = strlen(key);
    const size_t hash = HashDJB33X(key, keyLen);
    const size_t index = hash % table->hashmapSize;

    struct dictNode* head = table->nodes[index];

    if (!head)
    {
        table->nodes[index] = malloc(sizeof(struct dictNode));

        if (!table->nodes[index])
        {
            return -1;
        }

        table->nodes[index]->key = key;
        table->nodes[index]->keyLen = keyLen;
        table->nodes[index]->next = NULL;
        table->nodes[index]->prev = NULL;
        table->nodes[index]->value = value;

        return 0; 
    }

    struct dictNode* newItem = malloc(sizeof(struct dictNode));

    if (!newItem)
    {
        return -1;
    }

    newItem->key = key;
    newItem->keyLen = keyLen;
    newItem->next = NULL;
    newItem->value = value;

    struct dictNode *tail;
    
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



dictNode* DictContainsKey(struct dictTable* table, const char* key)
{
    const size_t key_len = strlen(key);
    const size_t hash = HashDJB33X(key, key_len);

    const size_t index = hash % table->hashmapSize;

    if (!table->nodes[index])
    {
        return NULL;
    }

    dictNode* current_node = table->nodes[index];
    
    for (size_t i = 0; i < table->hashmapSize; i++)
    {
        if (current_node->keyLen == key_len && !memcmp(current_node->key, key, key_len))
        {
            return current_node;
        }
        else if (current_node->next)
        {
            current_node = current_node->next;
        }
    }

    printf("Key not found\n");
    return NULL;
}



void DictRemoveKey(struct dictTable* table, const char* key)
{
    dictNode* nodeToRemove = DictContainsKey(table, key);

    if (nodeToRemove)
    {
        const size_t key_len = strlen(key);
        const size_t hash = HashDJB33X(key, key_len);
        const size_t index = hash % table->hashmapSize;

        dictNode* current_node = table->nodes[index];

        if (!nodeToRemove->prev)
        {
            // case node_to_remove is a head
            table->nodes[index] = table->nodes[index]->next;
            if (table->nodes[index])
            {
                // case the head have elements in his list
                table->nodes[index]->prev = NULL;
            }
            
            free(current_node);
            return;
        }
        else
        {  
            nodeToRemove->prev->next = nodeToRemove->next;
            if (nodeToRemove->next)
            {
                // if is not the last element of the list
                nodeToRemove->next->prev = nodeToRemove->prev;
            }
            
            free(nodeToRemove);
            return;
        }
    }
}




