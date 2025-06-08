#include <array>
#include <iostream>

int main()
{
  /**
   * C-Style for loop
   * init-statement: i will be a loop counter
   * condition: execute the loop as long as the condition is true
   * expression: incrementation ++i (post increment) i++ (pre increment)
   */
  for(int i = 0;i < 5; ++i)
  {
    std::cout << "Iteration: " << i << "\n";
  }
  /**
   * Range for loop (since C++ 11)
   * Used as more readable equivalent to the traditionnal for loop operating over a range 
   * of value, such, as all elements in a container.
   */

  std::array<int,5> tab = {5,4,3,2,1};
  for(auto& value : tab)
  {
    std::cout << "Array value: " << value << "\n";
  }


  return 0;
}