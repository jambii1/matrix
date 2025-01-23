#include "matrix.hpp"
#include <algorithm>
#include <exception>

void math::clear(int** matrix, std::size_t rows)
{
  for (std::size_t i = 0; i < rows; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

int** math::alloc(std::size_t rows, std::size_t cols)
{
  int** matrix = new int*[rows];
  std::size_t created = 0;
  try {
    for (; created < rows; ++created) {
      matrix[created] = new int[cols];
    }
  } catch (const std::bad_alloc& e) {
    clear(matrix, created);
    throw;
  }
  return matrix;
}

void math::input(std::istream& in, int** matrix, std::size_t rows, std::size_t cols)
{
  for (std::size_t i = 0; i < rows; ++i) {
    for (std::size_t j = 0; j < cols; ++j) {
      in >> matrix[i][j];
    }
  }
}

void math::print(std::ostream& out, const int* const* matrix, std::size_t rows, std::size_t cols)
{
  for (std::size_t i = 0; i < rows; ++i) {
    out << matrix[i][0];
    for (std::size_t j = 1; j < cols; ++j) {
      out << ' ' << matrix[i][j];
    }
    out << '\n';
  }
}

void math::copy(const int* const* data, std::size_t rows, std::size_t cols, int* const* matrix)
{
  for (std::size_t i = 0; i < rows; ++i) {
    for (std::size_t j = 0; j < cols; ++j) {
      matrix[i][j] = data[i][j];
    }
  }
}

math::Matrix::Matrix() noexcept:
  data_(nullptr),
  rows_(0),
  cols_(0)
{}

math::Matrix::Matrix(const Matrix& rhs):
  Matrix(rhs.rows_, rhs.cols_)
{
  copy(rhs.data_, rows_, cols_, data_);
}

math::Matrix::Matrix(std::size_t rows, std::size_t cols):
  data_(alloc(rows, cols)),
  rows_(rows),
  cols_(cols)
{}

math::Matrix::Matrix(std::size_t rows, std::size_t cols, int value):
  Matrix(rows, cols)
{
  fill(value);
}

math::Matrix::Matrix(std::size_t rows, std::size_t cols, const int* values):
  Matrix(rows, cols)
{
  fill(values);
}

math::Matrix::~Matrix()
{
  clear(data_, rows_);
}

void math::Matrix::input(std::istream& in) noexcept
{
  math::input(in, data_, rows_, cols_);
}

void math::Matrix::print(std::ostream& out) noexcept
{
  math::print(out, data_, rows_, cols_);
}

std::size_t math::Matrix::get_rows_number() const noexcept
{
  return rows_;
}

std::size_t math::Matrix::get_columns_number() const noexcept
{
  return cols_;
}

void math::Matrix::fill(int value) noexcept
{
  for (std::size_t i = 0; i < rows_; ++i) {
    for (std::size_t j = 0; j < cols_; ++j) {
      data_[i][j] = value;
    }
  }
}

void math::Matrix::fill(const int* values) noexcept
{
  for (std::size_t i = 0; i < rows_; ++i) {
    for (std::size_t j = 0; j < cols_; ++j) {
      data_[i][j] = values[i * cols_ + j];
    }
  }
}

void math::Matrix::swap(Matrix& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(rows_, rhs.rows_);
  std::swap(cols_, rhs.cols_);
}

void math::Matrix::resize(std::size_t new_rows, std::size_t new_cols)
{
  if ((new_rows != rows_) || (new_cols != cols_)) {
    Matrix resized_matrix(new_rows, new_cols, 0);
    std::size_t row_border = new_rows > rows_ ? rows_ : new_rows;
    std::size_t column_border = new_cols > cols_ ? cols_ : new_cols;

    for (std::size_t i = 0; i < row_border; ++i) {
      for (std::size_t j = 0; j < column_border; ++j) {
        resized_matrix.data_[i][j] = data_[i][j];
      }
    }

    swap(resized_matrix);
  }
}
