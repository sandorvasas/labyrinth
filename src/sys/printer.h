/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#ifndef __VS_C_PRINTER_H__
#define __VS_C_PRINTER_H__

#include <Windows.h>
#include "..\math\vector.h"

#define _CRT_SECURE_NO_WARNINGS

typedef unsigned int font_t;


/*
====================================
	printParams_t
====================================
*/
typedef struct {
	font_t		id;
	float		x, y;
	vsVec3		color;
	char		text[ 256 ];
} printParams_t;




font_t	font_create( char* name, int size );
void	font_print( font_t id, float x, float y, vsVec3* color, char* format, ... );
void	font_printQ( font_t id, float x, float y, vsVec3* color, char* format, ... );
void	font_printQueue( void );




#endif