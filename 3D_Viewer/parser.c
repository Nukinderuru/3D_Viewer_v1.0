#include "parser.h"

/* Считает общее количество вершин и полигонов в файле */
int count_vertices_and_facets(const char *filename, obj_info *data) {
  // Открываем файл:
  FILE *file;
  if ((file = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Couldn't open the.obj file\n");
    return 1;
  }
  // Считаем и записываем:
  char c = '\0';
  unsigned int count_vertices = 0, count_facets = 0;
  while ((c = fgetc(file)) != EOF) {
    if (c == 'f') {  // все полигоны (строки на "f")
      if ((c = fgetc(file)) == ' ') {
        count_facets++;
      }
    }
    if (c == 'v') {  // все вершины (строки на "v")
      if ((c = fgetc(file)) == ' ') {
        count_vertices++;
      }
    }
  }
  data->count_of_facets = count_facets;
  data->count_of_vertices = count_vertices;
  fclose(file);
  return 0;
}

/* Принимает на вход строку, начинающуюся с 'f',
  считает кол-во вершин в строке и записывает его в
  polygon_t[i]->numbers_of_vertices_in_facets; */
unsigned int count_vertices_in_a_facet(char *buf) {
  char str[255] = {0};
  unsigned int count = 0;
  char space = '\0';
  buf += 2;
  while (*buf && sscanf(buf, "%s", str)) {
    unsigned int length = strlen(str) + 1;
    buf += length;
    while (sscanf(buf, "%c", &space) && space == ' ') {
      length++;
      buf++;
    }
    if (length > 1) ++count;
    strcpy(str, "\0");
  }
  return count;
}

/* Выделяет память под массив polygon_t[i]->vertices размером в
polygon_t[i]->numbers_of_vertices_in_facets: */
void alloc_mem_for_vertices_in_a_facet(char *buf, unsigned int index,
                                       obj_info *data) {
  unsigned int f_amount = count_vertices_in_a_facet(buf);
  data->polygons[index].number_of_vertices_in_facets = f_amount;
  data->polygons[index].vertices = calloc(
      data->polygons[index].number_of_vertices_in_facets * 2, sizeof(double));
}

/* Принимает на вход строку, начинающуюся с 'f'
  и записывает вершины в polygon_t[i]->vertices */
void write_facet_vertices_to_array(char *buf, unsigned int index,
                                   obj_info *data) {
  char str[255] = {0};
  unsigned int count = 0, num = 0;
  char space = '\0';
  buf += 2;
  while (*buf && sscanf(buf, "%s", str)) {
    unsigned int length = strlen(str) + 1;
    buf += length;
    while (sscanf(buf, "%c", &space) && space == ' ') {
      length++;
      buf++;
    }
    if (length > 1) {
      if ((count > 0) && (count % 2 == 0)) {
        data->polygons[index].vertices[count] =
            data->polygons[index].vertices[count - 1];
        count++;
      }
      sscanf(str, "%u", &num);
      data->polygons[index].vertices[count] = num - 1;
      count++;
    }
    strcpy(str, "\0");
  }
  int last = data->polygons[index].number_of_vertices_in_facets * 2 - 1;
  data->polygons[index].vertices[last - 1] =
      data->polygons[index].vertices[count - 1];
  data->polygons[index].vertices[last] = data->polygons[index].vertices[0];
}

void count_indices(obj_info *data) {
  int count = 0;
  for (int i = 0; i < data->count_of_facets; i++) {
    for (unsigned int y = 0;
         y < data->polygons[i].number_of_vertices_in_facets * 2; y++) {
      count++;
    }
  }
  data->count_of_indices = count;
}

int create_matrix(int rows, int columns, matrix_t *result) {
  operation_result status = OK;
  if (rows < 1 || columns < 1)
    status = INCORRECT_MATRIX;
  else {
    *result = (matrix_t){NULL, 0, 0};
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
    }
    if (result->matrix == NULL) status = INCORRECT_MATRIX;
  }
  return status;
}

int parse_obj_file(const char *filename, obj_info *data) {
  //Считаем кол-во вершин и полигонов
  if ((count_vertices_and_facets(filename, data)) == 1) {
    fprintf(stderr, "Couldn't open the.obj file\n");
    return 1;
  }
  //Создаём матрицу для вершин, выделяем под неё память
  matrix_t vertices;
  int status = create_matrix(data->count_of_vertices, 3, &vertices);
  if (status) {
    fprintf(stderr, "Couldn't create a matrix for vertices\n");
    return 2;
  }
  //Выделяем память под массив полигонов
  data->polygons = calloc(data->count_of_facets, sizeof(polygon_t));
  // Снова открываем файл:
  FILE *file;
  if ((file = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Couldn't open the.obj file\n");
    return 1;
  }
  char str[100];
  char c = '\0';
  unsigned int v_count = 0, f_count = 0;
  while (fgets(str, 100, file)) {
    if (str[0] == 'f' && str[1] == ' ') {
      alloc_mem_for_vertices_in_a_facet(
          str, f_count, data);  // Выделяем память под массив вершин
      write_facet_vertices_to_array(
          str, f_count, data);  // Записываем значения вершин в массив
      f_count++;
    }
    if (str[0] == 'v' && str[1] == ' ') {  //Записываем вершины в matrix_t
      sscanf(str, "%c %lf %lf %lf", &c, &vertices.matrix[v_count][0],
             &vertices.matrix[v_count][1], &vertices.matrix[v_count][2]);
      v_count++;
    }
  }
  data->matrix_3d = vertices;
  count_indices(data);
  fclose(file);
  return 0;
}

void remove_matrix(matrix_t *A) {
  if (A != NULL) {
    for (unsigned int i = 0; i < A->rows; i++) free(A->matrix[i]);
    free(A->matrix);
    A->rows = 0;
    A->columns = 0;
    A->matrix = NULL;
  }
}

void remove_obj_info(obj_info *data) {
  if (data->matrix_3d.matrix != NULL) remove_matrix(&data->matrix_3d);
  if (data->polygons != NULL) {
    for (int i = 0; i < data->count_of_facets; i++) {
      free(data->polygons[i].vertices);
      data->polygons[i].number_of_vertices_in_facets = 0;
    }
  }
  free(data->polygons);
  data->count_of_facets = 0;
  data->count_of_vertices = 0;
  data = NULL;
}
