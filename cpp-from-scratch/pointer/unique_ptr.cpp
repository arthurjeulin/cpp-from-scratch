#include <iostream>
#include <memory>

int main()
{
  /**
   * equivalent of 
   *  std::make_unique<int[]>(10) == new int[10]
   */
  std::unique_ptr<int[]> ptr = std::make_unique<int[]>(10);
  for(int i = 0; i < 10; ++i)
  {
    ptr[i] = i*i;
  }
  std::cout << "value array : "<< ptr[4] << "\n";
  std::cout << "value array : "<< ptr[9] << "\n";
  return 0;
}