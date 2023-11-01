#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../3D_Viewer/affine.h"
#include "tests.h"

START_TEST(test_rotate) {
  float M[] = {+.5, -.5, -.5, +.5, -.5, +.5, -.5, -.5, +.5, -.5, -.5, -.5,
               +.5, +.5, -.5, +.5, +.5, +.5, -.5, +.5, +.5, -.5, +.5, -.5};
  rotateX(M, 24, 27);
  rotateY(M, 24, -46);
  rotateZ(M, 24, 529);
  ck_assert_float_eq_tol(M[0], -0.77412152, EPS);
  ck_assert_float_eq_tol(M[1], +0.37307161, EPS);
  ck_assert_float_eq_tol(M[2], -0.10748684, EPS);
  ck_assert_float_eq_tol(M[3], -0.05833548, EPS);
  ck_assert_float_eq_tol(M[4], +0.69642472, EPS);
  ck_assert_float_eq_tol(M[5], +0.51145828, EPS);
  ck_assert_float_eq_tol(M[6], +0.62356007, EPS);
  ck_assert_float_eq_tol(M[7], +0.56387770, EPS);
  ck_assert_float_eq_tol(M[8], -0.20788148, EPS);
  ck_assert_float_eq_tol(M[9], -0.09222595, EPS);
  ck_assert_float_eq_tol(M[10], +0.24052465, EPS);
  ck_assert_float_eq_tol(M[11], -0.82682663, EPS);
  ck_assert_float_eq_tol(M[12], -0.62356007, EPS);
  ck_assert_float_eq_tol(M[13], -0.56387770, EPS);
  ck_assert_float_eq_tol(M[14], +0.20788148, EPS);
  ck_assert_float_eq_tol(M[15], +0.09222595, EPS);
  ck_assert_float_eq_tol(M[16], -0.24052465, EPS);
  ck_assert_float_eq_tol(M[17], +0.82682663, EPS);
  ck_assert_float_eq_tol(M[18], +0.77412152, EPS);
  ck_assert_float_eq_tol(M[19], -0.37307161, EPS);
  ck_assert_float_eq_tol(M[20], +0.10748684, EPS);
  ck_assert_float_eq_tol(M[21], +0.05833548, EPS);
  ck_assert_float_eq_tol(M[22], -0.69642472, EPS);
  ck_assert_float_eq_tol(M[23], -0.51145828, EPS);
}
END_TEST

START_TEST(test_scale) {
  float M[] = {+.5, -.5, -.5, +.5, -.5, +.5, -.5, -.5, +.5, -.5, -.5, -.5,
               +.5, +.5, -.5, +.5, +.5, +.5, -.5, +.5, +.5, -.5, +.5, -.5};
  scale(M, 24, 2, 3, 0.5);
  ck_assert_float_eq_tol(M[0], 1, EPS);
  ck_assert_float_eq_tol(M[1], -1.5, EPS);
  ck_assert_float_eq_tol(M[2], -0.25, EPS);
  ck_assert_float_eq_tol(M[3], 1, EPS);
  ck_assert_float_eq_tol(M[4], -1.5, EPS);
  ck_assert_float_eq_tol(M[5], 0.25, EPS);
  ck_assert_float_eq_tol(M[6], -1, EPS);
  ck_assert_float_eq_tol(M[7], -1.5, EPS);
  ck_assert_float_eq_tol(M[8], 0.25, EPS);
  ck_assert_float_eq_tol(M[9], -1, EPS);
  ck_assert_float_eq_tol(M[10], -1.5, EPS);
  ck_assert_float_eq_tol(M[11], -0.25, EPS);
  ck_assert_float_eq_tol(M[12], 1, EPS);
  ck_assert_float_eq_tol(M[13], 1.5, EPS);
  ck_assert_float_eq_tol(M[14], -0.25, EPS);
  ck_assert_float_eq_tol(M[15], 1, EPS);
  ck_assert_float_eq_tol(M[16], 1.5, EPS);
  ck_assert_float_eq_tol(M[17], 0.25, EPS);
  ck_assert_float_eq_tol(M[18], -1, EPS);
  ck_assert_float_eq_tol(M[19], 1.5, EPS);
  ck_assert_float_eq_tol(M[20], 0.25, EPS);
  ck_assert_float_eq_tol(M[21], -1, EPS);
  ck_assert_float_eq_tol(M[22], 1.5, EPS);
  ck_assert_float_eq_tol(M[23], -0.25, EPS);
}
END_TEST

START_TEST(test_translate) {
  float M[] = {+.5, -.5, -.5, +.5, -.5, +.5, -.5, -.5, +.5, -.5, -.5, -.5,
               +.5, +.5, -.5, +.5, +.5, +.5, -.5, +.5, +.5, -.5, +.5, -.5};
  translate(M, 24, -0.1, 0.5, 1);
  ck_assert_float_eq_tol(M[0], 0.4, EPS);
  ck_assert_float_eq_tol(M[1], 0, EPS);
  ck_assert_float_eq_tol(M[2], 0.5, EPS);
  ck_assert_float_eq_tol(M[3], 0.4, EPS);
  ck_assert_float_eq_tol(M[4], 0, EPS);
  ck_assert_float_eq_tol(M[5], 1.5, EPS);
  ck_assert_float_eq_tol(M[6], -0.6, EPS);
  ck_assert_float_eq_tol(M[7], 0, EPS);
  ck_assert_float_eq_tol(M[8], 1.5, EPS);
  ck_assert_float_eq_tol(M[9], -0.6, EPS);
  ck_assert_float_eq_tol(M[10], 0, EPS);
  ck_assert_float_eq_tol(M[11], 0.5, EPS);
  ck_assert_float_eq_tol(M[12], 0.4, EPS);
  ck_assert_float_eq_tol(M[13], 1, EPS);
  ck_assert_float_eq_tol(M[14], 0.5, EPS);
  ck_assert_float_eq_tol(M[15], 0.4, EPS);
  ck_assert_float_eq_tol(M[16], 1, EPS);
  ck_assert_float_eq_tol(M[17], 1.5, EPS);
  ck_assert_float_eq_tol(M[18], -0.6, EPS);
  ck_assert_float_eq_tol(M[19], 1, EPS);
  ck_assert_float_eq_tol(M[20], 1.5, EPS);
  ck_assert_float_eq_tol(M[21], -0.6, EPS);
  ck_assert_float_eq_tol(M[22], 1, EPS);
  ck_assert_float_eq_tol(M[23], 0.5, EPS);
}
END_TEST

Suite *affine_suite(void) {
  Suite *s;
  TCase *tc_affine;
  s = suite_create("Affinne operators");
  tc_affine = tcase_create("Affinne operators");
  tcase_add_test(tc_affine, test_rotate);
  tcase_add_test(tc_affine, test_scale);
  tcase_add_test(tc_affine, test_translate);
  suite_add_tcase(s, tc_affine);
  return s;
}