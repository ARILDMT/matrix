#include "matrix.h"

int transpose(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL) {
    return ERROR_UNCORRECT_MATRIX;
  }
  if (A->rows < 1 || A->columns < 1) {
    return ERROR_UNCORRECT_MATRIX;
  }
  create_matrix(A->columns, A->rows, result);

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }

  return OK;
}