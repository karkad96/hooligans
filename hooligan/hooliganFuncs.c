#include "hooligan.h"

char* path;
char pathToTotem[256];

long hooliganToKill;

int getSignalValues()
{
	int offensiveDefence = rand() % 2;

	if( offensiveDefence )
	{
		signal( SIGUSR1, SIG_DFL );
		signal( SIGUSR2, SIG_IGN );
	}
		
	else
	{
		signal( SIGUSR1, SIG_IGN );
		signal( SIGUSR2, SIG_DFL );
	}
	
	return ( rand() % 2 ) ? SIGUSR1 : SIGUSR2;
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

        strcat( pathToTotem, path );
	if( !checkForSlash() )
                strcat( pathToTotem, "/" );

	strcat( pathToTotem, "Totem" );
}

void handleSignal(int signum, void (*handler)( int, siginfo_t*, void* ) )
{
	struct sigaction act;

	memset( &act, '\0', sizeof(act) );

	act.sa_sigaction = handler;
	act.sa_flags = SA_RESTART | SA_SIGINFO;

	if( sigaction( signum, &act, NULL ) == -1 )
		errorExit("sigaction");
}

void handlerSIGALRM( int sig, siginfo_t* si, void* ucontext )
{
	kill( si->si_pid, SIGBUS );
}

void handlerSIGBUS( int sig, siginfo_t* si, void* ucontext )
{
	hooliganToKill = si->si_pid;
}

void errorExit( const char* error )
{
	perror( error );
	exit( EXIT_FAILURE );
}
