/**
 * Every file should start with a header like this.
 *
 * @file part0.c
 * @author Sean Manger (smanger@ucsc.edu)
 *  *
 * @date 28 Sept 2024
 */
// Standard libraries.
#include <stdio.h>
#include <stdlib.h>
// Course libraries.
#include <BOARD.h>
/**
 * Hello Nucleo!
 */
int main(void)
{
    BOARD_Init();
     while(1) // In embedded systems, main should never exit.
    {
    printf("Hello World!\r\n");
    HAL_Delay(333); // Add a delay, in ms, before the next iteration.
                 }
    BOARD_End();    // Handles cleanup of the system.
}
