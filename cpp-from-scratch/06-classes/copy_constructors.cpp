#include <iostream>

struct Point
{
  // Data member
  int x;
  int y;
  // Member fonction
  /**
   * Member initialization list
   */
  // Constructor
  Point(int x_, int y_): x(x_),y(y_){}
  // Copy Constructor
  Point(const Point& p):x(p.x),y(p.y){}

  void print()
  {
    std::cout << "x=" << x << "\n";
    std::cout << "y=" << y << "\n";
  }
};

/**
 * Different manière d'appele le constructor
 * de copy:
 *  Point p(1,0);
 *  Point p2(p); // appel explicite
 *  Point p3 = p; copy initialization (initialization par copy)
 * 
 * Copy elision:
 *  La copy elision est une optimiation faite 
 *  par le compilateur qui supprime l'appel au 
 *  constructeur de copie (ou au constructeur move)
 *  lorsqu'il est possible de constructuire l'object
 *  directement à sa destination finale
 * "Autrement dit, le compilateur évite de créer
 *  un object temporaraire et de copier, en construisant
 *  directement le résultat là ou il doit aller"
 * 
 * Point make_point()
 * {
 *  Point p(5,10);
 *  return p;
 * }
 * Ici p devrait être copié au moment du return,
 * mais grâce à la copy elision, le compilateur 
 * construit directement l'object retourné à l'
 * endroit où make_point() est utilisé.
 * C++ 17 et mandatory copy elision
 * Depuis C++ 17 certaines copy elisions sont 
 * obligatoire, notamment dans les cas de retour
 * d'un object temporaire
 * Point make_point()
 * {
 *   return Point(1,2); // copy elision obligatoire en C++17
 * }
 */
int main()
{
  Point p(0,1);
  p.print();
  Point p2(p);
  p2.print();
  return 0;
}