#include <iostream>

/**
 * A struct is a type consisting of a sequence of members whose
 * storage is allocated in sequence ordered
 * 
 * struct have the access specifier public
 * class have different access spicifier
 *  - public
 *  - protected
 *  - private
 */
struct Base
{
  int x;
  int y;
  /**
   * use member initialization list
   * : x(new_x),y(new_y)
   * empty body
   */
  Base(int new_x, int new_y): x(new_x),y(new_y){}

  void print_x_y()
  {
    std::cout << "x= " << x << "\n";      
    std::cout << "y= " << y << "\n";        
  }
};

struct Derived1 : Base
{
  int z;
  /**
   * use member initialization list
   *  can call the constructor for the Base class
   *  initialize the Base component here
   * : Base(new_x,new_y),z(new_z)
   * empty body
   */
  Derived1(int new_x, int new_y,int new_z)
  : Base(new_x,new_y),z(new_z){};

  void print_z()
  {
    std::cout << "z= " << z << "\n";
  }
  
  void print_x_y_z()
  {
    std::cout << "x= " << x << "\n";      
    std::cout << "y= " << y << "\n";
    std::cout << "z= " << z << "\n";
  }
};

int main()
{
  Derived1 d1(1,2,3);
  d1.print_x_y();
  d1.print_z();
  d1.print_x_y_z();
  return 0;
}