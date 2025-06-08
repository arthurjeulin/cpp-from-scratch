#include <iostream>
#include <span>
#include <vector>

/**
 * What we can do is use a reference of vector
 * @brief print a subset of int vector
 */
void print_subvector(const std::vector<int>& vector, int begin, int end)
{

}

/**
 * We just want a subset of this vector
 */

void print_subvector(std::span<int> span)
{
  for(const auto& value: span)
  {
    std::cout << value << " ";
  }
  std::cout << "\n";
}

int main()
{
  std::vector<int> my_vector = {1,2,3,4,5};
  /**
   * Create a span from beginning +1 of my_vector and three elements
   */
  print_subvector(std::span(my_vector.begin()+1 ,3));

  return 0;
}