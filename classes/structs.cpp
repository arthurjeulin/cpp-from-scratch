#include <iostream>

/**
 * Create a new type Point
 */
struct Point
{
  // Member variable
  int x;
  int y;

  // Member function operate on the member variable
  void print()
  {
    std::cout << "x: " << x << "\n";
    std::cout << "y: " << y << "\n";
  }
};
/* Main fonction */
int main()
{
  /* Creating a instance of the class create an object */
  Point p1;
  p1.x = 20;
  p1.y = 10;
  p1.print();
  Point p2;
  p2.x = 2;
  p2.y = 2;
  p2.print();
  return 0;
}