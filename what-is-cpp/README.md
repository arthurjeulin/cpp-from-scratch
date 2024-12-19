
## What is cpp ?
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