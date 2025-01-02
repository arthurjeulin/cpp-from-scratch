#include <array>
#include <iostream>



void print_array(const std::array<int,3> array)
{
  for(const auto& element: array)
  {
    std::cout << element ;
  }
  std::cout << "\n";
}

// function Overloading
void print_array(const std::array<float,3> array)
{
  for(const auto& element: array)
  {
    std::cout << element ;
  }
  std::cout << "\n";
}

int main()
{
  std::array<int,3> my_int_array = {1,2,3};
  print_array(my_int_array);
  std::array<float,3> my_float_array = {1.1f,2.2f,3.3f};
  print_array(my_float_array);
  return 0;
}