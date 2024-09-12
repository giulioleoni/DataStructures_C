# DataStructures
 
This repo contains C language implementation of 4 common data structures as well as tests to check functionality.

The single-header library [clove unit](https://github.com/fdefelici/clove-unit), which can be found in the include directory, was used to write the tests.

In each directory there is a .bat file that is used to compile, it will create the bin directory where you will find the executable that will run the tests.

## LinkedLists and DoublyLinkedLists

I used a struct to represent che single item of the list (for convenience, I decided to make lists containing integers):

![photo_1_2024-09-11_15-35-54](https://github.com/user-attachments/assets/8f5d67d1-f375-487f-8de5-643c46c60d39)                     ![photo_2_2024-09-11_15-35-54](https://github.com/user-attachments/assets/d9ca3fc6-0d22-4cbd-85ff-9b1a67b52647)



The most complicated part for me was implementing removal in the linked lists, since I only know the next element and not the previous one, so I thought of making a loop that always look one position ahead 

![photo_2_2024-09-11_16-12-52](https://github.com/user-attachments/assets/657f1b00-dbeb-4fc4-92c1-416cbc37b5be)


Instead, in double-linked lists, I was able to split the removal of an item into two steps, search and remove, without having to do two loops


![photo_1_2024-09-11_16-12-52](https://github.com/user-attachments/assets/c3a18d16-ec34-405e-9f60-46d0c62efdec)




## Sets and Dictionaries

Sets and Dictionaries are implemented using a hashtable.

The hash function used is very simple:

![hashnuovo](https://github.com/user-attachments/assets/890729d8-aa63-4539-98b9-76342e290f45)


I used two structs, one to represent the table and one to represent the single element (node)  

![photo_1_2024-09-11_16-22-55](https://github.com/user-attachments/assets/1ea6a044-4475-44af-848e-99b3def43d16)           ![photo_2_2024-09-11_16-22-55](https://github.com/user-attachments/assets/e44f8a14-aa24-44d8-b007-4bf2ce07abf1)

In the case the hashing algorithm gives an equal value for two keys (a collision), the second one will be added at the end of the previous node, as if it were a list.

![Screenshot 2024-09-11 181549](https://github.com/user-attachments/assets/e8da71c4-70c3-4a9b-a09c-a9f554680d5f)

Initially I thought of handling the nodes, of both sets and dictionaries, as elements of a linked list, but I found it difficult to implement the removal, so I decided to make them nodes of a doubly linked list.

The Dictionary table takes into account the number of collisions because if they become too many, and the list becomes too large, it will have to recreate the table with increased capacity and rehash all the elements.

Inside the function that adds an element to the dictionary:

![Screenshot 2024-09-12 173254](https://github.com/user-attachments/assets/80b5f14d-ae32-4471-a471-12471fc80ebd)


![recreate](https://github.com/user-attachments/assets/95fafa32-af3c-4574-ab28-4b8854034a69)


## Tests

Sample of a test:

![test](https://github.com/user-attachments/assets/b5b8a16f-e7d9-4d0b-b9a3-62b21fb014f7)


To check that the item has been removed correctly I check that the head->next has changed.

Other tests might check the return value of the function.







