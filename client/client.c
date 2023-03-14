#include "client.h"

int main( int argc, char* argv[] )
{
	getAndSetPaths();

	struct timespec tim = { 0, 10000000 };

	struct stat statbuf;

	while( stat( pathToFI, &statbuf ) )
		nanosleep( &tim, NULL );

	int fd_FI;
	int fd_FO = openFifo( pathToFO, O_RDONLY | O_NONBLOCK );

	handleRealTimeSignal( SIGRTMIN + 13, handlerRealTime13 );	

	printf("Pid of client: %d\n", getpid());

	while(1)
	{
		if(!ring4You)
		{
			if(!inTurns)
			{
				inTurns = 1;
				char t;

				if( read( fd_FO, &t, 1 ) > 0 && submitted != 1 )
				{
					children++;

					switch( pid = fork() )
					{
						case -1:
							errorExit("fork");
						case 0:
							if( pgid == -1 )
							{
								if( setpgid( getpid(), 0 ) == -1 )
									errorExit("setpgrid");
							}

							else
							{
								if( setpgid( getpid(), pgid ) == -1 )
									errorExit("setpgid");
							}

							printf("pid: %d\tpgid: %d\n", getpid(), getpgid(getpid()));

							if( execlp( "./child", "./child", NULL ) == -1 )
								errorExit("execlp child");	
						default:
							if( pgid == -1 )
								pgid = pid;
					}

					pids[children] = pid;		
				}

				else if( submitted == 1 )
					submitted = -1;
			}

			else if( inTurns && submitted == 0 )
			{
				inTurns = 0;
				
				if( children >= 3 && ( fd_FI = open( pathToFI, O_WRONLY | O_NONBLOCK ) ) != -1 )
				{
					processIDs pd;
					
					pd.pid = getpid();
					pd.pgid = pgid;

					if( write(fd_FI, &pd, sizeof(pd)) > 0 )
						submitted = 1;

					if(close(fd_FI) == -1 )
						errorExit("close fd_FI in client");
				}
			}

			else if( inTurns && submitted == -1 )
			{
				inTurns = 0;
				submitted = 0; 
			}
		}
	

		else
		{
			siginfo_t infop;

			memset( &infop, '\0', sizeof(infop) );

			do
			{
				if( infop.si_pid != 0 )
					countTeeth++;
			}
			while( waitid(P_ALL, 0, &infop, WEXITED | WSTOPPED | WNOHANG ) != -1 );
		
			if( !winner )
			{			
				union sigval sv;
		
				sv.sival_int = 0;
			
				memset( pids, '\0', sizeof(pids) );

				printf("We lost...\n");

				children = 0;
				ring4You = 0;
				pgid = -1;
				countTeeth = 0;

				if( sigqueue( serverPid, SIGRTMIN + 13, sv ) == -1 )
					errorExit("sigqueue signal to server, this client won");
			}

			else
			{
				memset( pids, '\0', sizeof(pids) );

                //nie dziala przez setpgid!
				/*for( int i = 0; i < realCount; i++ )
				{
					switch( fork() )
					{
						case -1:
							errorExit("fork");
						case 0:
							//tu jak jeden z klientow wygra to nie chce sie ustawic
							//ten sam numer pgid, nie wiem czemu :(

							if( setpgid( getpid(), pgid ) == -1 )
								errorExit("setpgid");
						 	
							pids[i] = getpid();
	
							if( execlp( "./child", "./child", NULL ) == -1 )
								errorExit("execlp child");	
						default:
							break;
							
					}
				}*/
				
				ring4You = 0;	
				children = 0;//realCount;
				winner = 0;
				countTeeth = 0;
                pgid = -1;
			}
		}

		nanosleep( &tim, NULL );
	}
	
	if( close(fd_FO) == -1 )
		errorExit("close");

	exit(EXIT_SUCCESS);
}


