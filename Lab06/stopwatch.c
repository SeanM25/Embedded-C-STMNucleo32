/**
 * [WIP]
 * A benchmarking tool that measures time in terms of clock cycles and ms. 
 *
 * @file    stopwatch.c
 * @author  nubby (jlee211@ucsc.edu)
 *
 * @date    September 17, 2024
 */
#include <stdio.h>
#include <stdlib.h>
#include "stopwatch.h"
// Module-level variables.
static clock_t start_cycle;
static clock_t end_cycle;


// Library.
/**start_benchmark()
 *
 * Initializes benchmark CPU cycle count and time for benchmark.
 *
 * @returns success (int) : 0 for success, 1 for failure.
 */
int start_benchmark() {
  start_cycle = clock();
  if (!start_cycle) {
    return 1;
  }
  return 0;
}

int stop_benchmark() {
/**end_benchmark()
 *
 * Gets benchmark CPU cycle count and time for benchmark and prints to STDOUT.
 * TODO(nubby): Add STM32 support.
 *
 * @returns success (int) : 0 for success, 1 for failure.
 */
  end_cycle = clock();
  if (!end_cycle) {
    return 0;
  }
  return 1;
}

void print_benchmark_results() {
  if (!start_cycle || !end_cycle) {
    printf("ERROR: Please run benchmark before printing.");
    return -1;
  }
  uint64_t duration_cycles = end_cycle - start_cycle;
  double duration_ms = duration_cycles / CLOCKS_PER_SEC;
  printf(
      "Program took %llu cycles and %f ms to complete.\r\n",
      duration_cycles,
      duration_ms
  );
}

