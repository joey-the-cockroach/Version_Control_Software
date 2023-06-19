#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* sha256file(char* file);
int hashFile(char* source, char* dest);

#endif
