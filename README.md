# DataStructures

This project was done to understand how data structures work, so as to use them in the most efficient way.

This repo contains C language implementation of 4 common data structures as well as tests to check functionality.

The single-header library [clove unit](https://github.com/fdefelici/clove-unit), which can be found in the include directory, was used to write the tests.

In each directory there is a .bat file that is used to compile, it will create the bin directory where you will find the executable that will run the tests.

## LinkedLists and DoublyLinkedLists

I used a struct to represent che single item of the list (for convenience, I decided to make lists containing integers):

``` c                                                                        
typedef struct listItem                             
{
    struct listItem* next;
    int value;
} listItem ;
```
``` c   
typedef struct doublyListItem
{
    struct doublyListItem* next;
    struct doublyListItem* prev;
    int value;
} doublyListItem;
```



The most complicated part for me was implementing removal in the linked lists, since I only know the next element and not the previous one, so I thought of making a loop that always look one position ahead 

```c
void ListRemoveValue(listItem** head, int value)
{
    if (!*head)
    {
        return;
    }   
        
    listItem* itemToRemove = NULL;

    if ((*head)->value == value)
    {
        // head is the item to remove
        itemToRemove = *head;
        *head = (*head)->next;
        free(itemToRemove);
        return;
    }

    if ((*head)->next)
    {
        listItem* currentItem = *head;

        while (currentItem->next->value != value)
        {
            currentItem = currentItem->next;
            if (!currentItem->next)
            {
                return;
            }
        }    

        itemToRemove = currentItem->next;
        currentItem->next = currentItem->next->next;
        free(itemToRemove);
    }
}
```

Instead, in double-linked lists, I was able to split the removal of an item into two steps, search and remove, without having to do two loops

``` c                                                                        
void DoublyListRemoveValue(doublyListItem** head, int value)
{
    if (!*head)
    {
        return;
    }   
    
    doublyListItem* toRemove = DoublyListFindItem(*head, value);

    DoublyListRemoveItem(head, toRemove);
}
```




## Sets and Dictionaries

Sets and Dictionaries are implemented using a hashtable.

The hash function used is very simple:

``` c                                                                        
size_t HashDJB33X(const char* key, const size_t keyLen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keyLen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}
```


I used two structs, one to represent the table and one to represent the single element (node)  

``` c                                                                        
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
```

``` c                                                                        
typedef struct dictTable
{
    struct dictNode** nodes;
    size_t hashmapSize;
    size_t max_collisions;
    size_t collisions_count;
} dictTable;

typedef struct dictNode
{
    const char* key;
    size_t keyLen;
    struct dictNode* next;
    struct dictNode* prev;
    void* value; 
} dictNode;
```

In the case the hashing algorithm gives an equal value for two keys (a collision), the second one will be added at the end of the previous node, as if it were the head of a list.

``` c                                                                        
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
         // already existing key
        free(newItem);
        return -2;
    }

    tail = head;
    head = head->next;
}

tail->next = newItem;
newItem->prev = tail;
return 0;
```

Initially I thought of handling the nodes, of both sets and dictionaries, as elements of a linked list, but I found it difficult to implement the removal, so I decided to make them nodes of a doubly linked list.

The Dictionary table takes into account the number of collisions because if they become too many, and the list becomes too large, it will have to recreate the table with increased capacity and rehash all the elements.

Inside the function that adds an element to the dictionary:

``` c                                                                        
tail->next = newItem;
newItem->prev = tail;

// collision
(*table)->collisions_count++;
if ((*table)->collisions_count >= (*table)->max_collisions)
{
    DictRecreateTable(table);
}

return 0;
```

``` c                                                                        
void DictRecreateTable(dictTable** table)
{
    dictTable* new_table = NewDictTable((*table)->hashmapSize * 2);

    // rehash
    for (size_t i = 0; i < (*table)->hashmapSize; i++)
    {
        dictNode* current_node = (*table)->nodes[i];
       
        while(current_node)
        {
            DictAddKey(&new_table, current_node->key, current_node->value);
            current_node = current_node->next;
        }
    }

    dictTable* old_table = *table;
    *table = new_table;

    FreeDictTable(&old_table);
    return;
}
```


## Tests

Sample of a test:

``` c                                                                        
CLOVE_TEST(RemoveValueInsideList)
{
    listItem* head = NULL;
    ListAppend(&head, 10);
    ListAppend(&head, 20);
    ListAppend(&head, 30);

    ListRemoveValue(&head, head->next->value);

    CLOVE_INT_EQ(30, head->next->value);

    FreeListMemory(&head);
}
```


To check that the item has been removed correctly I check that the head->next has changed.

Other tests might check the return value of the function.







