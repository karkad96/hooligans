#ifndef ARBITER_H
#define ARBITER_H

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

#define SIZE 256

#define CREAT_F 0
#define DELET_F 1
#define CLOCK_ID CLOCK_REALTIME

extern char* path;
extern char pathToTotem[SIZE];

extern int state;


int openFifo(char*, int);
int checkForSlash();

void errorExit(const char*);
void menuFifo(char*, int);
void clear();
void getAndSetPaths();
void handlerRealTime13( int, siginfo_t*, void* );
void handleRealTimeSignal(int, void (*)( int, siginfo_t*, void* ) );

#endif

