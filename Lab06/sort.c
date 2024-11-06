/**
 * @file    sort.c
 */
// Heap size of >= 1024 required!
// Standard libraries.
#include <stdio.h>
#include <string.h>

// User libraries.
#include "sort.h"


/**
 * SelectionSort() performs a selection sort on a passed to it. The list is
 * sorted alphabetically, as determined by string.h's strcmp().  
 *
 * @param list Any element in a linked list to sort.  
 * @return a pointer to the head of the sorted list.
 * 
 * SelectionSort() assumes that no list items have a NULL data member. It also
 * assumes that 'list' is a valid, non-NULL pointer to a linked list.
 * 
 * This function does not print.
 */
ListItem *SelectionSort(ListItem* list)
{

const int zero = 0;

ListItem* first_unsorted = list;

 ListItem* scan;

 while(first_unsorted->nextItem != NULL){

    scan = first_unsorted->nextItem;

    //printf("%s\n", scan->data);

while(scan != NULL){

   // char* str_1 = first_unsorted->data;

    //char* str_2 = scan->data;

    if (strcmp(first_unsorted->data, scan->data) > zero){

            LinkedListSwapData(first_unsorted, scan);

    }

scan = scan->nextItem;

}
first_unsorted= first_unsorted->nextItem;
 }

return first_unsorted;
}

/**
 * InsertionSort() performs an insertion sort on a passed to it.  The list is sorted alphabetically,
 * as determined by string.h's strcmp().  
 *
 * @param list Any element in a linked list to sort.  
 * @return a pointer to the head of the sorted list.
 * 
 * SelectionSort() assumes that no list items have a NULL data member.  It also assumes that 'list'
 * is a valid, non-NULL pointer to a linked list.
 * 
 * This function does not print.
 */
ListItem *InsertionSort(ListItem* list)
{

const int zero = 0;

ListItem* first_sorted = LinkedListGetLast(list);

ListItem* scan;

ListItem* unsorted;

while(first_sorted->previousItem != NULL){

unsorted = first_sorted->previousItem;

if(strcmp(unsorted->data, first_sorted->data) < zero){

first_sorted = unsorted;

}else {

scan = first_sorted;

while(scan->nextItem != NULL){

if(strcmp(scan->nextItem->data, unsorted->data) > zero){

break;

} else{

scan = scan->nextItem;

}


}

char* data = LinkedListRemove(unsorted);

LinkedListCreateAfter(scan,data);

}

}

return scan;

}

/**
 * CreateUnsortedList() uses the functions in the LinkedList library to
 * generate an unsorted list.  
 * 
 * Students should not modify this function!
 * If an error occurs in this function, there is almost certainly 
 * a bug in your implementation of LinkedList.h.
 *   
 * @return A pointer to a ListItem which is the head of a new unsorted list. 
 */
ListItem *CreateUnsortedList(void)
{
    
    char* wordList[] = {
        "decide", "toothpaste", "lowly", "robin", "reign", "crowd", "pies",
        "reduce", "tendency", "surround", "finger", "rake", "alleged", "hug",
        "nest", "punishment", "eggnog", "side", "beef", "exuberant", "sort",
        "scream", "zip", "hair", "ragged", "damage", "thought", "jump",
        "frequent", "substance", "head", "step", "faithful", "sidewalk", "pig",
        "raspy", "juggle", "shut", "maddening", "rock", "telephone",
        "selective", NULL
    };

   // char* last_4_pres[] = {"D","C","B","A",NULL}; // {"George W. Bush", "Barack H. Obama", "Donald J. Trump", "Joseph R. Biden", NULL};          //{"D","C","B","A",NULL};
        
        //"George W. Bush", "Barack H. Obama", "Donald J. Trump", "Joseph R. Biden", NULL};

    int i = 0;
    ListItem* head = LinkedListNew(wordList[i]);
    ListItem* tail = head;
    for (i = 1; wordList[i] != NULL; i++) {
        tail = LinkedListCreateAfter(tail, wordList[i]);
        if (tail == NULL) {
          // If a NULL pointer is found, return NULL for the calling script to 
          // check.
          return NULL;
        }
        
    }
    return head;
}

