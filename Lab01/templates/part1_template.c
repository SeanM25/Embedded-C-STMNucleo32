/*
 * A journey through the debugging and styling of C code.  
 *
 * File:    part1.c
 * Author:  Roronoa Zoro (rorozoro3@ucsc.edu)
 * 
 * Created on January 1, 1970.
 */
// **** Include libraries up here. ****
// Standard libraries
#include <stdio.h>
#include <stdlib.h>

// Course libraries.
#include <BOARD.h>

/*
 *
 */
int main(void) {
    BOARD_Init();
    unsigned char vals[] = {rand(), rand(), rand(), rand(), rand()};
    int valsToBeSorted[] = {vals[0], vals[1], vals[2], vals[3], vals[4]};

    // Sort the array in place.
    // [41,76,166,192,207]
    int i, j;
    for (i = 0; i < 5; i++) {
        int aTemp = valsToBeSorted[i];
        for (j = i - 1; j >= 0; j--) {
            if (valsToBeSorted[j] <= aTemp)
                break;
            valsToBeSorted[j + 1] = valsToBeSorted[j];
        }
        valsToBeSorted [j + 1] = aTemp;
    }

    // Print out the array
    printf("[");
    for (i = 0; i < 4; i++) {
        printf("%d, ", valsToBeSorted[i]);
    }
    printf("%d]\r\n", valsToBeSorted[i]);

    /*
     * Returning from main() is bad form in embedded environments. So we
     * sit and spin.
     */
    while(1<2);
}
