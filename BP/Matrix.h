#ifndef _MATRIX_H_
#define _MATRIX_H_

/* ======================================================
 * includes
 * ====================================================== */
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<time.h>
#include<malloc.h>
#include<stdbool.h>
#include<string.h>
#include<cblas.h>


/* ======================================================
 * types and macros
 * ====================================================== */

#define cpus 4

typedef struct
{
    int N;
    int D;
    long ele_num;
    double *data;
}Matrix;



/* ======================================================
 * function definitions
 * ====================================================== */

/* method associated to matrix and its operation */

// implementing multiplication of two matrices and return a new Matrix
Matrix Matrix_dot(Matrix, Matrix); 

// implementing multiplication of two matrices, dot multiply to the first on directly
void Matrix_dot_by(Matrix *, Matrix); 

// implementing add operation of two matrices and return a new Matrix
Matrix Matrix_add(const Matrix, const Matrix); 

// implementing add one matrix directly to another one
void Matrix_add_by(Matrix *, const Matrix); 

// free the memory the matrix takes up
void Matrix_free(Matrix); 

// create a Matrix of size (N,D) without values assigned
Matrix Matrix_create(const int, const int);

// get the maximal value of a matrix along a given dimension
Matrix Matrix_max(const Matrix, int); 

// get the minimal value of a matrix along a given dimension
Matrix Matrix_min(const Matrix, const int axis);

//deep copy a Matrix
Matrix Matrix_copy(const Matrix); 

// set the value of one element of the Matrix
void Matrix_set(const Matrix, const int, const int, const double); 

// print the Matrix to screen
void Matrix_print(const Matrix); 

// reshape the Matrix
void Matrix_reshape(Matrix * const, const int, const int); 

// create a Matrix with all values to be 1
Matrix Matrix_ones(const int, const int);

// create a Matrix with all values to be 0
Matrix Matrix_zeros(const int, const int);

// create a 1-D Matrix with values from 0 to B-1
Matrix Matrix_range(const int);

// create a 1-D Matrix with values from A to B-1
Matrix Matrix_range2(const int, const int);


#endif
