#include "tests.h"

START_TEST(test_1) {
  obj_data got = {0};

  ck_assert_int_eq(parseObj("models/test1.obj", &got), OK);
  float v[] = {1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f};
  obj_data exp = {v, NULL, 2, 0, "test1.obj", {0}, {0}, 0};

  ck_assert_int_eq(eq_obj(got, exp), 1);
  free_obj_data(&got);
}
END_TEST

START_TEST(test_2) {
  obj_data got = {0};

  ck_assert_int_eq(parseObj("models/test2.obj", &got), OK);

  unsigned e[] = {1, 2, 2, 3, 3, 4, 4, 5, 5, 1, 1, 2, 2, 3, 3, 1};
  for (int i = 0; i < 16; i++) e[i]--;
  obj_data exp = {NULL, e, 0, 8, "test2.obj", {0}, {0}, 0};

  ck_assert_int_eq(eq_obj(got, exp), 1);
  free_obj_data(&got);
}
END_TEST

START_TEST(test_cube) {
  obj_data got = {0};

  ck_assert_int_eq(parseObj("models/cube.obj", &got), OK);
  float v[] = {2,         -0.984852,   1.00842,     5.96046e-08, -0.984852,
               1.00842,   5.96046e-08, -0.984852,   -0.991578,   5.96046e-08,
               1.01515,   -0.991578,   5.96046e-08, 1.01515,     1.00842,
               2,         1.01515,     1.00842,     2,           1.01515,
               -0.991577, 2,           -0.984852,   -0.991578};
  unsigned e[] = {1, 2, 2, 3, 3, 1, 4, 5, 5, 6, 6, 4, 7, 6, 6, 1, 1, 7,
                  6, 5, 5, 2, 2, 6, 2, 5, 5, 4, 4, 2, 8, 3, 3, 4, 4, 8,
                  8, 1, 1, 3, 3, 8, 7, 4, 4, 6, 6, 7, 8, 7, 7, 1, 1, 8,
                  1, 6, 6, 2, 2, 1, 3, 2, 2, 4, 4, 3, 7, 8, 8, 4, 4, 7};
  for (int i = 0; i < 72; i++) e[i]--;
  obj_data exp = {v, e, 24 / 3, 72 / 2, "cube.obj", {0}, {0}, 0};

  ck_assert_int_eq(eq_obj(got, exp), 1);
  free_obj_data(&got);
}
END_TEST

START_TEST(test_nothing) {
  obj_data got = {0};

  ck_assert_int_eq(parseObj("models/nothing.obj", &got), OK);
  obj_data exp = {NULL, NULL, 0, 0, "nothing.obj", {0}, {0}, 0};

  ck_assert_int_eq(eq_obj(got, exp), 1);
  free_obj_data(&got);
}
END_TEST

START_TEST(test_nofile) {
  obj_data got = {0};

  ck_assert_int_eq(parseObj("nofile.obj", &got), NO_FILE);
  free_obj_data(&got);
}
END_TEST

START_TEST(test_readname) {
  char *got = NULL;

  ck_assert_int_eq(readName("some_file.obj", &got), OK);
  ck_assert_str_eq("some_file.obj", got);
  if (got) free(got);
}
END_TEST

Suite *suite_parse() {
  Suite *s = suite_create("suite_parse");
  TCase *tc = tcase_create("parse_tc");
  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_cube);
  tcase_add_test(tc, test_nothing);
  tcase_add_test(tc, test_nofile);
  tcase_add_test(tc, test_readname);
  suite_add_tcase(s, tc);
  return s;
}