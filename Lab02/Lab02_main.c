/*
 * Math is fun!!
 *
 * File:    Lab2_main.c
 * Author:  nubby (jlee211@ucsc.edu)
 *
 * Created on August 13, 2024.
 */
// Standard libraries.
#include <stdio.h>
#include <math.h>

// User libraries.
#include "BOARD.h"


// CalculatorRun() prototype.
void CalculatorRun(void);

int main(void)
{
    BOARD_Init();
    
    CalculatorRun();

    printf(
        "Calculator has exited; restart to perform more calculations.\r\n"
    );

    BOARD_End();
    while(1);
}

