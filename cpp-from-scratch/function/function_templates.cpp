#include <array>
#include <iostream>

/**
 * Abbreviated function template => need C++20
 * delete template<typename T> before the function
 * and use auto instead
 * the compiler will deduced from the auto in the argument list 
 * we want a template<typename T>
 */

void print_array(const auto& array)
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
  std::array<float,3> my_float_array = {1.1f,2.2f,3.3f};
  // give the version of the template
  print_array<std::array<int,3>>(my_int_array);
  // the compiler will deduce the proper type for the template
  // similar to autotype deduction
  print_array(my_float_array);
  return 0;
}