#include "MatrixMath.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void MatrixPrint(float mat [3][3]){

for (int r = 0; r < DIM; r++){ // Go through rows

    for(int c = 0; c < DIM; c++){ // Go through columns

        printf("|"); // Print left side of matrix border

      printf("%3.1f", mat[r][c]); // print value at each index
    }
        printf("|\n"); // Print right side of matrix border

}

}

int MatrixEquals(float mat1[3][3], float mat2[3][3]){

    float diff; // checks to see if the difference between each of the entries in each matrix in within FPDELTA Tolerance

for(int r = 0; r < DIM; r++){  // Goes through the rows of Matrix

    for(int c = 0; c < DIM; c++){ // Goes through the cols of Matrix

    diff =  abs((mat1[r][c] - mat2[r][c])); // Gets the difference between each respective number at each position within each matrix

        if(diff > FP_DELTA){ // If thre is any Number not within FPDELTA Tolerance We Immedianly Know the matrices are not considered equal

            return 0; // Return False
    }
}
}

return 1; // Return True

}














