#include "module.h"
#include <math.h>
#include <omp.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define N 2000

int main(void) {
  omp_set_dynamic(0);
  double_t **A = random_matrix_alloc(N, N);
  double_t *B = random_vector_alloc(N);
  double_t start_time = omp_get_wtime();
  for (size_t i = 0; i < N - 1; i++) {
#pragma omp parallel default(none) shared(A, B, i)
    {
#pragma omp for nowait
      for (size_t j = i + 1; j < N; j++) {
        A[i][j] /= A[i][i];
      }
#pragma omp single
      B[i] /= A[i][i];
#pragma omp single
      A[i][i] = 1.0;
#pragma omp for collapse(2) nowait
      for (size_t k = i + 1; k < N; k++) {
        for (size_t j = i + 1; j < N; j++) {
          A[k][j] -= A[k][i] * A[i][j];
        }
      }
#pragma omp for
      for (size_t k = i + 1; k < N; k++) {
        B[k] -= B[i] * A[k][i];
      }
#pragma omp for
      for (size_t k = i + 1; k < N; k++) {
        A[k][i] = 0.0;
      }
    }
  }
  B[N - 1] /= A[N - 1][N - 1];
  A[N - 1][N - 1] = 1.0;
  for (size_t i = N - 1; i > 0; i--) {
#pragma omp parallel for shared(A, B, i)
    for (size_t k = i - 1; k < SIZE_MAX; k--) {
      B[k] -= B[i] * A[k][i];
    }
  }
  double_t end_time = omp_get_wtime();
  printf("Time = %lf seconds.\n", end_time - start_time);
  free(A);
  free(B);

  return EXIT_SUCCESS;
}
