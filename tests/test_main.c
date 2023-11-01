#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "tests.h"

int main() {
  int no_failed = 0;

  Suite *suites[] = {parser_suite(), affine_suite(), NULL};
  for (Suite **pS = suites; *pS != NULL; pS++) {
    SRunner *sr = srunner_create(*pS);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    srunner_free(sr);
  }

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}