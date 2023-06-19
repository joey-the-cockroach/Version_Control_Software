#ifndef TIMELINE_H
#define TIMELINE_H

void restoreCommit(char* hash_commit);
void myGitCheckoutBranch(char* branch);
List* filterList(List* L, char* pattern);
void myGitCheckoutCommit(char* pattern);
int listSize(List *l);

#endif
