#ifndef TESTS_H_
#define TESTS_H_

#include <check.h>
#define EPS 1e-7

Suite *parser_suite(void);
Suite *affine_suite(void);

#endif  // TESTS_H_