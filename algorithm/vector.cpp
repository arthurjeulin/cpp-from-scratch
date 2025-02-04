#include <iostream>
#include <vector>

// Abbreviated function template
void print(const auto& vector)
{
  // for based-range loop
  for(const auto& element : vector)
  {
    std::cout << element << "";
  }
  std::cout << "\n";
}

int main()
{
  std::vector<int> my_vector = {1,2,3,4,5};
  print(my_vector); // size of the vector is 5
  my_vector.push_back(6); // add an element at the end of the vector
  print(my_vector); // size of the vector is 6
  my_vector.pop_back(); // remove the last element of the vector
  print(my_vector); // size of the vector is 5
  std::vector<int> another_vector;
  for(int i = 0; i < 10 ; i++)
  {
    std::cout << "Size: " << another_vector.size() << "\n";
    std::cout << "Capacity: " << another_vector.capacity() << "\n";
    another_vector.push_back(i);
  }
  another_vector.clear();
  // reduce the amount of memory used by the vector.
  another_vector.shrink_to_fit();
  // capacity how many elements do we have space for. If we don't have enough
  // space, the vector will have to do a reallocation to find more space.
  // we can see an 2^N allocation over the size of the table
  // Capaticy: 0 -> 1 -> 2 -> 4 -> 8 -> 16 -> 32
  // When size becomes greater than allocation we have to reallocate
  // Important for performances
  // Use reserve  method to increase the capacity of the vector (avoid reallocation)
  // Reserve 10 elements before
  another_vector.reserve(10);
  // avoid to redo allocation over the time
  for(int i = 0; i < 10 ; i++)
  {
    std::cout << "Size: " << another_vector.size() << "\n";
    std::cout << "Capacity: " << another_vector.capacity() << "\n";
    another_vector.push_back(i);
  }
  return 0;
}