#include "DoublyLinkedLists.h"
// some tests for the main functionalities

int main(int argc, char** argv)
{
    doublyListItem* head = NULL;

    
    int numbers[4] = {10, 20, 30, 40};
    int numbersToAdd[4] ={5, 15, 50, 100};

    DoublyListAppend(&head, numbers[0]);
    DoublyListAppend(&head, numbers[1]);
    DoublyListAppend(&head, numbers[2]);
    DoublyListAppend(&head, numbers[3]);

    PrintDoublyList(head);
    printf("\n"); 
    PrintDoublyListReverse(head); 
    int removed;

    printf("remove the first value of the list\n");
    removed = RemoveValueFromDoublyList(&head, numbers[0]);  
    printf("Removed element: %d\n", removed);
    PrintDoublyList(head);   
    printf("\n"); 

    printf("remove value which is not in the list: %d\n", 2324);
    removed = RemoveValueFromDoublyList(&head, 2324);  
    printf("Removed element: %d\n", removed);
    PrintDoublyList(head);   
    printf("\n"); 

    printf("remove value at the end of the list\n");
    removed = RemoveValueFromDoublyList(&head, numbers[3]);  
    printf("Removed element: %d\n", removed);
    PrintDoublyList(head);   
    printf("\n"); 
    
    printf("adding value (before an item) inside the list\n");
    doublyListItem* item = head->next;
    AddValueBeforeItem(&item, numbersToAdd[0]);
    PrintDoublyList(head);   
    printf("\n"); 

    printf("adding value before the head\n");
    AddValueBeforeItem(&head, numbersToAdd[1]);
    PrintDoublyList(head);   
    printf("\n"); 

    printf("adding value (after an item) inside of the list\n");
    item = head->next;
    AddValueAfterItem(item, numbersToAdd[2]);
    PrintDoublyList(head);   
    printf("\n"); 

    printf("adding value at the end of the list\n");
    doublyListItem* tail = GetTail(head);
    AddValueAfterItem(tail, numbersToAdd[3]);
    PrintDoublyList(head);   
    printf("\n"); 
    PrintDoublyListReverse(head); 

    FreeDoublyListMemory(&head);
    
    return 0;
}




