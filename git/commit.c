#include "./header/hash.h"
#include "./header/list.h"
#include "./header/work.h"
#include "./header/commit.h"

/*EXERCICE 6*/

/*QUESTION 6.1: fonction kvp* createKeyVal(char* key, char* val) permettant d’allouer et
d’initialiser un  ́element.Fonction void freeKeyVal(kvp* kv) permettant de liberer la
memoire associe a un  ́element.
*/

kvp* createKeyVal(char* key , char* val){
    kvp* k = malloc(sizeof(kvp));
    k->key = strdup(key);
    k->value = strdup(val);
    return k;
 }


 void freeKeyVal(kvp* kv){
    free(kv->key);
    free(kv->value);
    free(kv);
 }

/*QUESTION 6.2: fonction char* kvts(kvp* k) qui permet de convertir un  ́element en une chaıne
de caracteres de la forme ”cle :valeur”. Fonction kvp* stkv(char* str) qui permet de
faire la conversion inverse.*/

char* kvts(kvp* k){
    if (k==NULL){ //1er cas: si l'element est NULL
        return "";
    }
    char* str = (char*)malloc(sizeof(char)*100);
    sprintf(str,"%s : %s",k->key,k->value);
    return str;
}

kvp* stkv(char* str){
    char key[100];
    char val[100];
    sscanf(str,"%s : %[^\n]",key,val);
    return createKeyVal(key,val);
}

void afficheKeyVal(kvp* kv){
    if (kv != NULL){
        printf("%s : %s\n",kv->key,kv->value);
    }
}

/*QUESTION 6.3: fonction Commit* initCommit() qui permet d’allouer et d’initialiser un Commit de
taille fixee (donn ́ee par une constante du programme).*/

Commit* initCommit (){
    Commit* c = malloc(sizeof(Commit));
    c->T = malloc(Nmaxcommit*sizeof(kvp*));
    c->size = Nmaxcommit;
    for (int i = 0; i<c->size; i++){
        c->T[i] = NULL;
    }
    c->n = 0;
    return c;  
 }

void afficheCommit(Commit *c){
    if (c==NULL){
        printf("le commit est vide\n");
        return ;
    }
    printf("nb commit : %d\tsize : %d\n", c->n,c->size);
    for (int i=0; i<c->size; i++){
        if (c->T[i]){
            afficheKeyVal(c->T[i]);
        }  
    }
}

 /*QUESTION 6.4: une fonction de hachage sur le site : http://www.cse.yorku.ca/~oz/hash.html choix de la 3ème fonction
*/

  unsigned long hash(unsigned char *str) 
    {
	unsigned int hash = 0;
	int c;

	while (c = *str++)
	    hash += c;

	return hash;
    }


/*QUESTION 6.5: une fonction void commitSet(Commit* c, char* key, char* value) qui insere la
paire (key, value) dans la table, en gerant les collisions par adressage ouvert et probing lineaire.
*/
//On stock les elements dans la table de hachage en utilisant la fonction de hachage
void commitSet(Commit* c, char* key , char* value){
    if (c==NULL){
        c = initCommit();
    }
    int cle_hasher = hash(key)%c->size;
    while (c->T[cle_hasher] != NULL){
        cle_hasher = (cle_hasher+1)%c->size; // probing linéaire pour trouver une case vide dans la table de hachage. Si la case correspondant à la clé est déjà occupée, on ajoute 1 à la position de la clé (modulo la taille de la table) et on continue jusqu'à trouver une case vide.
    }
    c->T[cle_hasher] = createKeyVal(key , value);
    c->n++;
}

/*QUESTION 6.6: fonction Commit* createCommit(char* hash)
qui alloue et initialise un Commit, puis ajoute l’element obligatoire correspondant a la cle "tree"*/

Commit* createCommit(char* hash){
    Commit* c = initCommit(Nmaxcommit);
    commitSet(c, "tree", hash);
    return c;
}


/*QUESTION 6.7:  une fonction char* commitGet(Commit* c, char* key) qui cherche dans la table s’il
existe un  ́element dont la cle est key (en sachant que les conflits sont resolus par adressage ouvert et
probing lin eaire). La fonction retourne la valeur de l’ element s’il existe, et NULL sinon.*/

char* commitGet(Commit* c, char* key){
    int p = hash(key) % c->size;
    int attempt=0;
    while (c->T[p] != NULL && attempt < c->size){
        if (strcmp(c->T[p]->key , key) == 0){
            return c->T[p]->value;
        }
        p=(p+1)%c->size;
        attempt=attempt+1;
    }

    return NULL;
}

void freeCommit(Commit* c){
    if (c==NULL){
        return ;
    }
    for (int i = 0; i < c->size; i++){
        if (c->T[i]){
            freeKeyVal(c->T[i]);
        }
    }
    free(c->T);
    free(c);
}

/*QUESTION 6.8: une fonction char* cts(Commit* c) qui convertit un commit en une chaˆıne de ca-
racteres. Cette chaˆıne doit ˆetre composee des chaˆınes de caract`eres representant chacun de ses couples
(cl ́e, valeur), s ́epar ́ees par un saut de ligne.  ́Ecrivez ensuite une fonction Commit* stc(char* ch) qui
r ́ealise la conversion inverse*/

char* cts(Commit* c){
    if (c==NULL){
        return "";
    }
    char* str = malloc(sizeof(char)*100*c->n);
    strcpy(str, "");
    for (int i = 1; i < c->size; i++){
        if(c->T[i] != NULL){
            char* tmp = kvts(c->T[i]);
            strcat(str , tmp);
            strcat(str , "\n");
            free(tmp);
        }
    }
    return str;
}


Commit* stc(char* ch){
    Commit* c = initCommit ();
    if (ch == NULL){
        return c;
    }
    int pos = 0;
    int n_pos = 0;
    int sep = '\n' ;
    char* ptr;
    char* result = malloc(sizeof(char)*10000);
    while (pos < strlen(ch)){
        ptr = strchr(ch + pos , sep);
        if (ptr == NULL)
            n_pos = strlen(ch)+1;
        else
            n_pos = ptr - ch + 1;
        memcpy(result , ch+pos , n_pos - pos - 1);
        result[n_pos - pos - 1] = '\0' ;
        pos = n_pos;
        kvp* elem = stkv(result);
        commitSet(c, elem->key , elem->value);
        freeKeyVal(elem);
    }
    free(result);
    return c;
}

/*QUESTION 6.9:une fonction void ctf(Commit* c, char* file) qui  ́ecrit dans le fichier file la
chaˆıne de caract`eres repr ́esentant le commit c.  ́Ecrivez la fonction Commit* ftc(char* file) qui
permet de charger un Commit depuis un fichier le repr ́esentant*/

Commit* ftc(char* file){
	if(strcmp(file, "")==0){
		return NULL;
	}
    char buff[MESSAGE_SIZE];
    char *all = malloc(sizeof(char)*MESSAGE_SIZE);
    strcpy(all, "");
    FILE *f = fopen(file, "r");
    if(f==NULL){
        printf("Erreur lors de l'ouverture du fichier\n");
        return NULL;
    }
    while(fgets(buff,N,f)!=NULL){
        strcat(all,buff);
    }
    fclose(f);
    Commit *c=stc(all);
    free(all);
    return c;
}

void ctf(Commit* c, char* file){
    FILE* f = fopen(file,"w");
    if (f==NULL){
        printf("Erreur lors de l'ouverture du fichier\n");
    } else{
        char* tmp = cts(c);
        fputs(tmp,f);
        free(tmp);
        fclose(f);  
    } 
}


/*Question 6.10: char* blobCommit(Commit* c) cree un enregistrement instantan ́e d’un Commit en passant par
un fichier temporaire. Cette fonction devra retourner le hash du fichier temporaire*/
char *blobCommit(Commit *c) {
  char fname[100] = "/tmp/myfileXXXXXX";
  int fd = mkstemp(fname);
  ctf(c, fname);
  char *hash = sha256file(fname);
  char *ch = hashToFile(hash);
  strcat(ch, ".c");
  cp(ch, fname);
  free(ch);
  return hash;
}
