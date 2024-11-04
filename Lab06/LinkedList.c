#include "LinkedList.h"
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

// Scenario 1 {Nothing Before item}: new_element <-> item <-> something after?

if(item->previousItem == NULL){ // If theres nothing before item

item->previousItem = new_item_before; // previous points to newly inserted item

new_item_before->nextItem = item; // New item next points to item

return new_item_before; // return pointer to newly inserted item

}else if(new_item_before->data == NULL){ // If passed a NULL pointer NO next item: prev? <-> new_element <-> NULL <->  NULL <->

new_item_before->previousItem = item->previousItem; // Null points to previous item but nothing after it

item->previousItem = NULL; // item no longer points backwards

item->nextItem = NULL; // or forwards

return new_item_before;

}else { // Scenario 2: {Another item is present before item}: A <-> new_element <-> B

new_item_before->previousItem = item->previousItem; // The previous item of the new item points to the previous item of the item its inserted before

new_item_before->nextItem = item; // Next item of the new item points to the item its inserted in front off

item->previousItem = new_item_before; // item previous points to the newly inserted item

return new_item_before; // return pointer to newly inserted item

}

}

ListItem *LinkedListCreateAfter(ListItem *item, char *data){

ListItem* new_item_after = LinkedListNew(data);

if(item->nextItem == NULL){

new_item_after->previousItem = item;

item->nextItem = new_item_after;

return new_item_after;

}else if(new_item_after->data == NULL){ // If passed a NULL pointer NO previous item: NULL <-> new_element <-> Next Item?

new_item_after->nextItem = item->nextItem; // Null points to next item but nothing before it

item->previousItem = NULL; // item no longer points backwards

item->nextItem = NULL; // or forwards

return new_item_after;

}else{

new_item_after->nextItem = item->nextItem;

new_item_after->previousItem = item;

item->nextItem = new_item_after;

return new_item_after;

}


}