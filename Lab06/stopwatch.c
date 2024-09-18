/**
 * [WIP]
 * A benchmarking tool that measures time in terms of clock cycles and ms. 
 *
 * @file    stopwatch.c
 * @author  nubby (jlee211@ucsc.edu)
 *
 * @date    September 17, 2024
 */
#ifdef STM32F4
#include <BOARD.h>
#else
#include <time.h>
#endif  /*  STM32F4 */


// Function prototypes.
clock_t* start_timer();
double stop_timer(clock_t* start_time);
