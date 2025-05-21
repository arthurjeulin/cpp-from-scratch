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