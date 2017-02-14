/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#ifndef __VS_C_DEBUG_H__
#define __VS_C_DEBUG_H__

#include <Windows.h>

#define _CRT_SECURE_NO_WARNINGS


#define DEBUG_MODE
//#undef DEBUG_MODE

#define EXTENDED_VERSION


void			win32_msgbox( char* format, ... );
void			debug_log( char* format, ... );

unsigned char	inRange( int n, int low, int high );

#endif