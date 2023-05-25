#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define frand() ((double)rand() / (RAND_MAX + 1.0))

double **matrix_alloc(size_t rows, size_t columns) {
  double **matrix = (double **)malloc(rows * sizeof(double *) +
                                      rows * columns * sizeof(double));
  if (matrix == NULL) {
    perror("malloc failed");
    exit(EXIT_FAILURE);
  }
  double *start = (double *)((char *)matrix + rows * sizeof(double *));
  for (size_t i = 0; i < rows; i++) {
    matrix[i] = start + i * columns;
  }
  return matrix;
}

void matrix_random(double **matrix, size_t rows, size_t columns) {
  for (size_t i = 0; i < columns; i++) {
    for (size_t j = 0; j < rows; j++) {
      matrix[i][j] = frand();
    }
  }
}
