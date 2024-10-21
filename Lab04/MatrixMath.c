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

void MatrixPrint2x2(float mat [2][2]){

for (int r = 0; r < 2; r++){ // Go through rows

    for(int c = 0; c < 2; c++){ // Go through columns

        printf("|"); // Print left side of matrix border

      printf("%f", mat[r][c]); // print value at each index
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

void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3]){

for(int r = 0; r < DIM; r++){ // Go through the rows

    for(int c = 0; c < DIM; c++){ // Go through the cols

        result[r][c] = (mat[r][c] * x); // Each indicies of mat is multiplied by 5 and stored in result

    }

}
}

void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3]){

    for(int r = 0; r < DIM; r++){ // Go through the rows

        for(int c = 0; c < DIM; c++){ // Go through the cols

      result[r][c] = 0; // Make sure reuslt matrix is initialized to 0 to prevent errors

            for(int pos = 0; pos < DIM; pos++){  // Need a third variable to keep track of row iterated down row in one matrix and down col in the other

            result[r][c] = result[r][c] + (mat1[r][pos] * mat2[pos][c]); // Do matrix multiplication rows * cols & store in result

        }
        }
    }    
}

void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3]){

for (int r = 0; r < DIM; r++){ // Go through the rows

    for(int c = 0; c < DIM; c++){ // Go through the cols

result[r][c] = (mat1[r][c] + mat2[r][c]); // Add the indices of each matrix together

    }
}

}

void MatrixScalarAdd(float x, float mat[3][3], float result[3][3]){

    for(int r = 0; r < DIM; r++){ // Go through the rows

        for(int c = 0; c < DIM; c++){ // Go through the cols

            result[r][c] = (mat[r][c] + x); // Add scalar to each indice and store in result
        }
    }



}

void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2]){

    int res_r = 0, res_c =0; // Indices of our result matrix

for(int r = 0; r < DIM; r++){ // Go through the rows

    if(r == i) continue; // Skip the row you don't want
    
    for(int c = 0; c < DIM; c++){ // Go through the cols

        if(c == j) continue; // Skip the col you don't want

        result[res_r][res_c] = mat[r][c]; // assign submatrix to our 2x2 result matrix

        res_c++; // Increment cols

    }

    res_c = 0; // reset cols

    res_r++; // increment rows

}
}

float MatrixTrace(float mat[3][3]){

   float sum = 0; // Sum of trace initialized to 0

    for(int r = 0; r < DIM; r++){ // Only 1 loop needed for diagonals

    sum = sum + mat[r][r]; // sum += diagonal entries

    }

    return sum; // return sum
}













