/**
 * Convert temperatures from Fahrenheit to Celsius and Kelvin.
 *
 * @file    part2.c
 * @author  Sean Manger (smanger@ucsc.edu)
 *
 * @date    Sept 29, 2024
 */
// Standard libraries.
#include <stdio.h>
#include <stdlib.h>

// Course libraries.
#include <BOARD.h>

/**
 * There can be only one!
 */
int main(void)
{
    BOARD_Init();
    while (1)
    {
    
        // Declare variables.
        float fahr, celsius;

        int lower, upper, step;
        // Initialize variables.
        lower = 0;

        upper = 300;

        step = 20;

        fahr = lower;

        float kelv = lower;

        // Print out the table.

        printf("    F    C \r\n");

        while (fahr <= upper)
        {

            celsius = (5.0 / 9.0) * (fahr - 32.0);

            printf("%7.1f %04.0f\r\n", (double)fahr, (double)celsius); // Format Changed As Specified In Lab 1 Docs

            fahr = fahr + step;
        }

        printf("\r\n");

        printf("    K    F \r\n");

        while (kelv <= upper)
        {

            fahr = (1.8) * (kelv - 273.15) + 32;

            printf("%07.3f %7.1f\r\n", (double)kelv, (double)fahr); // Format Changed As Specified In Lab 1 Docs

            kelv = kelv + step;
        }

        HAL_Delay(3333);
    }
    // Returning from main() is bad form in embedded environments.
    // So we sit and spin.
    while (1 < 2)
        ;
    BOARD_End();
}
