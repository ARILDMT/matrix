#include "matrix.h"

int calc_complements(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL) {
    return ERROR_UNCORRECT_MATRIX;
  }
  if (A->rows < 1 || A->columns < 1) {
    return ERROR_UNCORRECT_MATRIX;
  }
  create_matrix(A->rows, A->columns, result);
  if (A->rows == 1 && A->columns == 1) {
    result->matrix[0][0] = A->matrix[0][0];
    return OK;
  }
  if (A->rows != A->columns || A->rows < 2) {
    remove_matrix(result);
    return ERROR_MATHEMATICS_OPERATIONS;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      matrix_t minor = cut_matrix(*A, i, j);
      double det_minor = pow(-1, i + j) * det(&minor);
      result->matrix[i][j] = det_minor;
      remove_matrix(&minor);
    }
  }

  return OK;
}