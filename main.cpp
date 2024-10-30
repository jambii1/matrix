#include "matrix.hpp"
#include <iostream>
#include <exception>

int main()
{
  size_t rowsNumber = 0, columnsNumber = 0;
  if (!(std::cin >> rowsNumber >> columnsNumber))
  {
    std::cerr << "Incorrect input\n";
    return 1;
  }
  Matrix table(rowsNumber, columnsNumber);

  table.input();
  if (!std::cin)
  {
    std::cerr << "Incorrect input\n";
    return 1;
  }

  table.print();
}
