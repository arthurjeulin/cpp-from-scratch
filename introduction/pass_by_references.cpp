#include <iostream>
#include <vector>

void add_elements(std::vector<int>& vector, int n)
{
  for(int i = 0; i<n ;++i)
  {
    vector.push_back(i);
  }
}

int main()
{

  std::vector<int> my_vector;
  add_elements(my_vector,10);

  for(const auto& value: my_vector)
  {
    std::cout << value << "\n";
  }
  std::cout << "\n";
  return 0;
}