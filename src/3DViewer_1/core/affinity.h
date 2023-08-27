#ifndef AFFINITY_H
#define AFFINITY_H

#include "parser.h"

void translation(obj_data *obj, float x, float y, float z);
void rotation(obj_data *obj, float angle, char axis);
void scaling(obj_data *obj, float Sx, float Sy, float Sz);

void findMinMax(obj_data *obj);
float moveToCenter(obj_data *obj);

#endif  // AFFINITY_H
