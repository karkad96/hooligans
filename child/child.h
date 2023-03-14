#ifndef CHILD_H
#define CHILD_H

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

void errorExit( const char* );
void handlerRealTime13( int, siginfo_t*, void* );
void handleRealTimeSignal(int, void (*)( int, siginfo_t*, void* ) );

#endif
