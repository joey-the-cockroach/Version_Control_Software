CFLAGS = -g -Wno-unused-parameter
CC = gcc
HEADER = ./header/
PROGRAMS = main myGit

all: main myGit

main:	hash.o list.o work.o commit.o ref.o branch.o timeline.o merge.o main.c
	$(CC) $(CFLAGS) -o main hash.o list.o work.o commit.o ref.o branch.o timeline.o merge.o main.c

myGit:	hash.o list.o work.o commit.o ref.o branch.o timeline.o merge.o myGit.c
	$(CC) $(CFLAGS) -o myGit hash.o list.o work.o commit.o ref.o branch.o timeline.o merge.o myGit.c

hash.o: hash.c
	$(CC) -c hash.c -o hash.o

list.o: list.c
	$(CC) -c list.c -o list.o
	
work.o: work.c
	$(CC) -c work.c -o work.o
	
commit.o: commit.c
	$(CC) -c commit.c -o commit.o
	
ref.o: ref.c
	$(CC) -c ref.c -o ref.o
	
branch.o: branch.c
	$(CC) -c branch.c -o branch.o
	
timeline.o: timeline.c
	$(CC) -c timeline.c -o timeline.o
	
merge.o: merge.c
	$(CC) -c merge.c -o merge.o

clean:
	rm -rf *.o $(PROGRAMS) .refs/ .current_branch .add
