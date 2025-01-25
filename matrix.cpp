#include "matrix.hpp"
#include <algorithm>
#include <exception>
#include <cmath>

void math::clear(int** matrix, std::size_t rows) noexcept
{
  if (matrix != nullptr) {
    for (std::size_t i = 0; i < rows; ++i) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }
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

void math::input(std::istream& in, int** matrix, std::size_t rows, std::size_t cols) noexcept
{
  for (std::size_t i = 0; i < rows; ++i) {
    for (std::size_t j = 0; j < cols; ++j) {
      in >> matrix[i][j];
    }
  }
}

void math::print(std::ostream& out, const int* const* matrix, std::size_t rows, std::size_t cols) noexcept
{
  for (std::size_t i = 0; i < rows; ++i) {
    out << matrix[i][0];
    for (std::size_t j = 1; j < cols; ++j) {
      out << ' ' << matrix[i][j];
    }
    out << '\n';
  }
}

void math::copy(const int* const* data, std::size_t rows, std::size_t cols, int* const* matrix) noexcept
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

math::Matrix::Matrix(Matrix&& rhs) noexcept:
  data_(rhs.data_),
  rows_(rhs.rows_),
  cols_(rhs.cols_)
{
  rhs.data_ = nullptr;
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

math::Matrix& math::Matrix::operator=(const Matrix& rhs)
{
  int** new_data = alloc(rhs.rows_, rhs.cols_);
  copy(rhs.data_, rhs.rows_, rhs.cols_, new_data);
  clear(data_, rows_);
  data_ = new_data;
  rows_ = rhs.rows_;
  cols_ = rhs.cols_;
  return *this;
}

math::Matrix& math::Matrix::operator=(Matrix&& rhs) noexcept
{
  clear(data_, rows_);
  data_ = rhs.data_;
  rhs.data_ = nullptr;
  rows_ = rhs.rows_;
  cols_ = rhs.cols_;
  return *this;
}

math::Matrix& math::Matrix::operator+() noexcept
{
  return *this;
}

math::Matrix math::Matrix::operator+(const Matrix& rhs) const
{
  if (rows_ != rhs.rows_ || cols_ != rhs.cols_) {
    throw std::logic_error("incorrect matrix size");
  }
  Matrix result(rows_, cols_, 0);
  for (std::size_t i = 0; i < rows_; ++i) {
    for (std::size_t j = 0; j < cols_; ++j) {
      result.data_[i][j] = data_[i][j] + rhs.data_[i][j];
    }
  }
  return result;
}

math::Matrix& math::Matrix::operator+=(const Matrix& rhs)
{
  if (rows_ != rhs.rows_ || cols_ != rhs.cols_) {
    throw std::logic_error("incorrect matrix size");
  }
  for (std::size_t i = 0; i < rows_; ++i) {
    for (std::size_t j = 0; j < cols_; ++j) {
      data_[i][j] += rhs.data_[i][j];
    }
  }
  return *this;
}

math::Matrix& math::Matrix::operator-() noexcept
{
  for (std::size_t i = 0; i < rows_; ++i) {
    for (std::size_t j = 0; j < cols_; ++j) {
      data_[i][j] = -data_[i][j];
    }
  }
  return *this;
}

math::Matrix math::Matrix::operator-(const Matrix& rhs) const
{
  if (rows_ != rhs.rows_ || cols_ != rhs.cols_) {
    throw std::logic_error("incorrect matrix size");
  }
  Matrix result(rows_, cols_, 0);
  for (std::size_t i = 0; i < rows_; ++i) {
    for (std::size_t j = 0; j < cols_; ++j) {
      result.data_[i][j] = data_[i][j] - rhs.data_[i][j];
    }
  }
  return result;
}

math::Matrix& math::Matrix::operator-=(const Matrix& rhs)
{
  if (rows_ != rhs.rows_ || cols_ != rhs.cols_) {
    throw std::logic_error("incorrect matrix size");
  }
  for (std::size_t i = 0; i < rows_; ++i) {
    for (std::size_t j = 0; j < cols_; ++j) {
      data_[i][j] -= rhs.data_[i][j];
    }
  }
  return *this;
}

math::Matrix math::Matrix::operator*(const Matrix& rhs) const
{
  if (cols_ != rhs.rows_) {
    throw std::logic_error("incorrect matrix size");
  }
  Matrix result(rows_, rhs.cols_, 0);
  for (std::size_t i = 0; i < rows_; ++i) {
    for (std::size_t j = 0; j < rhs.cols_; ++j) {
      for (std::size_t k = 0; k < cols_; ++k) {
        result.data_[i][j] += data_[i][k] * rhs.data_[k][j];
      }
    }
  }
  return result;
}

math::Matrix& math::Matrix::operator*=(const Matrix& rhs)
{
  if (cols_ != rhs.rows_) {
    throw std::logic_error("incorrect matrix size");
  }
  Matrix result(rows_, rhs.cols_, 0);
  for (std::size_t i = 0; i < rows_; ++i) {
    for (std::size_t j = 0; j < rhs.cols_; ++j) {
      for (std::size_t k = 0; k < cols_; ++k) {
        result.data_[i][j] += data_[i][k] * rhs.data_[k][j];
      }
    }
  }
  *this = result;
  return *this;
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

void math::Matrix::transpose()
{
  Matrix transposed(cols_, rows_, 0);
  for (std::size_t i = 0; i < cols_; ++i) {
    for (std::size_t j = 0; j < rows_; ++j) {
      transposed.data_[i][j] = data_[j][i];
    }
  }
  *this = transposed;
}

int math::Matrix::get_determinant()
{
  if (rows_ != cols_) {
    throw std::logic_error("incorrect matrix size");
  }
  if (rows_ == 1) {
    return data_[0][0];
  }
  if (rows_ == 2) {
    return data_[0][0] * data_[1][1] - data_[0][1] * data_[1][0];
  }
  Matrix sub_matrix(rows_ - 1, cols_ - 1, 0);
  int determinant = 0;
  for (std::size_t i = 0; i < rows_; ++i) {
    std::size_t subi = 0;
    for (std::size_t j = 1; j < rows_; ++j) {
      std::size_t subj = 0;
      for (std::size_t k = 0; k < rows_; ++k) {
        if (k == i) {
          continue;
        }
        sub_matrix.data_[subi][subj++] = data_[i][j];
      }
      ++subi;
    }
    determinant += std::pow(-1, i) * data_[0][i] * sub_matrix.get_determinant();
  }
  return determinant;
}
