#include "hooligan.h"

int main( int argc, char* argv[] )
{
	srand((unsigned int)time(NULL));

	long oppositePgid = strtol( argv[1], NULL, 10 );

	int SIG;
	int fd_check;

	getAndSetPaths();

	handleSignal( SIGALRM, handlerSIGALRM );
	handleSignal( SIGBUS, handlerSIGBUS );

	struct timespec tim = { 0, 10000000 };

	nanosleep( &tim, NULL );

	while( 1 ) 
	{
		SIG = getSignalValues();

		fd_check = open( pathToTotem, O_RDONLY | O_NONBLOCK );

                struct pollfd pll = { fd_check, POLLIN, 0 };

		int p = poll( &pll, 1, 1 ); 

		if( p )
		{
			if( close(fd_check) == -1 )
				errorExit("close fd_check in hooligan");

			if( kill( -oppositePgid, SIGALRM ) == -1 )
			{
				if( kill( getppid(), SIGRTMIN + 13 ) == -1 )
					errorExit("kill from winners");
			}
		}

		else
		{	
			if( close(fd_check) == -1 )
				errorExit("close fd_check in hooligan");

			if( kill( -oppositePgid, SIGALRM ) == -1 )
			{
				if( kill( getppid(), SIGRTMIN + 13 ) == -1 )
					errorExit("kill from winners");
			}

			if( hooliganToKill )
			{
				kill( hooliganToKill, SIG );
				hooliganToKill = 0;
			}
		}

		nanosleep(&tim, NULL);
	}

	exit(EXIT_SUCCESS);
}




