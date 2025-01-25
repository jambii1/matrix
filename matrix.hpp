#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>

namespace math
{
  void clear(int** matrix, std::size_t rows) noexcept;
  int** alloc(std::size_t rows, std::size_t cols);
  void input(std::istream& in, int** matrix, std::size_t rows, std::size_t cols) noexcept;
  void print(std::ostream& out, const int* const* matrix, std::size_t rows, std::size_t cols) noexcept;
  void copy(const int* const* data, std::size_t rows, std::size_t cols, int* const* matrix) noexcept;

  class Matrix
  {
  public:
    Matrix() noexcept;
    Matrix(const Matrix& rhs);
    Matrix(Matrix&& rhs) noexcept;
    Matrix(std::size_t rows, std::size_t cols);
    Matrix(std::size_t rows, std::size_t cols, int value);
    Matrix(std::size_t rows, std::size_t cols, const int* values);
    ~Matrix();

    Matrix& operator=(const Matrix& rhs);
    Matrix& operator=(Matrix&& rhs) noexcept;
    Matrix& operator+() noexcept;
    Matrix operator+(const Matrix& rhs) const;
    Matrix& operator+=(const Matrix& rhs);
    Matrix& operator-() noexcept;
    Matrix operator-(const Matrix& rhs) const;
    Matrix& operator-=(const Matrix& rhs);
    Matrix operator*(const Matrix& rhs) const;
    Matrix& operator*=(const Matrix& rhs);

    void input(std::istream& in) noexcept;
    void print(std::ostream& out) noexcept;
    std::size_t get_rows_number() const noexcept;
    std::size_t get_columns_number() const noexcept;
    void fill(int value) noexcept;
    void fill(const int* values) noexcept;
    void swap(Matrix& rhs) noexcept;
    void resize(std::size_t new_rows, std::size_t new_cols);
    void transpose();
    int get_determinant();

  private:
    int** data_;
    std::size_t rows_, cols_;
  };
}

#endif
