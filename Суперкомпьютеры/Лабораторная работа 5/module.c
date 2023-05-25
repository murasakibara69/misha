#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define drand() ((double_t)rand() / (RAND_MAX + 1.0))

void *Malloc(size_t size) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
    perror("malloc failed");
    exit(EXIT_FAILURE);
  }
  return ptr;
}

double_t **random_matrix_alloc(size_t nrows, size_t ncolumns) {
  double_t **matrix = (double_t **)Malloc(
      nrows * (sizeof(double_t *) + ncolumns * sizeof(double_t)));
  double_t *start = (double_t *)((char *)matrix + nrows * sizeof(double_t *));
  for (size_t i = 0; i < nrows; i++) {
    matrix[i] = start + i * ncolumns;
  }
  for (size_t i = 0; i < nrows; i++) {
    for (size_t j = 0; j < ncolumns; j++) {
      matrix[i][j] = drand();
    }
  }
  return matrix;
}

double_t *random_vector_alloc(size_t nrows) {
  double_t *vector = (double_t *)Malloc(nrows * sizeof(double_t));
  for (size_t i = 0; i < nrows; i++) {
    vector[i] = drand();
  }
  return vector;
}
