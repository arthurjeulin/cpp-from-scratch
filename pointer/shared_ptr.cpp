#include <iostream>
#include <memory>

int main()
{
  /**
   * Doesn't work with compiler before g++-12
   * need --std=c++20 option
   */
  std::shared_ptr<int[]> ptr_1(new int[10]);
  // std::shared_ptr<int[]> ptr_1 = std::make_shared<int[]>(10);
  // Getting a second reference of the array of integer
  {
    auto ptr_2 = ptr_1;
    // The array of integer will be delete only when the two 
    // shared pointer goes out of scope.
    std::cout << "Reference count: " << ptr_1.use_count() << "\n";
  }
  // ptr_2 is out of scope here
  std::cout << "Reference count: " << ptr_1.use_count() << "\n";
  return 0;
}