// **** Include libraries here ****
// Standard libraries.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// User libraries:
#include "MatrixMath.h"


// Module-level variables:

float zero_matrix[3][3] = {{0, 0, 0},{0, 0, 0},{0, 0, 0}};
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
    

    // Add more tests here!

/***************MatrixEquals() Tests*****************/ 
int pass_cnt = 0;

int test1_actual, test2_actual, test3_actual, test4_actual;

int test_1_expectout = 0; // MatrixEquals(zero_matrix, ones_matrix) Clearly Not Equal

int test_2_expectout = 0; // MatrixEquals(neg_ninehun_matrix, ones_matrix) Clearly Not Equal

int test_3_expectout = 1; // MatrixEquals(one_two_three_matrix, one_two_three_matrix) Equal Dead On

int test_2_expectout = 1; // MatrixEquals(tens_matrix, tens_rnd_matrix) Equal to within FPDELTA



 test1_actual = MatrixEquals(zero_matrix, ones_matrix);


 if (test1_actual == test_1_expectout){

    pass_cnt++;
 }

 

 test2_actual = MatrixEquals(neg_ninehun_matrix, ones_matrix);

 if (test2_actual == test_2_expectout){

pass_cnt++;

 }

 test3_actual = MatrixEquals(one_two_three_matrix, one_two_three_matrix);

 if (test3_actual == test_3_expectout){

pass_cnt++;

 }

 test4_actual = MatrixEquals(tens_matrix, tens_rnd_matrix);

 if (test4_actual == test_4_expectout){

pass_cnt++;

 }

 printf("Matrix Equals() Passed (%d / 4) Tests\n" , pass_cnt);


 /**/


    while (1);
}

