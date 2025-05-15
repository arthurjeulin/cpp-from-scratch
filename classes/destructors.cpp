#include <iostream>
#include <memory>
/**
 * Design partern where an object will
 * acquire some resouce into the constructor
 * and free in the desctructor is called
 * RAII: Resource Acquisition Is Initialization
 * The user of the object doesn't have to
 * do any manuel management of resources
 */
struct IntArray
{
  /**
   * Pointer to store to a dynamically 
   * allocated array of int
   */
  int *array;

  IntArray(int size)
  {
    array = new int[size];
  }
  /**
   * Object clean up itself when out 
   * of scope.
   */
  ~IntArray()
  {
    std::cout << "Deleting memory !\n";
    delete[] array;
  }
};

/**
 * Design class improve
 */

 struct BetterIntArray
 {
  /**
   * unique prt to an array of integer
   */
  std::unique_ptr<int[]> array;
  BetterIntArray(int size) : array(std::make_unique<int[]>(size)) {}
 };

int main()
{
  IntArray a(10);
  a.array[0] = 10;

  BetterIntArray b(5);
  b.array[0] = 5;

  std::cout << "value: " << a.array[0] << "\n";
  std::cout << "value: " << b.array[0] << "\n";

  return 0;
}