#ifndef COMMON_H
#define COMMON_H

#define _GNU_SOURCE
#include <signal.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#define SIZE 256

#define CREAT_F 0
#define DELET_F 1
#define CLOCK_ID CLOCK_REALTIME

extern char* path;
extern char pathToFI[SIZE];
extern char pathToFO[SIZE];

extern int winner;
extern int beaten;

typedef struct processIDsTag
{
	int pid;
	int pgid;

}processIDs;

int openFifo(char*, int);
void errorExit(const char*);
void menuFifo(char*, int);
void clear();
void getAndSetPaths();
void handlerRealTime13( int, siginfo_t*, void* );
void handleRealTimeSignal(int, void (*)( int, siginfo_t*, void* ) );
int checkForSlash();

#endif
