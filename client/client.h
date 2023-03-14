#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <errno.h>

#define SIZE 256
#define CHILD_SIZE 2048

extern char* path;
extern char pathToFI[SIZE];
extern char pathToFO[SIZE];

extern int countTeeth;
extern int pids[CHILD_SIZE];
extern int ring4You;
extern int submitted;
extern int inTurns;
extern int children;
extern int pgid;
extern int serverPid;
extern int pid;
extern int winner;
extern int realCount;

typedef struct processIDsTag
{
	int pid;
	int pgid;
}processIDs;

int openFifo( char*, int );
int checkForSlash();

void getAndSetPaths();
void errorExit( const char* );
void handlerRealTime13( int, siginfo_t*, void* );
void handleRealTimeSignal(int, void (*)( int, siginfo_t*, void* ) );

#endif
