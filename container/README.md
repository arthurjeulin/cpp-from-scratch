## Container
### Span
```cpp
template<
  class T,
  std::size_t Extent = std::dynamic_extent
> class span
```
Français => "vue" ou "fenêtre" (literal étendue / durée / portée)
The class template span describes an object that can refer to a contiguous sequence of  objects with the first element of the sequece at position zero. A span can either have a static extent, in which case the number of elements in the sequence is known at compile-time and encoded in the type, or dynamic extent
Explication
- Allow us to look at sequence of object without owning the underline memory.
Don't want ownership of the underline memory of this object.
- Look at a subset ob a vector (don't want to own the memory of the vector into a new container)

```bash
 g++ container/span.cpp -o build/span --std=c++20
```