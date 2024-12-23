#include <iostream>
int main()
{
  int a = 11;
  int b = 10;
  if(a < b)
  {
    std::cout << " a is less than b!\n";
  }
  else if(a == b)
  {
    std::cout << "a is equal to be!\n";
  }
  else
  {
    std::cout << "a is great than b!\n";
  }
  return 0;
}