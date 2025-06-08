#include <algorithm>
#include <array>
#include <iostream>

/**
 * Use abbreviated template syntaxe
 */

void print(auto& array)
{
  // Change based-for loop
  for(auto& element : array)
  {
    std::cout << element << " ";
  }
  std::cout << "\n";
}

int main()
{
  std::array<int,5> my_array = {32,43,16,22,21};
  print(my_array);
  /**
   * Sort the array from the beginning to the end of the array
   */
  // std::sort(my_array.begin(), my_array.end());
  // other way is to used std::ranges
  std::ranges::sort(my_array);

  print(my_array);
  return 0;
}