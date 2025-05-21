#include <iostream>

class Point
{
  public:
  // Implement setter and getter
    Point& x(int x){ _x = x; return (*this);}
    Point& y(int y){ _y = y; return (*this);} 
  // class function => method
    void print()
    {
      std::cout << "x: " << _x << "\n";
      std::cout << "y: " << _y << "\n";
    }
  private:
  // data member => attribut
    int _x;
    int _y;
};

int main()
{
  Point p;
  p.x(1).y(2);

  p.print();

  return 0;
}