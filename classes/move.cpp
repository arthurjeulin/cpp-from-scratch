#include <iostream>
#include <memory>
#include <utility> // std::move()

int main()
{
  /**
   * ptr_1 owns a dynamically allocate
   * array of 10 integer
   * ptr_1.get() value ptr_1
   */
  std::unique_ptr<int[]> ptr_1 = std::make_unique<int[]>(10);
  std::cout << "ptr_1 before move: " << ptr_1.get() << "\n";
  auto ptr_2 = std::move(ptr_1);
  std::cout << "ptr_1 before move: " << ptr_1.get() << "\n";
  std::cout << "ptr_2 before move: " << ptr_2.get() << "\n";
  return 0;
}