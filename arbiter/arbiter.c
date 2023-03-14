#include "arbiter.h"

int main( int argc, char* argv[] )
{
	getAndSetPaths();
        
	handleRealTimeSignal( SIGRTMIN + 13, handlerRealTime13 );

	int fdWrite;
	int fdRead;

	float totemOp = strtof( getenv("TOTEM_OP"), NULL ) / 10.0;
	float totemCl = strtof( getenv("TOTEM_CL"), NULL ) / 10.0;

	struct timespec timOP = { 1000000000 * totemOp / 1000000000, 1000000000 * ( totemOp - (long)totemOp ) };
	struct timespec timCL = { 1000000000 * totemCl / 1000000000, 1000000000 * ( totemCl - (long)totemCl ) } ;

	menuFifo( pathToTotem, CREAT_F );

	while( 1 )
	{
		while( state % 2 == 1 )
		{
			fdRead = openFifo( pathToTotem, O_RDONLY | O_NONBLOCK );
			fdWrite = openFifo( pathToTotem, O_WRONLY | O_NONBLOCK );
			
			if( write( fdWrite, "a", 1 ) == -1 )
				errorExit("write in arbiter");

			nanosleep( &timOP, NULL );

			char t;

			if( read( fdRead, &t, 1 ) == -1)
				errorExit( "read in arbiter" );
		
			if(close(fdWrite)==-1)
				errorExit("close fdWrite from arbiter");

			if(close(fdRead)==-1)
				errorExit("close fdRead from arbiter");

			if( state % 2 == 0 )
				break;
	
			nanosleep( &timCL, NULL );
		}
		
		if( state % 2 == 0 )
			pause();
	}
	
	exit(EXIT_SUCCESS);
}


