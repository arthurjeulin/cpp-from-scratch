# C++ From Scratch
## Introduction: What is cpp ?
cpp is a compile language that is statically typed.
Compile language =>means can't execute our code directly (not like interpreted language like python).

The compilate translate the source code into a machine language an executable.
Statically type:
- Each value in our program have an associted type.
- The type describe the value (floating number, positive number or a complexe type)
- Statically type means when a type is assign to some variable the type can't change 
  => is static (isn't going to change at runtime)
  => at compile time the compiler know the type to generate the right code.

### first main.cpp!
#### create the file
```bash
vim main.cpp
```
#### write a simple main function
- a function is just a name for a body of code
- return is a keyword in cpp.  
- keyword is a word that is reserved by the language that has a special meaning.
- fonction description: return_type function_name(argument){body}
the simplest cpp program:
```cpp
int main()
{
  return 0; // the main function will return the value 0
}
```
the main function is where the c/c++ program starts the execution.

#### Compile
- g++ is a compiler driver
- main.cpp is our input source file
- -o give a name to the executable file: main
```bash
g++ main.cpp -o main
./main
```
generally return 0 meains that the program executed without errors.
we can get the return value with
```bash
echo $?
```
## Introduction: Printing

cout = character oupout
```bash
vim print.cpp
```
```cpp
#include <iostream> 
/**
  include directive

  Compilation steps:
  - preprocessing
      the preprocessor => find the header file and past them inside the program
      in the example => look for iostream and copy and past its content
  - compilation
  - assembly
  - linking
*/

int main()
{
  std::cout << "Hello World!" << std::endl;
  return 0;
}
```
We are only doing the preprocessor step of the compilation
```bash
g++ -E print.cpp -o print.ii
# print.ii is an intermediaire file type
```
we can see the content of #include <iostream> into print.ii

```cpp
#include <iostream>

int main()
{
  std::cout << "Hello, World!\n";
  return 0;
}
```
We want to print "Hello, World!\n" and use << which is an insertion operator
```bash
g++ print.cpp -o print
./print
```
To keep in mind for the future, std is a namespace and :: is scope resolution
## Introduction: Variables

Variable allows use to give a value a particular name
```bash
vim variable.cpp
```
Into variable.cpp
```cpp
#include <iostream>
int main()
{
  // Define a variable
  // A variable is a name for a value
  // variable declaration
  int var_1;
  // tell to the compiler, need an integer and I'm calling it var_1
  // variable assignation
  var_1 = 10;
  // Good pratice to do variable declaration and initialization on the same ligne
  int var_2 = 30;
  // Avoid to use uninitilize variable
  int var_3 = var_1 + var_2;
  // Print the result
  std::cout << var_3 << "\n";
  return 0;
}
```
compiling the program
```bash
g++ variable.cpp -o variable
./variable
```

Update variable.cpp
```cpp
#include <iostream>
int main()
{
  double var_1 = 10.7;
  double var_2 = 30.23;
  double var_3 = var_1 + var_2;
  // Print the result
  std::cout << var_3 << "\n";
  return 0;
}
```
Recompiling the program
```bash
g++ variable.cpp -o variable
./variable
```
Automatic type deduction: we shouldn't tell to the compiler things the compiler already know
```cpp
#include <iostream>
int main()
{
  /**
   * the declare var_1 as a double: double var_1
   * but we are also assigning to var_1 a double precition variable 10.7
   * the compiler will deduce from the variable assignation the type to the variable 
   */
  auto var_1 = 10.7;
  auto var_2 = 30.23;
  auto var_3 = var_1 + var_2;
  // Print the result
  std::cout << var_3 << "\n";
  return 0;
}
```

auto force use to do initialization and assignation at the same time.
cannot do
```cpp
// not enough context to deduce the variable
auto var;
var = 12;
```
## Introduction: Conditional Statements
```cpp
#include <iostream>
int main()
{
  int a = 11;
  int b = 10;
  if(a < b)
  {
    std::cout << " a is less than b!\n";
  }
  else if(a == b)
  {
    std::cout << "a is equal to be!\n";
  }
  else
  {
    std::cout << "a is great than b!\n";
  }
  return 0;
}
```

## Introduction: std::array
std::array is a container that encapsulates fixed size arrays.
- This container is an aggregate type with the same semantics as a struct holding a C-style array T[N] as its only non-static data member.  
- Unlike a C-style array, it doesn't decay to T* automatically. As an aggregate type, it can be initialized with aggregate-initialization given at most N initializers that are convertible to T: s
```cpp
std::array<int, 3> a = {1, 2, 3};
```
### Qu'est-ce qu'un type agrégé ?

Un type agrégé en C++ est une classe ou une structure qui satisfait certaines conditions, ce qui permet une initialisation directe de ses membres avec une liste d'initialisation (initialisation d'agrégat).
Voici les conditions pour qu'un type soit considéré comme agrégé :
- Il n'a pas de constructeur défini par l'utilisateur.
- Tous ses membres sont publics.
- Il ne possède pas de base de classe.
- Il n'a pas de fonctions membres virtuelles.

Cela signifie qu'un type agrégé se comporte comme un conteneur simple, où les valeurs peuvent être directement affectées aux membres lors de l'initialisation.

Exemple d'un type agrégé:
```cpp
struct Point {
    int x;
    int y;
};

// Initialisation d'agrégat
Point p = {10, 20}; // Initialise p.x = 10 et p.y = 20
```
#### La sémantique d'une struct contenant un tableau de type C T[N]
Lorsqu'une struct contient un tableau de style C comme membre (par exemple int arr[5]), le tableau est directement inclus dans l'objet struct et agit comme un simple tableau de type C. Voici ce que cela signifie :
- Taille fixe :
    - La taille du tableau est fixée à la compilation et fait partie intégrante de la struct.
    - Par exemple :
```cpp
struct MyStruct {
    int arr[5];
};

MyStruct s;
s.arr[0] = 1; // Accès direct aux éléments
```
- Décalage mémoire :
    - Le tableau est directement alloué en mémoire comme partie de l'objet struct.
    - Il ne s'agit pas d'un pointeur, mais d'un tableau réel, ce qui signifie que les éléments du tableau sont contigus avec les autres membres de la struct en mémoire.
- Pas de conversion automatique vers un pointeur :
    - Contrairement à un tableau isolé (comme int arr[5];), un tableau dans une struct ne peut pas être implicitement converti en un pointeur (int*), sauf si vous accédez explicitement à ses éléments.
- Limites :
  - Un tableau de type C a des limites rigides : il ne peut pas être redimensionné dynamiquement, et sa taille est fixe au moment de la compilation.

other example:
```cpp
struct MyStruct {
    int arr[3]; // Tableau fixe
    float value;
};

MyStruct s = {{1, 2, 3}, 4.5}; // Initialisation de tous les membres

// Accès aux éléments du tableau
s.arr[0] = 10;
```
#### Introduction: For Loops
Introduction to C-Style for loop and Range-based for loop (since C++11).
What does a for loop:
Iterate a statement (piece of code) over a certain number of times. We can specify the number of iteration using C-Style loop or iterate over a container with Range-based loop
```bash
g++ introduction/for.cpp -o build/for
./build/for
```
#### Introduction: While Loops

We don't know all the time how many iteration we need to do. Continue to run some piece of code until a condition happens.
while loop: 
while(condition) statement
Executes a statement repeatedly, until the value of condition becomes false.

do while loop: 
do statement while (condition)
Executes a statement repeatedly, until the value of expresisn becomes false.
```bash
g++ introduction/while.cpp -o build/while
./build/while
```

### References
Prevent a copy to happend.
- fonctional reason in the case of a lock
- performance reason, copying a integer is cheap but copying a vector of 10'000'000 integer is going to be expensive.
One of the ways to avoid copying inside cpp is using references.

Declares a named variable as a reference, that is, an alias to an already-existing object or function. 
Compiler
```bash
g++ introduction/references.cpp -o build/references
./build/references
```

### Pass By References

Compiler
```bash
g++ introduction/pass_by_references.cpp -o build/pass_by_references &&
./build/pass_by_references
```


### Qu’est-ce que [[fallthrough]] ?
  Attribut C++ 17.
  Signale explicitement qu’on veut laisser l’exécution tomber (« fall through ») dans le case suivant sans break.
  Évite que le compilateur n’émette un warning (« implicit fallthrough »).