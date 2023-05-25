#ifndef ARRAYS_H
#define ARRAYS_H

#include <stddef.h>

double **matrix_alloc(size_t rows, size_t columns);
void matrix_random(double **arr, size_t rows, size_t columns);

#endif // !ARRAYS_H
