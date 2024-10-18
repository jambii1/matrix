#include "matrix.hpp"
#include <iostream>
#include <exception>

int main()
{
  size_t m = 0, n = 0;
  std::cin >> m >> n;
  if (!std::cin)
  {
    std::cerr << "Incorrect input\n";
    return 1;
  }
  int **table = nullptr;
  try
  {
    table = create(m, n);
  }
  catch (const std::bad_alloc &e)
  {
    std::cerr << "Out of memory\n";
    return 1;
  }

  read(table, m, n);
  if (!std::cin)
  {
    std::cerr << "Incorrect input\n";
    return 1;
  }
  write(table, m, n);

  clean(table, m);
}