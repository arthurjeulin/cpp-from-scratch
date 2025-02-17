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