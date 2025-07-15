## Memory
1. Qu’est-ce que l’alignment mémoire** ?
L’alignment mémoire (ou memory alignment) décrit la façon dont les données sont disposées en mémoire pour respecter les contraintes de l’architecture matérielle.
Concrètement :
    Certaines architectures (CPU, GPU) lisent plus rapidement ou exigent que certaines variables soient stockées à des adresses multiples de leur taille (ou d’une taille donnée).
    Exemple : un int32_t (4 octets) est souvent aligné sur un multiple de 4.
    Cela permet au processeur ou au contrôleur mémoire de lire ou écrire en une seule opération efficace.

En C/C++ :
    Le compilateur aligne automatiquement les membres des structures pour éviter des lectures lentes ou des fautes d’accès mémoire.
    On peut contrôler l’alignement avec alignas, __attribute__((aligned)), ou __align__ en CUDA.

2. Lien avec alignof
En C++ alignof(type) donne l’alignement requis pour un type.
```cpp
std::cout << alignof(int) << std::endl; // souvent 4
std::cout << alignof(double) << std::endl; // souvent 8
```
3. Lien avec l’aliasing** ?
- L’aliasing (pointer aliasing) décrit une situation où deux pointeurs accèdent à la même zone mémoire, ce qui peut rendre certaines optimisations dangereuses.
- L’alignment concerne où une variable est placée en mémoire.
- Les deux peuvent se combiner : un mauvais aliasing + un mauvais alignement = perte de performance ou bugs subtils.


 4. En CUDA ?
Sur GPU, l’alignement est encore plus important car :
- Les threads d’un warp lisent en mémoire globale de façon optimisée si les données sont alignées (et coalescées).
- Mal aligner des structures peut provoquer plusieurs transactions mémoire au lieu d’une seule.
- On utilise souvent __align__ ou __attribute__((aligned(N))) pour forcer un alignement correct
Exemple CUDA :
```cpp
struct __align__(16) MyStruct {
    float x, y, z, w;  // aligné sur 16 bytes
};


| Concept       | Définition                                                       |
| ------------- | ---------------------------------------------------------------- |
| **Alignment** | Contrôle la position en mémoire pour maximiser les performances. |
| **alignof**   | Donne la taille d’alignement requise pour un type.               |
| **Aliasing**  | Plusieurs pointeurs sur la même zone mémoire.                    |
