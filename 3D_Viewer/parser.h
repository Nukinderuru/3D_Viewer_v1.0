#ifndef PARCER_H
#define PARCER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct matrix {
  double **matrix;
  unsigned int rows;
  unsigned int columns;
} matrix_t;

typedef struct facets {
  unsigned int *vertices;
  unsigned int number_of_vertices_in_facets;
} polygon_t;

typedef struct data {
  int count_of_vertices;
  int count_of_facets;
  int count_of_indices;
  matrix_t matrix_3d;
  polygon_t *polygons;
} obj_info;

typedef enum { OK, INCORRECT_MATRIX, CALCULATION_ERROR } operation_result;

int parse_obj_file(const char *filename, obj_info *data);
int count_vertices_and_facets(const char *filename, obj_info *data);
unsigned int count_vertices_in_a_facet(char *buf);
void alloc_mem_for_vertices_in_a_facet(char *buf, unsigned int index,
                                       obj_info *data);
void write_facet_vertices_to_array(char *buf, unsigned int index,
                                   obj_info *data);
void count_indices(obj_info *data);
void remove_obj_info(obj_info *data);
int create_matrix(int rows, int columns, matrix_t *result);
void remove_matrix(matrix_t *A);
void print_obj_data(obj_info *data);
void print_vertices_array(obj_info *data);
void print_indices_array(obj_info *data);

#endif  // PARCER_H
