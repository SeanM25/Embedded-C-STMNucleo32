/**
 * Every file should start with a header like this.
 *
 * @file helloworld.c
 * @author Sean Manger (smanger@ucsc.edu)
 *
 * @date 28 Sept 2024
 *
 * */
// Standard libraries.
#include <stdio.h>
#include <stdlib.h>
// Course libraries.
#include "BOARD.h"
/**
 * Hello World!
 */
int main(void)
{
    BOARD_Init();
    printf("Hello World!\r\n");
    BOARD_End(); // Handles cleanup of the system.
}
