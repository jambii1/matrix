#include <iostream>
#include <exception>
#include "matrix.hpp"

int main()
{
  size_t nRows = 0, nColumns = 0;
  if (!(std::cin >> nRows >> nColumns))
  {
    std::cerr << "Incorrect input\n";
    return 1;
  }
  Matrix table(nRows, nColumns);

  table.input(std::cin);
  if (!std::cin)
  {
    std::cerr << "Incorrect input\n";
    return 1;
  }

  table.print(std::cout);
  table.resize(2, 2);
  table.print(std::cout);
}
