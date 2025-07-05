#include <iostream>

/**
 * Upcasting
 *  casting a variable with the (upper class) 
 *  or the base class
 *  Derivated class => Base class
 *  storing Derivated class as a Base class 
 */

 /**
  * virtual function specifier
  *   virtual keyword
  * Virtual functions are members functions whose
  * behavior can be overriden in derived class.
  * As opposed to non-virtual function, 
  * the overriding behavior is preserved
  * even if there no compile-time information about
  *  the actual tpe of the class. 
  * If a derived class is handled using pointer or 
  * reference to the base class, a class to an overridden
  * virtual function would invoke the behavior defined in 
  * the derived class. 
  * 
  * Good pratice uses override specifier (since C++11)
  *   Specifies that a virtual function overrides another virtual function
  *   Overriting specifier prevent spelling mistake to tell the compiler
  *   we are overriding a function.
  */

// Animal is our base class
struct Animal
{
  virtual void speak()
  {
    std::cout << "Default speak function!\n";
  }
};
// Derivated class
struct Dog: Animal
{
  void speak() override // good pratice
  {
    std::cout << "Woof!\n";
  }
};

// Derivated class
struct Cat : Animal
{
  void speak() override // good pratice
  {
    std::cout << "Meow!\n";
  }

};
int main()
{
  Dog d;
  d.speak();
  Cat c;
  c.speak();

  // static polymorphism
  // call to the default speak function if speak is not virtual
  // class speak the function Dog because speak() is virtual
  Animal &a1 = d;
  a1.speak();
  // static polymorphism
  // call to the default speak function if speak is not virtual
  // dynamic polymorphism (get the behavior of the underlying class with
  // if we are reinterpreting the object as their base class)
  // class the speak function of Cat because speak() is virtual
  Animal &a2 = c;
  a2.speak();

  return 0;
}