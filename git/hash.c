#include "./header/hash.h"

// Vers la création d’enregistrements instantanées
// Exerice 1: Prise en main du langage Bash

// QUESTION 1.3
int hashFile(char* source, char* dest){
    char buff[100]; //On déclare un buffer assez grand pour pouvoir socker 
    sprintf(buff, "cat %s | sha256sum > %s", source, dest); //On construit la chaine de caractère qui va représenter la commande shell à execuuter  
    system(buff); //On execute la commande shell qui va écrire le hash du premier fichier pour l'écrire dans le deuxième
    return 1; //On retourne 1 pour indiquer que le calcul du hash s'est bien passé
}

//QUESTION 1.4
char* sha256file(char* file){
    static char template[] = "/tmp/myfileXXXXXX";
    char fname[1000];
    strcpy(fname, template);
    int fd = mkstemp(fname); //Crée un fichier tempporaire dont le nom sera stocké dans fname
    char *res=NULL; //Pointeur sur la chaine de caractères resultante 

    if (fd != -1){ //La fonction mkstemp renvoie -1 si il y a une erreur on entre dans la boucle uniquement si il y a pas d'erreur
        hashFile(file, fname); //On écrit le hash de file dans fname
        FILE *f = fopen(fname, "r");
        char buffer[65];
        fgets(buffer, 65, f); //On récupère la valeur du hash 
        buffer[strlen(buffer)-1]='\0'; //On remplace le dernier caractère par un \O pour indiquer que c'est une chaine de caractère;
        
        char buff[1500]; 
        sprintf(buff, "rm -f %s", fname); // Suppression du fichier temporaire
        system(buff);
        res = strdup(buffer); 
        fclose(f); // On ferme le fichier
    }
    return res; 
}
