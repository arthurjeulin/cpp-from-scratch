## Pointer 

Type of variable that stores an address is a pointer.
A pointer stores the memory address of some type.

Compile and Run
```bash
g++ pointer/pointer.cpp -o build/pointer && build/pointer
```

## Dynamic Allocation
Reserver memory at runtime. We already saw an example with the template library container like std::vector.

A pointer is used to store the address of a piece of memory.

new expression:
- use to allocate memory and return a pointer to the piece of memory just allocated. Example if we allocate memory for a integer it's will return a integer pointer.
- creates and initializes objects with dynamic storage duration, that is, objects whose lifetime is not necessarily limited by the scope in which they were created.

delete expression: Destroyes object(s) previously allocated by the new expression and releases obtained memory area.

Compile and Run
```bash 
g++ pointer/dynamic_allocation.cpp -o build/dynamic_allocation && build/dynamic_allocation
```
Précision:
En C++, les structures int a[] = { ... }; ou char a[] = { ... }; représentent des tableaux (arrays) de type int ou char.

1. Déclaration de tableaux (arrays) statique:
Un tableau (array) est une collection de valeurs de même type, stockées en mémoire de manière contiguë.
```cpp
int a[] = {1, 2, 3, 4, 5};
```
- Type: tableau d'entiers
- Taille: déterminer automatiquement selon le nombre d'élément; (ici 5)
- Mémoire: Les valeurs sont stockées dans des emplcaements consécutifs
Équivalent explicite avec taille définie :
```cpp
int a[5] = {1, 2, 3, 4, 5};
```
Exemple avec char a[]:
```cpp
char a[] = {'H', 'e', 'l', 'l', 'o'};
```
- Type: tableau de caracthères (char)
- Taille: Déterminée automatiquement (ici, 5)
- Pas de terminaison \0 automatiquement, ce n'est pas une chaîneC
Tableau de caractères avec chaîne C (string)
```cpp
char str[] = "Hello";
```
équivalent à: 
- Terminé par \0 (null caracter) automatiquement
```cpp
char str[] = {'H', 'e', 'l', 'l', 'o', '\0'};
```

Attention char str[] est un tableau tandis que char* str est un pointer vers une chaîne de caracter.

En C++, lorsqu’on exécute un programme depuis le terminal avec des arguments, ceux-ci sont transmis au programme via les paramètres argc et argv de la fonction main() :
1. Définition de argc et argv :
- argc (Argument Count):
C’est un entier représentant le nombre total d’arguments passés en ligne de commande, y compris le nom du programme.
- argv (Argument Vector) :
C’est un tableau de pointeurs (char* argv[]), où chaque élément est un argument sous forme de chaîne (char*).

The variables are named argc (argument count) and argv (argument vector) by convention, but they can be given any valid identifier:
```cpp
int main(int num_args, char** arg_strings)
````
is equally valid.

Structure de argv :
- argv[0] : Contient le chemin ou le nom de l’exécutable.
- argv[1], argv[2], … : Contiennent les arguments passés par l’utilisateur.
- Chaque argv[i] est un pointeur vers une chaîne de caractères (char*), terminée par un caractère nul ('\0').

char* argv[] :
	•	argv est un pointeur vers un tableau de pointeurs (char*)
	•	Chaque élément de ce tableau (argv[i]) est un pointeur vers une chaîne de caractères (char[])
	•	Chaque chaîne de caractères se termine par un caractère nul ('\0')

argv (pointeur) -> Tableau de pointeurs vers char
         ┌───────────┬────────────┬───────────┬────────────┬──────────────┐
argv[] : │ argv[0]   │ argv[1]    │ argv[2]   │ argv[3]    │ argv[4]      │
         │ "./programme"│"example.txt"│ "-o"    │ "output"   │ nullptr      │
         └───────────┴────────────┴───────────┴────────────┴──────────────┘

Chaque argv[i] pointe vers une chaîne de caractères terminée par '\0' :
argv[0] -> './programme\0'
argv[1] -> 'example.txt\0'
argv[2] -> '-o\0'
argv[3] -> 'output\0'

```cpp
for (int i = 0; argv[i] != nullptr; ++i) {        // 1️⃣ Boucle sur chaque argument
    cout << "Argument " << i << ": ";
    for (int j = 0; argv[i][j] != '\0'; ++j) {   // 2️⃣ Boucle sur chaque caractère
        cout << argv[i][j];                       // 3️⃣ Affiche chaque caractère
    }
    cout << endl;                                 // 4️⃣ Saut de ligne
}
```
### Dynamic allocation
1. Création du tableau dynamique de pointeurs (char* argv[])
•	char** argv : Pointeur vers un tableau de pointeurs.
•	argv[i] : Chaque pointeur pointe vers une chaîne (char*), elle-même allouée dynamiquement.
2. Libération de la mémoire (delete ou free)
•	Boucle pour désallouer chaque chaîne (argv[i]).
•	Puis désallouer le tableau (argv).

```cpp
#include <iostream>
#include <cstring>  // Pour strcpy
using namespace std;

int main() {
    int argc = 3;  // Nombre d'arguments
    char** argv = new char*[argc];  // Tableau dynamique de pointeurs

    // Allouer et copier des chaînes dynamiquement
    argv[0] = new char[15]; 
    strcpy(argv[0], "./programme");

    argv[1] = new char[10];
    strcpy(argv[1], "Hello");

    argv[2] = new char[20];
    strcpy(argv[2], "C++_Rocks");

    // Affichage des arguments
    for (int i = 0; i < argc; ++i) {
        cout << "Argument " << i << ": " << argv[i] << endl;
    }

    // Désallouer la mémoire
    for (int i = 0; i < argc; ++i) {
        delete[] argv[i];  // Supprimer chaque chaîne
    }
    delete[] argv;  // Supprimer le tableau de pointeurs

    return 0;
}
```
Explications détaillées :
1.	char** argv = new char*[argc];
•	Alloue un tableau de pointeurs (argv[]), chaque élément peut pointer vers une chaîne.
2.	argv[i] = new char[...];
•	Alloue dynamiquement une chaîne de caractères pour chaque argument.
3.	strcpy()
•	Copie une chaîne littérale dans la mémoire allouée.
4.	Désallocation en boucle :
•	delete[] argv[i]; : Libère chaque chaîne de caractères.
•	delete[] argv; : Libère le tableau de pointeurs.

 Version en C (avec malloc et free):
 ```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int argc = 3;
    char** argv = (char**)malloc(argc * sizeof(char*));

    argv[0] = (char*)malloc(15);
    strcpy(argv[0], "./programme");

    argv[1] = (char*)malloc(10);
    strcpy(argv[1], "Hello");

    argv[2] = (char*)malloc(20);
    strcpy(argv[2], "C_Rocks");

    for (int i = 0; i < argc; ++i) {
        printf("Argument %d: %s\n", i, argv[i]);
        free(argv[i]); // Libère chaque chaîne
    }

    free(argv); // Libère le tableau de pointeurs
    return 0;
}
```

### Raw pointer and Smart pointer
"sémantique" signifie: le sens ou le comportement associé à un élément de code.
La sémantique d’un code, c’est ce qu’il veut dire et comment il se comporte.
1. Raw pointers (int*)
```cpp
int* ptr_integer = new int;
int* ptr_integer_array = new int[10];
```
Tu utilises le même type int* dans les deux cas :
- new int alloue un objet unique de type int.
- new int[10] alloue un tableau de 10 éléments de type int.
Mais dans les deux cas, tu reçois un int*, car en C++ les tableaux sont vus comme un pointeur vers leur premier élément. Le type int* est aveugle : il ne sait pas si c’est un seul int ou un tableau.

C’est justement une source classique de bugs quand on oublie d’utiliser delete[] pour libérer un tableau :
```cpp
delete ptr_integer;        // OK
delete ptr_integer_array;  // Erreur : il faut utiliser delete[]
```
2. std::unique_ptr
C++ a corrigé cette ambigüité avec std::unique_ptr en distinguant clairement les deux usages:
```cpp
std::unique_ptr<int> ptr = std::make_unique<int>();       // pour un seul int
std::unique_ptr<int[]> ptr_array = std::make_unique<int[]>(10); // pour un tableau de 10 int
```
- std::unique_ptr<int> : version classique, appelle delete sur le pointeur.
- std::unique_ptr<int[]> : version spécialisée, appelle delete[] automatiquement.
Cela permet :
- Une sémantique explicite (tu sais ce que tu gères).
- Une libération correcte (delete vs delete[]) sans risque d’erreur.

# Deep dive into pointer and memory
## Difference entre string et const char*
```cpp
// Ici pas d'allocation dynamique
const char* name = "Arthur";
```
- "Arthur" est une string literal, c’est-à-dire une chaîne de caractères constante stockée dans la mémoire du programme (segment .rodata => Read-Only Data ni stack ni heap).
- "Arthur" est une string literal stockée en mémoire statique (au moment du chargement du binaire).
- name est une variable locale (sur la stack) qui pointe vers la chaîne "Arthur".

- "Arthur" est un string literal ⇒ de type const char[7]
- Il se convertit implicitement en const char*
- C’est une rvalue (valeur temporaire utilisée dans une expression)

| Élément    | Type            | Catégorie de valeur |
| ---------- | --------------- | ------------------- |
| `"Arthur"` | `const char[7]` | rvalue              |
| `name`     | `const char*`   | lvalue              |

Le pointeur name pointe simplement vers cette zone mémoire en lecture seule.
Une allocation est faite, mais par le compilateur, au moment de la compilation (pas à l'exécution).

Elle est automatiquement gérée par le système → tu n’as pas à la libérer.

"Arthur" : alloué dans .rodata → pas de delete
const char* : pointeur vers chaîne C
std::string : objet avec gestion mémoire automatique
"Arthur" : rvalue de type const char[7]

 Différence entre const char* et std::string comme argument de fonction
```cpp
void f1(const char* txt);
void f2(const std::string& txt);
```
| Critère              | `const char*`                                       | `const std::string&`                       |
| -------------------- | --------------------------------------------------- | ------------------------------------------ |
| Type                 | Pointeur vers `char`                                | Référence constante vers un objet          |
| Sécurité             | Moins sûre (attention au `nullptr`, `strlen`, etc.) | Plus sûre                                  |
| Fonctions            | Nécessite `<cstring>`                               | `.size()`, `.find()`, etc. disponibles     |
| Conversion implicite | Oui depuis string literal                           | Oui aussi (`"Arthur"` → string temporaire) |
| Performance          | Légèrement plus rapide (pas d’objet)                | Négligeable en pratique                    |

- sizeof(name_c) → juste la taille du pointeur (pas de la chaîne)
- sizeof(name_cpp) → taille de l'objet std::string lui-même (pas le buffer qu’il alloue dynamiquement sur le heap)

Comparaison: 
```cpp 
const char* name_c = "Arthur";
const std::string name_cpp = "Arthur";
```
1. const char* name_c = "Arthur";
En mémoire :
- "Arthur" est un string literal → stocké dans le segment .rodata (données en lecture seule).
- name_c est une variable sur la stack qui contient un pointeur vers cette chaîne
Illutration en mémoire
```bash
.rodata :
0x1000 → 'A' 'r' 't' 'h' 'u' 'r' '\0'

Stack :
name_c → 0x1000
```
address dans le segment .rodata 0x1000 
2. const std::string name_cpp = "Arthur";
En mémoire :
- "Arthur" est copié dans un objet std::string sur la stack.
- Ce std::string contient un pointeur vers un buffer dynamique alloué sur le heap (dans la plupart des implémentations).
- Il gère sa propre mémoire (via un destructeur).
Illustration mémoire (approximatif) :
```bash
.rodata :
0x1000 → 'A' 'r' 't' 'h' 'u' 'r' '\0'
Heap :
0x2000 → 'A' 'r' 't' 'h' 'u' 'r' '\0'   ← copie privée faite par le constructeur std::string
Stack :
name_cpp → structure std::string contenant le pointeur vers 0x2000, la taille, la capacité, etc.
```
. Qu’est-ce que le segment .rodata ?
- .rodata = Read-Only Data
- C’est un segment mémoire du binaire contenant les données constantes (littéraux de chaînes, constantes globales const, etc.)
- Il est généralement marqué en lecture seule par le système d’exploitation (protection mémoire).

Contenu typique :
- "Arthur" (chaîne constante)
- const double PI = 3.14;
- static const char* messages[] = {...}

C++ Compilation steps
- Pre-Processor
- Compiler -> assembly code
- Assembler -> Object file.o
- Linker (libraries + .o) Executable file

Voir le contenue de .rodata
```bash
readelf -x .rodata mon_programme
```
### sizeof()
sizeof() retourne une taillle en bytes
- sizeof(char) = 1 (1 byte = 8 bits)
- sizeof(int) = 4 (4 byte = 32 bits)
- sizeof(double) = 8
```cpp
const char* name_c = "Arthur";
std::cout << sizeof(name_c);  // → 8
```
- name_c est de type const char*
- C’est un pointeur
- Sur une architecture 64 bits (x86_64), un pointeur occupe 8 octets = 64 bits
| Architecture | Taille d’un `char*` |
| ------------ | ------------------- |
| 32 bits      | 4 bytes (32 bits)   |
| 64 bits      | 8 bytes (64 bits)   |
### Important: sizeof(pointer) in c++ 
Tous les pointeurs ont la même taille, quel que soit leur type pointé, sur une même architecture.
```bash
char*       → sizeof(char*)       = 8 (sur 64 bits)
int*        → sizeof(int*)        = 8
double*     → sizeof(double*)     = 8
void*       → sizeof(void*)       = 8
char**      → sizeof(char**)      = 8
int (*func_ptr)(double) → sizeof(...) = 8
```
Exception : std::function ou std::shared_ptr
Ce ne sont pas de vrais pointeurs → ce sont des objets qui encapsulent un pointeur et d'autres informations (ex: compteur de références).
```cpp
sizeof(std::shared_ptr<int>)  // souvent 16 ou plus
sizeof(std::function<void()>) // dépend de l’implémentation
```