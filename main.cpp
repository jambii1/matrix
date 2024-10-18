#include <iostream>
#include <cstddef>
#include <exception>

int **create(size_t m, size_t n);
void read(int **table, size_t m, size_t n);
void write(const int * const *table, size_t m, size_t n);
void clean(int **table, size_t m);

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

  clean(table, m);
}

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

void clean(int **table, size_t m)
{
  for (size_t i = 0; i < m; ++i)
  {
    delete[] table[i];
  }
  delete[] table;
}