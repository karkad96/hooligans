#include "child.h"

int main( int argc, char* argv[] )
{
	handleRealTimeSignal( SIGRTMIN + 13, handlerRealTime13 );

	while(1)
		pause();

	exit(EXIT_SUCCESS);
}

