#include "server.h"

char* path;
char pathToFI[SIZE];
char pathToFO[SIZE];

int beaten;
int winner;

int checkForSlash()
{
	int i = 0;

	for( ; *( path + i ) != '\0'; i++ );

	return *( path + i ) == '/';
}

void handleRealTimeSignal(int signum, void (*handler)( int, siginfo_t*, void* ) )
{
        struct sigaction act;

        memset( &act, '\0', sizeof(act) );

        act.sa_sigaction = handler;
        act.sa_flags = SA_RESTART | SA_SIGINFO;

        if( sigaction( signum, &act, NULL ) == -1 )
                errorExit("sigaction");
}

void handlerRealTime13( int sig, siginfo_t* si, void* ucontext )
{
	if( si->si_value.sival_int == 0 )
		beaten++;
	else
		winner++;
}

void getAndSetPaths()
{	
	path = getenv("CAMP");

	strcat(pathToFI, path);
	if( !checkForSlash() )
		strcat( pathToFI, "/" );
	
	strcat(pathToFI, "FI");

	strcat(pathToFO, path);
	if( !checkForSlash() )
		strcat( pathToFO, "/" );
	
	strcat(pathToFO, "FO");
}

void errorExit( const char* error )
{
	perror( error );
	exit( EXIT_FAILURE );
}

void menuFifo( char* str, int mode )
{
	switch(mode)
	{
		case CREAT_F:
			if( mkfifo( str, 0777 ) == -1 )
				errorExit("mkfifo");
			break;

		case DELET_F:
			if( remove(str) == -1 )
				errorExit("remove");
			break;
	}
}

int openFifo( char* str, int flags )
{
        int fd;       

       	if( ( fd = open( str, flags ) ) == -1 )
                errorExit("open FIFO");

        return fd;
}

void clear()
{
	menuFifo(pathToFI, DELET_F);
	menuFifo(pathToFO, DELET_F);		
}
