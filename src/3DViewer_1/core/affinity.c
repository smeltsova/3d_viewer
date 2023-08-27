#include "affinity.h"

void translation(obj_data *obj, float tx, float ty, float tz) {
  size_t size = obj->vertex_number * 3;
  for (size_t i = 0; i < size; i += 3) {
    obj->vertex_array[i] += tx;
    obj->vertex_array[i + 1] += ty;
    obj->vertex_array[i + 2] += tz;
  }
}
void rotation(obj_data *obj, float angle, char axis) {
  angle = angle / 180 * M_PI;
  size_t size = obj->vertex_number * 3;
  for (size_t i = 0; i < size; i += 3) {
    float x = obj->vertex_array[i];
    float y = obj->vertex_array[i + 1];
    float z = obj->vertex_array[i + 2];
    if (axis == 'x') {
      obj->vertex_array[i + 1] = y * cos(angle) - z * sin(angle);
      obj->vertex_array[i + 2] = y * sin(angle) + z * cos(angle);
    } else if (axis == 'y') {
      obj->vertex_array[i] = x * cos(angle) + z * sin(angle);
      obj->vertex_array[i + 2] = -x * sin(angle) + z * cos(angle);
    } else if (axis == 'z') {
      obj->vertex_array[i] = x * cos(angle) - y * sin(angle);
      obj->vertex_array[i + 1] = x * sin(angle) + y * cos(angle);
    }
  }
}

void scaling(obj_data *obj, float Sx, float Sy, float Sz) {
  size_t size = obj->vertex_number * 3;
  for (size_t i = 0; i < size; i += 3) {
    obj->vertex_array[i] *= Sx;
    obj->vertex_array[i + 1] *= Sy;
    obj->vertex_array[i + 2] *= Sz;
  }
}

void findMinMax(obj_data *obj) {
  unsigned i = 0;
  if (obj->vertex_number != 0) {
    obj->min[0] = obj->vertex_array[0];
    obj->max[0] = obj->vertex_array[0];
    obj->min[1] = obj->vertex_array[1];
    obj->max[1] = obj->vertex_array[1];
    obj->min[2] = obj->vertex_array[2];
    obj->max[2] = obj->vertex_array[2];
  } else {
    obj->min[0] = 0;
    obj->max[0] = 0;
    obj->min[1] = 0;
    obj->max[1] = 0;
    obj->min[2] = 0;
    obj->max[2] = 0;
  }
  for (i = 3; i < obj->vertex_number * 3; i += 3) {
    if (obj->min[0] > obj->vertex_array[i]) obj->min[0] = obj->vertex_array[i];
    if (obj->max[0] < obj->vertex_array[i]) obj->max[0] = obj->vertex_array[i];
    if (obj->min[1] > obj->vertex_array[i + 1])
      obj->min[1] = obj->vertex_array[i + 1];
    if (obj->max[1] < obj->vertex_array[i + 1])
      obj->max[1] = obj->vertex_array[i + 1];
    if (obj->min[2] > obj->vertex_array[i + 2])
      obj->min[2] = obj->vertex_array[i + 2];
    if (obj->max[2] < obj->vertex_array[i + 2])
      obj->max[2] = obj->vertex_array[i + 2];
  }
}

float moveToCenter(obj_data *obj) {
  findMinMax(obj);
  float center[3] = {0};
  center[0] = (obj->min[0] + obj->max[0]) / 2;
  center[1] = (obj->min[1] + obj->max[1]) / 2;
  center[2] = (obj->min[2] + obj->max[2]) / 2;
  translation(obj, -center[0], -center[1], -center[2]);
  float dx = obj->max[0] - center[0];
  float dy = obj->max[1] - center[1];
  float dz = obj->max[2] - center[2];
  float dmax = dx > dy ? dx : dy;
  dmax = dmax > dz ? dmax : dz;
  dmax *= 1.10;
  obj->max_coord = dmax;
  return dmax;
}
