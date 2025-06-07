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
struct Animal
{
  void speak()
  {
    std::cout << "Default speak function!\n";
  }
};

struct Dog : Animal
{
  /**
   * Member function overloading
   */
  void speak()
  {
    std::cout <<"Woof!\n";
  }
};

struct Cat : Animal
{
  /**
   * Member function overloading
   */
  void speak()
  {
    std::cout <<"Meow!\n";
  }
};  

int main()
{
  Dog d;
  d.speak();

  Cat c;
  c.speak();

  /**
   * Static Polymorphism: (at compile time the compiler make the decision
   *  of which method to class)
   * - use a reference to the base class (up casting)
   *  (castingfrom a derived type backup to a base class)
   *    - will call the base class method and not the derived class
   * Dynamic Polymorphism: 
   *  (make the decision of which method to use at runtime)
   *  - need virtual fonction
   */

  /**
  * Interpret the dog object as a Animal
  * because dog inherite from animal
  */
  Animal &a1 = d;
  // Will see the animal speak and not the dog one.
  a1.speak();

  Animal &a2 = c;
  a2.speak();
  return 0;
}