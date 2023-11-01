#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../3D_Viewer/parser.h"
#include "tests.h"

START_TEST(test_1) {
  const char filename[20] = "./tests/cube.obj1";
  obj_info objData = (obj_info){0, 0, 0, {NULL, 0, 0}, NULL};
  parse_obj_file(filename, &objData);

  obj_info result = (obj_info){0, 0, 0, {NULL, 0, 0}, NULL};
  result.count_of_facets = 12;
  result.count_of_indices = 72;
  result.count_of_vertices = 8;

  matrix_t res_vertices;
  create_matrix(result.count_of_vertices, 3, &res_vertices);
  res_vertices.matrix[0][0] = 0.500000;
  res_vertices.matrix[0][1] = -0.500000;
  res_vertices.matrix[0][2] = -0.500000;
  res_vertices.matrix[1][0] = 0.500000;
  res_vertices.matrix[1][1] = -0.500000;
  res_vertices.matrix[1][2] = 0.500000;
  res_vertices.matrix[2][0] = -0.500000;
  res_vertices.matrix[2][1] = -0.500000;
  res_vertices.matrix[2][2] = 0.500000;
  res_vertices.matrix[3][0] = -0.500000;
  res_vertices.matrix[3][1] = -0.500000;
  res_vertices.matrix[3][2] = -0.500000;
  res_vertices.matrix[4][0] = 0.500000;
  res_vertices.matrix[4][1] = 0.500000;
  res_vertices.matrix[4][2] = -0.500000;
  res_vertices.matrix[5][0] = 0.500000;
  res_vertices.matrix[5][1] = 0.500000;
  res_vertices.matrix[5][2] = 0.500000;
  res_vertices.matrix[6][0] = -0.500000;
  res_vertices.matrix[6][1] = 0.500000;
  res_vertices.matrix[6][2] = 0.500000;
  res_vertices.matrix[7][0] = -0.500000;
  res_vertices.matrix[7][1] = 0.500000;
  res_vertices.matrix[7][2] = -0.500000;
  result.matrix_3d = res_vertices;

  result.polygons = calloc(result.count_of_facets, sizeof(polygon_t));
  result.polygons[0].number_of_vertices_in_facets = 3;
  result.polygons[1].number_of_vertices_in_facets = 3;
  result.polygons[2].number_of_vertices_in_facets = 3;
  result.polygons[3].number_of_vertices_in_facets = 3;
  result.polygons[4].number_of_vertices_in_facets = 3;
  result.polygons[5].number_of_vertices_in_facets = 3;
  result.polygons[6].number_of_vertices_in_facets = 3;
  result.polygons[7].number_of_vertices_in_facets = 3;
  result.polygons[8].number_of_vertices_in_facets = 3;
  result.polygons[9].number_of_vertices_in_facets = 3;
  result.polygons[10].number_of_vertices_in_facets = 3;
  result.polygons[11].number_of_vertices_in_facets = 3;
  for (int i = 0; i < result.count_of_facets; i++) {
    result.polygons[i].vertices = calloc(
        result.polygons[i].number_of_vertices_in_facets * 2, sizeof(double));
  }
  result.polygons[0].vertices[0] = 1;
  result.polygons[0].vertices[1] = 2;
  result.polygons[0].vertices[2] = 2;
  result.polygons[0].vertices[3] = 3;
  result.polygons[0].vertices[4] = 3;
  result.polygons[0].vertices[5] = 1;
  result.polygons[1].vertices[0] = 7;
  result.polygons[1].vertices[1] = 6;
  result.polygons[1].vertices[2] = 6;
  result.polygons[1].vertices[3] = 5;
  result.polygons[1].vertices[4] = 5;
  result.polygons[1].vertices[5] = 7;
  result.polygons[2].vertices[0] = 4;
  result.polygons[2].vertices[1] = 5;
  result.polygons[2].vertices[2] = 5;
  result.polygons[2].vertices[3] = 1;
  result.polygons[2].vertices[4] = 1;
  result.polygons[2].vertices[5] = 4;
  result.polygons[3].vertices[0] = 5;
  result.polygons[3].vertices[1] = 6;
  result.polygons[3].vertices[2] = 6;
  result.polygons[3].vertices[3] = 2;
  result.polygons[3].vertices[4] = 2;
  result.polygons[3].vertices[5] = 5;
  result.polygons[4].vertices[0] = 2;
  result.polygons[4].vertices[1] = 6;
  result.polygons[4].vertices[2] = 6;
  result.polygons[4].vertices[3] = 7;
  result.polygons[4].vertices[4] = 7;
  result.polygons[4].vertices[5] = 2;
  result.polygons[5].vertices[0] = 0;
  result.polygons[5].vertices[1] = 3;
  result.polygons[5].vertices[2] = 3;
  result.polygons[5].vertices[3] = 7;
  result.polygons[5].vertices[4] = 7;
  result.polygons[5].vertices[5] = 0;
  result.polygons[6].vertices[0] = 0;
  result.polygons[6].vertices[1] = 1;
  result.polygons[6].vertices[2] = 1;
  result.polygons[6].vertices[3] = 3;
  result.polygons[6].vertices[4] = 3;
  result.polygons[6].vertices[5] = 0;
  result.polygons[7].vertices[0] = 4;
  result.polygons[7].vertices[1] = 7;
  result.polygons[7].vertices[2] = 7;
  result.polygons[7].vertices[3] = 5;
  result.polygons[7].vertices[4] = 5;
  result.polygons[7].vertices[5] = 4;
  result.polygons[8].vertices[0] = 0;
  result.polygons[8].vertices[1] = 4;
  result.polygons[8].vertices[2] = 4;
  result.polygons[8].vertices[3] = 1;
  result.polygons[8].vertices[4] = 1;
  result.polygons[8].vertices[5] = 0;
  result.polygons[9].vertices[0] = 1;
  result.polygons[9].vertices[1] = 5;
  result.polygons[9].vertices[2] = 5;
  result.polygons[9].vertices[3] = 2;
  result.polygons[9].vertices[4] = 2;
  result.polygons[9].vertices[5] = 1;
  result.polygons[10].vertices[0] = 3;
  result.polygons[10].vertices[1] = 2;
  result.polygons[10].vertices[2] = 2;
  result.polygons[10].vertices[3] = 7;
  result.polygons[10].vertices[4] = 7;
  result.polygons[10].vertices[5] = 3;
  result.polygons[11].vertices[0] = 4;
  result.polygons[11].vertices[1] = 0;
  result.polygons[11].vertices[2] = 0;
  result.polygons[11].vertices[3] = 7;
  result.polygons[11].vertices[4] = 7;
  result.polygons[11].vertices[5] = 4;

  ck_assert_int_eq(result.count_of_facets, objData.count_of_facets);
  ck_assert_int_eq(result.count_of_indices, objData.count_of_indices);
  ck_assert_int_eq(result.count_of_vertices, objData.count_of_vertices);

  // Compare matrices:
  ck_assert_int_eq(result.matrix_3d.columns, objData.matrix_3d.columns);
  ck_assert_int_eq(result.matrix_3d.rows, objData.matrix_3d.rows);
  for (unsigned int i = 0; i < result.matrix_3d.rows; i++) {
    for (unsigned int j = 0; j < result.matrix_3d.columns; j++) {
      ck_assert_double_eq_tol(result.matrix_3d.matrix[i][j],
                              objData.matrix_3d.matrix[i][j], EPS);
    }
  }

  // Compare polygons:
  for (int i = 0; i < result.count_of_facets; i++) {
    ck_assert_int_eq(result.polygons[i].number_of_vertices_in_facets,
                     objData.polygons[i].number_of_vertices_in_facets);
    for (unsigned int j = 0;
         j < result.polygons[i].number_of_vertices_in_facets * 2; j++) {
      ck_assert_int_eq(result.polygons[i].vertices[j],
                       objData.polygons[i].vertices[j]);
    }
  }

  remove_obj_info(&objData);
  remove_obj_info(&result);
}
END_TEST

START_TEST(test_2) {
  const char filename[20] = "./tests/cubr.obj";
  obj_info objData = (obj_info){0, 0, 0, {NULL, 0, 0}, NULL};
  int status = parse_obj_file(filename, &objData);
  ck_assert_int_eq(status, 1);
}
END_TEST

Suite *parser_suite(void) {
  Suite *s;
  TCase *tc_parser;

  s = suite_create("Parse input");

  tc_parser = tcase_create("Parse input");

  tcase_add_test(tc_parser, test_1);
  tcase_add_test(tc_parser, test_2);

  suite_add_tcase(s, tc_parser);

  return s;
}