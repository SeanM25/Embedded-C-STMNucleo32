// Lab 04: Matrix Math
// Sean Manger <smanger@ucsc.edu>
// 10 / 18 / 2024

// **** Include libraries here ****
// Standard libraries.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// User libraries:
#include "MatrixMath.h"

// Helper Function Prototypes

int MatrixEquals2x2(float mat1[2][2], float mat2[2][2]); // Checks equality for 2x2 matrix same as MatrixEquals() in practice.

// Module-level variables:

// Many random matrices for testing, input, output

float zero_matrix[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
float result_matrix[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
float ones_matrix[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
float one_two_three_matrix[3][3] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
float tens_matrix[3][3] = {{10, 10, 10}, {10, 10, 10}, {10, 10, 10}};
float tens_rnd_matrix[3][3] = {{9.999, 9.999, 9.999}, {9.999, 9.999, 9.999}, {9.999, 9.999, 9.999}};
float neg_ninehun_matrix[3][3] = {{-999, -999, -999}, {-999, -999, -999}, {-999, -999, -999}};
float rand_matrix_1[3][3] = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
float rand_matrix_2[3][3] = {{3, 5, 7}, {9, 11, 13}, {15, 17, 19}};
float rand_matrix_3[3][3] = {{1, 0, 5}, {2, 1, 6}, {3, 4, 0}};
float res_2x2[2][2] = {{0, 0}, {0, 0}};
float det_test_2[3][3] = {{2, 1, -3}, {4, -2, 1}, {3, 0, -5}};

int main()
{
    printf(
        "\nBeginning Sean Manger's (2088347) mml test harness, compiled on %s %s\n",
        __DATE__,
        __TIME__);

    /***************MatrixEquals() Tests*****************/

    // Note: Did 4 Tests here since lab doc stressed importance. Made sure to check for equality to within FPDELTA tolerance.
    // Did 2 fail cases. 1 obvious success & 1 success test to check that function checked equality to within FPDELTA tolerance.

    // Test 1: zero_matrix != ones_matrix
    // Test 2: neg_ninhun_matrix != ones_matrix
    // Test 3: ones_matrix == ones_matrix
    // Test 4: tens_matrix == tens_rnd_matrix within FPDELTA Tolerance

    int equals_pass_cnt = 0; // Counts number of succesful tests for MatrixEquals()

    if (MatrixEquals(zero_matrix, ones_matrix) == 0)
    { // MatrixEquals(zero_matrix, ones_matrix) Clearly Not Equal

        equals_pass_cnt++; // Increment if test successful
    }

    if (MatrixEquals(neg_ninehun_matrix, ones_matrix) == 0)
    { // MatrixEquals(neg_ninehun_matrix, ones_matrix) Clearly Not Equal

        equals_pass_cnt++; // Increment if test successful
    }

    if (MatrixEquals(one_two_three_matrix, one_two_three_matrix) == 1)
    { // MatrixEquals(one_two_three_matrix, one_two_three_matrix) Equal Dead On

        equals_pass_cnt++; // Increment if test successful
    }

    if (MatrixEquals(tens_matrix, tens_rnd_matrix) == 1)
    { // MatrixEquals(tens_matrix, tens_rnd_matrix) Equal to within FPDELTA

        equals_pass_cnt++; // Increment if test successful
    }

    printf("\nPassed: (%d / 4) MatrixEquals()\n", equals_pass_cnt); // Print How Many succeses out of 4 tests

    /*MatrixScalarMultiply() Tests*/

    // Tested for proper multiplication for an ordinary scalar & one with a decimal component

    // Test 1: tens_matrix * -5
    // Test 2: ones_matrix * 2.5

    int scalar_mul_pass_cnt = 0; // Counter for MatrixScalarMultiply() Tests successes

    float Scalar_Test_t1[3][3] = {{-50, -50, -50}, {-50, -50, -50}, {-50, -50, -50}}; // Expected Result of tens_matrix times t1 scalar

    float Scalar_Test_t2[3][3] = {{2.5, 2.5, 2.5}, {2.5, 2.5, 2.5}, {2.5, 2.5, 2.5}}; // Expected Result of ones_matrix times t2 Scalar

    MatrixScalarMultiply(-5, tens_matrix, result_matrix); // Perform test 1: tens_matrix * t1

    if (MatrixEquals(Scalar_Test_t1, result_matrix) == 1)
    { // Check actual result of test 1 matches expected result

        scalar_mul_pass_cnt++; // Increment success counter
    }

    MatrixScalarMultiply(2.5, ones_matrix, result_matrix); // Perform test 2: ones_matrix * t2

    if (MatrixEquals(Scalar_Test_t2, result_matrix) == 1)
    { // Check actual result of test 2 matches expected result

        scalar_mul_pass_cnt++; // Increment success counter
    }

    printf("\nPassed: (%d / 2) MatrixScalarMultiply()\n", scalar_mul_pass_cnt); // Display total number of passing tests

    /*MatrixMultiply() Tests*/

    // Tested for proper multiplication with one matrix multiplied by itself & two different matrices multiplied together

    // Test 1: one_two_three_matrix * one_two_three_matrix
    // Test 2: rand_matrix_1 * rand_matrix_2

    int mtrx_mult_pass_cnt = 0; // Success counter for MatrixMultiply()

    float mult_test1_res[3][3] = {{6, 12, 18}, {6, 12, 18}, {6, 12, 18}}; // one_two_three_matrix * one_two_three_matrix

    float mult_test2_res[3][3] = {{132, 156, 180}, {294, 354, 414}, {456, 552, 648}}; // rand_matrix_1 * rand_matrix_2

    MatrixMultiply(one_two_three_matrix, one_two_three_matrix, result_matrix); // Test 1: one_two_three matrix multiplied by itself

    if (MatrixEquals(mult_test1_res, result_matrix) == 1)
    { // If first test was successful

        mtrx_mult_pass_cnt++; // Increment success couunter
    }

    MatrixMultiply(rand_matrix_1, rand_matrix_2, result_matrix); // Test 2: Two Different Matrices multiplied together

    if (MatrixEquals(mult_test2_res, result_matrix) == 1)
    { // If Test 2 Was a success

        mtrx_mult_pass_cnt++; // Increment the success counter
    }

    printf("\nPassed: (%d / 2) MatrixMultiply()\n", mtrx_mult_pass_cnt); // Output total passes

    /* MatrixAdd() Tests*/

    // Test 1: one_two_three matrix added with itself.

    // Test 2: Simple Case of zero_matrix added to ones_matrix

    int mtrx_add_pass_cnt = 0; // MatrixAdd() Success counter

    float add_test_1_res[3][3] = {{2, 4, 6}, {2, 4, 6}, {2, 4, 6}}; // Expected Result of Test 1

    float add_test_2_res[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}; // Expected Result of Test 2

    MatrixAdd(one_two_three_matrix, one_two_three_matrix, result_matrix); // Actual Test 1 Result

    if (MatrixEquals(add_test_1_res, result_matrix) == 1)
    { // If Test 1 Success

        mtrx_add_pass_cnt++; // Increment success counter
    }

    MatrixAdd(zero_matrix, ones_matrix, result_matrix); // Actual Test 2 Result

    if (MatrixEquals(add_test_2_res, result_matrix) == 1)
    { // If Test 2 Success

        mtrx_add_pass_cnt++; // Increment success counter
    }

    printf("\nPassed: (%d / 2) MatrixAdd()\n", mtrx_add_pass_cnt); // Display total number of passing tests

    /* MatrixScalarAdd() Tests*/

    // Test 1: zero_matrix + (-1)
    // Test 2: ones_matrix + 1/3

    float scalar_add_test_1_res[3][3] = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}}; // Expected result of Test 1

    float scalar_add_test_2_res[3][3] = {{1.33, 1.33, 1.33}, {1.33, 1.33, 1.33}, {1.33, 1.33, 1.33}}; // Expected result of Test 2

    int mtrx_add_scalar_pass_cnt = 0; // MatrixScalarAdd() success counter

    MatrixScalarAdd(-1, zero_matrix, result_matrix); // Actual Reult of Test 1

    if (MatrixEquals(scalar_add_test_1_res, result_matrix) == 1)
    { // Check wheter test 1 success

        mtrx_add_scalar_pass_cnt++; // If success increment counter
    }

    MatrixScalarAdd(1 / 3, ones_matrix, result_matrix); // Actual Result of Test 2

    if (MatrixEquals(scalar_add_test_2_res, result_matrix) == 1)
    { // Check whether Test 2 Success

        mtrx_add_scalar_pass_cnt++; // If success increment counter
    }

    printf("\nPassed: (%d / 2) MatrixScalarAdd()\n", mtrx_add_scalar_pass_cnt); // Print # of MatrixScalarAdd() succeses

    /* MatrixSubmatrix() Tests*/

    // Test 1: Submatrix of one_two_three matrix given row 0 col 1
    // Test 2: Submatrix of rand_matrix_2 given row 2 col 2

    float sub_mtrx_t1_res[2][2] = {{1, 3}, {1, 3}}; // Expected Result of Test 1

    float sub_mtrx_t2_res[2][2] = {{3, 5}, {9, 11}}; // Expected Result of Test 2

    int sub_mtrx_pass_cnt = 0; // Submatrix test success counter

    MatrixSubmatrix(0, 1, one_two_three_matrix, res_2x2); // Actual Result of Test 1

    if (MatrixEquals2x2(sub_mtrx_t1_res, res_2x2) == 1)
    { // If Test 1 was successful

        sub_mtrx_pass_cnt++; // Increment Counter
    }

    MatrixSubmatrix(2, 2, rand_matrix_2, res_2x2); // Actual Result of Test 2

    if (MatrixEquals2x2(sub_mtrx_t2_res, res_2x2))
    { // If Test 2 was successful

        sub_mtrx_pass_cnt++; // Increment Counter
    }

    printf("\nPassed: (%d / 2) MatrixSubmatrix()\n", sub_mtrx_pass_cnt); // Print # of MatrixSubmatrix() succeses

    /* MatrixTrace() Tests*/

    // Test 1: Trace of one_two_three_matrix
    // Test 2: Trace of neg_ninehun_matrix

    int trace_pass_cnt = 0; // trace success counter

    float trace_t1 = 6; // Expected result of test 1

    float trace_t2 = -2997; // Expected result of test 2

    if (trace_t1 == MatrixTrace(one_two_three_matrix))
    { // If test 1 success

        trace_pass_cnt++; // increment counter
    }

    if (trace_t2 == MatrixTrace(neg_ninehun_matrix))
    { // If test 2 success

        trace_pass_cnt++; // increment counter
    }

    printf("\nPassed: (%d / 2) MatrixTrace()\n", trace_pass_cnt); // print # of traces success

    /**/

    int transp_pass_cnt = 0; // Transpose() success counter

    float transp_t1_res[3][3] = {{2, 8, 14}, {4, 10, 16}, {6, 12, 18}}; // Expected result of test 1

    float transp_t2_res[3][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}}; // Expected result of test 2

    MatrixTranspose(rand_matrix_1, result_matrix); // Actual Test 1 result

    if (MatrixEquals(transp_t1_res, result_matrix) == 1)
    { // If test 1 success

        transp_pass_cnt++; // Increment counter
    }

    MatrixTranspose(one_two_three_matrix, result_matrix); // Actual Test 2 result

    if (MatrixEquals(transp_t2_res, result_matrix) == 1)
    { // If test 2 success

        transp_pass_cnt++; // Increment counter
    }

    printf("\nPassed: (%d / 2) MatrixTranspose()\n", transp_pass_cnt); // Print # of Transpose() succeses

    /* MatrixDeterminant() Tests*/

    // Test 1: Determiant of rand_matrix_1

    // Test 2: Determianant of det_test_2

    int det_pass_cnt = 0; // determiant success counter

    float det_t1_res = 0; // Expected reult of test 1

    float det_t2_res = 25; // Expected reult of test 2

    if (MatrixDeterminant(rand_matrix_1) == det_t1_res)
    { // If test 1 success

        det_pass_cnt++; // Increment counter
    }

    if (MatrixDeterminant(det_test_2) == det_t2_res)
    { // If test 2 success

        det_pass_cnt++; // Increment counter
    }

    printf("\nPassed: (%d / 2) MatrixDeterminant()\n", det_pass_cnt); // print # of det successes

    /*MatrixInverse() Tests*/

    int inverse_cnt = 0; // counter

    float inv_t1[3][3] = {{-24, 20, -5}, {18, -15, 4}, {5, -4, 1}}; // Expected result of teset 1

    float inv_t2[3][3] = {{0.4, 0.2, -0.2}, {0.92, -0.04, -0.56}, {0.24, 0.12, -0.32}}; // Expected result of test 2

    MatrixInverse(rand_matrix_3, result_matrix); // Actual Test 1

    if (MatrixEquals(inv_t1, result_matrix) == 1)
    { // If successful

        inverse_cnt++; // increment counter
    }

    MatrixInverse(det_test_2, result_matrix); // Actual tes 2

    if (MatrixEquals(inv_t2, result_matrix) == 1)
    { // If successful

        inverse_cnt++; // Increment counter
    }

    printf("\nPassed: (%d / 2) MatrixInverse()\n", inverse_cnt); // print # of inv successes

    int num_tests = 22; // total test perfrom

    int num_success = inverse_cnt + det_pass_cnt + trace_pass_cnt + equals_pass_cnt + transp_pass_cnt + mtrx_add_pass_cnt + mtrx_add_scalar_pass_cnt + mtrx_mult_pass_cnt + scalar_mul_pass_cnt + sub_mtrx_pass_cnt;

    // num of succesful tests

    if (num_success == 22)
    { // If all tests were successful

        float percent = (float)100 * (num_success / num_tests); // Get percentage

        printf("\n10 out of 10 Functions Passed: (%3.1f%%)\n", percent); // Output message
    }

    printf("\nOutput of MatrixPrint():\n"); // MatrixPrint() Demonstration

    MatrixPrint(rand_matrix_1); // Print with a matrix

    printf("\nExpected Output of MatrixPrint():\n"); // Show expected output without matrix print

    for (int i = 0; i < DIM; i++)
    { // Go through rows

        for (int j = 0; j < DIM; j++)
        { // Go through cols

            printf("|"); // Print left side of matrix border

            printf("%3.1f", rand_matrix_1[i][j]); // Print values
        }

        printf("|\n"); // Print right border & newline
    }

    // while (1); // not necessary for testing
}

int MatrixEquals2x2(float mat1[2][2], float mat2[2][2])
{ // Helper Funct for 2x2 Matrices

    float diff; // checks to see if the difference between each of the entries in each matrix in within FPDELTA Tolerance

    for (int r = 0; r < 2; r++)
    { // Goes through the rows of Matrix

        for (int c = 0; c < 2; c++)
        { // Goes through the cols of Matrix

            diff = abs((mat1[r][c] - mat2[r][c])); // Gets the difference between each respective number at each position within each matrix

            if (diff > FP_DELTA)
            { // If thre is any Number not within FPDELTA Tolerance We Immedianly Know the matrices are not considered equal

                return 0; // Return False
            }
        }
    }
    return 1; // Return True
}

