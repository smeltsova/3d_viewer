#include "tests.h"

START_TEST(affinity_translate) {
  obj_data model = {0};
  float vertex_model[] = {0.4f,  1.2f,  0.98f, 1.1f,  1.22f, 1.5f,
                          0.06f, 0.07f, 0.3f,  21.2f, 34.6f, 23.8f};
  model.vertex_array = vertex_model;
  model.vertex_number = 4;
  float expected_res[] = {0.9f,  2.2f,  0.68f, 1.6f,  2.22f, 1.2f,
                          0.56f, 1.07f, 0.00f, 21.7f, 35.6f, 23.5f};
  translation(&model, 0.5f, 1.00f, -0.3f);
  ck_assert_int_eq(eq_array_f(expected_res, model.vertex_array, 12), 1);
}
END_TEST

START_TEST(affinity_rotate_x) {
  float vertex_model[] = {0.4,  1.2,  0.98, 1.1,  1.22, 1.5,
                          0.06, 0.07, 0.03, 21.2, 34.6, 23.8};
  obj_data model = {vertex_model, NULL, 4, 0, NULL, {0}, {0}, 0};
  const float waiting_vertex[] = {0.4,  1.2,  0.98, 1.1,  1.22, 1.5,
                                  0.06, 0.07, 0.03, 21.2, 34.6, 23.8};
  float angle = 90.0f;
  rotation(&model, angle, 'x');
  angle = angle / 180 * M_PI;
  for (size_t i = 0; i < model.vertex_number * 3; i += 3) {
    float y = waiting_vertex[i + 1];
    float z = waiting_vertex[i + 2];
    float waitValue1 = y * cos(angle) - z * sin(angle);
    float waitValue2 = y * sin(angle) + z * cos(angle);

    ck_assert_float_eq_tol(model.vertex_array[i + 1], waitValue1, 1e-6);
    ck_assert_float_eq_tol(model.vertex_array[i + 2], waitValue2, 1e-6);
  }
}
END_TEST

START_TEST(affinity_rotate_y) {
  float vertex_model[] = {0.4,  1.2,  0.98, 1.1,  1.22, 1.5,
                          0.06, 0.07, 0.03, 21.2, 34.6, 23.8};
  obj_data model = {vertex_model, NULL, 4, 0, NULL, {0}, {0}, 0};
  const float waiting_vertex[] = {0.4,  1.2,  0.98, 1.1,  1.22, 1.5,
                                  0.06, 0.07, 0.03, 21.2, 34.6, 23.8};
  float angle = 90.0f;
  rotation(&model, angle, 'y');
  angle = angle / 180 * M_PI;
  for (size_t i = 0; i < model.vertex_number * 3; i += 3) {
    float x = waiting_vertex[i];
    float z = waiting_vertex[i + 2];
    float waitValue1 = x * cos(angle) + z * sin(angle);
    float waitValue2 = -x * sin(angle) + z * cos(angle);

    ck_assert_float_eq_tol(model.vertex_array[i], waitValue1, 1e-6);
    ck_assert_float_eq_tol(model.vertex_array[i + 2], waitValue2, 1e-6);
  }
}
END_TEST

START_TEST(affinity_rotate_z) {
  float vertex_model[] = {0.4,  1.2,  0.98, 1.1,  1.22, 1.5,
                          0.06, 0.07, 0.03, 21.2, 34.6, 23.8};
  obj_data model = {vertex_model, NULL, 4, 0, NULL, {0}, {0}, 0};
  const float waiting_vertex[] = {0.4,  1.2,  0.98, 1.1,  1.22, 1.5,
                                  0.06, 0.07, 0.03, 21.2, 34.6, 23.8};
  float angle = 90.0f;
  rotation(&model, angle, 'z');
  angle = angle / 180 * M_PI;
  for (size_t i = 0; i < model.vertex_number * 3; i += 3) {
    float x = waiting_vertex[i];
    float y = waiting_vertex[i + 1];
    float waitValue1 = x * cos(angle) - y * sin(angle);
    float waitValue2 = x * sin(angle) + y * cos(angle);

    ck_assert_float_eq_tol(model.vertex_array[i], waitValue1, 1e-6);
    ck_assert_float_eq_tol(model.vertex_array[i + 1], waitValue2, 1e-6);
  }
}
END_TEST

START_TEST(affinity_scaling) {
  obj_data model = {0};
  float vertex_model[] = {0.4f,  1.2f,  0.98f, 1.1f,  1.22f, 1.5f,
                          0.06f, 0.07f, 0.03f, 21.2f, 34.6f, 23.8f};
  model.vertex_array = vertex_model;
  model.vertex_number = 4;
  float expected_res[] = {0.2f,  1.2f,  -0.49f,  0.55f, 1.22f, -0.75f,
                          0.03f, 0.07f, -0.015f, 10.6f, 34.6f, -11.9f};
  scaling(&model, 0.5f, 1.00f, -0.5f);
  ck_assert_int_eq(eq_array_f(expected_res, model.vertex_array, 12), 1);
}
END_TEST

START_TEST(moving_to_center) {
  obj_data got = {0};

  ck_assert_int_eq(parseObj("models/test3.obj", &got), OK);
  moveToCenter(&got);
  ck_assert_float_eq_tol(got.max_coord, 1.1, PRECISION);
  float v[] = {-1, -1, 0, 1, -1, 0, 1, 1, 0, -1, 1, 0};
  unsigned e[] = {0, 1, 1, 2, 2, 3, 3, 0};
  obj_data exp = {v, e, 4, 4, "test3.obj", {0}, {0}, 0};

  ck_assert_int_eq(eq_obj(got, exp), 1);
  free_obj_data(&got);
}
END_TEST

START_TEST(moving_to_center_nothing) {
  obj_data got = {0};

  ck_assert_int_eq(parseObj("models/nothing.obj", &got), OK);
  moveToCenter(&got);
  ck_assert_float_eq_tol(got.max_coord, 0, PRECISION);
  obj_data exp = {NULL, NULL, 0, 0, "nothing.obj", {0}, {0}, 0};

  ck_assert_int_eq(eq_obj(got, exp), 1);
  free_obj_data(&got);
}
END_TEST

Suite *suite_test_affinity() {
  Suite *s = suite_create("suite_test_affinity");
  TCase *tc = tcase_create("test_affinity_tc");

  tcase_add_test(tc, affinity_translate);
  tcase_add_test(tc, affinity_rotate_x);
  tcase_add_test(tc, affinity_rotate_y);
  tcase_add_test(tc, affinity_rotate_z);
  tcase_add_test(tc, affinity_scaling);
  tcase_add_test(tc, moving_to_center);
  tcase_add_test(tc, moving_to_center_nothing);
  suite_add_tcase(s, tc);
  return s;
}
