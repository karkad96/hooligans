#include "client.h"

char* path;
char pathToFI[SIZE];
char pathToFO[SIZE];

int countTeeth;
int pids[CHILD_SIZE];
int ring4You;
int submitted;
int inTurns;
int children;
int pgid = -1;
int serverPid;
int pid;
int winner;
int realCount;

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
	if( getpgid(si->si_pid) == pgid )
	{
		if(!winner)
		{
			union sigval sv;
		
			sv.sival_int = 1;
			winner = 1;
			
			write( 1, "We won!\n", 8 );
			
			kill( -pgid, SIGKILL );

			if( sigqueue( serverPid, SIGRTMIN + 13, sv ) == -1 )
				errorExit("sigqueue signal to server, this client won");
		}
	}

	else
	{
		serverPid = si->si_pid;
		
		ring4You = 1;
		
		for( int i = realCount; i <= children; i++ )	
			if( pids[i] && sigqueue( pids[i], SIGRTMIN + 13, si->si_value ) == -1 )
				errorExit("sigqueue in client pids");
	}
}

int checkForSlash()
{
        int i = 0;

        for( ; *( path + i ) != '\0'; i++ );

        return *( path + i ) == '/';
}

void getAndSetPaths()
{
	path = getenv("CAMP");

	strcat( pathToFI, path );
	if( !checkForSlash() )
                strcat( pathToFI, "/" );

	strcat( pathToFI, "FI" );

	strcat( pathToFO, path );
	if( !checkForSlash() )
                strcat( pathToFO, "/" );

	strcat( pathToFO, "FO" );
}

void errorExit( const char* error )
{
	perror( error );
	exit( EXIT_FAILURE );
}

int openFifo(char* str, int flags)
{
        int fd;

        if( (fd = open( str, flags )) == -1 )
                errorExit("open FIFO");

        return fd;
}

