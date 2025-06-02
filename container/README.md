## Container
### Span
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