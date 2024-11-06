#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    // LinkedListNew() Tests

    int pass_cnt_new_LL = 0; // Counter for passed tests

    char *ships_of_ww2[] = {"Bismarck", "Prinz Eugen", "Enterprise", "Yamato"}; // Some data to create linked lists with famous ww2 ships

    char *R_Fleet_Pac[] = {"Varyag", "Admiral Kuznetsov", "Red October", "Sovershennyy"}; // More data examples: NATO names of ships of Russian Pacific Fleet

    char *N[] = {NULL}; // Data thats just a NULL pointer

    ListItem *create_LL_test_1 = LinkedListNew(ships_of_ww2[0]); // Test creation of LL object that points to Bismarck

    ListItem *create_LL_test_2 = LinkedListNew(N[0]); // Test creation of LL object that points to NULL

    if (create_LL_test_1->data == ships_of_ww2[0])
    { // LL object points to "Bismarck" i.e. sucessful creation

        pass_cnt_new_LL++; // Increment test success counter
    }

    if (create_LL_test_2->data == NULL)
    { // LL object points to NULL i.e. sucessful creation

        pass_cnt_new_LL++; // Increment test success counter
    }

    printf("LinkedListNew() Passed (%d / 2) Tests!\n", pass_cnt_new_LL); // Print number of successful tests

    // LinkedListCreateBefore() Tests

    int pass_cnt_LL_b4 = 0; // Test success counter

    ListItem *item = LinkedListNew(ships_of_ww2[2]); // Enterprise

    char *add_data[] = {"Hornet"}; // New data to be inserted

    ListItem *new_insertion = LinkedListCreateBefore(item, add_data[0]); // Insert Data

    if (new_insertion->data == add_data[0] && new_insertion->nextItem->data == ships_of_ww2[2])
    { // Linked List is: Hornet <-> Enterprise

        pass_cnt_LL_b4++; // Increment test success
    }

    ListItem *item_2 = LinkedListNew(ships_of_ww2[2]); // LL: Enterprise

    ListItem *item_1 = LinkedListCreateBefore(item_2, add_data[0]); // Hornet <-> Enterprise

    char *data_btwn[] = {"PT-109"}; // Data to be inserted

    ListItem *item_3 = LinkedListCreateBefore(item_2, data_btwn[0]); // Hornet <-> PT-109 <-> Enterprise

    if (item_3->previousItem->data == add_data[0] && item_3->data == data_btwn[0] && item_3->nextItem->data == ships_of_ww2[2] && item_1->data == add_data[0])
    { // If LL is Hornet <-> PT-109 <-> Enterprise i.e. success

        pass_cnt_LL_b4++; // increment test success counter
    }

    printf("LinkedListCreateBefore() Passed (%d / 2) Tests!\n", pass_cnt_LL_b4); // Print number of successful tests for LL before

    // LinkedListCreateAfter() Tests

    int pass_cnt_LL_after = 0; // Initialize test success counter

    ListItem *ship_1 = LinkedListNew(R_Fleet_Pac[0]); // Varyag

    ListItem *ship_2 = LinkedListCreateAfter(ship_1, R_Fleet_Pac[3]); // Varyag <-> Sovershennyy

    if (ship_2->previousItem->data == R_Fleet_Pac[0] && ship_2->data == R_Fleet_Pac[3])
    { // If the Linked List is  Varyag <-> Sovershennyy

        pass_cnt_LL_after++; // Increment succss counter
    }

    char *new_ship[] = {"Chelyabinsk"}; // Another ship to be added to linked list

    char *new_ship_2[] = {"Peter the Great"}; // Yet another ship to be added to linked list

    ListItem *ship_btwn_12 = LinkedListCreateAfter(ship_1, new_ship[0]); // Varyag <-> Chelyabinsk <-> Sovershennyy

    ListItem *forth_ship_added = LinkedListCreateAfter(ship_btwn_12, new_ship_2[0]); // Varyag <-> Chelyabinsk <-> Peter the Great <-> Sovershennyy

    if (forth_ship_added->previousItem->data == ship_btwn_12->data && forth_ship_added->nextItem->data == R_Fleet_Pac[3])
    { // If Varyag <-> Chelyabinsk <-> Peter the Great <-> Sovershennyy

        pass_cnt_LL_after++; // Increment pass counter
    }

    printf("LinkedListCreateAfter() Passed (%d / 2) Tests!\n", pass_cnt_LL_after); // Print number of successful tests for LL after

    // LinkedListSize() Tests

    int size_pass = 0; // Initialize counter

    int size_t1 = LinkedListSize(forth_ship_added); // actual size of LL

    int size_t2 = LinkedListSize(item_3); // Actual size of LL

    if (size_t1 == 4)
    { // If actual is expected

        size_pass++; // increment success counter
    }

    if (size_t2 == 3)
    { // If actual is expected

        size_pass++; // increment success counter
    }

    printf("LinkedListSize() Passed (%d / 2) Tests!\n", size_pass); // Print number of successful tests for LL size

    // LinkedListGetFirst() Tests

    ListItem *null_elem = LinkedListNew(N[0]); // List item that is simply NULL

    ListItem *r_ship_1 = LinkedListNew(R_Fleet_Pac[0]); // Varyag

    ListItem *r_ship_2 = LinkedListCreateAfter(r_ship_1, R_Fleet_Pac[1]); // Varyag Kutzesov

    ListItem *r_ship_3 = LinkedListCreateAfter(r_ship_2, R_Fleet_Pac[2]); // Varyag Kutzesov Red October

    ListItem *r_ship_4 = LinkedListCreateAfter(r_ship_3, R_Fleet_Pac[3]); // Varyag Kutzesov Red October Sovershenny

    ListItem *r_ship_1_rev = LinkedListNew(R_Fleet_Pac[0]); // Varyag

    ListItem *r_ship_2_rev = LinkedListCreateBefore(r_ship_1_rev, R_Fleet_Pac[1]); // Kutzesov Varyag

    ListItem *r_ship_3_rev = LinkedListCreateBefore(r_ship_2_rev, R_Fleet_Pac[2]); // Red October Kutzesov Varyag

    ListItem *r_ship_4_rev = LinkedListCreateBefore(r_ship_3_rev, R_Fleet_Pac[3]); // Sovershenny Red October Kutzesov Varyag

    int get_first_pass = 0; // Initialize success counter

    ListItem *first_elem_1 = LinkedListGetFirst(r_ship_3); // test 1 get first

    ListItem *first_elem_2 = LinkedListGetFirst(r_ship_4_rev); // test 2 get first

    ListItem *first_elem_3 = LinkedListGetFirst(null_elem); // test 3 get first

    if (first_elem_1->data == r_ship_1->data)
    { // If GetFirst() is as expected

        get_first_pass++; // increment success counter
    }

    if (first_elem_2->data == r_ship_4_rev->data)
    { // If GetFirst() is as expected

        get_first_pass++; // increment success counter
    }

    if (first_elem_3->data == NULL)
    { // Checking NULL funtionality

        get_first_pass++; // Increment success counter
    }

    printf("LinkedListGetFirst() Passed (%d / 3) Tests!\n", get_first_pass); // Print number of successful tests for LL get first

    // LinkedListGetLast() Tests

    int get_last_pass = 0; // Initialize get last test counter

    ListItem *last_elem_1 = LinkedListGetLast(r_ship_3); // get last test 1

    ListItem *last_elem_2 = LinkedListGetLast(r_ship_4_rev); // get last test 2

    ListItem *last_elem_3 = LinkedListGetLast(null_elem); // get last test 3

    if (last_elem_1->data == r_ship_4->data)
    { // if GetLast() is succesful

        get_last_pass++; // increment success counter
    }

    if (last_elem_2->data == r_ship_1_rev->data)
    { // if GetLast() is succesful

        get_last_pass++; // increment success counter
    }

    if (last_elem_3->data == NULL)
    { // if GetLast() is succesful

        get_last_pass++; // increment success counter
    }

    printf("LinkedListGetLast() Passed (%d / 3) Tests!\n", get_last_pass); // Print number of successful tests for LL get last

    // LinkedListSwapData() Tests

    int swap_pass = 0;

    ListItem *data_swap_1 = LinkedListNew(R_Fleet_Pac[0]); // Initially Varyag

    ListItem *data_swap_2 = LinkedListCreateAfter(data_swap_1, R_Fleet_Pac[3]); // Initally Sorvershenny

    ListItem *more_data_swap_1 = LinkedListNew(ships_of_ww2[3]); // Yamato initially

    ListItem *more_data_swap_2 = LinkedListCreateAfter(more_data_swap_1, ships_of_ww2[1]); // Prinz Eugen Initially

    LinkedListSwapData(data_swap_1, data_swap_2); // Swap Varyag & Sorvershenny

    LinkedListSwapData(more_data_swap_1, more_data_swap_2); // Swap Yamato & Prinz Eugen

    if (data_swap_1->data == R_Fleet_Pac[3] && data_swap_2->data == R_Fleet_Pac[0])
    { // If data was succesfully swapped

        swap_pass++; // increment counter
    }

    if (more_data_swap_1->data == ships_of_ww2[1] && more_data_swap_2->data == ships_of_ww2[3])
    { // If the other data swap test was succesful

        swap_pass++; // increment counter
    }

    printf("LinkedListSwap() Passed (%d / 2) Tests!\n", swap_pass); // Print number of successful tests for LL print

    // LinkedListPrint() Tests

    int print_pass = 0; // printing success counter

    printf("LinkedListPrint() Testing & Demonstation:\n"); // prepare to print

    if (LinkedListPrint(r_ship_3) == 1)
    { // if printing was successful

        print_pass++; // increment success counter
    }

    if (LinkedListPrint(r_ship_3_rev) == 1)
    { // if printing was successful

        print_pass++; // increment success counter
    }

    printf("LinkedListPrint() Passed (%d / 2) Tests!\n", print_pass); // Print number of successful tests for LL print

    // LinkedListRemove() Tests

    int remove_pass = 0; // LinkedListRemove() pass counter

    char *odds[] = {"1", "3", "5"}; // some odd numbers to test removal

    char *evens[] = {"2", "4", "6"}; // some even numbers to test removal

    ListItem *odd_num_1 = LinkedListNew(odds[0]);

    ListItem *odd_num_2 = LinkedListCreateAfter(odd_num_1, odds[1]);

    ListItem *odd_num_3 = LinkedListCreateAfter(odd_num_2, odds[2]); // 1 3 5 LL

    ListItem *even_num_1 = LinkedListNew(evens[0]);

    ListItem *even_num_2 = LinkedListCreateAfter(even_num_1, evens[1]);

    ListItem *even_num_3 = LinkedListCreateAfter(even_num_2, evens[2]); // 2 4 6 LL

    int size_inital_1 = LinkedListSize(odd_num_2); // initial size before removal

    int size_inital_2 = LinkedListSize(even_num_2); // initial size before removal

    char *result_rem_1 = LinkedListRemove(odd_num_2); // data removed

    char *result_rem_2 = LinkedListRemove(even_num_2); // data removed

    int size_after_1 = LinkedListSize(odd_num_1); // size after removal

    int size_after_2 = LinkedListSize(even_num_1); // size after removal

    if (result_rem_1 == odds[1] && size_after_1 == size_inital_1 - 1 && odd_num_3->data == odds[2])
    {

        remove_pass++; // increment success counter
    }

    if (result_rem_2 == evens[1] && size_after_2 == size_inital_2 - 1 && even_num_3->data == evens[2])
    {

        remove_pass++; // increment success counter
    }

    printf("LinkedListRemove() Passed (%d / 2) Tests!\n", remove_pass); // Print number of successful tests for LL remove
}
