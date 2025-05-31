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