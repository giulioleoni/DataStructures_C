# DataStructures
 
This repo contains C language implementation of 4 common data structures as well as tests to check functionality.

The single-header library [clove unit](https://github.com/fdefelici/clove-unit) was used to write the tests.

## LinkedLists and DoublyLinkedLists

I used a struct to represent che single item of the list (for convenience, I decided to make lists containing integers):

![photo_1_2024-09-11_15-35-54](https://github.com/user-attachments/assets/8f5d67d1-f375-487f-8de5-643c46c60d39)                     ![photo_2_2024-09-11_15-35-54](https://github.com/user-attachments/assets/d9ca3fc6-0d22-4cbd-85ff-9b1a67b52647)



The most complicated part for me was implementing removal in the linked lists, since I only know the next element and not the previous one, so I thought of making a loop that always look one position ahead 

![photo_2_2024-09-11_16-12-52](https://github.com/user-attachments/assets/657f1b00-dbeb-4fc4-92c1-416cbc37b5be)


Instead, in double-linked lists, I was able to split the removal of an item into two steps, search and removal, without having to do two loops


![photo_1_2024-09-11_16-12-52](https://github.com/user-attachments/assets/c3a18d16-ec34-405e-9f60-46d0c62efdec)

## Sets and Dictionaries

Sets and Dictionaries are implemented using a hashtable.

The hash function used is very simple:


![hash](https://github.com/user-attachments/assets/32702528-d57b-49b6-b50a-01f47e0ce646)

I used two structs, one to represent the table and one to represent the single element (node)  

![photo_1_2024-09-11_16-22-55](https://github.com/user-attachments/assets/1ea6a044-4475-44af-848e-99b3def43d16)           ![photo_2_2024-09-11_16-22-55](https://github.com/user-attachments/assets/e44f8a14-aa24-44d8-b007-4bf2ce07abf1)

In the case the hashing algorithm gives an equal value for two keys (a collision), the second one will be added at the end of the previous node, as if it were a list.

I used doubly linked lists because they facilitate removal

The Dictionary table takes into account the number of collisions because if they become too many, and the list becomes too large, it will have to regenerate the table with increased capacity and rehash all the elements

















