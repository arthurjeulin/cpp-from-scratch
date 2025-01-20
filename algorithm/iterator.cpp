#include <array>
#include <iostream>

int main()
{
  std::array<int,5> my_array = { 1, 2, 3, 4,5};
  /**
   * iterate value from the array
   * c-style for loop using iterator
   */
  for(auto itr = my_array.begin(); itr < my_array.end();++itr)
  {
    std::cout << *itr << ' ';
  }
  std::cout << "\n";
  /**
   * iterate through a array from the end to the beginning 
  */
  for(auto itr = my_array.rbegin() ; itr < my_array.rend() ; ++itr)
  {
    std::cout << *itr << ' '; 
  }
  std::cout << "\n";
  /**
   * Can start with an offset
   */
  for(auto itr = my_array.rbegin() + 1; itr < my_array.rend() ; ++itr)
  {
    std::cout << *itr << ' '; 
  }
  std::cout << "\n";
  return 0;
}