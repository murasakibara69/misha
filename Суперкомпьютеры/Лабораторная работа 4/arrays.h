#ifndef ARRAYS_H
#define ARRAYS_H

#include <stddef.h>

double **two_dimensional_array_alloc(size_t rows, size_t columns);
void two_dimensional_array_random(double **arr, size_t rows, size_t columns);

#endif // !ARRAYS_H
