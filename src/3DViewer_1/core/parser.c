#include "parser.h"

int parseObj(const char *filename, obj_data *obj) {
  int error = OK;
  FILE *file = fopen(filename, "r");
  if (!file) {
    error = NO_FILE;
  } else {
    readName(filename, &obj->name);
    error = fillArrays(file, obj);
    fclose(file);
  }
  return error;
}

int readName(const char *filename, char **name) {
  int error = OK;
  char *last = strrchr(filename, '/');
  if (last) {
    last++;
    *name = (char *)calloc(strlen(last) + 1, sizeof(char));
    if (*name == NULL) {
      error = MALLOC_ERROR;
    } else {
      strcpy(*name, last);
    }
  } else {
    *name = (char *)calloc(strlen(filename) + 1, sizeof(char));
    if (*name == NULL) {
      error = MALLOC_ERROR;
    } else {
      strcpy(*name, filename);
    }
  }

  return error;
}

int fillArrays(FILE *file, obj_data *obj) {
  int error = OK;
  char *line = NULL;
  size_t len = 0;
  size_t i = 0;
  obj->vertex_array = NULL;
  obj->edges_array = NULL;
  obj->vertex_number = 0;
  obj->edges_number = 0;
  while (error == OK && getline(&line, &len, file) != -1) {
    if (line[0] == 'v' && line[1] == ' ') {
      obj->vertex_number += 1;
      float *new_p =
          realloc(obj->vertex_array, (3 * obj->vertex_number) * sizeof(float));
      if (new_p == NULL) {
        error = MALLOC_ERROR;
      } else {
        obj->vertex_array = new_p;
        sscanf(line + 2, "%f %f %f", obj->vertex_array + i,
               obj->vertex_array + i + 1, obj->vertex_array + i + 2);
        i += 3;
      }
    } else if (line[0] == 'f' && line[1] == ' ') {
      error = parsePoligon(line, obj);
    }
  }
  if (line) free(line);
  return error;
}

int parsePoligon(char *line, obj_data *obj) {
  int error = OK;
  char *current = line + 2;
  unsigned first = 0, cur = 0;
  while (current && error == OK) {
    char *endptr = NULL;
    unsigned prev = cur;
    cur = strtoul(current, &endptr, 10);
    if (current != endptr) {
      if (first == 0) {
        first = cur;
      } else {
        obj->edges_number++;
        unsigned *new_p = realloc(obj->edges_array,
                                  (2 * obj->edges_number) * sizeof(unsigned));
        if (new_p == NULL) {
          error = MALLOC_ERROR;
        } else {
          obj->edges_array = new_p;
          obj->edges_array[2 * obj->edges_number - 2] = prev - 1;
          obj->edges_array[2 * obj->edges_number - 1] = cur - 1;
        }
      }
      current = endptr;
      current = strchr(current, ' ');
    } else {
      current = NULL;
      cur = prev;
    }
  }
  if (cur) {
    obj->edges_number++;
    unsigned *new_p =
        realloc(obj->edges_array, (2 * obj->edges_number) * sizeof(unsigned));
    if (new_p == NULL) {
      error = MALLOC_ERROR;
    } else {
      obj->edges_array = new_p;
      obj->edges_array[2 * obj->edges_number - 2] = cur - 1;
      obj->edges_array[2 * obj->edges_number - 1] = first - 1;
    }
  }
  return error;
}

void free_obj_data(obj_data *obj) {
  if (obj->vertex_array) {
    free(obj->vertex_array);
    obj->vertex_array = NULL;
  }
  if (obj->edges_array) {
    free(obj->edges_array);
    obj->edges_array = NULL;
  }
  if (obj->name) {
    free(obj->name);
    obj->name = NULL;
  }
  obj->vertex_number = 0;
  obj->edges_number = 0;
}
