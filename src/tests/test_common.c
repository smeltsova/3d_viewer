#include "tests.h"

int eq_obj(obj_data obj1, obj_data obj2) {
  int result = 1;
  if (obj1.vertex_number != obj2.vertex_number) {
    result = 0;
    printf("vertex_number %u %u\n", obj1.vertex_number, obj2.vertex_number);
  } else if (obj1.edges_number != obj2.edges_number) {
    result = 0;
    printf("edges_number %u %u\n", obj1.edges_number, obj2.edges_number);
  } else if (strcmp(obj1.name, obj2.name) != 0) {
    result = 0;
    printf("names '%s' '%s'", obj1.name, obj2.name);
  } else if (!eq_array_f(obj1.vertex_array, obj2.vertex_array,
                         obj1.vertex_number * 3)) {
    result = 0;
    printf("vertex_array\n");
  } else if (!eq_array_uint(obj1.edges_array, obj2.edges_array,
                            obj1.edges_number * 2)) {
    result = 0;
    printf("edges_array %u\n", obj1.edges_number * 2);
  }
  return result;
}

int eq_array_f(float *A, float *B, int number_array) {
  int res = 1;
  for (int i = 0; i < number_array; i++) {
    if (fabs(A[i] - B[i]) > PRECISION) {
      res = 0;
      printf("i %d %f %f\n", i, A[i], B[i]);
    }
  }
  return res;
}

int eq_array_uint(unsigned *A, unsigned *B, int number_array) {
  int res = 1;
  for (int i = 0; i < number_array; i++) {
    if (A[i] != B[i]) {
      res = 0;
      printf("i %d %u %u\n", i, A[i], B[i]);
    }
  }
  return res;
}