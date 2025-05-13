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