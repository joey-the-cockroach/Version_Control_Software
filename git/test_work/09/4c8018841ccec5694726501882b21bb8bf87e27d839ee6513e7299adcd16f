#include "list.h"

int main() {
    // Création d'une liste vide
    List* L = initList();

    // Ajout de quelques éléments à la liste
    insertFirst(L, buildCell("fichier1.txt"));
    insertFirst(L, buildCell("fichier2.txt"));
    insertFirst(L, buildCell("fichier3.txt"));

    // Affichage de la liste
    char* contenu_L = ltos(L);
    printf("Contenu de la liste L : %s", contenu_L);

    // Recherche d'un élément dans la liste
    char* recherche = "fichier2.txt";
    Cell* resultat = searchList(L, recherche);
    if (resultat != NULL) {
        printf("%s est présent dans la liste.\n", recherche);
    } else {
        printf("%s n'est pas présent dans la liste.\n", recherche);
    }

    // Enregistrement de la liste dans un fichier
    ltof(L, "ma_liste.txt");

    // Chargement de la liste depuis un fichier
    List* L2 = ftol("ma_liste.txt");
    char* contenu_L2 = ltos(L2);
    printf("Contenu de la liste chargée depuis le fichier :%s", contenu_L2);

    //véification 
    printf("Premiere cellule %s\n",(*L2)->data);
    *L2=(*L2)->next;
    printf("Premiere cellule %s\n",(*L2)->data);
    *L2=(*L2)->next;
    printf("Premiere cellule %s\n",(*L2)->data);

    free(contenu_L);
    free(contenu_L2);
    freeList(L);
    freeList(L2);

    return 0;
}
