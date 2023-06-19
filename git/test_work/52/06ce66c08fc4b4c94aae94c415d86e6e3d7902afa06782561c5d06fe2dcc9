#include "hash.h"

int main(){

    char* hash = sha256file("main1.c"); //On recupère la valeur du hash de notre fichier main1.c
    printf("Hash de main1.c : %s\n", hash); //On l'affiche au terminal

    int res = hashFile("main1.c", "hash.main1.txt");
    
    free(hash);
    
    return res;
}
