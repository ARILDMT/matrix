#include "matrix.h"

int create_matrix(int rows, int columns, matrix_t *result) {
  matrix_return flag = OK;
  if (rows >= 1 && columns >= 1 && result != NULL) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));

    if (result->matrix == NULL)
      flag = ERROR_UNCORRECT_MATRIX;
    else {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
      }
    }
  } else
    flag = ERROR_UNCORRECT_MATRIX;
  return flag;
}
