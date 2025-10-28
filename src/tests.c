#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "matrix.h"

double get_rand(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}

START_TEST(create_valid) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t m = {0};
  ck_assert_int_eq(create_matrix(rows, cols, &m), OK);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ck_assert_ldouble_eq_tol(0.0, m.matrix[i][j], 1e-07);
    }
  }
  ck_assert_int_eq(m.rows, rows);
  ck_assert_int_eq(m.columns, cols);
  remove_matrix(&m);
}
END_TEST

START_TEST(create_invalid_size) {
  matrix_t m = {0};
  ck_assert_int_eq(create_matrix(0, 10, &m), ERROR_UNCORRECT_MATRIX);
  ck_assert_int_eq(create_matrix(10, 0, &m), ERROR_UNCORRECT_MATRIX);
  ck_assert_int_eq(create_matrix(-1, 2, &m), ERROR_UNCORRECT_MATRIX);
}
END_TEST

START_TEST(create_null_result) {
  ck_assert_int_eq(create_matrix(1, 2, NULL), ERROR_UNCORRECT_MATRIX);
}
END_TEST

START_TEST(remove_valid) {
  matrix_t m = {0};
  create_matrix(4, 2, &m);
  remove_matrix(&m);
  ck_assert_ptr_null(m.matrix);
  ck_assert_int_eq(m.rows, 0);
  ck_assert_int_eq(m.columns, 0);
}
END_TEST

START_TEST(remove_null) {
  remove_matrix(NULL);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(eq_valid_same) {
  matrix_t A = {0}, B = {0};
  create_matrix(2, 2, &A);
  create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.00000000234;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3.05;
  A.matrix[1][1] = 4;
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3.05;
  B.matrix[1][1] = 4;
  ck_assert_int_eq(eq_matrix(&A, &B), SUCCESS);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(eq_valid_different) {
  matrix_t A = {0}, B = {0};
  create_matrix(2, 2, &A);
  create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.0001;
  B.matrix[0][0] = 1;
  ck_assert_int_eq(eq_matrix(&A, &B), FAILURE);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(eq_invalid) {
  matrix_t A = {0}, B = {0};
  ck_assert_int_eq(eq_matrix(&A, &B), FAILURE);
  create_matrix(2, 2, &A);
  ck_assert_int_eq(eq_matrix(&A, NULL), FAILURE);
  ck_assert_int_eq(eq_matrix(NULL, &B), FAILURE);
  remove_matrix(&A);
}
END_TEST

START_TEST(eq_size_mismatch) {
  matrix_t A = {0}, B = {0};
  create_matrix(2, 3, &A);
  create_matrix(3, 2, &B);
  ck_assert_int_eq(eq_matrix(&A, &B), FAILURE);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(sum_valid) {
  int rows = 3, cols = 3;
  matrix_t A = {0}, B = {0}, result = {0}, expected = {0};
  create_matrix(rows, cols, &A);
  create_matrix(rows, cols, &B);
  create_matrix(rows, cols, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 6;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 0;
  B.matrix[0][2] = 0;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 0;
  B.matrix[1][2] = 0;
  B.matrix[2][0] = 3;
  B.matrix[2][1] = 4;
  B.matrix[2][2] = 1;

  expected.matrix[0][0] = 2;
  expected.matrix[0][1] = 2;
  expected.matrix[0][2] = 3;
  expected.matrix[1][0] = 2;
  expected.matrix[1][1] = 4;
  expected.matrix[1][2] = 5;
  expected.matrix[2][0] = 3;
  expected.matrix[2][1] = 4;
  expected.matrix[2][2] = 7;

  ck_assert_int_eq(sum_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(eq_matrix(&result, &expected), SUCCESS);

  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&result);
  remove_matrix(&expected);
}
END_TEST

START_TEST(sum_invalid) {
  matrix_t A = {0}, B = {0}, result = {0};
  create_matrix(2, 3, &A);
  create_matrix(3, 2, &B);
  ck_assert_int_eq(sum_matrix(&A, &B, &result),
                   ERROR_MATHEMATICS_OPERATIONS);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(sub_valid) {
  int rows = 3, cols = 3;
  matrix_t A = {0}, B = {0}, result = {0}, expected = {0};
  create_matrix(rows, cols, &A);
  create_matrix(rows, cols, &B);
  create_matrix(rows, cols, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 6;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 0;
  B.matrix[0][2] = 0;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 0;
  B.matrix[1][2] = 0;
  B.matrix[2][0] = 3;
  B.matrix[2][1] = 4;
  B.matrix[2][2] = 1;

  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 2;
  expected.matrix[0][2] = 3;
  expected.matrix[1][0] = -2;
  expected.matrix[1][1] = 4;
  expected.matrix[1][2] = 5;
  expected.matrix[2][0] = -3;
  expected.matrix[2][1] = -4;
  expected.matrix[2][2] = 5;

  ck_assert_int_eq(sub_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(eq_matrix(&result, &expected), SUCCESS);

  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&result);
  remove_matrix(&expected);
}
END_TEST

START_TEST(sub_matrix_1x1) {
  matrix_t A = {0}, B = {0}, result = {0};
  create_matrix(1, 1, &A);
  create_matrix(1, 1, &B);
  A.matrix[0][0] = 5;
  B.matrix[0][0] = 2;
  ck_assert_int_eq(sub_matrix(&A, &B, &result), OK);
  ck_assert_double_eq(result.matrix[0][0], 3.0);
  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_invalid_size) {
  matrix_t A = {0}, B = {0}, result = {0};
  create_matrix(2, 3, &A);
  create_matrix(2, 2, &B);
  ck_assert_int_eq(sub_matrix(&A, &B, &result),
                   ERROR_MATHEMATICS_OPERATIONS);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_null_result) {
  matrix_t A = {0}, B = {0};
  create_matrix(2, 2, &A);
  create_matrix(2, 2, &B);
  ck_assert_int_eq(sub_matrix(&A, &B, NULL), ERROR_UNCORRECT_MATRIX);
  remove_matrix(&A);
  remove_matrix(&B);
}
END_TEST

START_TEST(mult_number_valid) {
  matrix_t A = {0}, result = {0}, expected = {0};
  create_matrix(3, 3, &A);
  create_matrix(3, 3, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  expected.matrix[0][0] = 2;
  expected.matrix[0][1] = 4;
  expected.matrix[0][2] = 6;
  expected.matrix[1][0] = 8;
  expected.matrix[1][1] = 10;
  expected.matrix[1][2] = 12;
  expected.matrix[2][0] = 14;
  expected.matrix[2][1] = 16;
  expected.matrix[2][2] = 18;

  ck_assert_int_eq(mult_number(&A, 2.0, &result), OK);
  ck_assert_int_eq(eq_matrix(&result, &expected), SUCCESS);

  remove_matrix(&A);
  remove_matrix(&result);
  remove_matrix(&expected);
}
END_TEST

START_TEST(mult_number_1x1) {
  matrix_t A = {0}, result = {0};
  create_matrix(1, 1, &A);
  A.matrix[0][0] = 5;
  ck_assert_int_eq(mult_number(&A, 2.0, &result), OK);
  ck_assert_double_eq(result.matrix[0][0], 10.0);
  remove_matrix(&A);
  remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_invalid_size) {
  matrix_t A = {0}, result = {0};
  create_matrix(0, 2, &A);
  ck_assert_int_eq(mult_number(&A, 2.0, &result), ERROR_UNCORRECT_MATRIX);
  remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_null_result) {
  matrix_t A = {0};
  create_matrix(2, 2, &A);
  ck_assert_int_eq(mult_number(&A, 2.0, NULL), ERROR_UNCORRECT_MATRIX);
  remove_matrix(&A);
}
END_TEST

START_TEST(mult_matrix_valid) {
  matrix_t A = {0}, B = {0}, result = {0}, expected = {0};
  create_matrix(3, 2, &A);
  create_matrix(2, 3, &B);
  create_matrix(3, 3, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 3;
  B.matrix[1][2] = 4;

  expected.matrix[0][0] = 9;
  expected.matrix[0][1] = 11;
  expected.matrix[0][2] = 17;
  expected.matrix[1][0] = 12;
  expected.matrix[1][1] = 13;
  expected.matrix[1][2] = 22;
  expected.matrix[2][0] = 15;
  expected.matrix[2][1] = 15;
  expected.matrix[2][2] = 27;

  ck_assert_int_eq(mult_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(eq_matrix(&result, &expected), SUCCESS);

  remove_matrix(&A);
  remove_matrix(&B);
  remove_matrix(&result);
  remove_matrix(&expected);
}
END_TEST

START_TEST(transpose_valid) {
  matrix_t A = {0}, result = {0}, expected = {0};
  create_matrix(3, 2, &A);
  create_matrix(2, 3, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;

  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 2;
  expected.matrix[0][2] = 3;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = 5;
  expected.matrix[1][2] = 6;

  ck_assert_int_eq(transpose(&A, &result), OK);
  ck_assert_int_eq(eq_matrix(&result, &expected), SUCCESS);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 3);

  remove_matrix(&A);
  remove_matrix(&result);
  remove_matrix(&expected);
}
END_TEST

START_TEST(det_valid_1x1) {
  matrix_t A = {0};
  create_matrix(1, 1, &A);
  A.matrix[0][0] = 984.1238;
  double deter = 0;
  ck_assert_int_eq(determinant(&A, &deter), OK);
  ck_assert_double_eq_tol(deter, 984.1238, 1e-7);
  remove_matrix(&A);
}
END_TEST

START_TEST(det_valid_2x2) {
  matrix_t A = {0};
  create_matrix(2, 2, &A);
  A.matrix[0][0] = 9;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 96;
  A.matrix[1][1] = 1931;
  double deter = 0;
  ck_assert_int_eq(determinant(&A, &deter), OK);
  ck_assert_double_eq_tol(deter, 17187.0, 1e-7);
  remove_matrix(&A);
}
END_TEST

START_TEST(det_invalid_null) {
  ck_assert_int_eq(determinant(NULL, NULL), ERROR_UNCORRECT_MATRIX);
}
END_TEST

START_TEST(det_invalid_not_square) {
  matrix_t A = {0};
  create_matrix(3, 4, &A);
  double deter = 0;
  ck_assert_int_eq(determinant(&A, &deter), ERROR_MATHEMATICS_OPERATIONS);
  remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_1x1) {
  matrix_t A = {0}, result = {0};
  create_matrix(1, 1, &A);
  A.matrix[0][0] = 5;
  ck_assert_int_eq(calc_complements(&A, &result), OK);
  ck_assert_double_eq(result.matrix[0][0], 5);
  remove_matrix(&A);
  remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_2x2) {
  matrix_t A = {0}, result = {0};
  create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  ck_assert_int_eq(calc_complements(&A, &result), OK);
  ck_assert_double_eq(result.matrix[0][0], 4);
  ck_assert_double_eq(result.matrix[0][1], -3);
  ck_assert_double_eq(result.matrix[1][0], -2);
  ck_assert_double_eq(result.matrix[1][1], 1);
  remove_matrix(&A);
  remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_null) {
  matrix_t A = {0}, result = {0};
  ck_assert_int_eq(calc_complements(&A, &result), ERROR_UNCORRECT_MATRIX);
  ck_assert_int_eq(calc_complements(NULL, &result), ERROR_UNCORRECT_MATRIX);
  ck_assert_int_eq(calc_complements(&A, NULL), ERROR_UNCORRECT_MATRIX);
}
END_TEST

START_TEST(calc_complements_invalid_size) {
  matrix_t A = {0}, result = {0};
  create_matrix(0, 2, &A);
  ck_assert_int_eq(calc_complements(&A, &result), ERROR_UNCORRECT_MATRIX);
  remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_non_square) {
  matrix_t A = {0}, result = {0};
  create_matrix(3, 4, &A);
  ck_assert_int_eq(calc_complements(&A, &result),
                   ERROR_MATHEMATICS_OPERATIONS);
  remove_matrix(&A);
}
END_TEST

START_TEST(inverse_1x1) {
  matrix_t A = {0}, result = {0};
  create_matrix(1, 1, &A);
  A.matrix[0][0] = 5;
  ck_assert_int_eq(inverse_matrix(&A, &result), OK);
  ck_assert_double_eq(result.matrix[0][0], 1.0 / 5.0);
  remove_matrix(&A);
  remove_matrix(&result);
}
END_TEST

START_TEST(inverse_2x2) {
  matrix_t A = {0}, result = {0};
  create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  ck_assert_int_eq(inverse_matrix(&A, &result), OK);
  ck_assert_double_eq(result.matrix[0][0], -2.0);
  ck_assert_double_eq(result.matrix[0][1], 1.0);
  ck_assert_double_eq(result.matrix[1][0], 1.5);
  ck_assert_double_eq(result.matrix[1][1], -0.5);
  remove_matrix(&A);
  remove_matrix(&result);
}
END_TEST

START_TEST(inverse_invalid_singular) {
  matrix_t A = {0};
  create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 1;
  matrix_t result = {0};
  ck_assert_int_eq(inverse_matrix(&A, &result),
                   ERROR_MATHEMATICS_OPERATIONS);
  remove_matrix(&A);
}
END_TEST

START_TEST(inverse_null) {
  matrix_t A = {0}, result = {0};
  ck_assert_int_eq(inverse_matrix(&A, &result), ERROR_UNCORRECT_MATRIX);
  ck_assert_int_eq(inverse_matrix(NULL, &result), ERROR_UNCORRECT_MATRIX);
  ck_assert_int_eq(inverse_matrix(&A, NULL), ERROR_UNCORRECT_MATRIX);
}
END_TEST

START_TEST(inverse_non_square) {
  matrix_t A = {0}, result = {0};
  create_matrix(3, 4, &A);
  ck_assert_int_eq(inverse_matrix(&A, &result),
                   ERROR_MATHEMATICS_OPERATIONS);
  remove_matrix(&A);
}
END_TEST

int main(void) {
  Suite *s;
  TCase *tc;
  SRunner *sr;
  int failed = 0;

  s = suite_create("create_matrix");
  tc = tcase_create("Core");
  tcase_add_test(tc, create_valid);
  tcase_add_test(tc, create_invalid_size);
  tcase_add_test(tc, create_null_result);
  suite_add_tcase(s, tc);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  s = suite_create("remove_matrix");
  tc = tcase_create("Core");
  tcase_add_test(tc, remove_valid);
  tcase_add_test(tc, remove_null);
  suite_add_tcase(s, tc);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  s = suite_create("eq_matrix");
  tc = tcase_create("Core");
  tcase_add_test(tc, eq_valid_same);
  tcase_add_test(tc, eq_valid_different);
  tcase_add_test(tc, eq_invalid);
  tcase_add_test(tc, eq_size_mismatch);
  suite_add_tcase(s, tc);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  s = suite_create("sum_matrix");
  tc = tcase_create("Core");
  tcase_add_test(tc, sum_valid);
  tcase_add_test(tc, sum_invalid);
  suite_add_tcase(s, tc);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  s = suite_create("sub_matrix");
  tc = tcase_create("Core");
  tcase_add_test(tc, sub_valid);
  tcase_add_test(tc, sub_matrix_1x1);
  tcase_add_test(tc, sub_matrix_invalid_size);
  tcase_add_test(tc, sub_matrix_null_result);
  suite_add_tcase(s, tc);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  s = suite_create("mult_number");
  tc = tcase_create("Core");
  tcase_add_test(tc, mult_number_valid);
  tcase_add_test(tc, mult_number_1x1);
  tcase_add_test(tc, mult_number_invalid_size);
  tcase_add_test(tc, mult_number_null_result);
  suite_add_tcase(s, tc);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  s = suite_create("mult_matrix");
  tc = tcase_create("Core");
  tcase_add_test(tc, mult_matrix_valid);
  suite_add_tcase(s, tc);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  s = suite_create("transpose");
  tc = tcase_create("Core");
  tcase_add_test(tc, transpose_valid);
  suite_add_tcase(s, tc);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  s = suite_create("determinant");
  tc = tcase_create("Core");
  tcase_add_test(tc, det_valid_1x1);
  tcase_add_test(tc, det_valid_2x2);
  tcase_add_test(tc, det_invalid_null);
  tcase_add_test(tc, det_invalid_not_square);
  suite_add_tcase(s, tc);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  s = suite_create("calc_complements");
  tc = tcase_create("Core");
  tcase_add_test(tc, calc_complements_1x1);
  tcase_add_test(tc, calc_complements_2x2);
  tcase_add_test(tc, calc_complements_null);
  tcase_add_test(tc, calc_complements_invalid_size);
  tcase_add_test(tc, calc_complements_non_square);
  suite_add_tcase(s, tc);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  s = suite_create("inverse_matrix");
  tc = tcase_create("Core");
  tcase_add_test(tc, inverse_1x1);
  tcase_add_test(tc, inverse_2x2);
  tcase_add_test(tc, inverse_invalid_singular);
  tcase_add_test(tc, inverse_null);
  tcase_add_test(tc, inverse_non_square);
  suite_add_tcase(s, tc);
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}