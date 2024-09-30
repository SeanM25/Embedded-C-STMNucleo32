/**
 * Hello, OLED!
 *
 * @file    part3.c
 * @author  Sean Manger (smanger@ucsc.edu)
 *
 * @date    Sept 30, 2024
 */
// Standard libraries.
#include <stdio.h>
#include <stdlib.h>

// Course libraries.
#include <BOARD.h>
#include <Oled.h>

/**
 * This time with an OLED screen.
 */
int main(void)
{
    BOARD_Init();

    while (1)

    {

        OledInit(); // Turns on Screen

        OledDrawString("Hello\nWorld!\n"); // Draw desired text

        OledUpdate(); // Text displays on screen.

        HAL_Delay(3000);

        OledClear('1');

        OledDrawString("ECE\n13!\n"); // Draw desired text

        OledUpdate(); // Text displays on screen.

        HAL_Delay(3000);

        OledClear('1');
    }

    while (1)
        ; // if embedded, we should never exit.

    BOARD_End(); // Handles cleanup of the system.
}
