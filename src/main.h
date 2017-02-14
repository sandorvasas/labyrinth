#ifndef __VS_MAIN_H__
#define __VS_MAIN_H__

/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#include <Windows.h>
#include "OpenGL\GLexp.h"
#include "game\actor.h"
#include "game\gameLocal.h"
#include "sys\sys.h"


//--------------------------------------------------------------------
//	Functions
//--------------------------------------------------------------------
void	app_init( void );
void	app_uninit( void );
void	app_update( void );
void	app_processUserInput( void );
void	app_render( void );
void	app_newgame( void );


// Main Window's Message Handler procedure
LRESULT CALLBACK MainWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );



#endif