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
ListItem *SelectionSort(ListItem *list)
{

    const int zero = 0; // constant int for strcmp comparison

    ListItem *first_unsorted = list; // first unsorted is initially the list

    ListItem *scan; // initialize scan variable

    while (first_unsorted->nextItem != NULL)
    { // While not the tail

        scan = first_unsorted->nextItem; // advance scan

        while (scan != NULL)
        { // while scan isnt null

            if (strcmp(first_unsorted->data, scan->data) > zero)
            { // if first_unsorted > scan

                LinkedListSwapData(first_unsorted, scan); // swap places
            }

            scan = scan->nextItem; // advance scan
        }
        first_unsorted = first_unsorted->nextItem; // advance first_unsorted
    }

    return first_unsorted; // return first item in sorted list
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
ListItem *InsertionSort(ListItem *list)
{

    const int zero = 0; // constant int for strcmp comparison

    ListItem *first_sorted = LinkedListGetLast(list); // first sorted is tail of the list

    ListItem *scan; // initialze scan

    ListItem *unsorted; // initialize unsorted

    while (first_sorted->previousItem != NULL)
    { // while first sortedd is not the head

        unsorted = first_sorted->previousItem; // unsorted equals previous item

        if (strcmp(unsorted->data, first_sorted->data) < zero)
        { // if unsorted < sorted

            first_sorted = unsorted; // unsorted is now sorted
        }
        else
        {

            scan = first_sorted; // scan is initilized with first sorted

            while (scan->nextItem != NULL)
            { // while scan is not the tail

                if (strcmp(scan->nextItem->data, unsorted->data) > zero)
                { // if scan > unsorted

                    break; // break
                }
                else
                {

                    scan = scan->nextItem; // otherwise advance scna
                }
            }

            char *data = LinkedListRemove(unsorted); // remove data

            LinkedListCreateAfter(scan, data); // reinsert after scan
        }
    }

    return scan; // return head of new sorted List
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

    char *wordList[] = {
        "decide", "toothpaste", "lowly", "robin", "reign", "crowd", "pies",
        "reduce", "tendency", "surround", "finger", "rake", "alleged", "hug",
        "nest", "punishment", "eggnog", "side", "beef", "exuberant", "sort",
        "scream", "zip", "hair", "ragged", "damage", "thought", "jump",
        "frequent", "substance", "head", "step", "faithful", "sidewalk", "pig",
        "raspy", "juggle", "shut", "maddening", "rock", "telephone",
        "selective", NULL};

    int i = 0;
    ListItem *head = LinkedListNew(wordList[i]);
    ListItem *tail = head;
    for (i = 1; wordList[i] != NULL; i++)
    {
        tail = LinkedListCreateAfter(tail, wordList[i]);
        if (tail == NULL)
        {
            // If a NULL pointer is found, return NULL for the calling script to
            // check.
            return NULL;
        }
    }
    return head;
}
