#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define MIN -100

double **matrix_alloc(size_t nrows, size_t ncolumns) {
  double **matrix =
      (double **)malloc(nrows * (sizeof(double *) + ncolumns * sizeof(double)));
  if (matrix == NULL) {
    perror("Matrix malloc failed");
    exit(EXIT_FAILURE);
  }
  double *start = (double *)((char *)matrix + nrows * sizeof(double *));
  for (size_t i = 0; i < nrows; i++) {
    matrix[i] = start + i * ncolumns;
  }
  return matrix;
}

double **random_symmetric_positive_definite_matrix_alloc(size_t n) {
  double **matrix = matrix_alloc(n, n);
  double **temp_matrix = matrix_alloc(n, n);
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      temp_matrix[i][j] = (double)(MIN + rand() % (MAX - MIN + 1));
    }
  }
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      matrix[i][j] = (temp_matrix[i][j] + temp_matrix[j][i]) / 2.0;
    }
  }
  free(temp_matrix);
  return matrix;
}

double *vector_alloc(size_t n) {
  double *vector = (double *)malloc(n * sizeof(double));
  if (vector == NULL) {
    perror("Vector malloc failed");
    exit(EXIT_FAILURE);
  }
  return vector;
}

double *random_vector_alloc(size_t n) {
  double *vector = vector_alloc(n);
  for (size_t i = 0; i < n; i++) {
    vector[i] = (double)(MIN + rand() % (MAX - MIN + 1));
  }
  return vector;
}
