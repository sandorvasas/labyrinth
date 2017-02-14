#include "sys.h"
#include <stdio.h>

void	win32_msgbox( char* format, ... ) {
#ifdef DEBUG_MODE
	va_list list;
	char txt[ 256 ];


	va_start( list, format );
	vsprintf( txt, format, list );
	va_end( list );


	MessageBox( 0, txt, "Debug Message", MB_OK );
#endif
}

void	debug_log( char* format, ... ) {
#ifdef DEBUG_MODE
	va_list list;
	char txt[ 256 ];
	FILE * f;


	va_start( list, format );
	vsprintf( txt, format, list );
	va_end( list );


	f = fopen( "labylog.txt", "a+" );
		fprintf( f, "%s\n", txt );
	fclose( f );
#endif
}


//------------------------------------------------- 
//	inRange
//		Returns 1 if n is in [low, high]. 0 otherwise.
//-------------------------------------------------
unsigned char	inRange( int n, int low, int high ) {
	return ( unsigned char ) ( n >= low && n <= high );
}