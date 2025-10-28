#ifndef MATRIX_H
#define MATRIX_H

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;
typedef enum matrix_return {
  OK,
  ERROR_UNCORRECT_MATRIX,
  ERROR_MATHEMATICS_OPERATIONS
} matrix_return;

typedef enum matrix_return_eq { FAILURE, SUCCESS } matrix_return_eq;
int create_matrix(int rows, int columns, matrix_t *result);
void remove_matrix(matrix_t *A);
int eq_matrix(matrix_t *A, matrix_t *B);
int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int mult_number(matrix_t *A, double number, matrix_t *result);
int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int transpose(matrix_t *A, matrix_t *result);
double det(matrix_t *A);
matrix_t cut_matrix(matrix_t A, int i, int j);
int determinant(matrix_t *A, double *result);
int calc_complements(matrix_t *A, matrix_t *result);
int inverse_matrix(matrix_t *A, matrix_t *result);

#endif