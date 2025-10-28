#include "matrix.h"

int inverse_matrix(matrix_t *A, matrix_t *result) {
  matrix_return flag = OK;
  if (A != NULL) {
    if (A->rows >= 1 && A->columns >= 1 && result != NULL) {
      double det_value = 0;
      int det_result = determinant(A, &det_value);
      if (det_value != 0 && det_result == 0 && A->rows >= 2) {
        matrix_t matrix_temp_0;
        calc_complements(A, &matrix_temp_0);
        matrix_t matrix_temp_1;
        transpose(&matrix_temp_0, &matrix_temp_1);
        mult_number(&matrix_temp_1, 1 / det_value, result);

        remove_matrix(&matrix_temp_0);
        remove_matrix(&matrix_temp_1);
      } else if (det_value != 0 && det_result == 0 && A->rows == 1) {
        create_matrix(1, 1, result);
        result->matrix[0][0] = 1 / A->matrix[0][0];
      } else
        flag = ERROR_MATHEMATICS_OPERATIONS;
    } else
      flag = ERROR_UNCORRECT_MATRIX;
  } else
    flag = ERROR_UNCORRECT_MATRIX;

  return flag;
}
