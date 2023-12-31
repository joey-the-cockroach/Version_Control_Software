#ifndef BRANCH_H
#define BRANCH_H

void initBranch();
int branchExists(char* branch);
void createBranch(char* branch);
char* getCurrentBranch();
char* hashToPathCommit(char* hash);
void printBranch(char* branch);
List* branchList(char* branch);
List* getAllCommits();

#endif
