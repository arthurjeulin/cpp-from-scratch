# C++ From Scratch
## C++ From Scratch What is cpp ?
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
## C++ From Scratch: Printing

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
## C++ From Scratch: Variables

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
## C++ From Scratch: Conditional Statements
```cpp
#include <iostream>
int main()
{
  int a = 5;
  int b = 10;
  if(a < b)
  {
    std::cout << " a is less than b!\n";
  }
  return 0;
}
```