#include "./header/hash.h"
#include "./header/list.h"
#include "./header/work.h"
#include "./header/commit.h"
#include "./header/ref.h"
#include "./header/branch.h"

/*EXERCICE 8*/

//Q8.1  crée le fichier caché .current branch contenant la chaîne de caractères ”master”
void initBranch(){
    FILE* f = fopen(".current_branch", "w"); 
    if (f==NULL){
        printf("Erreur d'ouverture de fichier\n");
        return ;
    }
    fputs("master",f);
    fclose(f);
}

//Q8.2 vérie l'existance d'une branch
int branchExists(char* branch){
    List* refs = listdir(".refs");
    int res=searchList(refs, branch) != NULL;
    freeList(refs); //On libiefe bien la mémoire allouée pour la liste créer 
    return res;
}

//Q8.3 crée une référence appelée branch qui pointe vers le même commit que la référence HEAD

void createBranch(char* branch){ 
    char* hash = getRef("HEAD"); //on recupere ce sur quoi pointe HEAD 
    createUpdateRef(branch , hash);//pour en faire une reference nommée branche avec le meme hash 
    free(hash);
}

//Q8.4 lit le fichier caché .current_branch pour retourner le nom de la branche courante 
char* getCurrentBranch(){
    FILE* f = fopen(".current_branch", "r"); 
    if (f==NULL){
        printf("Erreur d'ouverture de fichier\n");
        return "";
    }
    char* branche = (char*)malloc(sizeof(char)*100);
    fscanf(f,"%s",branche);
    fclose(f);
    return branche;
}
//Q8.5 
char* hashToPathCommit(char* hash){
    char* path = hashToPath(hash);
    if(strcmp(path, "") == 0){
    	return path;
    }
    strcat(path, ".c");
    return path;
}

 //parcourt la branche appelée branch et pour chacun de ses cmmits affiche son hash ainsi que son message descriptif 
void printBranch(char* branch){
    char* commit_hash = getRef(branch);
    char* commit_path = hashToPathCommit(commit_hash);
    Commit* c = ftc(commit_path);
    while (c != NULL){
        if (commitGet(c, "message")!=NULL)
            printf("%s -> %s \n" ,commit_hash , commitGet(c, "message"));
        else
            printf("%s \n", commit_hash);
        if (commitGet(c, "predecessor")!=NULL){
            commit_hash = commitGet(c, "predecessor");
            c = ftc(hashToPathCommit(commit_hash)); 
        }
        else{
            c = NULL; 
        }
    }
    free(commit_hash);
    free(commit_path);
    freeCommit(c);
}

//Q8.6 construit et retourne une liste chainée contenant le hash de tous les commits de la branch
List* branchList(char* branch){
    List* L = initList();
    char* commit_hash = getRef(branch);
    char* tmp = hashToPathCommit(commit_hash);
    Commit* c = ftc(tmp); 
    while (c != NULL){
        insertFirst(L, buildCell(commit_hash)); 
        if (commitGet(c, "predecessor")!=NULL){
            commit_hash = commitGet(c, "predecessor");
            c = ftc(tmp); 
        }
        else{
            c = NULL; 
        }
    }
    free(tmp);
    free(commit_hash);
    

    return L;
}

//Q8.7 renvoie la liste des hash des commits de toutes les branches (sans répétitions) 
List* getAllCommits(){
    List* L = initList();
    List* content = listdir(".refs");
    for(Cell* ptr = *content; ptr != NULL; ptr = ptr->next){
        if (ptr->data[0] =='.') 
            continue;
        List* list = branchList(ptr->data); 
        Cell* cell = *list;
        while (cell != NULL){
            if (searchList(L, cell->data) == NULL){ 
                insertFirst(L,buildCell(cell->data));
            }
            cell = cell->next; 
        }
    freeList(list);
 
    }
       
    freeList(content);
    return L; 
}
