#include "matrix.hpp"
#include <iostream>
#include <exception>

int **create(size_t m, size_t n)
{
  int **table = new int *[m];
  size_t created = 0;
  try
  {
    for (; created < m; ++created)
    {
      table[created] = new int[n];
    }
  }
  catch (const std::bad_alloc &e)
  {
    clean(table, created);
    throw;
  }
  return table;
}

void read(int **table, size_t m, size_t n)
{
  for (size_t i = 0; i < m; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      std::cin >> table[i][j];
    }
  }
}

void write(const int * const *table, size_t m, size_t n)
{
  for (size_t i = 0; i < m; ++i)
  {
    std::cout << table[i][0];
    for (size_t j = 1; j < n; ++j)
    {
      std::cout << ' ' << table[i][j];
    }
    std::cout << '\n';
  }
}

void clean(int **table, size_t m)
{
  for (size_t i = 0; i < m; ++i)
  {
    delete[] table[i];
  }
  delete[] table;
}