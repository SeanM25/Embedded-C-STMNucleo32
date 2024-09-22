/**
 * stopwatch.h
 *
 * NOTE: Uses C11.
 * NOTE: Timing resolution can be enhanced on POSIX-compatible systems with
 *       clock_gettime().
 */
#ifdef STM32F4
#include <BOARD.h>
#else
#include <time.h>
#endif  /*  STM32F4 */


// Function prototypes.
int start_benchmark(void);
int stop_benchmark(void);
void print_benchmark_results(void);

