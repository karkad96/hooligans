#include "child.h"

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
	char buff[SIZE];
	
	sprintf( buff, "%d", si->si_value.sival_int );
		
	if( execlp( "./hooligan", "./hooligan", buff, NULL ) == -1 )
		errorExit("execlp");
}
void errorExit( const char* error )
{
	perror( error );
	exit( EXIT_FAILURE );
}

