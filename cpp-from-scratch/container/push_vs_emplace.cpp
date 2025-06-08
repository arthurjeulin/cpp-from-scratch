#include <iostream>
#include <utility> // std::move()
#include <vector>

/**
 * push_back adds an element to the end
 * emplace_back constructs an element in place at the end
 */

struct S
{
  int x;  
  S(int new_x): x(new_x)
  {
    std::cout << "Constructor!\n";
  }
  S(const S& s): x(s.x)
  {
    std::cout << "Copy Constructor!\n";
  }
  /**
   * T& => reference
   * T&& => rvalue reference
   * 
   * il est important d'ajouter le Move Constructor comme
   * noexecpt si possible sinon le Copy Constructor sera utiliser 
   * par préference lors de la Copy/Deplacement des containers lors
   * de la réallocation.
   */
  S(S&& s): x(s.x)
  {
    std::cout << "Move Constructor!\n";
  }

};
int main()
{
  std::vector<S> my_vector;
  my_vector.reserve(4);
  /**
   * Creating an object of type S;
   * Initialization of s with 10
   * s here is a lvalue
   */
  S s(10);
  /**
   * when push_back get a s value call the
   * version of push_bash who does a copy of s.
   */
  my_vector.push_back(s);
  /**
   * std::move(s) change s from lvalue to
   * rvalue which trigger the version of push_bash
   * who moves the value
   */
  my_vector.push_back(std::move(s));
  /**
   * here S(12) is a rvalue so push_bash call
   * the move version
   */
  my_vector.push_back(S(12));

  /**
   * emplace back ajoute un element à la fin du 
   * container
   * emplace_back will create the object at memory
   * place in the vector
   * my_vector a alloué de la mémoire avec ::operator new
   * qui alloue des blocs de mémoire pour chaque element du
   * vecteur.
   * emplace_back appelle placement new qui appelera le constructor
   * de S à l'emplacement mémoire déjà ajoute par my_vector
   */
  my_vector.emplace_back(13);
  return 0;
}