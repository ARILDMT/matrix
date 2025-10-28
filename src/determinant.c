#include "matrix.h"

double det(matrix_t *A) {
  if (A == NULL || A->matrix == NULL || A->rows != A->columns || A->rows < 1) {
    return 0.0;
  }
  double result = 0.0;

  if (A->rows == 1) {
    result = A->matrix[0][0];
  } else if (A->rows == 2) {
    result = A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
  } else {
    int i = 0;
    for (int j = 0; j < A->columns; j++) {
      matrix_t new_matrix = cut_matrix(*A, i, j);
      result += pow(-1, i + j) * A->matrix[i][j] * det(&new_matrix);
      remove_matrix(&new_matrix);
    }
  }

  return result;
}

matrix_t cut_matrix(matrix_t A, int i, int j) {
  matrix_t result_matrix;
  create_matrix(A.rows - 1, A.columns - 1, &result_matrix);

  int new_i = 0;
  for (int i_old = 0; i_old < A.rows; i_old++) {
    if (i_old == i) continue;

    int new_j = 0;
    for (int j_old = 0; j_old < A.columns; j_old++) {
      if (j_old == j) continue;

      result_matrix.matrix[new_i][new_j] = A.matrix[i_old][j_old];
      new_j++;
    }
    new_i++;
  }

  return result_matrix;
}

int determinant(matrix_t *A, double *result) {
  matrix_return flag = OK;
  if (A != NULL) {
    if (A->rows >= 1 && A->columns >= 1 && result != NULL) {
      if (A->rows == A->columns && A->rows >= 2)
        *result = det(A);
      else if (A->rows == A->columns && A->rows == 1)
        *result = A->matrix[0][0];
      else
        flag = ERROR_MATHEMATICS_OPERATIONS;
    } else
      flag = ERROR_UNCORRECT_MATRIX;
  } else
    flag = ERROR_UNCORRECT_MATRIX;

  return flag;
}