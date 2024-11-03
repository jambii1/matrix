#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <iostream>

void clear(int **matrix, size_t nRows);
int **alloc(size_t nRows, size_t nColumns);
void input(std::istream &in, int **matrix, size_t nRows, size_t nColumns);
void print(std::ostream &out, int *const *matrix, size_t nRows, size_t nColumns);

struct Matrix
{
  explicit Matrix(size_t nRows, size_t nColumns);
  Matrix(const Matrix &other);
  ~Matrix();

  void input(std::istream &in);
  void print(std::ostream &out);
  size_t getRowsNumber() const;
  size_t getColumnsNumber() const;
  void fill(int n);
  void resize(size_t newNRows, size_t newNColumns);

private:
  int **matrix_;
  size_t nRows_, nColumns_;
};

#endif
