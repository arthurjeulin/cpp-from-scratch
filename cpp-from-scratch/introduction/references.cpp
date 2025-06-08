#include <iostream>

int main()
{
  int a = 5;
  // References declaration
  // Refer to ingeter a using b.
  // b will be an alias to a.
  // it's will be the exact same piece of memory.
  int &b = a;
  b += 1;

  std::cout << "a: " << a << "\n";
  std::cout << " &a: " << &a << "\n";
  std::cout << "b: " << b << "\n"; 
  std::cout << "&b: " << &b << "\n";
  // Can observe that a and b are having the same memory 
  // address.
  return 0;
}