#ifndef LIST_H
#define LIST_H

#include <dirent.h>
#include <sys/stat.h>

#define MAX_FILES 100
#define N 1000

//Définition de la structure qui va représenter les maillons de notre liste chainée//
typedef struct cell {
    char * data;
    struct cell* next;
} Cell;

typedef Cell* List; //On définit un alias 

List* initList();
Cell* buildCell(char* str);
void insertFirst(List* list, Cell* cell);
char* ctos(Cell* cell);
char* ltos(List* list);
Cell* listGet(List* list, int index);
Cell* searchList(List* list, char* str);
List* stol(char* str);
void ltof(List* list, char* path);
List* ftol(char* path);
void freeList(List *l);
void freeCell(Cell* c);


/*.h pour l'exercice 3 */


// Fonctions pour lister les fichiers et repertoires dans un dossier
List* listdir(char* root_dir);
int file_exists(char* file);

// Fonction pour copier le contenu d'un fichier vers un autre
void cp(char* to, char* from);

// Fonction pour obtenir le chemin d'un fichier a partir de son hash
char* hashToPath(char* hash);

// Fonction pour creer un repertoire et copier le contenu d'un fichier dedans
void blobFile(char* file);

//Fonction pour tester si deux fichiers sont identiques utile pour le test de la fonction cp 
int compare_files( char* path1, char* path2);

#endif
