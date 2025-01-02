#include <array>
#include <iostream>

// using abbreviated function template syntaxe
void print_array(const auto& array)
{
  for(const auto& element: array)
  {
    std::cout << element ;
  }
  std::cout << "\n";
}
/**
 * Feature Write a specialization for a print_array of 3 int
 * to tell to the compiler this function print_array 
 * is part of the template print_array.
 * We need to add template<>
 */
template<>
void print_array(const std::array<int,3>& array)
{
  std::cout <<"Printing from our specialization!\n";
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