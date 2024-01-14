#include "LinkedLists.h"
// some tests for the main functionalities

int main(int argc, char** argv)
{
    int numbers[4] = {10, 20, 30, 40};

    listItem* head = NULL;
    int removed = RemoveValueFromList(&head, 3);
    PrintList(head);

    ListAppend(&head, numbers[0]);
    ListAppend(&head, numbers[1]);
    ListAppend(&head, numbers[2]);
    ListAppend(&head, numbers[3]);

    PrintList(head);  

    ReverseList(&head);
    printf("Reversed list\n");
    PrintList(head);  

    // back to the original
    ReverseList(&head);

    removed = RemoveValueFromList(&head, 3);
    printf("Removed element: %d\n", removed);         // -1 if the value isn't in the list 
    printf("\n");
    

    printf("Removing the head\n");
    removed = RemoveValueFromList(&head, numbers[0]);
    printf("Removed element: %d\n", removed); 
    PrintList(head);  
    printf("\n");

    printf("Removing a value in the middle of the list \n");
    removed = RemoveValueFromList(&head, numbers[2]);
    printf("Removed element: %d\n", removed); 
    PrintList(head);  
    printf("\n");

    printf("Removing a value at the end of the list \n");
    removed = RemoveValueFromList(&head, numbers[3]);
    printf("Removed element: %d\n", removed); 
    PrintList(head);  
    printf("\n");

    FreeListMemory(&head);
    
    return 0;
}



