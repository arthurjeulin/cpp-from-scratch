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
```

| Concept       | Définition                                                       |
| ------------- | ---------------------------------------------------------------- |
| **Alignment** | Contrôle la position en mémoire pour maximiser les performances. |
| **alignof**   | Donne la taille d’alignement requise pour un type.               |
| **Aliasing**  | Plusieurs pointeurs sur la même zone mémoire.                    |


## Storage duration

En C++, la storage duration (ou durée de vie de stockage) désigne combien de temps un object existe en mémoire après a création, qui contrôle sa durée de vie.
Il y a quatre catégories principales de storage duration:
1. Automatic storage duration
    - Les objets locaux à une fonction, déclarées sans static ni thread_local
    - Leur durée de vie est limitée au bloc dans lequels ils sont déclarés
    - Mémoire gérée automatiquement (pile / stack)
    exemple:
    ```cpp
    void foo ()
    {
        int x = 42; // x a une durée de vie automatique
    } // x est détruit ici
    ```
2. Static storage duration
    - Les objets déclarés au niveau global ou avec static ou extern
    - Ils existent pendant toute la durée du programme
    - Mémoire allouée une seule fois
    exemple:
    ```cpp
    static int counter = 0; // Static duration
    int global_var = 1;     // Static duration aussi
    ```
3. Thread storage duration
    - Les objets délcarés avec le mot-lcé thread_local
    - Durée de vie = la durée du thread courant
    example: 
    ```cpp
    thread_local int local_to_thread = 0;
    ```
4. Dynamic storage duration
    - Objets crées avec new ou allocation dynamique (malloc en C)
    - L'objet existe jusqu'a ce qu'on le librée explicitement (delete ou free)
    ```cpp
    int *p = new int(5); // dynamic duration
    delete p; // libération
    ```

| Storage Duration | Allocation          | Libération               |
| ---------------- | ------------------- | ------------------------ |
| Automatic        | Entrée dans le bloc | Sortie du bloc           |
| Static           | Début programme     | Fin programme            |
| Thread           | Début thread        | Fin thread               |
| Dynamic          | `new` / `malloc`    | `delete` / `free` manuel |


General Exemple:
```cpp
#include <iostream>
#include <thread>

// --- Static storage duration ---
int global_var = 42;

thread_local int thread_var = 100; // Thread storage duration

void exampleFunction()
{
    // --- Automatic storage duration ---
    int local_var = 10;

    // --- Dynamic storage duration ---
    int* dynamic_var = new int(20);

    std::cout << "Inside function:\n";
    std::cout << "  local_var (automatic) = " << local_var << "\n";
    std::cout << "  *dynamic_var (dynamic) = " << *dynamic_var << "\n";

    // static local variable -> static storage duration
    static int static_local = 50;
    std::cout << "  static_local (static) = " << static_local << "\n";

    std::cout << "  thread_var (thread) = " << thread_var << "\n";

    // Libération manuelle de l'objet dynamique
    delete dynamic_var;
}

void threadFunction()
{
    thread_var = 200; // Spécifique à ce thread
    exampleFunction();
}

int main()
{
    std::cout << "global_var (static) = " << global_var << "\n";

    std::cout << "\n--- Main thread ---\n";
    exampleFunction();

    std::cout << "\n--- New thread ---\n";
    std::thread t(threadFunction);
    t.join();

    return 0;
}
```

Résultat attendu
- global_var est toujours accessible et existe pendant toute l’exécution (static storage duration).
- thread_var a une valeur différente dans le thread principal et dans le thread secondaire (thread storage duration).
- local_var existe seulement pendant l’appel de la fonction (automatic storage duration).
- dynamic_var doit être libéré avec delete (dynamic storage duration).
- static_local dans la fonction exampleFunction garde sa valeur d’un appel à l’autre (static storage duration, même si c’est une variable locale).

###  Récapitulatif général
| Storage Duration | Emplacement mémoire             | Exemple de segment         |
| ---------------- | ------------------------------- | -------------------------- |
| Automatic        | **Stack**                       | Pile                       |
| Static / global  | **Data segment** ou **BSS**     | `.data` / `.bss`           |
| Thread           | **Thread stack** ou TLS segment | TLS (Thread Local Storage) |
| Dynamic          | **Heap**                        | Tas                        |
| Const / literals | **Read-only segment**           | `.rodata`                  |

Schema Global

```bash
+-------------------------+
|     Text segment (.text)     |  ← Code du programme
+-------------------------+
|   Read-only segment (.rodata) |  ← Constantes
+-------------------------+
|   Initialized data (.data)    |  ← Statics init
+-------------------------+
|   Uninitialized data (.bss)   |  ← Statics non init
+-------------------------+
|             Heap               |  ← new / malloc
|             grows ↑            |
+-------------------------+
|             Stack              |  ← local vars
|             grows ↓            |
+-------------------------+
```

##### Qu’est-ce qu’un TLS segment ?
TLS veut dire Thread Local Storage (stockage local au thread).
C’est une zone spéciale de mémoire où sont stockées les variables marquées thread_local (en C++11+) ou __thread (en C/C++).
Chaque thread a sa propre copie de ces variables, isolée des autres threads.