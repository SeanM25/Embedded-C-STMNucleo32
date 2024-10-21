#include "MatrixMath.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Helper Functions

void MatrixPrint2x2(float mat[2][2]); // Used for debugging / quicky checking functions dealing with 2x2 submatrices like MatrixDeterminant()

float MatrixDeterminant2x2(float submtrx[2][2]); // Helper function to calculate 2x2 determiant

void MatrixPrint(float mat[3][3])
{

    for (int r = 0; r < DIM; r++)
    { // Go through rows

        for (int c = 0; c < DIM; c++)
        { // Go through columns

            printf("|"); // Print left side of matrix border

            printf("%3.1f", mat[r][c]); // print value at each index
        }
        printf("|\n"); // Print right side of matrix border
    }
}

void MatrixPrint2x2(float mat[2][2])
{

    for (int r = 0; r < 2; r++)
    { // Go through rows

        for (int c = 0; c < 2; c++)
        { // Go through columns

            printf("|"); // Print left side of matrix border

            printf("%3.1f", mat[r][c]); // print value at each index
        }
        printf("|\n"); // Print right side of matrix border
    }
}

int MatrixEquals(float mat1[3][3], float mat2[3][3])
{

    float diff; // checks to see if the difference between each of the entries in each matrix in within FPDELTA Tolerance

    for (int r = 0; r < DIM; r++)
    { // Goes through the rows of Matrix

        for (int c = 0; c < DIM; c++)
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

void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3])
{

    for (int r = 0; r < DIM; r++)
    { // Go through the rows

        for (int c = 0; c < DIM; c++)
        { // Go through the cols

            result[r][c] = (x * mat[r][c]); // Each indicies of mat is multiplied by 5 and stored in result
        }
    }
}

void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3])
{

    for (int r = 0; r < DIM; r++)
    { // Go through the rows

        for (int c = 0; c < DIM; c++)
        { // Go through the cols

            result[r][c] = 0; // Make sure reuslt matrix is initialized to 0 to prevent errors

            for (int pos = 0; pos < DIM; pos++)
            { // Need a third variable to keep track of row iterated down row in one matrix and down col in the other

                result[r][c] = result[r][c] + (mat1[r][pos] * mat2[pos][c]); // Do matrix multiplication rows * cols & store in result
            }
        }
    }
}

void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3])
{

    for (int r = 0; r < DIM; r++)
    { // Go through the rows

        for (int c = 0; c < DIM; c++)
        { // Go through the cols

            result[r][c] = (mat1[r][c] + mat2[r][c]); // Add the indices of each matrix together
        }
    }
}

void MatrixScalarAdd(float x, float mat[3][3], float result[3][3])
{

    for (int r = 0; r < DIM; r++)
    { // Go through the rows

        for (int c = 0; c < DIM; c++)
        { // Go through the cols

            result[r][c] = (mat[r][c] + x); // Add scalar to each indice and store in result
        }
    }
}

void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2])
{

    int res_r = 0, res_c = 0; // Indices of our result matrix

    for (int r = 0; r < DIM; r++)
    { // Go through the rows

        if (r == i)
            continue; // Skip the row you don't want

        for (int c = 0; c < DIM; c++)
        { // Go through the cols

            if (c == j)
                continue; // Skip the col you don't want

            result[res_r][res_c] = mat[r][c]; // assign submatrix to our 2x2 result matrix

            res_c++; // Increment cols
        }

        res_c = 0; // reset cols

        res_r++; // increment rows
    }
}

float MatrixTrace(float mat[3][3])
{

    float sum = 0; // Sum of trace initialized to 0

    for (int r = 0; r < DIM; r++)
    { // Only 1 loop needed for diagonals

        sum = sum + mat[r][r]; // sum += diagonal entries
    }

    return sum; // return sum
}

void MatrixTranspose(float mat[3][3], float result[3][3])
{

    for (int r = 0; r < DIM; r++)
    { // Go through the rows

        for (int c = 0; c < DIM; c++)
        { // Go through the cols

            result[r][c] = mat[c][r]; // make the rows of mat the cols of result
        }
    }
}

float MatrixDeterminant2x2(float submtrx[2][2])
{ // Helper function for 2x2 determiant

    float det = 0; // Intialize determinant to 0

    det = (submtrx[0][0] * submtrx[1][1]) - (submtrx[0][1] * submtrx[1][0]); // a * d - b * c

    return det; // return determinant
}

float MatrixDeterminant(float mat[3][3])
{

    float sub_matrix_11[2][2]; // Intialize the first needed submatrix gets found by getting rid of row 1 col 1

    float sub_matrix_12[2][2]; // Intialize the first needed submatrix gets found by getting rid of row 1 col 2

    float sub_matrix_13[2][2]; // Intialize the first needed submatrix gets found by getting rid of row 1 col 3

    float det_11, det_12, det_13; // Intialize the individual determinants of the above submatrices

    float total_det; // Final determinant result initialized

    // Get submatrices for the determinant

    MatrixSubmatrix(0, 0, mat, sub_matrix_11); // 1st Submatrix

    MatrixSubmatrix(0, 1, mat, sub_matrix_12); // 2nd Submatrix

    MatrixSubmatrix(0, 2, mat, sub_matrix_13); // // 3rd Submatrix

    // Get determinants of the submatrices

    det_11 = MatrixDeterminant2x2(sub_matrix_11); // det of 1st Submatrix

    det_12 = MatrixDeterminant2x2(sub_matrix_12); // det of 2nd Submatrix

    det_13 = MatrixDeterminant2x2(sub_matrix_13); // det of 3rd Submatrix

    total_det = (mat[0][0] * det_11) - (mat[0][1] * det_12) + (mat[0][2] * det_13); // Final Determiant

    return total_det; // return final determiant
}

void MatrixInverse(float mat[3][3], float result[3][3])
{

    float det_a = MatrixDeterminant(mat); // Get det A

    float res[2][2]; // 2x2 array

    float res_extra[3][3]; // 3x3 array for for loop

    float res_extra_2[3][3]; // 3x3 array for transposing

    for (int r = 0; r < DIM; r++)
    { // Go through cols

        for (int c = 0; c < DIM; c++)
        { // Go through rows

            MatrixSubmatrix(r, c, mat, res); // Go through cols

            if ((r + c) % 2 != 0)
            { // Check even or odd condition

                res_extra[r][c] = (-1 * MatrixDeterminant2x2(res));
            }
            else
            {

                res_extra[r][c] = MatrixDeterminant2x2(res);
            }
        }
    }

    MatrixTranspose(res_extra, res_extra_2); // Transpose Cofactor

    MatrixScalarMultiply((1 / det_a), res_extra_2, result); // Get final inverse result
}
