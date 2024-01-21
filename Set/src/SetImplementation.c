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

void PrintSet(struct setTable* table)
{
    if (!table)
    {
        return;
    }
    
    for (int i = 0; i < table->hashmapSize; i++)
    {
        if (table->nodes[i])
        {
            printf("%s key of keylen %zu at set index [%d]\n", table->nodes[i]->key, table->nodes[i]->keyLen, i);

            if (table->nodes[i]->next)
            {
                setNode* node = table->nodes[i]->next;

                int a = 1;

                while (node)
                {
                    printf("%s key of keylen %llu it the [%d] list at list index {%d}\n", node->key, node->keyLen, i, a);
                    
                    node = node->next;
                    a++;
                }
            }   
        }
    } 
}

setTable* NewSetTable(const size_t hashmapSize)
{
    if (hashmapSize <= 0)
    {
        return NULL;
    }
    
    struct setTable* table = malloc(sizeof(struct setTable));

    if(!table)
    {
        return NULL;
    }

    table->hashmapSize = hashmapSize;
    table->nodes = calloc(table->hashmapSize, sizeof(struct setNode *));

    if (!table->nodes)
    {
        free(table);
        return NULL;
    }
    
    return table;
}



int SetInsert(struct setTable* table, const char *key)
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
        //printf("There aren't any elements at this set index\n");
        return NULL;
    }

    setNode* currentNode = table->nodes[index];
    
    for (size_t i = 0; i < table->hashmapSize; i++)
    {
        if (currentNode->keyLen == keyLen && !memcmp(currentNode->key, key, keyLen))
        {
            //printf("FOUND %s at index [%llu], linked list slot {%llu}\n", key, index, i);
            
            return currentNode;
        }
        else if (currentNode->next)
        {
            currentNode = currentNode->next;
        }
        
    }
    //printf("Key not found");
    return NULL;
}



int SetRemove(struct setTable* table, const char* key)
{
    setNode* nodeToRemove = SetSearch(table, key);

    if (nodeToRemove)
    {
        const size_t keyLen = strlen(key);
        const size_t hash = HashDJB33X(key, keyLen);
        const size_t index = hash % table->hashmapSize;

        setNode* currentNode = table->nodes[index];

        if (!nodeToRemove->prev)
        {
            // case nodeToRemove is a head
            table->nodes[index] = table->nodes[index]->next;
            if (table->nodes[index])
            {
                // case the head have elements in his list
                table->nodes[index]->prev = NULL;
            }
            
            free(currentNode);
            return 0;
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
            return 0;
        }
    }

    return -1;
}


