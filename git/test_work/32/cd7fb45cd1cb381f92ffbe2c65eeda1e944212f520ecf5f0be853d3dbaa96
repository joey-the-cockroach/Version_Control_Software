#include "list.h"

int main(){

    List *L =listdir("."); // liste des éléments dans le répertoire courant

    List ptr = * L ;
    printf("les noms de fichiers et/ou repertoires dans le repertoire courant sont :\n");
    while ( ptr != NULL ) {
        printf("%s\n", ptr->data);
        ptr = ptr->next ;
    }

    char* file = "main3.c"; // Chemin du fichier à copier et créer un instantané

    //Test de l'existance du fichier file
    if (file_exists(file)){
    	printf("le fichier %s existe\n", file);
    }
    else{
    	printf("le fichier %s n'existe pas\n", file);
    }

    // Copie le fichier pointé par file vers le fichier pointer par to qui est ici le fichier "fichier.tmp"
    char* to = "fichier.tmp"; 
    cp(to, file);

    if (compare_files(file,to)==1){
        printf("Le fichier:%s exitse\n",file);
    }
    else{
      printf("Le fichier:%s exitse pas\n",file);  
    }
     
    // Obtient le chemin du fichier à partir de son hash
    char* hash = sha256file("fichier.tmp");
    char* path = hashToPath(hash);
    printf("Chemin pour le hash '%s': '%s'.\n", hash, path);

    blobFile("fichier.tmp");//creation d'un instantané.

    freeList(L);
    free(hash);
    free(path);

    return 0;
}
