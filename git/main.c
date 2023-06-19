#include "./header/hash.h"
#include "./header/list.h"
#include "./header/work.h"
#include "./header/commit.h"
#include "./header/ref.h"
#include "./header/branch.h"
#include "./header/timeline.h"
#include "./header/merge.h"
//modif
int main(){   
/*
	//TEST EXO 1: 
    char* hash = sha256file("main.c"); //On recupère la valeur du hash de notre fichier main1.c
    printf("Hash de main.c : %s\n", hash); //On l'affiche au terminal
    int res = hashFile("main.c", "hash.main.txt");
    free(hash);//libération de la mémoire allouée pour avoir aucune fuites de mémoires 
    
    
    //TEST Exercice 2
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

    //LIBERATION DE LA MEMOIRE
    free(contenu_L);
    free(contenu_L2);
    freeList(L);
    freeList(L2);
    freeCell(resultat);
    
    */


    /*
    
    //TEST EXERCICE 3
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

    //LIBERATION DE TOUTES LA MEMOIRE ASSOCIES 
    freeList(L);
    free(hash);
    free(path);

    */
    
    /*
     // TEST Exercice 4
    WorkFile* wf = createWorkFile("workfile");
    char* hash = "hash"; //Hash associé au workfile
    wf->hash = strdup(hash);
    
    char* s = wfts(wf); //On transforme le WorkFile en chaine de caractère pour pouvoir l'afficher
    printf("%s\n",s);
    
    WorkFile* wf2 = stwf("name\t6\t0");
    afficheWorkFile(wf2);
    
    WorkTree* wt3 = initWorkTree();
    appendWorkTree(wt3, "name", "hash",0);
    appendWorkTree(wt3, "name2", "hash2",0);
    appendWorkTree(wt3, "name3", "hash3",0);
    char* str = wtts(wt3);
    printf("%s\n",str);

    wttf(wt3,"WorkTree.txt");


    //LIBERATION DE TOUTE LA MEMOIRE ASSOCIE 
    free(s);
    freeWorkFile(wf);
    freeWorkFile(wf2);
    free(str);
    freeWorkTree(wt3);
    */
    
    /*
    // TEST  Exercice 5   72 ALLOCS 66 FREES
    WorkTree* wt = initWorkTree();
    appendWorkTree(wt, "name", "hash",0);
    appendWorkTree(wt, "name2", "hash2",0);
    appendWorkTree(wt, "name3", "hash3",0);

    char* hashtree = blobWorkTree(wt); //Crée un fichie temporaire représentant notre WorkTree wt5 et retourne son hash complet 
    printf("%s\n",hashtree);//affiche le hash complet du fichier temporaire
 
    
    
    WorkTree* wt6 = initWorkTree();
    appendWorkTree(wt6,"main1.c",sha256file("test_work/main1.c"),1);
    appendWorkTree(wt6,"main2.c",sha256file("test_work/main2.c"),1);
    appendWorkTree(wt6,"main3.c",sha256file("test_work/main3.c"),1);
    afficheWorkTree(wt6);

    char buffer[1000];
    getcwd(buffer,1000); //on récuerer le chemin absolu du répertoire de travail courant (pwd)
    strcat(buffer,"/test_work"); //On ajoute le chemin du répertoire test à la fin du chemin du répertoire courant
    
    char* hash = saveWorkTree(wt6, buffer); //on sauvegarde le worktreer dans le répertoire test
    

    //LIBERATION DE LA MEMOIRE ASSOCIEE
    free(hashtree);//libère la mémoire allouée pour le hash
    freeWorkTree(wt);
    free(hash);
    freeWorkTree(wt6);
    

    return 0;
    */


    /*
    
    // TEST Exercice 6 + LIBERATION DE LA MEMOIRE 
    Commit * c = initCommit();
    commitSet(c,"kay","velue");
    afficheCommit(c);
    freeCommit(c);;

    Commit* c1 = stc("cle1 : valeur1\ncle2 : valeur2\ncle3 : valeur3\n");
    afficheCommit(c1);
    ctf(c1,"commit.txt");
    afficheCommit(c1);
    freeCommit(c1);

    Commit* c3 = ftc("commit.txt");
    afficheCommit(c3);
    freeCommit(c3);

    Commit* c4 = createCommit("123456789");
    commitSet(c4,"Youssef","Hello it is my first commit");
    commitSet(c4,"David","I will add some files soon");
    afficheCommit(c4);
    ctf(c4,"myFirstCommit.txt");
    freeCommit(c4);

    Commit* c5 = ftc("commit.txt");
    afficheCommit(c5);
    char *hash_file=blobCommit(c5);
    printf("Le hash du fichier temporaire est : %s\n",hash_file);
    freeCommit(c5);
    free(hash_file);
    /*


    
    */

	/*
    //TEST Exercice 7


	//initialisation des refs (HEAD, master)
	initRefs();
	
	//création d'une ref, obtention de son hash puis suppression de cette ref
	createUpdateRef("test_ref", "test_hash");
	char* test_hash = getRef("test_ref");
	printf("hash du ref : %s\n", test_hash);
	deleteRef("test_ref");

	//premier commit
	myGitAdd("test_commit/fichier1");
	myGitAdd("test_commit/fichier3");
	myGitCommit("master", "premier commit");
    
	//deuxieme commit
	myGitAdd("test_commit/fichier4");
	myGitCommit("master", "deuxieme commit");
	
	free(test_hash);
	*/
	
	/*
    //Exercice 8
	//initialisa la branche courante
    initRefs();
	initBranch();
	
	//création de la branche et test d'existence
	createBranch("test_branch");
	if(branchExists("test_branch")){
		printf("La branche test_branch existe\n");
	}
	else{
		printf("La branche test_branch n'existe pas\n");
	}
	
	//obtention de la branche courante puis affichage des commits de la branche
	char* current_branch = getCurrentBranch();
	printf("La branche courante est %s\n", current_branch);
	printf("\nAffichage de la branche %s\n", current_branch);
	printBranch(current_branch);
	
	//obtention de la liste des commits (hash) de la branche courante
	List* list_commit = branchList(current_branch);
    char* s1 = ltos(list_commit);
    printf("\nListe des commit de la branche %s : %s\n", current_branch, s1);

    //obtention de la liste des commits (hash) de toutes les branches
    List* list_all_commit = getAllCommits();
    char* s2 = ltos(list_all_commit);
    printf("\nListe des commit de toutes les branches : %s\n", s2);
    
    free(current_branch);
    freeList(list_commit);
    freeList(list_all_commit);
    free(s2);
    free(s1);
    */
    
    /*
    //Exercice 9
    
    initRefs();
	initBranch();
	myGitAdd("test_commit/fichier1");
	myGitAdd("test_commit/fichier3");
	myGitCommit("master", "premier commit");
    //création d'une branche et commit dessus
    createBranch("test_branch");
    myGitCheckoutBranch("test_branch");

    myGitAdd("test_commit/fichier2");
	myGitCommit("test_branch", "troisieme commit");
	printf("\nAffichage de la branche test_branch\n");
	printBranch("test_branch");

	//retour sur la branche master
	myGitCheckoutBranch("master");
	printf("\nAffichage de la branche master\n");
	printBranch("master");
	*/
	
   	//Exercice 11
    WorkTree* wt7 = initWorkTree();
    appendWorkTree(wt7, "name", "hash",0);
    appendWorkTree(wt7, "name2", "hash2",0);
    appendWorkTree(wt7, "name3", "hash3",0);
    
    WorkTree* wt8 = initWorkTree();
    appendWorkTree(wt8, "name", "hash",0);
    appendWorkTree(wt8, "name2", "hash4",0); // modifié
    appendWorkTree(wt8, "name5", "hash5",0); // nouveau
    
    List* conflicts = initList();

	WorkTree* merged_wt = mergeWorkTrees(wt7, wt8, &conflicts);
	
	char* s_conflicts = ltos(conflicts);
	char* s_merged_wt = wtts(merged_wt);
	printf("Affichage du WorkTree fusionné : \n%s\n", s_merged_wt);
	printf("Affichage des WorkFile en conflits : \n%s\n", s_conflicts);
	
	free(s_conflicts);
	free(s_merged_wt);
	freeWorkTree(wt7);
	freeWorkTree(wt8);
	freeWorkTree(merged_wt);
	
	

    
    
    
    return 0;
}
