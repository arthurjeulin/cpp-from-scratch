# Algorithm

## Iterator 
Provides general way of traversing our standard library container.
Ranges access:
- begin, cbgegin: returns an iterator to the beginning of the container or array.

Compile and Run
```bash
g++ algorithm/iterator.cpp -o build/iterator
build/iterator
```

## Sort
Sort elements in the range first to last.
```cpp
/**
 * Sort the array from the beginning to the end of the array
 */
std::sort(my_array.begin(), my_array.end());
```
Can use constrained algorithms to simplies to no use iterator.
Synthetic sugar, do the same than just above
```cpp
std::vector<int> v {7, 1, 4, 0, -1};
std::ranges::sort(v); // constrained algorithm
```

Compile and Run
```bash
g++ algorithm/sort.cpp -o build/sort -std=c++20
build/sort
```
