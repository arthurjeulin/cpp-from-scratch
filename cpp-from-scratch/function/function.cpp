#include <iostream>
#include <array>

void print_array(const std::array<int,3>& tab)
{
  for(const auto& element : tab)
  {
    std::cout << element ;
  }
  std::cout << "\n";
}

int main()
{
  std::array<int,3> my_array = {1,2,3};
  print_array(my_array);
  my_array.at(2) = 5; 
  print_array(my_array);

  return 0;
}