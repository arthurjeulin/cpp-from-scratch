#include <array>
#include <iostream>


int sum(const std::array<int,3> tab)
{
  int sum = 0;
  for(const auto& value: tab)
  {
    sum+= value;
  }
  return sum;
}

int main()
{
  std::array<int,3> my_array = {1,2,3};
  auto result = sum(my_array);
  std::cout << "The sum of our array is: " << result << "\n";
  
  return 0;
}