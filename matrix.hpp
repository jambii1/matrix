#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>

void clear(int **matrix, size_t rowsNumber);
int **alloc(size_t rowsNumber, size_t columnsNumber);
void input(int **matrix, size_t rowsNumber, size_t columnsNumber);
void print(const int * const *matrix, size_t rowsNumber, size_t columnsNumber);


struct Matrix
{
  explicit Matrix(size_t rowsNumber, size_t columnsNumber);
  Matrix(const Matrix &other);
  ~Matrix();

  void input();
  void print();
  size_t getRowsNumber() const;
  size_t getColumnsNumber() const;
  void fill(int n);
  void resize(size_t newRowsNumber, size_t newColumnsNumber);

private:
  int **matrix_;
  size_t rowsNumber_, columnsNumber_;
};

#endif
