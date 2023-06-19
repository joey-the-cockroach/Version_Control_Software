#include "./header/hash.h"
#include "./header/list.h"

// Exerice 2: Implémentation d'une liste de chaînes de caractères //

// QUESTION 2.1
List* initList(){
    List* L = (List*)malloc(sizeof(List)); //On alloue l'espace en mémoire nécéssaire pour la structure//
    if (!L) { //On vérifie si l'allocation à pu se faire 
		printf("Erreur allocation List\n");
		return NULL;
	}
    *L = NULL;
    return L;
}

// QUESTION 2.2
Cell* buildCell(char * ch){
    Cell* c = (Cell*)malloc(sizeof(Cell));
    c->data = strdup(ch);
    c->next = NULL;
    return c;
}

// QUESTION 2.3
void insertFirst(List* L, Cell* C){
    C->next = *L; 
    *L = C;//Chaînage de la tête de liste 
}

// QUESTION 2.4
char* ctos(Cell* c){
    return c->data;
}

//Convertirt une liste en string 
char *ltos(List *L){ 
	if (L == NULL){
		return "";
	}
	Cell *tmp = *L;
	char *res = (char *)malloc(sizeof(char) * MAX_FILES * N);
	strcpy(res, "");
	while (tmp){
		strcat(res, ctos(tmp));
		if(tmp->next){
            strcat(res, "|");
        }
        tmp = tmp->next;
		
	}
	return res;
}

// QUESTION 2.5
Cell* listGet(List* L, int i){
    Cell* temp = *L;
    int k = 0;
    while (temp != NULL){
        if (k == i) { //1er cas si k=i alors on a trouver la cellule, on sort de la boucle
            break;
        }
        temp = temp->next;
        k++;
    }
    if (temp == NULL){ //2ème cas si temp==NULL alors l'index est hors de plage 
        printf("ERROR:INDEX OUT OF RANGE\n");
    }
    return temp;
}

// QUESTION 2.6
Cell* searchList(List* L, char* str){
    List pc = *L;
    while (pc != NULL && strcmp(str, pc->data) != 0){
        pc = pc->next;
    }
    return pc;
}

// QUESTION 2.7
List* stol(char* s){
    int pos = 0;
    int n_pos = 0;
    int size = strlen(s);
    char* ptr;
    char* result = malloc(sizeof(char) * N); 
    List* L = initList();
    while (pos < size){
        ptr = strchr(s + pos, '|'); //On rechrche la 1ère occurence de '|', nous renvoie un pointeur sur la première occurrence du caractère recherché, ou NULL si le caractère n'est pas trouvé. Le résultat de l'appel de la fonction strchr est stocké dans la variable ptr, qui sera utilisée plus tard pour extraire la sous-chaîne entre les positions pos et n_pos-1.
        if (ptr == NULL){
            n_pos = strlen(s);
        } else {
            n_pos = ptr - s;
        }
        memcpy(result, s + pos, n_pos - pos);
        result[n_pos - pos] = '\0';
        pos = n_pos + 1;
        insertFirst(L, buildCell(result));
    }
    free(result);
    return L;
}

// QUESTION 2.8

List *ftol(char *path) {
  FILE *f = fopen(path, "r");
  if (f == NULL) {
    printf("Erreur lors de l'ouverture du fichier\n");
    return NULL;
  }
  char buffer[100]; 
  fgets(buffer, 100, f);
  fclose(f);
  return stol(buffer);
}


void ltof(List *L, char *path){
    FILE *fp = fopen(path, "w"); // Ouvre le fichier en mode écriture
    if (fp != NULL) { // Vérifie que l'ouverture s'est bien déroulée
        char* r = ltos(L);
        fputs(r, fp); // Écrit la représentation de la liste dans le fichier
        free(r);
        fclose(fp); // Ferme le fichier
    }
}



// Exercice 3: Gestion de fichiers sous git

// QUESTION 3.1
List* listdir(char* root_dir) {
    DIR* dp; // Déclaration d'un pointeur de type DIR
    struct dirent* ep; // Déclaration d'un pointeur de type struct dirent qui servira à stocker les informations d'un fichier ou d'un dossier
    List* L = initList(); // Initialisation d'une liste L vide
    Cell* temp_cell; // Déclaration d'un pointeur de type Cell pour stocker temporairement une cellule
    dp = opendir(root_dir); // Ouverture du répertoire racine
    if (dp != NULL){ // Vérification que l'ouverture s'est bien déroulée
        while ((ep = readdir(dp)) != NULL){ // Tant qu'il y a des fichiers ou des dossiers dans le répertoire
            temp_cell = buildCell(ep->d_name); // Création d'une cellule contenant le nom du fichier ou du dossier
            insertFirst(L, temp_cell); // Ajout de la cellule en tête de liste
        }
        (void)closedir(dp); // Fermeture du répertoire
    }
    else{ // Si l'ouverture du répertoire a échoué
        perror("Couldn't open the directory"); // Affichage d'un message d'erreur
        return NULL; // Retourne NULL pour indiquer qu'il y a eu une erreur
    }
    return L; // Retourne la liste contenant les noms des fichiers et des dossiers du répertoire
}


// QUESTION 3.2

int file_exists(char* file)
{
    struct stat buffer;
    return (stat(file, &buffer) == 0);
}


// QUESTION 3.3
void cp(char *to, char *from){

    if (file_exists(from)){
        char command[500];
        sprintf(command, "cat %s > %s",from,to);
        system(command);
    } 
    else {
        printf("le fichier n'existe pas\n");
    }
}

int compare_files(char *file1, char *file2) {
    FILE *f1, *f2;
    int c1, c2;
    f1 = fopen(file1, "r");
    f2 = fopen(file2, "r");
    if (f1 == NULL || f2 == NULL) { // vérifie si les fichiers sont ouverts avec succès
        printf("Erreur: impossible d'ouvrir les fichiers.\n");
        return -1; // retourne -1 en cas d'erreur
    }
    do {
        c1 = getc(f1); // lit le prochain caractère de f1
        c2 = getc(f2); // lit le prochain caractère de f2
        if (c1 != c2) { // si les caractères sont différents
            fclose(f1); // ferme les fichiers
            fclose(f2);
            return 0; // retourne 0 pour indiquer que les fichiers sont différents
        }
    } while (c1 != EOF && c2 != EOF); // continue tant que ni f1 ni f2 n'ont atteint la fin du fichier
    fclose(f1); // ferme les fichiers
    fclose(f2);
    if (c1 == EOF && c2 == EOF) { // vérifie si les fichiers ont la même taille
        return 1; // retourne 1 pour indiquer que les fichiers sont identiques
    } else {
        return 0; // sinon, retourne 0 pour indiquer que les fichiers sont différents
    }
}

// QUESTION 3.4
char* hashToPath(char* hash)
{
    char* dir = malloc((strlen(hash) + 4) * sizeof(char)); // alloue dynamiquement un tableau de caractères
    dir[0] = hash[0]; // copie le premier caractère du hash dans le premier caractère du chemin
    dir[1] = hash[1]; // copie le deuxième caractère du hash dans le deuxième caractère du chemin
    dir[2] = '/'; // insère le caractère '/' au troisième emplacement du chemin
    int i;
    for (i = 3; i <= strlen(hash); i++) // copie le reste du hash dans le chemin à partir du quatrième caractère
    {
        dir[i] = hash[i - 1];
    }
    dir[i] = '\0'; // ajoute un caractère de fin de chaîne
    return dir; // renvoie le chemin construit
}

// QUESTION 3.5
void blobFile(char* file) {
    // Calcul du hash du fichier
    char *hash = sha256file(file);

    // On crée une copie du hash pour récupérer les deux premiers caractères
    char *ch2 = strdup(hash);
    ch2[2] = '\0'; // On termine la chaîne de caractères à la deuxième position

    // Si le dossier correspondant aux deux premiers caractères n'existe pas alors on le crée
    if (!file_exists(ch2)) {
        char buff[100];
        sprintf(buff, "mkdir %s", ch2); // On construit la commande shell mkdir avec les deux premiers caractères
        system(buff); // On exécute la commande shell pour créer le dossier
    }

    // On calcule le chemin du fichier à partir de son hash
    char *ch = hashToPath(hash);

    // On copie le fichier dans le dossier correspondant à son hash
    cp(ch, file);
    free(hash); 
    free(ch2);
    free(ch);
}

void freeCell(Cell* c){
    free(c->data);
    free(c);
}

void freeList(List *L){
	if(L==NULL){
		return;
	}
    List l = (*L);
    List tmp = NULL;

    while (l!=NULL){
        tmp = l->next;
        free(l->data);
        free(l);
        l = tmp;
    }
    free(L);
}

