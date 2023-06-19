#include "./header/hash.h"
#include "./header/list.h"
#include "./header/work.h"
#include "./header/commit.h"
#include "./header/ref.h"
#include "./header/branch.h"
#include "./header/timeline.h"
#include "./header/merge.h"

// Gestion des fusions de branches
// Exercice 11: Une première méthode de fusion

// QUESTION 11.1
WorkTree* mergeWorkTrees(WorkTree* wt1, WorkTree* wt2, List** conflicts){

    //initialisation
    WorkTree *wt = initWorkTree();
    *conflicts = initList();

    //parcours du WorkTree wt1
    for(int i = 0; i < wt1->n; i++){
        int ind = inWorkTree(wt2, wt1->tab[i].name);
        if ( ind >= 0 && strcmp(wt1->tab[i].hash, wt2->tab[ind].hash) != 0){ // si même nom mais hash différent
            insertFirst(*conflicts, buildCell(wt1->tab[i].name)); // insertion du nom du fichier en conflit dans la conflicts
        }
        else{ // si pas dans le worktree on l'ajoute
            appendWorkTree(wt, wt1->tab[i].name, wt1->tab[i].hash, wt1->tab[i].mode); 
        }
    }

    //parcours du WorkTree wt2
    for(int j = 0; j < wt2->n; j++){
        int ind = inWorkTree(wt1, wt2->tab[j].name);
        if ( ind >= 0 && strcmp(wt2->tab[j].hash, wt1->tab[ind].hash) != 0){ // si même nom mais hash différent
        }
        else{ // si pas déjà dans le worktree on l'ajoute
            appendWorkTree(wt, wt2->tab[j].name, wt2->tab[j].hash, wt2->tab[j].mode); 
        }
    }

    return wt;
}

// QUESTION 11.2
List* merge(char* remote_branch, char* message){
	char* current_branch = getCurrentBranch();

    //Commit + WorkTree de la branche courante
    char* current_commit_hash = getRef(current_branch);
	char* current_commit_path = hashToPathCommit(current_commit_hash);
    Commit* current_commit = ftc(current_commit_path);
    char* current_wt_hash = commitGet(current_commit, "tree");
    char* current_wt_path = strcat(hashToPath(current_wt_hash), ".t");
    WorkTree* current_wt = ftwt(current_wt_path);

    //Commit + WorkTree de la branche distante
    char* remote_commit_hash = getRef(remote_branch);
    char* remote_commit_path = hashToPathCommit(remote_commit_hash);
    Commit* remote_commit = ftc(remote_commit_path);
    char* remote_wt_hash = commitGet(remote_commit, "tree");
	char* remote_wt_path = strcat(hashToPath(remote_wt_hash), ".t");
    WorkTree* remote_wt = ftwt(remote_wt_path);

    //feusion des deux WorkTree wt1 et wt2
    List* conflicts = initList();
    WorkTree* merged_wt = mergeWorkTrees(current_wt, remote_wt, &conflicts);

    if (listSize(conflicts) > 0){
    	free(current_branch);
     free(current_commit_hash);
    	free(current_commit_path);
    	freeCommit(current_commit);
    	free(current_wt_path);
    	freeWorkTree(current_wt);
    	free(remote_commit_hash);
    	free(remote_commit_path);
    	freeCommit(remote_commit);
    	free(remote_wt_path);
    	freeWorkTree(remote_wt);
    	freeWorkTree(merged_wt);
		return conflicts;
	}

    //Commit
    char* merged_wt_hash = saveWorkTree(merged_wt, ".");
	Commit* c = createCommit(merged_wt_hash);
	commitSet(c, "message", message);
	commitSet(c, "predecessor", current_commit_hash);
	commitSet(c, "merged_predecessor", remote_commit_hash);
	char* merged_commit_hash = blobCommit(c);
	createUpdateRef(current_branch, merged_commit_hash);
	createUpdateRef("HEAD", merged_commit_hash);


    deleteRef(remote_branch);
    restoreWorkTree(merged_wt, ".");

    //libération de mémoire
    free(current_branch);
	free(current_commit_hash);
	free(current_commit_path);
	freeCommit(current_commit);
	free(current_wt_path);
	freeWorkTree(current_wt);
	free(remote_commit_hash);
	free(remote_commit_path);
	freeCommit(remote_commit);
	free(remote_wt_path);
	freeWorkTree(remote_wt);
	freeWorkTree(merged_wt);
	freeCommit(c);
	free(merged_commit_hash);
    return NULL;
}

// QUESTION 11.3
void emptyAddFile(){ 
    FILE* add_file = fopen(".add", "w");
    fclose(add_file);
}

void createDeletionCommit(char* branch, List* conflicts, char* message){

    char* current_branch = getCurrentBranch();

    //checkout sur la branche en question
    myGitCheckoutBranch(branch);

    //Commit + WorkTree de la branche courante
    char* current_commit_hash = getRef(getCurrentBranch());
	char* current_commit_path = hashToPathCommit(current_commit_hash);
    Commit* current_commit = ftc(current_commit_path);
    char* current_wt_hash = commitGet(current_commit, "tree");
    char* current_wt_path = strcat(hashToPath(current_wt_hash), ".t");
    WorkTree* current_wt = ftwt(current_wt_path);

    //vidage de la zone de préparation
    emptyAddFile();

    //ajout au WorkTree si pas en conflit
    for(int i = 0; i < current_wt->n; i++){
        if (searchList(conflicts, current_wt->tab[i].name)==NULL){
            myGitAdd(current_wt->tab[i].name);
        }
    }

    //Commit de suppression
    myGitCommit(branch, message);

    //Retour sur la branche de départ
    myGitCheckoutBranch(current_branch);
    
	//libération de mémoire
	free(current_branch);
	free(current_commit_hash);
	free(current_commit_path);
	freeCommit(current_commit);
	free(current_wt_hash);
	free(current_wt_path);
	freeWorkTree(current_wt);
}
