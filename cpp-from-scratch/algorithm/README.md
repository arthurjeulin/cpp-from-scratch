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

## Vector 
When we don't know how many elements we want into the containers.
For std::array<> the number of element in the table has to be known at compile time.

- std::vector is a sequence container that encapsulates dynamic size arrays.
- The elements are stored contiguously, which means that elements can be accessed not only through iterators, but also using offsets to regular ponters to elements.
This means that a pointer of element of vector my be passed to any function that expects a pointer to
an element of an array.
- The storage of the vector is handled automatically, being expanded as needed.
- Vectors usualy occupy more space than static arrays, because more memory is allocated to handle future growth. This way a vector does not need to reallocated each time an element is inserted, but only when the additional memory is exhausted.
- The total amount of allocated memory can be queried using capacity() function.
- Extra memory can be returned to the system via a call to shrink_to_fit()
- Reallocations are usually costly operations in terms of performance.
- The reserver() function can be used to eliminate reallocation if the number of elements is know beforehand.

The complexity (efficiency) of common operations on vectors is as follows:
- Random access - constant O(1)
- Insertion or removals at the end - amortized constant 0(1)
- Insertion or removal of elements - linerar in the distance of the end of the vector O(n)

Different from array the following section:
Capaticy:
- empty: checks whether the container is empty
- size: returns the number of elements
- max_size: return the maximum possible number of elements
- reserver: reserves storage
- capacity: returns the number of elements that the container has currently allocated space for. 
(maximum number of element that can be store before a new allocation)
- shrink_to_fit: reduces memory usage by freeing unused memory
Modifiers
- clear: clears the contents
- insert: insert elements
- insert_range(C++23): inserts a range of elements
- emplace: constructs element in-place
- erase: erases elements
- push_back: adds elementto the tend
- emplace_back(C++11) constructs element in-place at the end
- apprend_range(C++23) adds a range of elements to the end
- pop_back: removes the last element
- resize: changes the number of elements sotred
- swap: swaps the contents
Compile
```bash
g++ algorithm/vector.cpp -o build/vector -std=c++20 &&
build/vector
```
Output
```bash
g++ algorithm/vector.cpp -o build/vector -std=c++20 && build/vector
12345
123456
12345
Size: 0
Capacity: 0
Size: 1
Capacity: 1
Size: 2
Capacity: 2
Size: 3
Capacity: 4
Size: 4
Capacity: 4
Size: 5
Capacity: 8
Size: 6
Capacity: 8
Size: 7
Capacity: 8
Size: 8
Capacity: 8
Size: 9
Capacity: 16
```