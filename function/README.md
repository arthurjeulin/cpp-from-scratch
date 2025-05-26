## Functions
#### Functions
A function allow us to give a name to a sequence of statements we want to execute.
Avoid code duplication. To avoid we can refector a sequence of statement inside a function.
```cpp
return_type function_name()<- parameter list
{
  // function body
  return value_to_return;
}
```
Compile
```bash
g++ introduction/function.cpp -o build/function
build/function
```

Compile
```bash
g++ introduction/return_value.cpp -o build/return_value
build/return_value
```
#### Functions: Function Overloding
- Function overloading
- Overload resolution
Rely on the compiler choose the right function for us.
Based on the signature of the function. The compiler will know which function to call based on a combinaison of function name and the number and order of the parameters inside our parameter list.
2 functions with the exact same name but both functions have differente functions signature.
Compile
```bash
g++ function/overloading.cpp -o build/overloading
./build/overloading
```
#### Functions: Function Templates
Allow use to right a function template to avoid duplication with function with each type
```cpp
#include <array>
#include <iostream>

/**
 * The compiler will create the function with the proper type
 */
template<typename T>
void print_array(const T& array)
{
  for(const auto& element: array)
  {
    std::cout << element ;
  }
  std::cout << "\n";
}

int main()
{
  std::array<int,3> my_int_array = {1,2,3};
  std::array<float,3> my_float_array = {1.1f,2.2f,3.3f};
  // give the version of the template
  print_array<std::array<int,3>>(my_int_array);
  // the compiler will deduce the proper type for the template
  // similar to autotype deduction
  print_array(my_float_array);
  return 0;
}
```
Compile
```bash
g++ function/function_templates.cpp -o build/function_templates
./build/function_templates
```
Compile Abbreviated function template
```cpp
#include <array>
#include <iostream>

/**
 * Abbreviated function template => need C++20
 * delete template<typename T> before the function
 * and use auto instead
 * the compiler will deduced from the auto in the argument list 
 * we want a template<typename T>
 */

void print_array(const auto& array)
{
  for(const auto& element: array)
  {
    std::cout << element ;
  }
  std::cout << "\n";
}

int main()
{
  std::array<int,3> my_int_array = {1,2,3};
  std::array<float,3> my_float_array = {1.1f,2.2f,3.3f};
  // give the version of the template
  print_array<std::array<int,3>>(my_int_array);
  // the compiler will deduce the proper type for the template
  // similar to autotype deduction
  print_array(my_float_array);
  return 0;
}
```
Compile
```bash
g++-11 function/function_templates.cpp -o build/function_templates -std=c++20
./build/function_templates
```
#### Function: Template Specialization
Sometimes we don't want to have the exact same function body for every type.
We need a specialization of the function.
Compile
```bash
g++-11 function/template_spacialization.cpp -o build/template_spacialization -std=c++20
./build/template_spacialization
```
### Fonction avec ou sans nom pour l'argument
La déclaration dans l'en-tête (ou signature) :
```cpp
static void on_media_unprepared(GstRTSPMedia* media, gpointer user_data);
```
Cela déclare une fonction avec ses types d’arguments, y compris ici GstRTSPMedia* media.
Tu donnes un nom à l’argument, ce qui est utile pour :
- la lisibilité
- les cas où tu utiliseras ce paramètre dans le corps de la fonction
La définition avec un argument non utilisé :
```cpp
void RtspStream::on_media_unprepared(GstRTSPMedia*, gpointer user_data)
```
Ici, on définit la fonction, mais on omet le nom du premier paramètre (media) car on ne l’utilise pas dans le corps de la fonction.
Cela sert à éviter un warning du compilateur comme :
```bash
warning: unused parameter ‘media’ [-Wunused-parameter]
```