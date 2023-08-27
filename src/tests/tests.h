#ifndef SRC_TESTS_TESTS_H_
#define SRC_TESTS_TESTS_H_

#include <check.h>

#include "../3DViewer_1/core/affinity.h"
#include "../3DViewer_1/core/parser.h"

#define PRECISION 1e-6

int eq_array_f(float *A, float *B, int number_array);
int eq_array_uint(unsigned *A, unsigned *B, int number_array);
int eq_obj(obj_data obj1, obj_data obj2);

Suite *suite_test_affinity();
Suite *suite_parse();

void run_tests();
void run_testcase(Suite *testcase);

#endif  // SRC_TESTS_TESTS_H_