#include "LinkedList.h"
#include <BOARD.h>
#include <stdio.h>
#include <stdlib.h>


ListItem *LinkedListNew(char *data){

ListItem *LL_new = (ListItem*)malloc(sizeof(ListItem)); // Create a new Linked List using malloc

if(LL_new == NULL){ // If malloc fails No Memory !!!

return NULL; // Return null

}else{ // If malloc succeeds

LL_new->data = data; // The data type for the new linked list is a char

LL_new->nextItem = NULL; // Since this is the first item nextItem == previousItem

LL_new->previousItem = NULL; // Same Idea as above

return LL_new; // Return our new Doubly Linked List

}

}

ListItem *LinkedListCreateBefore(ListItem *item, char *data){

ListItem* new_item_before = LinkedListNew(data);

if(new_item_before->data == NULL){ // If passed a NULL pointer NO next item: prev? <-> new_element <-> NULL <->  NULL <->

new_item_before->previousItem = item->previousItem; // Null points to previous item but nothing after it

item->previousItem = NULL; // item no longer points backwards

item->nextItem = NULL; // or forwards

return new_item_before;

// Scenario 1 {Nothing Before item}: new_element <-> item <-> something after?

}else if(item->previousItem == NULL){ // If theres nothing before item

item->previousItem = new_item_before; // previous points to newly inserted item

new_item_before->nextItem = item; // New item next points to item

return new_item_before; // return pointer to newly inserted item


} else { // Scenario 2: {Another item is present before item}: A <-> new_element <-> B

new_item_before->previousItem = item->previousItem; // The previous item of the new item points to the previous item of the item its inserted before

new_item_before->nextItem = item; // Next item of the new item points to the item its inserted in front off

item->previousItem = new_item_before; // item previous points to the newly inserted item

return new_item_before; // return pointer to newly inserted item

}

}

ListItem *LinkedListCreateAfter(ListItem *item, char *data){

ListItem* new_item_after = LinkedListNew(data);

if(new_item_after->data == NULL){ // If passed a NULL pointer NO previous item: NULL <-> new_element <-> Next Item?

new_item_after->nextItem = item->nextItem; // Null points to next item but nothing before it

item->previousItem = NULL; // item no longer points backwards

item->nextItem = NULL; // or forwards

return new_item_after; // Then return newly created ListItem

}else if(item->nextItem == NULL){ // Scenario 1: Inserted at end of a Linked List

new_item_after->previousItem = item; // Point to previous item

item->nextItem = new_item_after; // Previous item points to newly inserted item

return new_item_after; // Return newly created List Item

}else{ // Scenario 2: Inserted Anywhere else in the list

new_item_after->nextItem = item->nextItem; // Newly inserted item points to next item after it previously pointed at by item

new_item_after->previousItem = item; // previous pointer points to item which new item was inserted after

item->nextItem = new_item_after; // item next pointer points to newly inserted item

return new_item_after; // return newly created item

}


}

int LinkedListSize(ListItem *list){

 if(list == NULL){

    return 0;
 }   

 const int list_index = 1; // The index at which we start. Since we search both ends of the list we need to add the inital index back in

 int count_right = 0; // How many elements to the right of given List Item? 

 int count_left = 0; // How many elements to the left of given List Item??

ListItem* go_right = list->nextItem; // Start at the item to the right of given itme

ListItem* go_left = list->previousItem; // Start at the item to the left of given itme

while(go_right != NULL){ // While we don't hit null

count_right++; // increment rightwards elements counter

go_right = go_right->nextItem; // point to next item

}

while(go_left != NULL){ // Start at the item to the right of given item

count_left++; // increment rightwards element counter

go_left = go_left->previousItem; // point to next item

}

return count_right + count_left + list_index; // Return total Linked List size

}


ListItem *LinkedListGetFirst(ListItem *list){

if(list == NULL){ // if passed a null element

return NULL; // return null

}    

ListItem* go_first = list; // list item to return the first element

while(go_first != NULL && go_first->previousItem != NULL){ // While the end of the list hasn't been reached going left

go_first = go_first->previousItem; // increment the pointers

}

return go_first; // then return the first element

}

ListItem *LinkedListGetLast(ListItem *list){

    ListItem* go_last = list; // List item to return the least element

while(go_last != NULL && go_last->nextItem != NULL){ // while we haven't reached the end of the list going right

go_last = go_last->nextItem; // increment the pointers

}

return go_last; // then return last element


}

int LinkedListPrint(ListItem *list){

if(list == NULL){ // if what we want to print is NULL

    return STANDARD_ERROR; // return standard error

}else{

ListItem* printer = LinkedListGetFirst(list); // otherwise get the first item of the list to begin printing

while(printer != NULL){ // While we haven't reached the end of the linked list

printf("%s ", printer->data); // print the element of the linked list

printer = printer->nextItem; // point to next item in the list


}

printf("\n"); // print a newline for readability

return SUCCESS; // return success upon sucessful printing


}
}

int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem){

if(firstItem == NULL || secondItem == NULL){ // If either of the items we which to swap are NULL

return STANDARD_ERROR; // return standard error

}

char* first_item_data = firstItem->data; // item 1 data

char* second_item_data = secondItem->data; // item 2 data

secondItem->data = first_item_data; // secondItem gets the data of firstItem

firstItem->data = second_item_data; // firstItem gets data of secondItem

return SUCCESS; // return success

}

char *LinkedListRemove(ListItem *item){

if(item == NULL){ // if passed a null

    return NULL; // return null to signal an error
}    

char* data_return = item->data; // Get the data of the item we wish to remove immediantly

if(item->previousItem == NULL){  // Removing the head of list 

item->nextItem->previousItem = item->previousItem; // item after given item is the new head

free(item); // free space removed item was using

}else if(item->nextItem == NULL){ // Removing the tail

item->previousItem->nextItem = item->nextItem; // item before given item is the new tail

free(item); // free space removed item was using

}else{ // removing an element somewhere in the middle of the list

item->previousItem->nextItem = item->nextItem; // next pointer of item before the one removed points to the element after the removed item

item->nextItem->previousItem = item->previousItem; // prev pointer of item after the one removed points to the element before the removed item

free(item); // free space removed item was using

}

return data_return; // return data of removed item

}


