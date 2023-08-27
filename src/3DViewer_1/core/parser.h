#ifndef PARSER_H
#define PARSER_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { OK, NO_FILE, MALLOC_ERROR };

typedef struct {
  float *vertex_array;
  unsigned *edges_array;
  unsigned vertex_number;
  unsigned edges_number;
  char *name;
  float min[3];
  float max[3];
  float max_coord;
} obj_data;

int parseObj(const char *filename, obj_data *obj);
int readName(const char *filename, char **name);
int fillArrays(FILE *file, obj_data *obj);
int parsePoligon(char *line, obj_data *obj);
void free_obj_data(obj_data *obj);

#endif  // PARSER_H
