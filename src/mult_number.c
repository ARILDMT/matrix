#include "matrix.h"

int mult_number(matrix_t *A, double number, matrix_t *result) {
  matrix_return flag = OK;
  if (A != NULL && result != NULL && A->columns >= 1 && A->rows >= 1) {
    create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  } else if (A != NULL && result != NULL && A->columns >= 1 && A->rows >= 1)
    flag = ERROR_MATHEMATICS_OPERATIONS;
  else
    flag = ERROR_UNCORRECT_MATRIX;

  return flag;
}
