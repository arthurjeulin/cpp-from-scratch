#include <iostream>

struct Point
{
  // Data member - attribut
  int x;
  int y;

  // Constructor
  Point(int new_x, int new_y) : x(new_x), y(new_y){}

  // member function - method
  void print()
  {
    std::cout << "x= " << x << "\n";
    std::cout << "y= " << y << "\n";
  }

  /**
   * Operator functions are function
   *  - here an example of the function
   *  as member function
   * this operator is used of the right 
   * and side
   * p1 is left hand side
   * p2 is right and side
   * p1.operator+(p2); 
   */
  Point operator+(const Point& rhs)
  {
    return Point(x+rhs.x, y+rhs.y);
  }
  Point& operator+=(const Point& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    // return reference to the current
    // object
    return *this;
  }
};
int main()
{
  Point p1(10,20);
  Point p2(30,40);
  /**
   * verbose equivalent
   * p3 = p1.operator+(p2)
   */
  Point p3 = p1 + p2;
  
  p3+=p1;

  p3.print();
  return 0;
}