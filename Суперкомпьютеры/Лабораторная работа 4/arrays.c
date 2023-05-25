#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define frand() ((double)rand() / (RAND_MAX + 1.0))

double **two_dimensional_array_alloc(size_t rows, size_t columns) {
  double **arr = (double **)malloc(rows * sizeof(double *) +
                                   rows * columns * sizeof(double));
  if (arr == NULL) {
    perror("malloc failed");
    exit(EXIT_FAILURE);
  }
  double *start = (double *)((char *)arr + rows * sizeof(double *));
  for (size_t i = 0; i < rows; i++) {
    arr[i] = start + i * columns;
  }
  return arr;
}

void two_dimensional_array_random(double **arr, size_t rows, size_t columns) {
  for (size_t i = 0; i < columns; i++) {
    for (size_t j = 0; j < rows; j++) {
      arr[i][j] = frand();
    }
  }
}
