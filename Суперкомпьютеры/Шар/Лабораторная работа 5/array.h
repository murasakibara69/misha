#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

double **random_symmetric_positive_definite_matrix_alloc(size_t n);

double **matrix_alloc(size_t nrows, size_t ncolumns);

double *random_vector_alloc(size_t n);

double *vector_alloc(size_t n);

#endif // ARRAY_H
