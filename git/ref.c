#include "./header/hash.h"
#include "./header/list.h"
#include "./header/work.h"
#include "./header/commit.h"
#include "./header/ref.h"

/*EXERCICE 7*/

//Q7.1
void initRefs() {
    if (!file_exists(".refs")){
        system("mkdir .refs");
    }
    if (!file_exists(".refs/master")){
        system("touch .refs/master");
        createUpdateRef("master", "");
    } 
    if (!file_exists(".refs/HEAD")){
        system("touch .refs/HEAD");
        createUpdateRef("HEAD", "");
    }
}

//Q7.2
void createUpdateRef(char* ref_name , char* hash){
    char buffer [100];
    sprintf(buffer, "echo %s > .refs/%s",hash,ref_name);
    system(buffer);
}

//Q7.3
void deleteRef(char* ref_name){ 
    char buff [256];
    sprintf(buff, ".refs/%s",ref_name);
    if (!file_exists(buff)){
        printf("la reference %s n'existe pas\n",ref_name);
    }
    else{
        sprintf(buff,"rm .refs/%s ",ref_name);
        system(buff);
    }
}

//Q7.4 a controler pour être sur 
char* getRef(char* ref_name){ 
    char* result = malloc(sizeof(char)*256); 
    char buff [256];
    sprintf(buff, ".refs/%s", ref_name);
    if (!file_exists(buff)){
        printf("La référence %s n'existe pas\n", ref_name);
        return NULL; 
    }
    FILE *fp = fopen(buff, "r"); 
    if (fp == NULL) {
        printf("Error opening file.\n");
        return NULL; 
    }
   
    fgets(result , 256, fp); 
    fclose(fp);
    
    int len = strlen(result);
    if (len > 0 && result[len-1] == '\n') {
        result[len-1] = '\0';
    }


    return result;
}

//Q7.5
void createFile(char* file){ 
    char buff [100];
    sprintf(buff, "touch %s", file);
    system(buff); 
}

void myGitAdd(char* file_or_folder){
    WorkTree * wt;
    if (!file_exists(".add")){
        createFile(".add");
        wt = initWorkTree();
    } else {
        wt = ftwt(".add");
    }
    if (file_exists(file_or_folder)){
        appendWorkTree(wt,file_or_folder,NULL,0); //Quand on append dans le WorkTree, le hash et le mode n'ont pas d'importance, en effet il auront une importance dans la fonction saveWorkTree c'est à ce moment la que nous entrerons le vrai hashh et le bon mode 

        wttf(wt,".add");
    } else {
        printf("Le fichier ou repertoire n'existe pas\n");
    }
    freeWorkTree(wt);
}


//Q7.6
void myGitCommit(char* branch_name , char* message){ 
    if (!file_exists(".refs")){
        printf("Il faut d’abord initialiser les références du projet");
        return; 
    }
    char buff [256];
    sprintf(buff, ".refs/%s", branch_name); 
    if (!file_exists(buff)){
        printf("La branche n'existe pas\n");
        return; 
    }
    char* last_hash = getRef(branch_name); 
    char* head_hash = getRef("HEAD");
    if(strcmp(last_hash ,head_hash)!=0){
        printf("HEAD doit pointer sur le dernier commit de la branche\n");
        return; 
    }
    WorkTree* wt = ftwt(".add");
    char* hashwt = saveWorkTree(wt, "."); 
    Commit* c = createCommit(hashwt);
    if (strlen(last_hash)!=0){
    commitSet(c,"predecessor",last_hash); }
    if (message != NULL){
        commitSet(c, "message", message);
    }
    
    char* hashc = blobCommit(c); 
    createUpdateRef(branch_name , hashc); 
    createUpdateRef("HEAD", hashc); 
    createUpdateRef(branch_name, hashc); 
    system("rm .add");

    //Ne pas oublier la libération de la mémoire 
    freeCommit(c);
    free(head_hash);
    freeWorkTree(wt);
    free(hashc);
    free(last_hash);
    free(hashwt);
}

