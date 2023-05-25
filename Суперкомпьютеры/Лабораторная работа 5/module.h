#ifndef MODULE_H
#define MODULE_H

#include <math.h>
#include <stddef.h>

double_t **random_matrix_alloc(size_t nrows, size_t ncolumns);

double_t *random_vector_alloc(size_t nrows);

#endif // !MODULE_H
