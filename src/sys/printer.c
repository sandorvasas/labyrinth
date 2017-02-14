/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#include "printer.h"
#include "..\OpenGL\GLexp.h"
#include "..\math\vector.h"
#include <stdio.h>


printParams_t	queue[ 200 ];
int				lenQueue = 0;

//------------------------------------------------
//	font_create()
//------------------------------------------------
font_t font_create( char* name, int size ) {
	HFONT font;
	HDC dc;
	unsigned int id;

	font = CreateFont(	size, 0, 0, 0, 
						FW_BOLD, 0, 0, 0, 
						ANSI_CHARSET, 
						OUT_DEFAULT_PRECIS,
						CLIP_DEFAULT_PRECIS, 
						ANTIALIASED_QUALITY, 
						DEFAULT_PITCH | FF_DONTCARE, 
						name ); 


	dc = wglGetCurrentDC();
	id = glGenLists( 256 );
	SelectObject( dc, font );
	wglUseFontBitmaps( dc, 0, 255, id );
	SelectObject( dc, 0 );

	return id;
}

//------------------------------------------------
//	font_print()
//------------------------------------------------
void font_print( font_t id, float x, float y, vsVec3* color, char* format, ... ) {
	va_list list;
	char text[ 256 ];

	va_start( list, format );
	vsprintf( text, format, list );
	va_end( list );

	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glOrtho( -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f );
	glPushMatrix();

		if ( color == 0 ) 
			glColor3f( 1.0f, 1.0f, 1.0f );
		else
			glColor3fv( ( float* )color );
		glRasterPos3f( x, y, -0.5f );

		glListBase( id );
		glCallLists( strlen( text ), GL_UNSIGNED_BYTE, text );

	glPopMatrix();
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
}

//------------------------------------------------
//	font_printQ()
//------------------------------------------------
void	font_printQ( font_t id, float x, float y, vsVec3* color, char* format, ... ) {
	va_list list;

	va_start( list, format );
	vsprintf( queue[ lenQueue ].text, format, list );
	va_end( list );

	if ( color == (vsVec3*)0 )
		vec3_set( &queue[ lenQueue ].color, 1.0f, 1.0f, 1.0f );
	else
		vec3_equ( &queue[ lenQueue ].color, color );
	queue[ lenQueue ].id = id;
	queue[ lenQueue ].x = x;
	queue[ lenQueue++ ].y = y;
}


//------------------------------------------------
//	font_printQueue()
//------------------------------------------------
void	font_printQueue( void ) {
	int i;
	for ( i = 0; i < lenQueue; i++ ) {
		font_print( queue[ i ].id, queue[ i ].x, queue[ i ].y, &queue[ i ].color, queue[ i ].text );
	}
	lenQueue = 0;
}



