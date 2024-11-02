#include "matrix.hpp"
#include <iostream>
#include <exception>

void clear(int ** matrix, size_t nRows)
{
  for (size_t i = 0; i < nRows; ++i)
  {
    delete[] matrix[i];
  }
  delete[] matrix;
}

int ** alloc(size_t nRows, size_t nColumns)
{
  int ** matrix = new int * [nRows];
  size_t created = 0;
  try
  {
    for (; created < nRows; ++created)
    {
      matrix[created] = new int[nColumns];
    }
  }
  catch (const std::bad_alloc & e)
  {
    clear(matrix, created);
    throw;
  }
  return matrix;
}

void input(std::istream & in, int ** matrix, size_t nRows, size_t nColumns)
{
  for (size_t i = 0; i < nRows; ++i)
  {
    for (size_t j = 0; j < nColumns; ++j)
    {
      in >> matrix[i][j];
    }
  }
}

void print(std::ostream & out, int * const * matrix, size_t nRows, size_t nColumns)
{
  for (size_t i = 0; i < nRows; ++i)
  {
    out << matrix[i][0];
    for (size_t j = 1; j < nColumns; ++j)
    {
      out << ' ' << matrix[i][j];
    }
    out << '\n';
  }
}

Matrix::Matrix(size_t rowsNumber, size_t nColumns):
  matrix_(::alloc(rowsNumber, nColumns)),
  nRows_(rowsNumber),
  nColumns_(nColumns)
{}

Matrix::Matrix(const Matrix & other):
  matrix_(other.matrix_),
  nRows_(other.nRows_),
  nColumns_(other.nColumns_)
{
  for (size_t i = 0; i < nRows_; ++i)
  {
    for (size_t j = 0; j < nColumns_; ++j)
    {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

Matrix::~Matrix()
{
  ::clear(matrix_, nRows_);
}

void Matrix::input(std::istream & in)
{
  ::input(in, matrix_, nRows_, nColumns_);
}

void Matrix::print(std::ostream & out)
{
  ::print(out, matrix_, nRows_, nColumns_);
}

size_t Matrix::getRowsNumber() const
{
  return nRows_;
}

size_t Matrix::getColumnsNumber() const
{
  return nColumns_;
}

void Matrix::fill(int n)
{
  for (size_t i = 0; i < nRows_; ++i)
  {
    for (size_t j = 0; j < nColumns_; ++j)
    {
      matrix_[i][j] = n;
    }
  }
}

void Matrix::resize(size_t newNRows, size_t newNColumns)
{
  if ((newNRows != nRows_) || (newNColumns != nColumns_))
  {
    Matrix resizedMatrix(newNRows, newNColumns);
    resizedMatrix.fill(0);
    size_t rowBorder = newNRows > nRows_ ? nRows_ : newNRows;
    size_t columnBorder = newNColumns > nColumns_ ? nColumns_ : newNColumns;

    for (size_t i = 0; i < rowBorder; ++i)
    {
      for (size_t j = 0; j < columnBorder; ++j)
      {
        resizedMatrix.matrix_[i][j] = matrix_[i][j];
      }
    }

    ::clear(matrix_, nRows_);
    matrix_ = resizedMatrix.matrix_;
    nRows_ = newNRows;
    nColumns_ = newNColumns;
  }
}
