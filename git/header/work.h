#ifndef WORK_H
#define WORK_H

#include <errno.h>

typedef struct{
    char *name;
    char* hash;
    int mode;
} WorkFile; //Représente un fichier ou un repértoire dont on souhaite enregistrer un instantanée

typedef struct{
    WorkFile *tab;
    int size;
    int n;
}WorkTree;  //Un WorkTree est un tableau de Worfile

WorkFile* createWorkFile(char* name);
char* wfts(WorkFile* wf);
WorkFile* stwf(char* ch);
WorkTree* initWorkTree();
int inWorkTree(WorkTree* wt, char* name);
int appendWorkTree(WorkTree * wt , char * name , char * hash , int mode );
WorkTree* ftwt(char* file);
int wttf(WorkTree* wt, char* path);
WorkTree* stwt(char* ch);
char* wtts(WorkTree* wt);
void afficheWorkFile(WorkFile* wf);
void afficheWorkTree(WorkTree* wt);


int getChmod(char* path);
void setMode(int mode, char* path);
void printWorkTree(WorkTree* wt);
char* hashToFile(char* hash);
char* blobWorkTree(WorkTree* wt);
char* concat_paths(char* path1, char* path2);
char* saveWorkTree(WorkTree* wt, char* path);
int isWorkTree(char* hash);
void restoreWorkTree(WorkTree* wt, char* path);
void freeWorkFile(WorkFile * wf);
void freeWorkTree(WorkTree * wt);

#endif
