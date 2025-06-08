#include <iostream>
#include <array>

int main()
{
  // std::array is a template for what ever T type we want
  // we can do the initialization with aggragate-initialization
  std::array<int,4> array = {1,2,3,4};
  /**
   * From cpp reference we can check the member function
   * - at() access specified element with bounds checking (safe)
   * - operator[] access specified element (no safe because can access out of range
   * - front() access the first element
   * - back() acess the last element
   * - data() direct access to the underlying contiguous storage.
   */

  // use at() member functions
  std::cout << array.at(0) << "\n";
  // use operator[]
  std::cout << array[1] << "\n";
  // use front()
  std::cout << array.front() << "\n";
  // use back()
  std::cout << array.back() << "\n";
  std::cout << "------------------------\n";
  // Member functions for Operations:
  // fill at the value 3 at all the element of the array
  array.fill(3);
  // use front()
  std::cout << array.front() << "\n";
  // use back()
  std::cout << array.back() << "\n";
  std::cout << "------------------------\n";
  /**
   * Member functions for Capacity
   *  empty: check whether the container is empty
   *  size: return the number of elements
   *  max_size: return the maximum possible number of elements
   */

  std::cout << "array size: " << array.size() << "\n";
  return 0;
}