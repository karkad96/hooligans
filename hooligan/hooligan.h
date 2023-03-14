#ifndef HOOLIGAN_H
#define HOOLIGAN_H

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
#include <poll.h>

#define SIZE 256

extern char* path;
extern char pathToTotem[256];

extern long hooliganToKill;

int getSignalValues();

void errorExit( const char* );
void handlerSIGALRM( int, siginfo_t*, void* );
void handlerSIGBUS( int, siginfo_t*, void* );
void handleSignal(int, void (*)( int, siginfo_t*, void* ) );
void getAndSetPaths();

#endif
