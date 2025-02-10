#include <iostream>

int main()
{
  int a = 5;
  // b is a reference to a
  int& b = a;
  /**
   * When I'm changing a or b I'm changing the memory location
   * where the 5 is stored.
   */
  // type is the memory address of an integer.
  int* c = &a;

  std::cout << "a: " << a << "\n";
  std::cout << "&a: " << &a << "\n";
  std::cout << "c: " << c << "\n";
  // We can see that c is storing the address of a.

  // to access the value of a pointer we want to dereference it.
  std::cout << "*c: " << *c << "\n";
  return 0;
}