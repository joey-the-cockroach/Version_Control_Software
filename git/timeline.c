#include "./header/hash.h"
#include "./header/list.h"
#include "./header/work.h"
#include "./header/commit.h"
#include "./header/ref.h"
#include "./header/branch.h"
#include "./header/timeline.h"

/*EXERCICE 9*/

//Q9.1:permet de restaurer le worktree associé à un commit dont le hash est donné en paramètre
void restoreCommit(char* hash_commit){
    char* commit_path = hashToPathCommit(hash_commit);
    Commit* c = ftc(commit_path);
    
    char* s = commitGet(c, "tree");
    char* path = hashToPath(commitGet(c, "tree"));
    
    char* tree_hash = strcat(path, ".t"); 
    WorkTree* wt = ftwt(tree_hash);
    restoreWorkTree(wt, ".");

    freeWorkTree(wt);
    freeCommit(c);
    free(commit_path);
    free(path);
   
    
    
}

//Q9.2 Nous permet de naviguer entre les branches 
void myGitCheckoutBranch(char* branch){
    FILE* f = fopen(".current_branch", "w"); 
    fprintf(f, "%s", branch);
    fclose(f);
    char* hash_commit = getRef(branch); 
    createUpdateRef("HEAD",hash_commit); 
    restoreCommit(hash_commit);
    free(hash_commit);
}

//Q9.3 retourne une nouvelle liste contenant uniquelent les éléments de L qui commence par la chaine "pattern"
List* filterList(List* L, char* pattern){ 
    List* filtered = initList();
    for (Cell* ptr = *L; ptr != NULL; ptr = ptr->next){
        char* c = strdup(ptr->data); 
        c[strlen(pattern)] = '\0';
        if (strcmp(c, pattern) == 0){
            insertFirst(filtered, buildCell(ptr->data)); 
        }
        free(c); 
    }
    return filtered; 
}

//Q9.4 permettant à l’utilisateur de retourner sur n’importe quelle version de son projet
void myGitCheckoutCommit(char* pattern){
    List* L = getAllCommits();
    List* filtred_list = filterList(L, pattern); 
        if(listSize(filtred_list) == 1){
            char* commit_hash = (listGet(filtred_list , 0))->data;
            createUpdateRef("HEAD",commit_hash); 
            restoreCommit(commit_hash);
            free(commit_hash);
        }
        else{
            if(listSize(filtred_list) == 0){
                printf("No pattern matching .\n"); 
            }
            else{
                printf("Multiple matchings found : \n");
                for (Cell* ptr = *filtred_list; ptr!= NULL; ptr = ptr->next){
                    printf("-> %s \n", ptr->data); 
                }
            }
        }
    freeList(L); //libération de la mémoire
    freeList(filtred_list);
}

int listSize(List *l){ //fonction auxiliaire nous permettant de récupérer la taille d'une liste 
    int cpt=0;
    Cell *c=*l;
  while(c!=NULL){
    cpt++;
    Cell *tmp=c;
    c=c->next;
  }
  return cpt;
}

