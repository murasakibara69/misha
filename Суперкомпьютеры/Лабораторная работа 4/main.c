#include "arrays.h"
#include <math.h>
#include <omp.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define N 16
#define EPS 0.000001

int main() {
  size_t num_threads;
  printf("Enter number of threads: ");
  scanf("%zd", &num_threads);
  omp_set_num_threads(num_threads);

  double **A = two_dimensional_array_alloc(N, N);
  two_dimensional_array_random(A, N, N);
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      if (i == j) {
        A[i][j] = 1.0;
      } else {
        A[i][j] = 0.0;
      }
    }
  }

  size_t num_zeros = 0;

  double start_time = omp_get_wtime();
#pragma omp parallel for collapse(2) shared(A) reduction(+ : num_zeros)
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      if (fabs(A[i][j]) <= EPS) {
        num_zeros++;
      }
    }
  }
  double end_time = omp_get_wtime();

  free(A);

  double sparsity = num_zeros / pow(N, 2.0);

  printf("Time: %f seconds\n", end_time - start_time);
  printf("Number of zeros: %zd\n", num_zeros);
  printf("Sparsity: %f\n", sparsity);

  return 0;
}
