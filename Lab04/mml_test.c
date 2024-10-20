// **** Include libraries here ****
// Standard libraries.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// User libraries:
#include "MatrixMath.h"


// Module-level variables:

float zero_matrix[3][3] = {{0, 0, 0},{0, 0, 0},{0, 0, 0}};
float result_matrix[3][3] = {{0, 0, 0},{0, 0, 0},{0, 0, 0}};
float ones_matrix[3][3] = {{1, 1, 1},{1, 1, 1},{1, 1, 1}};
float one_two_three_matrix[3][3] = {{1, 2, 3},{1, 2, 3},{1, 2, 3}};
float tens_matrix[3][3] = {{10, 10, 10},{10, 10, 10},{10, 10, 10}};
float tens_rnd_matrix[3][3] = {{9.999, 9.999, 9.999},{9.999, 9.999, 9.999},{9.999, 9.999, 9.999}};
float neg_ninehun_matrix[3][3] = {{-999, -999, -999},{-999, -999, -999},{-999, -999, -999}};

int main()
{
    printf(
        "Beginning CRUZID's mml test harness, compiled on %s %s\n",
        __DATE__,
        __TIME__
    );
    

/***************MatrixEquals() Tests*****************/ 

// Note: Did 4 Tests here since lab doc stressed importance. Made sure to check for equality to within FPDELTA tolerance.
// Did 2 fail cases. 1 obvious success & 1 success test to check that function checked equality to within FPDELTA tolerance.

int equals_pass_cnt = 0; // Counts number of succesful tests for MatrixEquals()

 if (MatrixEquals(zero_matrix, ones_matrix) == 0){ // MatrixEquals(zero_matrix, ones_matrix) Clearly Not Equal

    equals_pass_cnt++; // Increment if test successful
 }

 if (MatrixEquals(neg_ninehun_matrix, ones_matrix) == 0){ // MatrixEquals(neg_ninehun_matrix, ones_matrix) Clearly Not Equal

equals_pass_cnt++; // Increment if test successful

 }

 if (MatrixEquals(one_two_three_matrix, one_two_three_matrix) == 1){ // MatrixEquals(one_two_three_matrix, one_two_three_matrix) Equal Dead On

equals_pass_cnt++; // Increment if test successful

 }

 if (MatrixEquals(tens_matrix, tens_rnd_matrix) == 1){ // MatrixEquals(tens_matrix, tens_rnd_matrix) Equal to within FPDELTA

equals_pass_cnt++; // Increment if test successful

 }

 printf("\nPassed: (%d / 4) MatrixEquals()\n", equals_pass_cnt); // Print How Many succeses out of 4 tests


 /*MatrixScalarMultiply() Tests*/

 // Tested for proper multiplication for an ordinary scalar & one with a decimal component

 int scalar_mul_pass_cnt = 0; // Counter for MatrixScalarMultiply() Tests successes

 float t1 = -5; // Scalar for Test 1

 float t2 = 2.5; // Scalar for Test 2

 float Scalar_Test_t1[3][3] = {{-50, -50, -50},{-50, -50, -50},{-50, -50, -50}}; // Expected Result of tens_matrix times t1 scalar

 float Scalar_Test_t2[3][3] = {{2.5, 2.5, 2.5}, {2.5, 2.5, 2.5}, {2.5, 2.5, 2.5}}; // Expected Result of ones_matrix times t2 Scalar


 MatrixScalarMultiply(t1, tens_matrix,result_matrix); // Perform test 1: tens_matrix * t1


 if (MatrixEquals(Scalar_Test_t1, result_matrix) == 1){ // Check actual result of test 1 matches expected result

    scalar_mul_pass_cnt++; // Increment success counter

 }

MatrixScalarMultiply(t2, ones_matrix, result_matrix); // Perform test 2: ones_matrix * t2

 if (MatrixEquals(Scalar_Test_t2, result_matrix) == 1){ // Check actual result of test 2 matches expected result

    scalar_mul_pass_cnt++; // Increment success counter
 }

printf("\nPassed: (%d / 2) MatrixScalarMultiply()\n", scalar_mul_pass_cnt); // Display total number of passing tests


/*MatrixScalarAdd() Tests*/



    while (1);
}

