#include "matrix.h"

int eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;

  if (A == NULL || B == NULL) {
    return FAILURE;
  }
  if (A->rows < 1 || A->columns < 1 || A->rows != B->rows ||
      A->columns != B->columns) {
    return FAILURE;
  }
  for (int i = 0; i < A->rows && result == SUCCESS; i++) {
    for (int j = 0; j < A->columns && result == SUCCESS; j++) {
      double a_val = round(A->matrix[i][j] * 1e7);
      double b_val = round(B->matrix[i][j] * 1e7);
      if (a_val != b_val) {
        result = FAILURE;
      }
    }
  }

  return result;
}