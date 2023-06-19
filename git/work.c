#include "./header/hash.h"
#include "./header/list.h"
#include "./header/work.h"

// Enregistrement de plusieurs instantanées
// Exercice 4: Fonctions de manipulation de base

// Fonction pour récupérer le mode de permission (chmod) d'un fichier
int getChmod(char* path) {
    struct stat ret; // déclaration d'une structure de type stat pour stocker les informations sur le fichier
    if (stat(path, &ret) == -1) { // récupération des informations sur le fichier et vérification des erreurs
        printf("Error: unable to get chmod for file %s\n", path); // affichage d'un message d'erreur si la récupération échoue
        return -1; // retourne -1 en cas d'erreur
    }
    // Calcul du mode de permissions du fichier
    return (ret.st_mode & S_IRUSR) | (ret.st_mode & S_IWUSR) | (ret.st_mode & S_IXUSR) | // permissions du propriétaire
           (ret.st_mode & S_IRGRP) | (ret.st_mode & S_IWGRP) | (ret.st_mode & S_IXGRP) | // permissions du groupe
           (ret.st_mode & S_IROTH) | (ret.st_mode & S_IWOTH) | (ret.st_mode & S_IXOTH); // permissions des autres
}


// Fonction pour modifier le mode de permission (chmod) d'un fichier
void setMode(int mode, char* path) {
    char buff[100];
    sprintf(buff , "chmod %o %s ", mode , path);
    system(buff);
}

// QUESTION 4.1
WorkFile* createWorkFile(char* name){
    WorkFile *wf=(WorkFile*)malloc(sizeof(WorkFile));
    wf->name=strdup(name);
    wf->hash=NULL;
    wf->mode=0; //initalisé à 0 par défault 
    return wf;
}

// QUESTION 4.2
char* wfts(WorkFile* wf){
    if(wf == NULL){
        return "";
    }
    char* chaine = (char *)malloc(sizeof(char) *1000);
    sprintf(chaine,"%s\t%s\t%d",wf->name,wf->hash,wf->mode);
    return chaine;
}


// QUESTION 4.3
WorkFile* stwf(char* ch){
    char name[100];
    char hash[100];
    int mode;
    sscanf(ch,"%s\t%s\t%d",name,hash,&mode);
    WorkFile* wf = createWorkFile(name);
    wf->hash = strdup(hash);
    wf->mode = mode;
    return wf;
}

// QUESTION 4.4
WorkTree* initWorkTree(){
    WorkTree* wt = (WorkTree*)malloc(sizeof(WorkTree));
    wt->tab = (WorkFile*)malloc(N*sizeof(WorkFile));
    wt->size = N;
    wt->n = 0;
    return wt;
}

// QUESTION 4.5
int inWorkTree(WorkTree* wt, char* name){
    if (wt==NULL){
        printf("WorkTree vide\n");
        return -1;
    }
    for(int i = 0; i < wt->n; i++){
        if(strcmp(wt->tab[i].name,name) == 0){
            return i;
        }
    }
    //printf("%s n'est pas dans le Worktree\n",name);
    return -1;
}

// QUESTION 4.6: ajoute un fichier ou un repértoire dans un WorkTree
int appendWorkTree(WorkTree* wt, char* name, char* hash, int mode){

    int ind = wt->n;

    if (wt->size <= ind){
        printf("Le WorkTree est complet\n");
        return -1;
    }

    if (inWorkTree(wt,name) == -1){
        wt->tab[ind].name = strdup(name);
        if (hash!=NULL){ //Cas utile notamment pour a fonction myGitAdd ou la valeur du hash sera null
        	wt->tab[ind].hash = strdup(hash);
        }else{
            wt->tab[ind].hash=NULL;
        }
        wt->tab[ind].mode = mode;
        wt->n++;
        return 0;
    }

    printf("%s existe deja dans le WorkTree\n",name);
    return -1;
}

//QUESTION 4.7
char* wtts(WorkTree* wt){
    char * chaine = malloc(wt->size*256*sizeof(char));
    strcpy(chaine, "");
    for (int i = 0; i < wt->n; i++){
        char* s = wfts(&(wt->tab[i]));
        strcat(chaine,s);
        free(s);
        if (i!= wt->n-1){ 
            strcat(chaine,"\n");
        }
    }
    return chaine ;
}


// QUESTION 4.8
// string to WorkTree
WorkTree* stwt(char* ch){ 
    int pos = 0;
    int n_pos = 0;
    int sep = '\n';
    char* ptr;
    char* result = malloc(sizeof(char)*10000); WorkTree* wt = initWorkTree();
    while (pos < strlen(ch)){
        ptr = strchr(ch + pos, sep); 
        if (ptr == NULL)
            n_pos = strlen(ch)+1; 
        else{
            n_pos = ptr - ch + 1; 
        }
        memcpy(result, ch+pos, n_pos - pos - 1); //copy dans result
        result[n_pos - pos - 1] = '\0';
        pos = n_pos;
        WorkFile* wf = stwf(result);
        appendWorkTree(wt, wf->name, wf->hash, wf->mode);
    }
    return wt; 
}

// QUESTION 4.9
// WorkTree to file
int wttf(WorkTree* wt, char* path){ 
    FILE *fp = fopen(path, "w");
    char* c = wtts(wt);
    if (fp != NULL){
        fputs(c, fp); //ecrit wtts(wt) dans fp
        free(c);
        fclose(fp);
        return 0;
    }
    return -1; 
}

// QUESTION 4.10
// file to WorkTree

WorkTree* ftwt(char* file){
	FILE* f = fopen(file,"r");
	if (f==NULL){
    	printf("Erreur lors de l'ouverture du fichier\n");
        return NULL;
    }
    WorkTree* wt = initWorkTree();
    WorkFile* wf=NULL;
	char buffer[100];
	while(fgets(buffer,100,f) != NULL){
        wf = stwf(buffer);
        appendWorkTree(wt,wf->name,wf->hash,wf->mode);
        freeWorkFile(wf); 
    }
	fclose(f);
	return wt;
}



/*Nous avons ajouté une Fonction d'affichage de worktree*/
void afficheWorkTree(WorkTree* wt){
    printf("%d fichiers dans WorkTree\n", wt->n);
    for (int i=0; i<wt->n; i++){
        printf("%s (hash: %s, mode: %o)\n", wt->tab[i].name, wt->tab[i].hash, wt->tab[i].mode);
    }
}

void afficheWorkFile(WorkFile* wf){
    printf("%s\t%s\t%d\n",wf->name,wf->hash,wf->mode);
}


// Exercice 5: Enregistrement instantanée et restauration d’un WorkTree

struct stat st = { 0 };

// QUESTION 5.1

// retourne le chemin du hachage dun fichier
char* hashToFile(char* hash){ 
    char* ch2 = strdup(hash); 
    ch2[2] = '\0';
    if (stat(ch2,&st) == -1){
        mkdir(ch2, 0700); 
    }
    free(ch2);
    return hashToPath(hash); 
}

char* blobWorkTree(WorkTree* wt){

    static char template[] = "/tmp/myfileXXXXXX";
    char fname[100];
    strcpy(fname,template);
    mkstemp(fname);

    wttf(wt,fname);

    char* hash = sha256file(fname);
    char* chemin = hashToPath(hash);
    strcat(chemin,".t");

    char* repertoire = strdup(chemin);
    repertoire[2] = '\0';
    /* si le repertoire n'existe pas on le cree */
    if (!file_exists(repertoire)){
        char command1[500];
        sprintf(command1, "mkdir %c%c",chemin[0],chemin[1]);
        system(command1);
    }

    char command2[500];
    sprintf(command2, "cat %s > %s",fname,chemin);
    system(command2);

    free(chemin);
    free(repertoire);

    return hash;
}

// QUESTION 5.2
char* concat_paths(char* path1, char* path2){
    char* result = malloc(strlen(path1) + strlen(path2) + 2); 
    if (result == NULL) {
        printf("Error : unable to allocate memory\n");
        return NULL; 
    }
    strcpy(result, path1); // Copy path1 to result 
    strcat(result, "/"); // Append a slash to result 
    strcat(result, path2); // Append path2 to result 
    return result;
}

//Ajout d'une fonction qui permet de savoir si un fichier est un repertoire/fichier ou non
int isFile(const char* name)
{
    DIR* directory = opendir(name); // Ouvre le répertoire avec le nom donné

    if(directory != NULL) // Si l'ouverture du répertoire réussit, cela signifie que le chemin donné correspond à un dossier
    {
     closedir(directory); // On ferme le répertoire
     return 0; // On retourne 0 pour indiquer que le chemin correspond à un dossier
    }

    if(errno == ENOTDIR) // Si l'ouverture du répertoire échoue et que l'erreur est ENOTDIR, cela signifie que le chemin correspond à un fichier
    {
     return 1; // On retourne 1 pour indiquer que le chemin correspond à un fichier
    }

    return -1; // Si une autre erreur se produit, on retourne -1 pour indiquer une erreur
}



char* saveWorkTree(WorkTree* wt, char* path) {
    chdir(path); // On se place dans le dossier spécifié par le chemin path

    for (int i = 0; i < wt->n; i++) {
        char buffer[1000];
        getcwd(buffer, 1000); // On récupère le chemin du dossier courant
        strcat(buffer, "/");
        strcat(buffer, wt->tab[i].name); // On construit le chemin du fichier ou dossier courant

        if (!isFile(wt->tab[i].name)) { // Si c'est un dossier

            WorkTree* newWT = initWorkTree(); // On initialise un nouveau WorkTree
            List* L = listdir(buffer); // On liste les fichiers et dossiers du dossier courant
            chdir(buffer); // On se place dans le dossier courant

            while ((*L) != NULL) {
                if ((*L)->data[0] == '.') { // On ignore les fichiers et dossiers cachés (commençant par un point)
                    (*L) = (*L)->next;
                    continue;
                }
                appendWorkTree(newWT, (*L)->data, NULL, 0); // On ajoute le fichier ou dossier à newWT
                (*L) = (*L)->next;
            }
            freeList(L); // On libère la mémoire de la liste des fichiers et dossiers

            wt->tab[i].hash = saveWorkTree(newWT, buffer); // On sauvegarde le WorkTree courant dans le dossier courant
            wt->tab[i].mode = getChmod(buffer); // On récupère les permissions du dossier courant
            freeWorkTree(newWT); // On libère la mémoire du nouveau WorkTree
            chdir(path); // On retourne dans le dossier de départ

        } else { // Si c'est un fichier

            blobFile(wt->tab[i].name); // On sauvegarde le fichier
            wt->tab[i].hash = sha256file(wt->tab[i].name); // On calcule le hash du fichier
            wt->tab[i].mode = getChmod(buffer); // On récupère les permissions du fichier

        }
    }
    return blobWorkTree(wt); // On retourne le hash du WorkTree
}

                 
//QUESTION 5.3

int isWorkTree(char* hash){
	char* tmp = hashToPath(hash);
    if(file_exists(strcat(tmp,".t"))){
    	free(tmp);
        return 1; 
    }
    if(file_exists(tmp)){
    	free(tmp);
        return 0;
    }
    free(tmp);
    return -1; 
}

void restoreWorkTree(WorkTree *wt, char *path) {
  for (int i = 0; i < wt->n; i++) {
    char *absPath = concat_paths(path, wt->tab[i].name); // chemin absolu du fichier/dossier à restaurer
    char *copyPath = hashToPath(wt->tab[i].hash); // chemin du fichier/dossier dans le dépôt
    if (isWorkTree(wt->tab[i].hash) == 0) { // si c'est un fichier
      cp(absPath, copyPath); // copier le fichier
      setMode(getChmod(copyPath), absPath); // restaurer les droits sur le fichier
    }
    if (isWorkTree(wt->tab[i].hash) == 1) { // si c'est un dossier
      strcat(copyPath, ".t"); // ajouter l'extension ".t" pour le dossier dans le dépôt
      WorkTree *newWT = ftwt(copyPath); // charger l'arbre de travail pour le dossier à restaurer
      restoreWorkTree(newWT, absPath); // restaurer les fichiers/dossiers dans le dossier à partir de son arbre de travail
      setMode(getChmod(copyPath), absPath); // restaurer les droits sur le dossier
    }
    free(absPath);
    free(copyPath);
    
  }
}

// Libération de la mémoire allouée pour les WorkFiles
void freeWorkFile(WorkFile* wf){
    free(wf->name);
    free(wf->hash);
    free(wf);
}

// Libération de la mémoire allouée pour les WorkTrees
void freeWorkTree(WorkTree* wt){
    if (wt==NULL){
        printf("WorkTree vide\n");
        return;
    }
    for (int i =0; i<wt->n;i++){
        free((wt->tab[i]).name);
        free((wt->tab[i]).hash);
    }
    free(wt->tab);
    free(wt);
}
