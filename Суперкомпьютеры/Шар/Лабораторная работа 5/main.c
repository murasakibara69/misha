#include "array.h"
#include <math.h>
#include <omp.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define N 15000
#define OMEGA 1.7
#define EPS 0.000001

void init_residual(double *R, double *C, double *X, size_t n);
double calculate_resiadual(double R, double *P, double *X, size_t n);

int main() {
  omp_set_dynamic(0);
#pragma omp declare reduction(                                                 \
    maxfabs:double_t                                                           \
    : omp_out = fabs(omp_in) > omp_out ? fabs(omp_in) : omp_out)               \
    initializer(omp_priv = 0.0)

  double **A = random_symmetric_positive_definite_matrix_alloc(N);
  double *B = random_vector_alloc(N);
  // for (size_t i = 0; i < N; i++) {
  //   for (size_t j = 0; j < N; j++) {
  //     printf("%f\t", A[i][j]);
  //   }
  //   printf("%f\n", B[i]);
  // }

  double start_time = omp_get_wtime();

  double **P = matrix_alloc(N, N);
  double *C = vector_alloc(N);
#pragma omp parallel shared(A, B, P, C)
  {
#pragma omp for collapse(2) nowait
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < N; j++) {
        if (i == j) {
          P[i][j] = 0.0;
        } else {
          P[i][j] = -A[i][j] / A[i][i];
        }
      }
    }
#pragma omp for
    for (size_t i = 0; i < N; i++) {
      C[i] = B[i] / A[i][i];
    }
  }
  free(A);
  free(B);

  double *R = vector_alloc(N);
  double *X = vector_alloc(N);
#pragma omp parallel for shared(X)
  for (size_t i = 0; i < N; i++) {
    X[i] = 0.0;
  }
  double abs_max_residual;
  do {
#pragma omp parallel shared(R, C, X)
    { init_residual(R, C, X, N); }
    for (size_t i = 0; i < N; i++) {
#pragma omp parallel for reduction(+ : R[i]) shared(i, P, X)
      for (size_t j = 0; j < N; j++) {
        R[i] += P[i][j] * X[j];
      }
      X[i] += OMEGA * R[i];
    }
#pragma omp parallel shared(R, C, X)
    { init_residual(R, C, X, N); }
    for (size_t i = N - 1; i < SIZE_MAX; i--) {
#pragma omp parallel for reduction(+ : R[i]) shared(i, P, X)
      for (size_t j = 0; j < N; j++) {
        R[i] += P[i][j] * X[j];
      }
      X[i] += OMEGA * R[i];
    }
    abs_max_residual = 0.0;
#pragma omp parallel for reduction(maxfabs : abs_max_residual) shared(R)
    for (size_t i = 0; i < N; i++) {
      if (fabs(R[i]) > abs_max_residual) {
        abs_max_residual = fabs(R[i]);
      }
    }
  } while (abs_max_residual >= EPS);

  double end_time = omp_get_wtime();
  printf("Time: %f seconds\n", end_time - start_time);

  free(P);
  free(C);
  free(R);
  // for (size_t i = 0; i < N; i++) {
  //   printf("%f\t", X[i]);
  // }
  free(X);

  return 0;
}

void init_residual(double *R, double *C, double *X, size_t n) {
#pragma omp for
  for (size_t i = 0; i < n; i++) {
    R[i] = C[i] - X[i];
  }
}
