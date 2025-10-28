#include "matrix.h"

int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  matrix_return flag = OK;
  if (A != NULL && B != NULL && result != NULL && A->rows == B->rows &&
      A->columns == B->columns && A->columns >= 1 && A->rows >= 1) {
    create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  } else if ((A->rows != B->rows || A->columns != B->columns) && A != NULL &&
             B != NULL && result != NULL && A->columns >= 1 && A->rows >= 1 &&
             B->columns >= 1 && B->rows >= 1) {
    flag = ERROR_MATHEMATICS_OPERATIONS;
  } else {
    flag = ERROR_UNCORRECT_MATRIX;
  }

  return flag;
}
