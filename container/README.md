## Idiome fondamental en C++
Un idiome C++ fondament est une forme de code reconnue, typique et recommandé pour exprimer une idée récurrente d'une manière:
- sûre
- efficace
-optimisée,
compatible avec les conventions du langage
#### Example d'idiomes fondamentaux en C++
| Idiome                 | Ce que ça exprime                                                          |
| ---------------------- | -------------------------------------------------------------------------- |
| **RAII**               | Gérer des ressources (fichier, mutex, etc.) via la durée de vie d'un objet |
| **Rule of 5 / 0**      | Gérer proprement les constructeurs et opérateurs spéciaux                  |
| **SFINAE / Concepts**  | Contraindre des templates à certains types valides                         |
| **Perfect Forwarding** | Transmettre des arguments **sans perte** (ex: `Args&&... args`)            |
| **CRTP**               | Simuler du polymorphisme sans coût virtuel                                 |
| **pImpl**              | Séparer l’interface et l’implémentation (cacher les détails)               |

## Containers
### span
```cpp
template<
  class T,
  std::size_t Extent = std::dynamic_extent
> class span
```
Français => "vue" ou "fenêtre" (literal étendue / durée / portée)
The class template span describes an object that can refer to a contiguous sequence of  objects with the first element of the sequence at position zero. A span can either have a static extent, in which case the number of elements in the sequence is known at compile-time and encoded in the type, or dynamic extent
Explication
- Allow us to look at sequence of object without owning the underline memory.
Don't want ownership of the underline memory of this object.
- Look at a subset ob a vector (don't want to own the memory of the vector into a new container)

```bash
 g++ container/span.cpp -o build/span --std=c++20
```

### vector
| Élément         | Description                                                      |
| --------------- | ---------------------------------------------------------------- |
| `data_`         | Pointeur brut vers la mémoire allouée                            |
| `size_`         | Nombre d’éléments construits                                     |
| `capacity_`     | Capacité totale allouée sans réallocation                        |
| `push_back(T)`  | Ajoute un élément (par copie ou par déplacement)                 |
| `reserve(cap)`  | Alloue un nouveau buffer et déplace les anciens éléments         |
| `operator new`  | Utilisé pour allouer la mémoire brute (pas d'appel constructeur) |
| `placement new` | Construit un objet à une adresse spécifique                      |
| `~T()`          | Appelé explicitement pour détruire les objets                    |
### Implementation explication
1. ::operator new(new_cap * sizeof(T))
  C'est l'appel direct à l'opérateur de base operator new fourni par le langage C++ (pas le new keyword)
  ```cpp
  T* new_data = static_cast<T*>(::operator new(new_cap * sizeof(T)));
  ```
  Pourquoi ne pas utiliser new T[new_cap];
    - new T[new_cap] => alloue et construit chaque élément (par défaut!)
    - or ici on veut juste allouer de la mémoire brute, sans construire les objects immédiatement
  ::operator new:
    - alloue un bloc mémoire brut
    - ne construit pas d'object (T() n'est pas appelé)
    - retourne un void*
  Pourquoi static_cast<T*>
    Car ::operator new(...) retourn un void*, il faut le caster vers T* pour l'utiliser avec new ensuite.
    ```cpp
    T* new_cata = static_cast<T*>(::operator new(...));
    ```
2. new(data_ + size_) T(std::move(value));
  C'est un appel à placement new, qui signifie:
    Construit un object de type T,en appelant son constructeur à une addresse mémoire donnée.
  ```cpp
  new (data_ + size_) T(std::move(value));
  ```
  - data_ + size_ = l'adresse mémoire où tu veux construire l'object
  - T(std::move(value)) = appel du constructeur par déplacement
  Résultat: un objet T est construit dans la mémoire du buffer, sans allouter de nouvelle mémoire.

std::vector alloue de la mémoire une fois (grâce à operator new), puis utilise placement new pour construire les objets au fur et à mesure, sans provoquer de re-allocation inutile.

### Tableau récapitulatif des différents new et delete en C++
| Syntaxe                                | Allocation de mémoire ? | Construction objet ?           | Désallocation ?           | Exemple                           |
| -------------------------------------- | ----------------------- | ------------------------------ | ------------------------- | --------------------------------- |
| `new T`                                | ✅ oui                   | ✅ oui (T())                    | via `delete`              | `T* p = new T(42);`               |
| `new T[n]`                             | ✅ oui (tableau)         | ✅ oui (T() n fois)             | via `delete[]`            | `T* p = new T[10];`               |
| `::operator new(size)`                 | ✅ oui                   | ❌ non                          | via `::operator delete()` | `void* raw = ::operator new(64);` |
| `new (ptr) T(args...)` (placement new) | ❌ non                   | ✅ oui à l'adresse donnée       | ❌ (nécessite `obj->~T()`) | `new (ptr) T(42);`                |
| `delete p`                             | ✅ oui                   | ✅ appelle `~T()`               | ✅ libère mémoire          | `delete p;`                       |
| `delete[] p`                           | ✅ oui                   | ✅ appelle `~T()` n fois        | ✅ libère mémoire          | `delete[] p;`                     |
| `::operator delete(ptr)`               | ✅ oui                   | ❌ n'appelle pas le destructeur | ✅ libère mémoire brute    | `::operator delete(ptr);`         |

Remarques:
- ::operator new / ::operator delete = version bas niveau : alloue/libère la mémoire brute, ne touche pas aux objets.
- placement new = construction explicite dans une mémoire déjà allouée.
- delete / delete[] = fait à la fois la destruction et la libération de mémoire.

### Resolution de porté ::
En C++, le :: en tout début d'un identifiant indique:
  - "je veux accéder à l'entité depuis la portée globale"
    (c'est à dire en dehors de tout namespace ou class en cours)
Donc:
```cpp
::operator new(size)
```
  signifie:
  -  Utilise la fonction operator new définie dans la portée globale, non une version surchargé ou dans un namespace
  - est utiliser pour éviter toutes ambiguïté avec une éventuelle surcharge de new dans une class ou un namespace
Conclusion
- :: seul signifie : "à partir de la portée globale".
- C’est crucial pour éviter les conflits de noms dans les namespaces ou les classes.
- En ::operator new, c’est pour forcer l’utilisation de la version standard du C++ (non surchargée).
- En ::testing::Test, c’est pour clarifier qu’on veut la classe Test du namespace testing global, utile quand on est dans d'autres scopes.

### push_back vs emplace_back
- std::vector is one of the most used container because it is really pratical.
- now let learn how to use well std::vector
#### emplace_back explanation
Example cpp reference
```cpp
#include <vector>
#include <cassert>
#include <iostream>
#include <string>
 
struct President
{
  std::string name;
  std::string country;
  int year;

  President(std::string p_name, std::string p_country, int p_year)
      : name(std::move(p_name)), country(std::move(p_country)), year(p_year)
  {
      std::cout << "I am being constructed.\n";
  }

  President(President&& other)
      : name(std::move(other.name)), country(std::move(other.country)), year(other.year)
  {
      std::cout << "I am being moved.\n";
  }

  President& operator=(const President& other) = default;
};
 
int main()
{
  std::vector<President> elections;
  std::cout << "emplace_back:\n";
  auto& ref = elections.emplace_back("Nelson Mandela", "South Africa", 1994);
  assert(ref.year == 1994 && "uses a reference to the created object (C++17)");

  std::vector<President> reElections;
  std::cout << "\npush_back:\n";
  reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));

  std::cout << "\nContents:\n";
  for (const President& president: elections)
      std::cout << president.name << " was elected president of "
                << president.country << " in " << president.year << ".\n";

  for (const President& president: reElections)
      std::cout << president.name << " was re-elected president of "
                << president.country << " in " << president.year << ".\n";
}
```
Output:
```bash
emplace_back:
I am being constructed.
 
push_back:
I am being constructed.
I am being moved.
 
Contents:
Nelson Mandela was elected president of South Africa in 1994.
Franklin Delano Roosevelt was re-elected president of the USA in 1936.
```
importante nuance de emplace qui à deux surcharges possibles:
```cpp
template< class... Args >
void emplace_back( Args&&... args ); (until C++17)

template< class... Args >
reference emplace_back( Args&&... args ); (since C++17 (Retourne T&)) (constexpr since C++20 (Retourne T&, et constexpr)
)
```
Avant C++17: emplace_back ne retournait rien
Pour accéder à l'object il fallait:
```cpp
vec.emplace_back();
President& ref = vec.back(); // accès manuel
```
Depuis C++ 17: retourn ference (c'est à dire T&)
A partir de C++17, le standard a modifié emplace_back pour qu'il retourne une référence à l'objet construit dans le container.
- emplace_back depuis C++17 retourne un reference de l'object crée.
Depuis C++20: constexpr ajouté:
- emplace_back peut-être applé à la compilation si toutes les ocnditions sont réunies. 
```cpp
std::vector<President> elections;
auto& ref = elections.emplace_back("Nelson Mandela", "South Africa", 1994);
assert(ref.year == 1994 && "uses a reference to the created object (C++17)");
```
### Pourquoi on ne std::move pas forcement un type primitif comme int ?
- int est un type primitif, copiable à coût constant
- En C++, les types primitifs (comme int, double, bool) ne peuvent pas être "déplacés", car ils ne possèdent pas de move constructor.
- Il n'y a pas de différence entre "copier" et déplacer" un in: c'et toujours une simple copie binaire.
```cpp
year = p_year;          // équivalent à std::move(p_year);
year = other.year;      // idem
```
- Il est inutile et non idiomatique d'écrire std::move(p_year) pour un int
### Explication de assert()
Définition
```cpp
assert(expression);
```
- Vérifie que l'expression est vraie à l'exécution (pas à la compilation)
- Si expression == false, le programme:
  - s'arrête immédiatement
  - avec un message d'erreur contenant l'expression
```cpp
assert(x==42 && "x should be 42 here");
```
Si x!=42 message d'erreur:
```cpp
Assertion failed: x == 42 && "x should be 42 here", file main.cpp, line XX
```
### template<class... Args> ?
C'est un idome fondamental du C++ moderne: les "parameter packs' utilisés dans les templates variadiques.
Un template variadique:
```cpp
template< class... Args >
```
- Cela signifie: "Args est une liste de types (0 ou plus)"
- Args - représente plusieurs types, pas un seul
Exemple d'instanciation possible de emplace_back:
```cpp
emplace_back(int, std::string,double)
```
Dans ce cas:
- Args devient: int, std::string,double
Que signifie Args&&... args dans les paramètres
```cpp
emplace_back(Args&&... args)
```
Détails
- Args&&...: correspond à une liste de références de rvalue universelles, une pour chaque type de Args.
- args...: ce sont les noms des arguments correspondants
Args&&... args = listes d'arguments "perfect forwarded" (Mécanismes de transfert parfait en C++11)
Exemple simple
```cpp
template<typename... Args>
void log_all(Args&&... args) {
    (std::cout << ... << args); // fold expression
}
```
Appel:
```cpp
log_allo("ID= ",42,", x= ", 3.14);
```
- Args... = const char*, int, const char*, double
- args... = ID = ", 42, ", x = ", 3.14
Différence entre Args et args (et ...)
| Élément                       | Ce que c’est                                           | Représente                              |
| ----------------------------- | ------------------------------------------------------ | --------------------------------------- |
| `Args...`                     | **liste de types** (template)                          | Ex : `int, std::string, double`         |
| `args...`                     | **liste d'arguments** (paramètres)                     | Ex : `42, "hello", 3.14`                |
| `Args&&...`                   | liste de **rvalue/lvalue references**                  | rend possible le **perfect forwarding** |
| `std::forward<Args>(args)...` | **Dépliage + preservation** du type de chaque argument | Core du perfect forwarding              |
### Example avec une fonction template variadique avec perfect forwarding
Définition générique:
```cpp
template<typename... Args>
void func(Args&&... args)
{
  some_function(std::forward<Args>(args)...);
}
```
Exemple d'appel utilisateur
```cpp
std::string name = "Arthur";
int age = 30;
func(name,42,std::move(age));
```
Ce que voit le compilateur
| Élément                       | Contenu déduit                                                                  |
| ----------------------------- | ------------------------------------------------------------------------------- |
| `Args...`                     | `std::string&`, `int`, `int&&`                                                  |
| `args...`                     | `name`, `42`, `std::move(age)`                                                  |
| `Args&&...`                   | `std::string& &&`, `int&&`, `int&& &&` → simplifiés                             |
| `std::forward<Args>(args)...` | `std::forward<std::string&>(name)`, `42`, `std::forward<int&&>(std::move(age))` |

std::forward<Args>(args)... fait une expansion "1 par 1" qui préserve :
- les & si c'était des lvalues,
- les && si c'était des rvalues.
```cpp
// Expansion 1 par 1 avec Args = (std::string&, int, int&&)

some_function(
    std::forward<std::string&>(name),  // reste une lvalue
    42,                                // simple value
    std::forward<int&&>(std::move(age)) // reste une rvalue
);
```
Résultat : perfect forwarding
| Argument original | Type réel dans `Args` | Après `std::forward<Args>(args)` |
| ----------------- | --------------------- | -------------------------------- |
| `name`            | `std::string&`        | `std::string&`                   |
| `42`              | `int`                 | `int`                            |
| `std::move(age)`  | `int&&`               | `int&&`                          |
Le comportement de chaque argument est parfaitement respecté sans copie ou conversion inutile.
| Élément                       | Rôle                                                       |
| ----------------------------- | ---------------------------------------------------------- |
| `Args...`                     | Paramètre pack de **types**                                |
| `args...`                     | Paramètre pack de **valeurs**                              |
| `Args&&... args`              | Permet d’accepter n’importe quoi **avec sa valeur exacte** |
| `std::forward<Args>(args)...` | Fait le **forwarding parfait** avec expansion 1 par 1      |
| `...`                         | Syntaxe de **dépliage du pack** (parameter pack expansion) |
