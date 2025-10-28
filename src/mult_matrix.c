#include "matrix.h"

int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL) {
    return ERROR_UNCORRECT_MATRIX;
  }
  if (A->rows < 1 || A->columns < 1 || B->rows < 1 || B->columns < 1) {
    return ERROR_UNCORRECT_MATRIX;
  }
  if (A->columns != B->rows) {
    return ERROR_MATHEMATICS_OPERATIONS;
  }
  int flag = OK;

  create_matrix(A->rows, B->columns, result);

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0;
      for (int r = 0; r < B->rows; r++) {
        result->matrix[i][j] += A->matrix[i][r] * B->matrix[r][j];
      }
    }
  }

  return flag;
}