#ifndef REF_H
#define REF_H

void initRefs();
int isFile(const char* name); //pour un jeux de tests
void createUpdateRef(char* ref_name , char* hash);
void deleteRef(char* ref_name);
char* getRef(char* ref_name);
void createFile(char* file);
void myGitAdd(char* file_or_folder);
void myGitCommit(char* branch_name , char* message);

#endif
