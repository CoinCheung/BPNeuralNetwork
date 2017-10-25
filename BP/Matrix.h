#ifndef _MATRIX_H_
#define _MATRIX_H_

/* 
 * This is a C Matrix calculus libray written by Coin:
 *
 * 1. This libary is heavily dependant on Openblas, with some functions merely a wrapper is Openblas functions. Thus, to use this library, openblas should first be compiled and installed. When gcc is utilized to compile, the '-lopenblas' link option should be added.
 *
 * 2. this lib depends on openblas(assigned by -lopenblas), numberic.h
 *
 *
 * the functions that is rewritable with openblas is:
 * Matrix_add_by(); // cblas_axpy
 * Matrix_scale(); // cblas_scale
 *
 *  */




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
#include"numeric.h"


/* ======================================================
 * types and macros
 * ====================================================== */

/* definition of a 2 dimension matrix */
typedef struct
{
    int N;
    int D;
    long ele_num;
    double *data;
}Matrix;

/* definition of a 3 dimension matrix */
typedef struct
{
    int N;
    int D;
    int H;
    long ele_num;
    double *data;
}Matrix3;


/* ======================================================
 * function definitions
 * ====================================================== */

// implementing multiplication of two matrices and return a new Matrix
Matrix Matrix_dot(const Matrix, const Matrix); 

// implementing dot multiplication of two matrices, works on original Matrix
void Matrix_dot_by(Matrix *, const Matrix); 

// implementing add operation of two matrices and return a new Matrix
Matrix Matrix_add(const Matrix, const Matrix); 

// implementing add one matrix directly to another one
void Matrix_add_by(Matrix *, const Matrix); 

// reverse the sign of all elements of a matrix
void Matrix_sign_reverse(Matrix *);

// transpose a matrx
void Matrix_transpose(Matrix *);

// calculate hadmard product of one matrix by another, directly
void Matrix_multi_by(Matrix*, const Matrix);

// calculate hadmard product of one matrix by another, return new
Matrix Matrix_multi(const Matrix, const Matrix);

// calculate hadmard division of one matrix by another, directly
void Matrix_divide_by(Matrix*, const Matrix);

// calculate hadmard division of one matrix by another, return new
Matrix Matrix_divide(const Matrix, const Matrix);

// calculate exp() of all the elements of a Matrix on the original
void Matrix_exp_ele_by(Matrix*);

// calculate exp() of all the elements of a Matrix, return a new one
Matrix Matrix_exp_ele(const Matrix);

// calculate ln() of all the elements of a Matrix on the original
void Matrix_log_ele_by(Matrix*);

// calculate ln() of all the elements of a Matrix, return a new one
Matrix Matrix_log_ele(const Matrix);

// compute the sum of a matrix along given axis
Matrix Matrix_sum_axis(const Matrix, const int);

// compute the sum of a matrix along given axis, change given matrix
void Matrix_sum_axis_by(Matrix*, const int);

// compute the sum of all the elements of the matrix
double Matrix_sum_all(const Matrix);

// scale all elements of the matrix, works on the original matrix
void Matrix_scale_by(Matrix*, const double);

// scale all elements of the matrix, and return a new one
Matrix Matrix_scale(const Matrix, const double);

// free the memory the matrix takes up
void Matrix_free(Matrix); 

// create a Matrix of size (N,D) without values assigned
Matrix Matrix_create(const int, const int);

// get the maximal value of a matrix along a given dimension
Matrix Matrix_max_axis(const Matrix, int); 

// get the maximal value of all the elements of one matrix
double Matrix_max_all(const Matrix); 

// get the minimal value of a matrix along a given dimension
Matrix Matrix_min_axis(const Matrix, const int axis);

// get the minimal value of all the elements of one matrix
double Matrix_min_all(const Matrix); 

// pick the rows of a Matrix and combine them to be a new one, return the new one
Matrix Matrix_pick_rows(const Matrix, const Matrix);

// pick one specific element in each given row and return a new vector 
Matrix Matrix_pick_eles(const Matrix, const Matrix, const Matrix);

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

// create a identity Matrix 
Matrix Matrix_eye(const int);

// create a Matrix whose elements are gaussian random numbers 
Matrix Matrix_gaussian(const int, const int);

// create a 1-D Matrix with values from 0 to B-1
Matrix Matrix_range(const int);

// create a 1-D Matrix with values from A to B-1
Matrix Matrix_range2(const int, const int);


#endif
