#include <exception>
#include <iostream>
#include "matrix.hpp"

int main()
{
  math::Matrix matrix1;
  try {
    matrix1 = math::Matrix(3, 3, 0);
  } catch (const std::bad_alloc& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  matrix1.print(std::cout);
  std::cout << '\n';

  math::Matrix matrix2;
  try {
    matrix2 = matrix1;
  } catch (const std::bad_alloc& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  matrix2.print(std::cout);
  std::cout << '\n';

  math::Matrix matrix3;
  try {
    matrix3 = math::Matrix(2, 2, 1);
    matrix1 = matrix3;
  } catch (const std::bad_alloc& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  matrix1.print(std::cout);
}
