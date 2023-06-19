#ifndef COMMIT_H
#define COMMIT_H

#define Nmaxcommit 100
#define MESSAGE_SIZE 1200

typedef struct key_value_pair{
    char* key;
    char* value;
 } kvp; //Structure qui représente un couple clé/valeur

 typedef struct hash_table{
    kvp** T;
    int n;
    int size;
 } HashTable; //Structure qui représente une table de hachage

typedef HashTable Commit;

kvp* createKeyVal(char* key, char* val);
void freeKeyVal(kvp* kv);
char* kvts(kvp* k);
kvp* stkv(char* str);
Commit* initCommit();
void commitSet(Commit* c, char* key, char* value);
Commit* createCommit(char* hash);
char* commitGet(Commit* c, char* key);
char* cts(Commit* c);
Commit* stc(char* ch);
Commit* ftc(char* file);
char* blobCommit(Commit* c);
unsigned long hash(unsigned char *str);
void ctf(Commit* c, char* file);
void afficheCommit(Commit* c);
void afficheKeyVal(kvp* kv);
void freeCommit(Commit* c);

#endif
