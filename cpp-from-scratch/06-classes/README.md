## Classes and Struct

We want to create our own type.

### Struct
#### Definition
A struct is a type consisting of a sequence of members whose storage is allocated in an ordered sequence (as opposed to union, which is a type consisting of sequence of members whse storage overlaps).
#### Explication in French
#### Un structure
- Une struct est un regroupement ordonnée de plusieurs membres (variables).
- Chaque membre a sa propre zone mémoire, les unes à la suite des autres en mémoire.
```cpp
struct Position
{
  int x; // 4 bytes
  int y; // 4 bytes
}
```
En mémoire
```bash
[ x (4 bytes) ][ y (4 bytes) ] => total: 8 bytes
```
Chaque membre est indépendant et accessible séparement.
#### Union
Dans une union, tous les membres partagent le même emplacement mémoire.
Cela veut dire:
- Tous les membres se superposent
- Une seule valeur peut -etre utilisée à la fois.
```cpp
union FloatInt
{
  float f;
  uint32_t i;
};
```
```bash
[ shared storage (4 bytes) ]
```
```cpp
FloatInt value;
value.f = 3.14f;
std::cout << "Bits de 3.14 : " << std::hex << value.i << "\n";
```

### Class
- the main difference between a class and a struct is how to access members of the struct / class by default.
- access specifiers for the class:
  - public
  - private
  - protected
- By default the access specifier for a class is private.

### Constructors and member initialize lists
- Constructors are non-static member functions declared with a special syntax, they are used to initialize objects of their class type.
To remember: as soon as we are creating the constructor the default constructor by the compiler is disable. To enable the compiler's default constructor we need to:
```cpp
Point() = default;
```

### Desctructors
- A desctructor is a special member function that is called when the lifetime of an object ends. The purpose of the desctructor is to free the resouces that the object may have acquired during its lifetime.
### Copy Constructor
A copy constructor is a constructor which can be called with an argument of the same class type ad copies the content of the argument without mutating the argument.
- const flags means "READ ONLY"
- argument has to be const to guarentee the copy object won't be changed.
```cpp
Point(const Point& p);
```
- The compiler will also generate a default copy constructor.
- Sometimes we don't want to allow any copy
```cpp
Point(const Point& p) = delete;
```
example std::unique_ptr<T>, we don't want to copy a unique_ptr;

### Move
Moving allows us to transfer resources from one object to another instead of copying them.
#### std::unique_ptr
std::unique_ptr is a smart pointer that owns (is responsible for) and manages another object via a pointer and subsequently disposes (free, delete) of that object when the unique_ptr goes out of scope.
- std::unique_ptr cannot be copy
Avoiding copying => semantics move
- instead of copying some resource to some object we steal the underlying resouces.
- The class std::unique_ptr satisfies the requirements of MoveConstructible and MoveAssignable, but neither CopyConstructible nor CopyAssignable.
Move Consstructors
A move constructor is a constructor which can be called with an argument of the same class type and copies the content of the argument, possibly mutating the argument

Move constructors typically transfer the resouces held by the argument (e.g pointers to dynamically-allocated objects, file descriptors, TCP sockets, thread handles, etc) rather than make a copies of them, and leave the argument in some valid but otherwise indeterminate state. Since move constructor doesn't change the lifetime of the argument, the destructor will typucally be called on the argument at a later point. 
For example
- moving from a std::string or std::vector may result in the argument being left empty(we can not rely on the value into the container).
- For some types, such as std::unique_ptr, the moved-from state is fully specified (important that means we can rely on the state of the std::unique_ptr afterward)
### Value categories
Each C++ expression (an operator with its operands, a literal, a variable name, etc) is characterized by two independent properties: a type and a value category.
Each expression has some non-eference type and each expression belons exactly one of the three primary value categories: prvalue, xvalue, and lvalue.

```cpp
/**
 * lvalue:
 * (typically on the left side of an assignement expression)
 * auto ptr_1 has an address and can be 
 * assigned to.
 * 
 * rvalue: 
 * (typically on the right hand side of these assignement expression)
 * don't have a name (nameless temporary)
 *  we do not assigned values to a rvalue
 * std::make_unique<int[]>(10)
 * 
 * Main difference between lvalues and rvalue:
 * how do we treat them in term of copying and moving
 * By default on a lvalue we can have references, copies
 * rvalue (nameless value, temporaries like return values) are values we move
 * 
 * We can convert a lvalue into rvalue
 */
auto ptr_1 = std::make_unique<int[]>(10);
auto ptr_2 = std::move(ptr_2);
```

### Operator overloading
Customizes the C++ operators for operands of user-defined type
Use operator with our class. Doesn't work by default because the compiler doesn't know what our class means. 
- Like Point p; => p1 += p2; ?

Syntax: 
- Operator functions are functions with special function names
  - operator op (1)
  - operator new or operator new[] (2)
  - operator delete or operator delete[] (3)
  - operator co_await (4)

(1) An overloaded punctuation operator
(2) An allocation function
(3) A deallocation function
(4) An overloaded co_await operator for use in co_await expressions 

When an operator appears in an expression, and at least one of its operants has a class type or an enumaration type, then overload resolution is used to determine the user-defined function to be called among all the functio whose signatures match the following: 
## Table de surcharge des opérateurs en C++

| Expression     | En tant que fonction membre       | En tant que fonction non-membre     | Exemple                                                                 |
|----------------|-----------------------------------|--------------------------------------|-------------------------------------------------------------------------|
| `@a`           | `(a).operator@()`                 | `operator@(a)`                       | `!std::cin` appelle `std::cin.operator!()`                             |
| `a@b`          | `(a).operator@(b)`                | `operator@(a, b)`                    | `std::cout << 42` appelle `std::cout.operator<<(42)`                  |
| `a = b`        | `(a).operator=(b)`                | ❌ ne peut pas être non-membre        | `std::string s; s = "abc"` appelle `s.operator=("abc")`                |
| `a(b...)`      | `(a).operator()(b...)`            | ❌ ne peut pas être non-membre        | `std::random_device r; auto n = r();` appelle `r.operator()()`        |
| `a`            |
| `a->`          | `(a).operator->()`                | ❌ ne peut pas être non-membre        | `std::unique_ptr<S> p; p->bar()` appelle `p.operator->()`              |
| `a@` (postfix) | `(a).operator@(0)`                | `operator@(a, 0)`                    | `std::vector<int>::iterator i; i++` appelle `i.operator++(0)`         |

> Dans ce tableau, `@` est un symbole générique représentant :
> - tous les opérateurs préfixes dans `@a`
> - tous les opérateurs postfixes sauf `->` dans `a@`
> - tous les opérateurs infixes sauf `=` dans `a@b`

---

### Remarques

- Les opérateurs de comparaison `==`, `!=`, `<`, `>`, `<=`, `>=`, `<=>` sont également résolus via les **candidats réécrits** : `operator==` ou `operator<=>` *(depuis C++20)*.

### Volatile
En C++, le mot-clé volatile est un qualificateur de type qui indique au compilateur qu'une variable peut être modifié à tout moment, en dehors du controle du programme (par exemple par du matériel, un thread concurrent, ou une interruption)
Definition
```cpp
volatile int x;
```
Cela signifie que w peut être modifié de manière externe, donc le compilateur ne doit pas optimiser les accès à cette variable.

| Qualificateur | But principal                        | Thread-safe |
| ------------- | ------------------------------------ | ----------- |
| `const`       | Lecture seule                        | Non         |
| `volatile`    | Empêche les optimisations agressives | Non         |
| `std::atomic` | Accès sûr et synchronisé             | ✅ Oui      |
   

### Move constructors
A move constructor is a constructor which can be called with an argument of the same class and copies the content of the argument, possibly muatating the argument

Instead of copying a resource we can move the underlying resource from one object to another.

#### use std::vector<T,Allocator>::push_back
There is two signature to push_back
```cpp
// take a reference
void push_back(const T& value);
// take a rvalue
void push_back(T&& value);
```
- Appends a copy of value to the end of the container.
- If after the operation the new size() is greater than old capacity() a reallocation takes place, in chich case iterators (including the end() iterator) and all reference to the elements are invalidated.

#### std::quoted
- est une fonction utilitaire dans <iomanip> qui sert à formater une cha-ine de caractères avec des quillemts lors de l'affichage
- std::quoted(e): entoure la chaîne e de guillemets" et échapped les caractères spéciaux si nécessaires

### std::vector
- std::vector stocke ses éléments dans une zone mémoire contiguë comme un tableau (T*).
- Cela signifie que tous les éléments sont côté à côté en mémoire, ce qui permet un
  accès rapide par index (operator[]) et une excellente localité mémoire (bon pour
  performances CPU)
### Explication step by step du code move_constructors sans preallocation
```cpp
std::vector<S> my_vector;
S s;
my_vector.push_back(s); // Capacity = 1
```
- Le vecteur alloue un block mémoire de taille 1
- Il contient une copie de s à l'address ptr[0] => *(ptr + 0)
étape au moment du my_vector.push_back(std::move(p))
  - Le vector a déjà 1 élément, mai sa capacité est 1, donc
    il ne peut pas ajouter un deuxième élément sans réallouer.
  - Le vector décide donc de 
    - allouer un nouveau bloc mé"moire de capcité 2 (ou plus)
    - déplacer les anciens éléments dans ce nouveau bloc
    - puis y ajouter le nouveau élément p
Pourquoi p est mové avant s soit copié ?
  Deux choses distincs se passent:
    1. std::move(p) crée un rvalue, et push_back appel immédiatement 
    le move constructor pour l'insérer
    2. Ensuite, la réallocaito internet est déclenché, donc vector
      doit bouger/copier les anciens éléments dans le nouveau block
  Mais ! Selon l'implémentation du compilateur, la séquence peut être:
    - faire une réallocation anciticipé, allouer un nouveau bloc
    - puis
      - construire le nouveau élément p directment dans le nouveau
        bloc (move constructor)
      - ensuite copier les anciens éléments (s) dans le nouveau bloc.
Ordre des opérations :
- Le nouvel élément (p) est construit dans la nouvelle mémoire, puis les anciens éléments sont copiés/déplacés.
  Cela permet d'éviter un double déplacement si on ajoutait d'abord p dans l’ancien bloc (puis qu'on devait le redéplacer).
Parce que le vecteur :
- alloue de la mémoire,
- construit les éléments dedans en respectant leur ordre logique (ex: index size() doit recevoir p),
- déplace/copier les anciens éléments dans les premières positions.
Donc la construction du nouvel élément (à la fin) précède le déplacement des anciens éléments (au début).


resultat with preallocation
```bash
nvidia@dev-kit:/ssd/dev/cpp-from-scratch$ ./build/move_constructors 
Constructor(1)
Copy Constructor(1) [ 0xaaaab372deb0]
Constructor(2)
Move Constructor(2) [ 0xaaaab372deb4]
Constructor(3)
Move Constructor(3) [ 0xaaaab372deb8]
Desctructor(3) [ 0xfffff90dcba8]
Desctructor(2) [ 0xfffff90dcba0]
Desctructor(1) [ 0xfffff90dcb98]
Desctructor(1) [ 0xaaaab372deb0]
Desctructor(2) [ 0xaaaab372deb4]
Desctructor(3) [ 0xaaaab372deb8]
```
Explication:
- 1. Bloc 0xaaaab3... → c’est le buffer du std::vector (dans le tas = heap)
  - Les adresses comme 0xaaaab372deb0, ...deb4, ...deb8 sont contiguës et dans la plage mémoire typique du tas alloué dynamiquement, donc elles correspondent aux éléments stockés dans le std::vector.
- 🔹 2. Bloc 0xfffff9... → c’est la pile (stack) du main
  - Les adresses comme 0xfffff90dcb98, ...cba0, etc. sont dans la plage haute mémoire typique de la pile, et correspondent à tes objets S s(1), S p(2) et S(3) temporaires dans main.
Pourquoi l'objet S(3) est détruit deux fois ?
```cpp
my_vector.push_back(S(3));
```
Step:
- S(3) est construit sur la stack → appel au constructor :
```cpp
Constructor(3)
```
- Il est passé à push_back en tant que rvalue.
  Dans push_back(T&& value)
  ```cpp
  new (data_ + size_) T(std::move(value));
  ```
- À la fin de l’expression complète, le temporaire S(3) créé sur la stack est détruit :
```bash
Desctructor(3) [stack address]
```
- Puis, à la fin du programme, les éléments du vector sont détruits un à un 
```cpp
Desctructor(3) [heap address]
```
#### add noexcept
```cpp
MyClass(MyClass&& other) noexcept {...};
```
Si le move constructor n'est pas marqué noexcept:
- Les containers de la STL (comme std::vector, std::map, etc) vont préférer copier plutôt que déplacer lors de réallocation or réorganisation
- Car s'il déplacent un object et que le move throw une exception, ils risquent de corropre la structure du container
```cpp
if(std::is_nothrow_move_constructibe<T>::value)
  move element;
else
  copy elements;
```
#### La règle des 5 / règle 0 /règle 6
| Nom                     | Contenu                                                                                                                                                                 |
| ----------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Règle des 5**         | Si tu définis un des 5 suivants, tu dois souvent en définir les autres : <br> - destructeur<br> - copy constructor<br> - copy assignment<br> - move constructor<br> - move assignment |
| **Règle des 0**         | Si tu peux, laisse le compilateur tout générer : RAII via smart pointers & containers                                                                                   |
| **Règle des 6** (C++20) | Ajoute l’**opérateur de comparaison par défaut `operator<=>`** à la règle des 5                                                                                         |
Si tu déclares l’un d’eux, le compilateur ne génère pas automatiquement les autres → risque de comportement inattendu ou inefficace.

#### = default et delete
- Contrôle explicite de ce que le compilateur peut générer
```cpp
class MyClass
{
  public:
    MyClass() = default; // explicite
    MyClass(const MyClass&) = delete; // interdit la copie
};
```
- Permet des optimisation en forçans certains appels à être en-ligne ou supprimés.
- STL utlise ça partout pour contr-oler la sémentique des types.
#### Trivialité / StandardLayout / POD
Ces propriétés influencent comment la STL traite ton type (via type_traits) :
| Propriété                        | Ce que cela implique                                  |
| -------------------------------- | ----------------------------------------------------- |
| `std::is_trivially_copyable`     | Peut être copié par `memcpy`, aucune logique spéciale |
| `std::is_trivially_destructible` | Pas besoin d’appeler de destructeur explicitement     |
| `std::is_standard_layout`        | Le layout mémoire est compatible C (interopérabilité) |
| `std::is_pod` (pré-C++20)        | Plain Old Data = trivial + standard layout            |
ces propriétés sont utiliséées par la STL pour accélérer des algos

#### [[nodiscard]], explicit, consteval, constexpr
##### [[nodiscard]]: 
Le compilateur génère un avertissement si tu appelles une fonction ou crées un objet dont la valeur de retour est ignorée.
Syntaxe
```cpp
[[nodiscard]] int compute();
```
Example:
```cpp
[[nodiscard]] int divide(int a, int b) {
    return a / b;
}

void test()
{
  divide(10, 2); // ⚠️ Avertissement : la valeur retournée est ignorée
}
```
Cas typiques :
- Fonctions qui retournent des error_code, bool, Result, Status, etc.
- Objet RAII que tu ne veux pas que l’utilisateur jette.
```cpp
[[nodiscard]] std::error_code do_something();
```
##### explicit:
Le mot-clé explicit interdit la conversion implicite d'un argument vers  type (par appel au constructeur)
```cpp
explicit MyClass(int); // empêche: MyClass c = 42;
```
Example
```cpp
struct MyClass {
    explicit MyClass(int x) { std::cout << "MyClass(" << x << ")\n"; }
};
void foo(MyClass m) {}
void test()
{
  foo(42);      // ❌ erreur si le constructeur est `explicit`
  foo(MyClass(42)); // ✅ OK
}
```
Sans explicit, l’appel foo(42) serait automatiquement converti en MyClass(42), ce qui est souvent dangereux ou ambigu.
 Bonnes pratiques :

Toujours utiliser explicit sur les constructeurs à un seul argument, sauf si une conversion implicite est voulue.

  Utilisé pour éviter des bugs subtils
##### consteval
Une fonction consteval doit être appelée à la compilation, sinon il y a une erreur de compilation.
Plus scrit que constexpr
```cpp
consteval int square(int x) { return x*x;}
```
Example:
```cpp
consteval int add(int a, int b) {
    return a + b;
}
int main() {
    constexpr int x = add(2, 3); // ✅ OK : évaluation à la compilation
    int y = 10;
    int z = add(y, 1); // ❌ Erreur : `add` ne peut pas être appelée à l'exécution
}
```

consteval exige que l’appel de la fonction soit fait à la compilation, tandis que constexpr le permet seulement si les conditions sont réunies.

| Attribut                 | `constexpr`                          | `consteval`                                     |
| ------------------------ | ------------------------------------ | ----------------------------------------------- |
| Appel à l'exécution ?    | ✅ Oui si pas en contexte `constexpr` | ❌ Interdit — compile error                    |
| Appel à la compilation ? | ✅ Oui                                | ✅ Obligatoire                                 |
| Souplesse                | ✅ Plus souple (polyvalent)           | ❌ Plus strict (compiler-only)                 |
| Usage typique            | fonctions optimisables               | fonctions **réservées à des calculs constants** |
| C++ version              | Depuis C++11 (amélioré C++14, C++20) | Introduit en C++20                              |

#### comparatif constexpr & consteval
##### constexpr
```cpp
constexpr int square(int x)
{
  return x * x;
}

int runtime_val = 3;
int x1 = square(5);         // ✅ compilation
int x2 = square(runtime_val); // ✅ exécution (appel non constexpr)
```
=> square() peut être évaluée à la compilation si l'appel est constexpr, sinon elle est exécuté normalement
##### consteval
```cpp
consteval int cube(int x)
{
  return x * x * x;
}
int x1 = cube(5); // ✅ OK, 5 est connu à la compilation
int y = 3;
int x2 = cube(y); // ❌ Erreur de compilation : `y` est une valeur runtime
```
Quand préférer consteval à constexpr ?
Utilise consteval quand :
- tu veux forcer une évaluation à la compilation,
- la fonction n’a de sens qu’à compile-time,
- tu veux éviter toute exécution possible à runtime.
Cas d’usage typiques de consteval
| Cas                             | Exemple                                                     |
| ------------------------------- | ----------------------------------------------------------- |
| Générer une clé de hachage fixe | `consteval uint32_t hash(const char*)`                      |
| Générer un ID de type ou nom    | `consteval std::string_view type_name()`                    |
| Indexation statique / dispatch  | `consteval int index_of<T>()`                               |
| Static assertions complexes     | `static_assert(my_check(x));` où `my_check` est `consteval` |

#### Empty Base Optimization (EBO)
- Si tu fais hériter une classe vide d'une autre, le compilateur peut supprimer sa taille (layout-aware)
```cpp
struct Empty{};
struct Derived : Empty
{
  int x;
};
```
- sizeof(Derived) == sizeof(int)
STL l'utilise pour optimiser std::functio, std::tuple, std::pair, etc
#### std::move_if_noexcept
Utilisé par la STL pour faire
```cpp
if constexpr(std::is_nothrow_move_constructibe<T>::value)
{
  move(x);
}
else if constexpr(std::is_copy_constructible<T>::value)
{
  copy(x);
}
```
- Permet de choisir la meilleur stragégie de transfert sans compromettre la sûreté

#### Alignement (aglinas, alignof)
- Important pour optimisation SIMD, cache line etpour les structures en shared memory ou hardware-specific
#### Final / override
```cpp
class Base
{
  virtual void foo();
};
class Derived final : public Base
{
  void foo() override; // décurise l'intention
};
```
- override: le compilateur vérifie que la surchare bien une méthode virtuel
- final: interndit d'hériter de cette classe


### Optimisation:
#### const vs constexpr
Faut-il préférer constexpr ou const ?
- Pour des valeurs littérales et utilisables à la compilation → constexpr
- Pour une valeur connue à l’exécution mais non modifiable → const
Donc ici : constexpr est parfaitement adapté, car :
- la valeur est connue au moment de la compilation,
- elle peut être utilisée dans des expressions static_assert, std::array, etc.
##### Exemple: calcul
```cpp
#include <iostream>

constexpr int VIDEO_WIDTH  = 1920;
constexpr int VIDEO_HEIGHT = 1080;

constexpr int surface(int width, int height) {
    return width * height;
}

int main() {
    constexpr int total_pixels = surface(VIDEO_WIDTH, VIDEO_HEIGHT);

    std::cout << "Résolution : " << VIDEO_WIDTH << "x" << VIDEO_HEIGHT << "\n";
    std::cout << "Nombre total de pixels : " << total_pixels << "\n";

    return 0;
}
```
- Le compilateur va remplacer la valeur de total_pixels par la vrai valeur à la compilation.
- Il n'y a aucune instruction d'execution pour le calcul
##### Example Array
- utiliser constexpr pour initialiser une table de valeurs à la compilation (LUT,masque, configuration fixe, ext)
```cpp
#include <array>
#include <iostream>

constexpr std::array<int, 10> generate_squares() {
    std::array<int, 10> arr = {};
    for (int i = 0; i < 10; ++i)
        arr[i] = i * i;
    return arr;
}

int main() {
    constexpr auto squares = generate_squares();

    for (int val : squares)
        std::cout << val << " ";
    std::cout << "\n";
}
```
- Ce tableau est entièrement généré à la compilation, sans boucle à l'exécution
##### Example Class
- définir une classe entièrement utlisable à la compilation, si toutes ses méthodes et sontructeurs sont constexpr
```cpp
#include <iostream>

class Resolution {
    int width_;
    int height_;

public:
    constexpr Resolution(int w, int h) : width_(w), height_(h) {}
    constexpr int width() const { return width_; }
    constexpr int height() const { return height_; }
    constexpr int area() const { return width_ * height_; }
};
int main()
{
  constexpr Resolution full_hd(1920, 1080);
  static_assert(full_hd.area() == 2073600, "Surface incorrecte");
  std::cout << "Résolution : " << full_hd.width() << "x" << full_hd.height() << "\n";
}
```

- Idomatique: Une manière typique, naturelle, reconnue de d'exprimer dans un langage.
  - utiliser une structure d'écritire
  - reconnue par la communauté C++
  - claire, efficace, robuste et expressive
  - souvent optimisée par le compilateur  
| Idiome                                              | Description concise                                                                               | Bénéfice principal                         | Extrait/code                          |
| --------------------------------------------------- | ------------------------------------------------------------------------------------------------- | ------------------------------------------ | ------------------------------------- |
| **RAII** (*Resource Acquisition Is Initialization*) | Gestion automatique des ressources (fichier, mutex, socket) via objets                            | Plus de `new/delete`, pas de fuite mémoire | `std::lock_guard`, `unique_ptr`       |
| **Rule of 5 / Rule of 0**                           | Si tu gères une ressource → définis les 5 opérateurs spéciaux. Sinon, laisse faire le compilateur | Sécurité de copie/déplacement              | `= default`, `= delete`               |
| **Copy and Swap**                                   | Écriture simple, sûre et exception-safe de `operator=`                                            | Empêche corruption d’état                  | `MyClass& operator=(MyClass rhs)`     |
| **Curiously Recurring Template Pattern (CRTP)**     | Classe qui hérite de son template parent pour faire du polymorphisme statique                     | Aucune surcharge dynamique, inlining total | `template<typename T> class Base`     |
| **pImpl** (*Pointer to Implementation*)             | Séparer l’interface (header) de l’implémentation (source)                                         | Réduction des dépendances, ABI stable      | `class Foo { struct Impl; Impl* p; }` |
| **Constexpr all the things**                        | Evaluation à la compilation partout où c’est possible                                             | Zéro coût à l’exécution                    | `constexpr int compute(...)`          |
| **Strong typedefs / tag dispatch**                  | Création de types différents sans coût (avec `struct` vides ou `enum class`)                      | Plus de clarté, surcharge des fonctions    | `struct Meters { double value; };`    |
| **SFINAE / Concepts (C++20)**                       | Contraindre les templates proprement (remplace SFINAE classique)                                  | Meilleurs messages d’erreurs, plus clair   | `template <Integral T>`               |
| **Lambda capture by move** (C++14+)                 | Capturer un `unique_ptr` ou un `std::vector` dans une lambda par `std::move`                      | Sécurité mémoire, logique propre           | `[p = std::move(ptr)]() {}`           |
| **std::move\_if\_noexcept**                         | Choisit entre `move` et `copy` en fonction de la sûreté                                           | Robustesse des containers STL              | `std::move_if_noexcept(obj)`          |
| **Trivial types optimisés**                         | Créer des types trivials pour être compatibles avec `memcpy`, placement new, etc.                 | Performances bas niveau                    | `is_trivially_copyable_v<T>`          |
| **Compile-time introspection**                      | Utiliser `std::is_*`, `if constexpr`, ou `requires` pour adapter le code                          | Code générique optimisé et sûr             | `if constexpr (std::is_enum_v<T>)`    |
| **std::unique\_ptr\<T\[]>**                         | Gestion RAII des tableaux dynamiques (remplace `delete[]`)                                        | Zéro fuite mémoire, zéro overhead          | `unique_ptr<int[]> p(new int[100])`   |
| **Monostate pattern (std::monostate)**              | Pour que `std::variant` ait une valeur "vide par défaut"                                          | Initialisation propre                      | `std::variant<std::monostate, A, B>`  |
| **\[\[nodiscard]] / explicit / override / final**   | Spécificateurs modernes pour prévenir les erreurs silencieuses                                    | Sécurité et lisibilité                     | `[[nodiscard]]`, `explicit Foo(int)`  |



| Usage                     | `constexpr` t’apporte…                            |
| ------------------------- | ------------------------------------------------- |
| `std::array`              | allocation fixe, remplie à la compilation         |
| `constexpr class`         | objets entiers éligibles au `static_assert`, etc. |
| `constexpr function`      | fonctions évaluées à la compilation               |
| `static_assert` + logique | sécurité logique à la compilation                 |
### Inheritance

### Polymorphism
Polymorphism: 
- in the context of inheritance is treat object of different type as the same type. 
- We can treat different derived class as their base class.
- Usefull with container to hold different objects from the same base class.
### Virtual function specifier