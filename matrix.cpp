#include "matrix.hpp"
#include <iostream>
#include <exception>

void clear(int **matrix, size_t rowsNumber)
{
  for (size_t i = 0; i < rowsNumber; ++i)
  {
    delete[] matrix[i];
  }
  delete[] matrix;
}

int **alloc(size_t rowsNumber, size_t columnsNumber)
{
  int **matrix = new int *[rowsNumber];
  size_t created = 0;
  try
  {
    for (; created < rowsNumber; ++created)
    {
      matrix[created] = new int[columnsNumber];
    }
  }
  catch (const std::bad_alloc &e)
  {
    clear(matrix, created);
    throw;
  }
  return matrix;
}

void input(int **matrix, size_t rowsNumber, size_t columnsNumber)
{
  for (size_t i = 0; i < rowsNumber; ++i)
  {
    for (size_t j = 0; j < columnsNumber; ++j)
    {
      std::cin >> matrix[i][j];
    }
  }
}

void print(const int * const *matrix, size_t rowsNumber, size_t columnsNumber)
{
  for (size_t i = 0; i < rowsNumber; ++i)
  {
    std::cout << matrix[i][0];
    for (size_t j = 1; j < columnsNumber; ++j)
    {
      std::cout << ' ' << matrix[i][j];
    }
    std::cout << '\n';
  }
}

Matrix::Matrix(size_t rowsNumber, size_t columnsNumber):
  matrix_(::alloc(rowsNumber, columnsNumber)),
  rowsNumber_(rowsNumber),
  columnsNumber_(columnsNumber)
{}

Matrix::Matrix(const Matrix &other):
  matrix_(other.matrix_),
  rowsNumber_(other.rowsNumber_),
  columnsNumber_(other.columnsNumber_)
{
  for (size_t i = 0; i < rowsNumber_; ++i)
  {
    for (size_t j = 0; j < columnsNumber_; ++j)
    {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

Matrix::~Matrix()
{
  ::clear(matrix_, rowsNumber_);
}

void Matrix::input()
{
  ::input(matrix_, rowsNumber_, columnsNumber_);
}

void Matrix::print()
{
  ::print(matrix_, rowsNumber_, columnsNumber_);
}

size_t Matrix::getRowsNumber() const
{
  return rowsNumber_;
}

size_t Matrix::getColumnsNumber() const
{
  return columnsNumber_;
}

void Matrix::fill(int n)
{
  for (size_t i = 0; i < rowsNumber_; ++i)
  {
    for (size_t j = 0; j < columnsNumber_; ++j)
    {
      matrix_[i][j] = n;
    }
  }
}

void Matrix::resize(size_t newRowsNumber, size_t newColumnsNumber)
{
  if ((newRowsNumber != rowsNumber_) || (newColumnsNumber != columnsNumber_))
  {
    Matrix resizedMatrix(newRowsNumber, newColumnsNumber);
    size_t rowBorder = newRowsNumber > rowsNumber_ ? rowsNumber_ : newRowsNumber;
    size_t columnBorder = newColumnsNumber > columnsNumber_ ? columnsNumber_ : newColumnsNumber;

    for (size_t i = 0; i < rowBorder; ++i)
    {
      for (size_t j = 0; j < columnBorder; ++j)
      {
        resizedMatrix.matrix_[i][j] = matrix_[i][j];
      }
    }

    ::clear(matrix_, rowsNumber_);
    matrix_ = resizedMatrix.matrix_;
    rowsNumber_ = newRowsNumber;
    columnsNumber_ = newColumnsNumber;
  }
}
