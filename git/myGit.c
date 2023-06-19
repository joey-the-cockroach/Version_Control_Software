#include "./header/hash.h"
#include "./header/list.h"
#include "./header/work.h"
#include "./header/commit.h"
#include "./header/ref.h"
#include "./header/branch.h"
#include "./header/timeline.h"
#include "./header/merge.h"

int main(int argc, char* argv[]) { //Pour permettre la lecture au clavier de l'utilisateur 

    if (argc < 2) {
        printf("Usage: %s <vous devez entrez une commande ! >\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "init") == 0) { 
        initRefs();
        initBranch();
    }
    
    if (strcmp(argv[1],"list-refs") == 0){ 
        printf("REFS : \n");
        if (file_exists(".refs")){
            List* L = listdir(".refs"); 
            for (Cell* ptr = *L; ptr !=NULL; ptr = ptr->next) {
                if (ptr->data[0] == '.')
                    continue;
                char* content = getRef(ptr->data);
                printf("- %s \t %s \n", ptr->data, content); 
                free(content);
            }
        freeList(L);
        }
    }

    
    if (strcmp(argv[1], "create-ref") == 0) { 
        createUpdateRef(argv[2], argv[3]);
    }

    
    if (strcmp(argv[1], "delete-ref") == 0) {
        deleteRef(argv[2]); 
    }



     
    if (strcmp(argv[1], "add") == 0) { 
        for (int i = 2; i < argc; i++) {
            myGitAdd(argv[i]); 
        }
    }

    
    if (strcmp(argv[1], "clear-add") == 0) {
        system("rm .add");
    }
    if (strcmp(argv[1],"list-add")==0){ 
        printf("Zone de préparation : \n"); 
            if (file_exists(".add")){
                WorkTree* wt = ftwt(".add");
                char*wts=wtts(wt);
                printf("%s\n", wts); 
                freeWorkTree(wt);
                free(wts);
            }
    }

 
    if (strcmp(argv[1], "commit") == 0) {
        if (argc > 3) {
            if (strcmp(argv[3], "-m") == 0) {
                myGitCommit(argv[2], argv[4]);
            }
        } else {
        if (argc < 3) {
            printf("Erreur : ./myGit commit <ref-name>\n");
            return 1;
        }
        myGitCommit(argv[2], NULL);
        }
    }
    
    if (strcmp(argv[1], "get-current-branch") == 0){ 
    	char* branch = getCurrentBranch();
        printf("%s\n", branch);
        free(branch);
    }

    if (strcmp(argv[1], "branch") == 0) { 
        if (!branchExists(argv[2]))
            createBranch(argv[2]);
        else
            printf("The branch already exists.\n");
    }

    if (strcmp(argv[1], "branch-print") == 0) { 
        if (!branchExists(argv[2]))
            printf("The branch does not exist.\n"); 
        else
            printBranch(argv[2]);
    }

    //Corriger le fameux cas spécial 
    if (strcmp(argv[1], "checkout-branch") == 0) { 
        if (!branchExists(argv[2]))
            printf("The branch does not exist."); 
        else
            myGitCheckoutBranch(argv[2]);
    }

    if (strcmp(argv[1], "checkout-commit") == 0) { 
        myGitCheckoutCommit(argv[2]);
    }
    
    if (strcmp(argv[1], "merge") == 0){
        if (argc<3 || argc>4) {
            printf("Mauvais nombre d'arguments\n");
			return 1;
        }
        List *conflicts = merge(argv[2], argv[3]);
        if (conflicts==NULL){
            printf("fusion effectuee\n");
        }
        else{
        	char* current_branch = getCurrentBranch();
       		printf("Conflits detectés, choisissez une option :\n");
        	printf("1. Garder les fichiers de la branche %s\n", current_branch);
        	printf("2. Garder les fichiers de la branche %s\n", argv[2]);
        	printf("3. Choisir manuellement les fichiers en conflit %s\n", argv[2]);
			int choix = 0;
			scanf("%d",&choix);
			while(choix<1 || choix>3){
				printf("Choix invalide, recommencez :\n");
			}
			printf("Choix effectué : %d\n", choix);
			if(choix == 1){
				createDeletionCommit(argv[2], conflicts, argv[3]);
				List* m = merge(argv[2], argv[3]);
				if (m != NULL){
            		printf("erreur fusion\n");
            	}
            	freeList(m);
            }
            if(choix == 2){
				createDeletionCommit(current_branch, conflicts, argv[3]);
				myGitCheckoutBranch(argv[2]);
				List* m = merge(current_branch, argv[3]);
				if (m != NULL){
            		printf("erreur fusion\n");
            	}
            	freeList(m);
            }
            if(choix == 3){
            	List* save_current = initList();
            	List* save_remote = initList();
            	for (Cell *ptr = *conflicts; ptr != NULL; ptr = ptr->next){
                	printf("Choix pour le fichier/dossier %s\n", ptr->data);
                	printf("1. Garder la version de la branche %s\n", current_branch);
                	printf("2. Garder la version de la branche %s\n", argv[2]);
                	int choix2 = 0;
                	scanf("%d",&choix2);
                	while(choix2<1 || choix2>2){
						printf("Choix invalide, recommencez :\n");
					}
					printf("Choix effectué : %d\n", choix2);
                	if (choix2 == 1){
                    	insertFirst(save_current, buildCell(ptr->data));
                	}
                	if  (choix2 == 2){
                    	insertFirst(save_remote, buildCell(ptr->data));
                	}
            	}
            	createDeletionCommit(current_branch, save_remote, argv[3]);
            	createDeletionCommit(argv[2], save_current, argv[3]);
            	List* m = merge(argv[2], argv[3]);
				if (m != NULL){
            		printf("erreur fusion\n");
            	}
                //LIBERATION DE LA MEMOIRE 
            	freeList(save_current);
            	freeList(save_remote);
            	freeList(m);
            }
            free(current_branch);
            freeList(conflicts);
		}
    }

    return 0;
}



 
