#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>

int **create(size_t m, size_t n);
void read(int **table, size_t m, size_t n);
void write(const int * const *table, size_t m, size_t n);
void clean(int **table, size_t m);

#endif