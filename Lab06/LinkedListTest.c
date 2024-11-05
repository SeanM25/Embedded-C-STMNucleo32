#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

// LinkedListNew() Tests

int pass_cnt_new_LL = 0; // Counter for passed tests

char *ships_of_ww2[]  = {"Bismarck", "Prinz Eugen", "Enterprise", "Yamato"}; // Some data to create linked lists with famous ww2 ships

char *Red_Fleet_Pac[] = {"Varyag", "Admiral Kuznetsov","Red October","Sovershennyy"}; // More data examples: NATO names of ships of Russian Pacific Fleet 

char *N[] = {NULL}; // Data thats just a NULL pointer


ListItem* create_LL_test_1 = LinkedListNew(ships_of_ww2[0]); // Test creation of LL object that points to Bismarck

ListItem* create_LL_test_2 = LinkedListNew(N[0]); // Test creation of LL object that points to NULL

if(create_LL_test_1->data == ships_of_ww2[0]){ // LL object points to "Bismarck" i.e. sucessful creation

pass_cnt_new_LL++; // Increment test success counter

}

if(create_LL_test_2->data == NULL){ // LL object points to NULL i.e. sucessful creation

pass_cnt_new_LL++; // Increment test success counter

}

printf("LinkedListNew() Passed (%d / 2) Tests!\n", pass_cnt_new_LL); // Print number of successful tests




// LinkedListCreateBefore() Tests

int pass_cnt_LL_b4 = 0; // Test success counter

ListItem* item = LinkedListNew(ships_of_ww2[2]); // Enterprise

char* add_data[] ={"Hornet"}; // New data to be inserted

ListItem* new_insertion = LinkedListCreateBefore(item,add_data[0]); // Insert Data


if(new_insertion->data == add_data[0] && new_insertion->nextItem->data == ships_of_ww2[2]){ // Linked List is: Hornet <-> Enterprise

pass_cnt_LL_b4++;

}

ListItem* item_2 = LinkedListNew(ships_of_ww2[2]); // LL: Enterprise

ListItem* item_1 = LinkedListCreateBefore(item_2,add_data[0]); // Hornet <-> Enterprise

char* data_btwn[] = {"PT-109"}; // Data to be inserted

ListItem* item_3 = LinkedListCreateBefore(item_2,data_btwn[0]); // Hornet <-> PT-109 <-> Enterprise

if(item_3->previousItem->data == add_data[0] && item_3->data == data_btwn[0] && item_3->nextItem->data == ships_of_ww2[2]){ // If LL is Hornet <-> PT-109 <-> Enterprise i.e. success

pass_cnt_LL_b4++; // increment test success counter

}

printf("LinkedListCreateBefore() Passed (%d / 2) Tests!\n", pass_cnt_LL_b4); // Print number of successful tests for LL before



// LinkedListCreateAfter() Tests

int pass_cnt_LL_after = 0;

ListItem* ship_1 = LinkedListNew(Red_Fleet_Pac[0]); // Varyag

ListItem* ship_2 = LinkedListCreateAfter(ship_1,Red_Fleet_Pac[3]); // Varyag <-> Sovershennyy

if(ship_2->previousItem->data == Red_Fleet_Pac[0] && ship_2->data == Red_Fleet_Pac[3]){

pass_cnt_LL_after++;

}

char* new_ship[] = {"Chelyabinsk"};

char* new_ship_2[] = {"Peter the Great"};

ListItem* ship_btwn_12 = LinkedListCreateAfter(ship_1, new_ship[0]);  // Varyag <-> Chelyabinsk <-> Sovershennyy

ListItem* forth_ship_added = LinkedListCreateAfter(ship_btwn_12, new_ship_2[0]); // Varyag <-> Chelyabinsk <-> Peter the Great <-> Sovershennyy

if(forth_ship_added->previousItem->data == ship_btwn_12->data && forth_ship_added->nextItem->data == Red_Fleet_Pac[3]){

    pass_cnt_LL_after++;
}

printf("LinkedListCreateAfter() Passed (%d / 2) Tests!\n", pass_cnt_LL_after); // Print number of successful tests for LL after


// LinkedListSize() Tests

int size_pass = 0;

int size_t1 = LinkedListSize(forth_ship_added);

int size_t2 = LinkedListSize(item_3);

if(size_t1 == 4){

size_pass++;

}

if(size_t2 == 3){

size_pass++;

}

printf("LinkedListSize() Passed (%d / 2) Tests!\n", size_pass); // Print number of successful tests for LL size

// LinkedListGetFirst() Tests


ListItem* r_ship_1 = LinkedListNew(Red_Fleet_Pac[0]);

ListItem* r_ship_2 = LinkedListCreateAfter(r_ship_1, Red_Fleet_Pac[1]);

ListItem* r_ship_3 = LinkedListCreateAfter(r_ship_2, Red_Fleet_Pac[2]);

ListItem* r_ship_4 = LinkedListCreateAfter(r_ship_3, Red_Fleet_Pac[3]);


ListItem* r_ship_1_rev = LinkedListNew(Red_Fleet_Pac[0]);

ListItem* r_ship_2_rev = LinkedListCreateBefore(r_ship_1_rev, Red_Fleet_Pac[1]);

ListItem* r_ship_3_rev = LinkedListCreateBefore(r_ship_2_rev, Red_Fleet_Pac[2]);

ListItem* r_ship_4_rev = LinkedListCreateBefore(r_ship_3_rev, Red_Fleet_Pac[3]);


int get_first_pass = 0;

ListItem* first_elem_1 = LinkedListGetFirst(r_ship_3);

ListItem* first_elem_2 = LinkedListGetFirst(r_ship_4_rev);

if(first_elem_1->data == r_ship_1->data){

    get_first_pass++;
}

if(first_elem_2->data == r_ship_4_rev->data){

 get_first_pass++;

}

printf("LinkedListGetFirst() Passed (%d / 2) Tests!\n", get_first_pass); // Print number of successful tests for LL get first

// LinkedListGetLast() Tests

int get_last_pass = 0;

ListItem* last_elem_1 = LinkedListGetLast(r_ship_3);

ListItem* last_elem_2 = LinkedListGetLast(r_ship_4_rev);

if(last_elem_1->data == r_ship_4->data){

    get_last_pass++;
}

if(last_elem_2->data == r_ship_1_rev->data){

    get_last_pass++;
}

printf("LinkedListGetLast() Passed (%d / 2) Tests!\n", get_last_pass); // Print number of successful tests for LL get last


// LinkedListSwapData() Tests

int swap_pass = 0;

ListItem* data_swap_1 = LinkedListNew(Red_Fleet_Pac[0]); // Initially Varyag

ListItem* data_swap_2 = LinkedListCreateAfter(data_swap_1,Red_Fleet_Pac[3]); // Initally Sorvershenny

ListItem* more_data_swap_1 = LinkedListNew(ships_of_ww2[3]); // Yamato initially

ListItem* more_data_swap_2 = LinkedListCreateAfter(more_data_swap_1,ships_of_ww2[1]); // Prinz Eugen Initially


LinkedListSwapData(data_swap_1,data_swap_2);

LinkedListSwapData(more_data_swap_1,more_data_swap_2);

if(data_swap_1->data == Red_Fleet_Pac[3] && data_swap_2->data == Red_Fleet_Pac[0]){

swap_pass++;

}


if(more_data_swap_1->data == ships_of_ww2[1] && more_data_swap_2->data == ships_of_ww2[3]){

swap_pass++;

}


printf("LinkedListSwap() Passed (%d / 2) Tests!\n", swap_pass); // Print number of successful tests for LL print


// LinkedListPrint() Tests

int print_pass = 0;

printf("LinkedListPrint() Testing & Demonstation:\n");

if(LinkedListPrint(r_ship_3) == 1){

print_pass++;

}

if(LinkedListPrint(r_ship_3_rev) == 1){

print_pass++;

}

printf("LinkedListPrint() Passed (%d / 2) Tests!\n", print_pass); // Print number of successful tests for LL print




















}