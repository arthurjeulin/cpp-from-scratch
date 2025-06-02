#include <iostream>
#include <vector>
#include <utility> // std::move()

/**
 * A struct is a type consisting of a sequence of member
 * whose storage is allocated in a ordered sequence.
 */
struct S
{
  int id;
  S(int i): id(i) { std::cout << "Constructor(" << id << ")\n";  }
  S(const S& s) : id(s.id)
  { 
    std::cout << "Copy Constructor(" << id << ") [ " << this <<"]\n";
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
  S(S&& s) noexcept : id(s.id)  
  { 
    std::cout << "Move Constructor(" << id << ") [ " << this <<"]\n";
  }
  ~S(){ std::cout <<"Desctructor(" << id << ") [ " << this <<"]\n";}
};

int main()
{
  std::vector<S> my_vector;
  /**
   * IMPORTANT L'ALLOCATION DE my_vector
   * ======================================
   * result with preallocation
   * Constructor!
   * Copy Constructor!
   * Constructor!
   * Move Constructor!
   * Constructor!
   * Move Constructor!
   * ======================================
   * result without preallocation
   * Constructor! => S s; s est un lvalue
   * Copy Constructor! => my_vector.push_back(s);
   * Constructor! => S p;
   * Move Constructor! => my_vector.push_back(std::move(p));
   *                   => std::move(p) est un rvalue donc appel du move constructor
   * Copy Constructor! => std::vector réalloue pour augmenter la capacité
   *                   => std::vector déplace les éléments existant donc seul s ici
   *                   => mais le move constructor n'est pas marqué noexcept donc
   *                   => std::vector copie au lieu de déplacer
   * Constructor!
   * Move Constructor!
   * Copy Constructor!
   * Copy Constructor!
   * 
   * my_vector à une capacité null au début
   *  1. std::vector commence souvent avec une capacité nulle.
   *  2. Lorsqu'on insère un premier élément, il alloue une capacité (souvent 1).
   *  3. Lorsqu'on insère un deuxième élément, il double généralement sa capacité (1 → 2), 
   *  ce qui force le déplacement ou la copie des éléments existants vers 
   *  le nouveau bloc mémoire.
   * 
   *  4. Mais dans ton cas, comme tu as défini le Copy Constructor mais pas marqué Move
   *  Constructor comme noexcept, std::vector choisit la copie par sécurité, 
   *  car les standards C++ préfèrent copier plutôt que déplacer si le move n’est pas noexcept.
   */
  my_vector.reserve(3);
  /**
   * here s is a lvalue
   */
  S s(1); // call the Contructor;
  /**
   * push_back fait appel au Copy Constructor de S
   * car s est une lvalue
   * Donc le Constructor de Copy 
   * sera appelé
   */
  my_vector.push_back(s);

  /**
   * On veut eviter la copie car
   * l'object est important
   * 
   * Si l'on fait std::move() d'un lvalue
   * sans savoir definit de move constructor
   * on aura appel au Copy Constructor
   * si le user-defined Copy Constructor
   * est defini 
   * 
   * Une fois le move constructor defnit
   * on aura un appel au Move Constructor
   */
  S p(2);
  my_vector.push_back(std::move(p));

  /**
   * ici on ajoute dans le vector un object
   * sans nom S() donc c'est un rvalue
   * Donc on a appel au Move Constructor
   */
  my_vector.push_back(S(3));

  /**
   * A se rappeller il n'y a que les
   * lvalue que l'on doit appeler std::move
   * pour déplacer les resources
   * si la valeur est un rvalue est sera
   * déplacer par defaut
   */
  return 0;
}