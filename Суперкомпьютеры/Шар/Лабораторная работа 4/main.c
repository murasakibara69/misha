#include "arrays.h"
#include <omp.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define N 15000

int main() {
  omp_set_dynamic(0);

  double **A = matrix_alloc(N, N);
  matrix_random(A, N, N);
  double **B = matrix_alloc(N, N);
  matrix_random(B, N, N);
  double **C = matrix_alloc(N, N);

  double start_time = omp_get_wtime();
#pragma omp parallel for collapse(2) shared(A, B, C)
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      C[i][j] = A[i][j] + B[i][j];
    }
  }
  double end_time = omp_get_wtime();

  free(A);
  free(B);
  free(C);

  printf("Time: %f seconds\n", end_time - start_time);

  return EXIT_SUCCESS;
}
