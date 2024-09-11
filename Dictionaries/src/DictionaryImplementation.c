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
    table->max_collisions = 3;
    table->collisions_count = 0;
    table->nodes = calloc(table->hashmapSize, sizeof(struct dictNode*));

    if (!table->nodes)
    {
        return NULL;
    }
    
    return table;
}



int DictAddKey(struct dictTable** table, const char* key, void* value)
{
    const size_t keyLen = strlen(key);
    const size_t hash = HashDJB33X(key, keyLen);
    const size_t index = hash % (*table)->hashmapSize;

    struct dictNode* head = (*table)->nodes[index];

    if (!head)
    {
        (*table)->nodes[index] = malloc(sizeof(struct dictNode));

        if (!(*table)->nodes[index])
        {
            return -1;
        }

        (*table)->nodes[index]->key = key;
        (*table)->nodes[index]->keyLen = keyLen;
        (*table)->nodes[index]->next = NULL;
        (*table)->nodes[index]->prev = NULL;
        (*table)->nodes[index]->value = value;

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

    struct dictNode* tail;
    
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

    // collision
    (*table)->collisions_count++;
    if ((*table)->collisions_count >= (*table)->max_collisions)
    {
        //DictRehash(table);
        DictRecreateTable(table);
    }

    return 0;
}



dictNode* DictContainsKey(struct dictTable* table, const char* key)
{
    const size_t keyLen = strlen(key);
    const size_t hash = HashDJB33X(key, keyLen);

    const size_t index = hash % table->hashmapSize;

    if (!table->nodes[index])
    {
        return NULL;
    }

    dictNode* currentNode = table->nodes[index];

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



void DictRemoveKey(struct dictTable* table, const char* key)
{
    dictNode* nodeToRemove = DictContainsKey(table, key);

    if (nodeToRemove)
    {
        const size_t key_len = strlen(key);
        const size_t hash = HashDJB33X(key, key_len);
        const size_t index = hash % table->hashmapSize;

        dictNode* currentNode = table->nodes[index];

        if (!nodeToRemove->prev)
        {
            // case node_to_remove is a head
            table->nodes[index] = table->nodes[index]->next;
            if (table->nodes[index])
            {
                // case the head have elements in his list
                table->nodes[index]->prev = NULL;
            }
            
            free(currentNode);
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

void DictRehash(dictTable** table)
{
    // dictTable* new_table = NewDictTable((*table)->hashmapSize * 2);

    for (size_t i = 0; i < (*table)->hashmapSize; i++)
    {
        dictNode* current_node = (*table)->nodes[i];
        while(current_node)
        {
            DictAddKey(table, current_node->key, current_node->value);
            current_node = current_node->next;
        }
    }

    // dictTable* old_table = *table;
    // *table = new_table;
    // free(old_table);
    // return;
}

void DictRecreateTable(dictTable **table)
{
    dictTable* new_table = NewDictTable((*table)->hashmapSize * 2);

    DictRehash(&new_table);

    dictTable* old_table = *table;
    *table = new_table;
    free(old_table);
    return;
}
