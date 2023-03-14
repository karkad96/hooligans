#include "server.h"

int main( int argc, char* argv[] )
{
	srand((unsigned int)time(NULL));

	getAndSetPaths();

	handleRealTimeSignal( SIGRTMIN + 13, handlerRealTime13 );

	int arbiterPid;

	switch( arbiterPid = fork() )
	{
		case -1:
			errorExit("fork");
		case 0:
			if( execlp( "./arbiter", "./arbiter", NULL ) ) 
				errorExit("execlp arbiter");
		default:
			break;
	}

	menuFifo( pathToFI, CREAT_F );
	menuFifo( pathToFO, CREAT_F );
	
	float ringReg = strtof( getenv("RING_REG"), NULL ) / 10.0;
	float recDly = strtof( getenv("RECRUIT_DLY"), NULL) / 10.0;
	long recMax = strtol( getenv("RECRUIT_MAX"), NULL, 10 );	
	
	int i = 0;
	int openedFI;
	
	int fd_check;
	int fd_FI;
	int fd_FO = openFifo( pathToFO, O_WRONLY );

    int ring4You = 0;

	unsigned char permissions[recMax + 1];// +1 for '\0'
		
	processIDs client1;
	processIDs client2;

	struct timespec timFO = { 1000000000 * recDly / 1000000000, 1000000000 * ( recDly - (long)recDly ) };
	struct timespec timFI = { 1000000000 * ringReg / 1000000000, 1000000000 * ( ringReg - (long)ringReg ) };

	while( 1 )
	{
		fd_check = openFifo( pathToFO, O_RDONLY | O_NONBLOCK );
		
		struct pollfd pll = { fd_check, POLLIN, 0 };

		if( poll( &pll, 1, 10 ) == 1 )
		{
			if( close(fd_check) == -1 )
				errorExit("close fd_check");
		}

		else
		{	
			if( close(fd_check) == -1 )
				errorExit("close fd_check");

			int rnd = rand() % ( recMax + 1 );
	
			for( i = 0; i < rnd; i++ )
				permissions[i] = 'a';
			
			permissions[i] = '\0';
					
			if( write( fd_FO, permissions, i ) == -1)
				errorExit("write to FO");
			
			printf("Server sent %d bytes to clients\n", i);
		}
		
		nanosleep( &timFO, NULL );
	
		openedFI = rand() % 2;//change value after '%' to read from FI less often

		if( !ring4You && !openedFI )
		{	
			fd_FI = openFifo( pathToFI, O_RDONLY | O_NONBLOCK );
				
			nanosleep( &timFI, NULL );
						
			memset(&client1, '\0', sizeof(client1));
			memset(&client2, '\0', sizeof(client2));
			
			if( read( fd_FI, &client1, sizeof(client1) ) == -1 )
				errorExit("reading from FI");

			if( read( fd_FI, &client2, sizeof(client2) ) == -1 )
				errorExit("reading from FI");

			if( close(fd_FI) == -1 )
				errorExit("close fd_FI in timer handler");				
	
			if( client1.pid && client2.pid && client1.pid != client2.pid )
			{
				union sigval oppositePgid1;
				union sigval oppositePgid2;
				
				oppositePgid1.sival_int = client2.pgid;
				oppositePgid2.sival_int = client1.pgid;

				if( sigqueue( client1.pid, SIGRTMIN + 13, oppositePgid1 ) == -1)
					errorExit("sigqueue to client1");
		
				if( sigqueue( client2.pid, SIGRTMIN + 13, oppositePgid2 ) == -1 )
					errorExit("sigqueue to client2");

				struct timespec tim = { 0, 100000000 };
		
				printf("pid: %d\tpgid: %d\n", client1.pid, client1.pgid);
				printf("pid: %d\tpgid: %d\n", client2.pid, client2.pgid);

				nanosleep( &tim, NULL );
			
				if( kill( arbiterPid, SIGRTMIN + 13 ) == -1 )
					errorExit("kill arbiter");		

				ring4You = 1;
			}
		}
		
		if( ( winner == 1 && beaten == 1 ) || beaten == 2 )
		{
			struct timespec tim = {2,0};
			nanosleep(&tim,NULL);
			printf("\nNext cycle to ring4You\n\n");
			
			winner = 0;
			beaten = 0;
			ring4You = 0;
		}
	}

	exit(EXIT_SUCCESS);
}



