#include <iostream>

int main()
{
  /**
   * new request space for a single integer.
   * Then allocate the space for this integer and
   * return the address of this memory block
   */
  int* int_ptr = new int;
  // Can the a value by dereference the pointer
  *int_ptr = 1;
  std::cout << "Value: " << *int_ptr << "\n";
  std::cout << "Address: " << int_ptr << "\n";
  /**
   * Free the memory
   * delete the allocate piece of memory.
   * Destroys one non-array ojects created by a new-repression
   */
  delete int_ptr;
  
  /**
   * Can allocate an array of element.
   * int_ptr_array is the pointer to the first element
   * of an array of 10 elements.
   */
  int* int_ptr_array = new int[10];
  /**
   * *int_ptr_array same as int_ptr_array[0]
   */
  int_ptr_array[3] = 3;
  std::cout << "Value: " << int_ptr_array[3] << "\n";
  std::cout << "Address: " << &int_ptr_array[3] << "\n";
  /**
   * Destroys an array created by a new[]-expression
   * Free up the 10 integer
   */
  delete[] int_ptr_array;
  return 0;
}