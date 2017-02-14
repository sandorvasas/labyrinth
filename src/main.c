/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#include "main.h"


//--------------------------------------------------------------------
//	Global Variables
//--------------------------------------------------------------------
HWND			g_hMainWnd;					// Handle to main window
HDC				g_hDC;						// Device Context
HGLRC			g_hRC;						// Render Context
unsigned char	g_appRunning = 0;			// 1 if application is running. Exit if 0.
unsigned char	g_keys[ 256 ];				// key[ n ] == 1 if n key is down, 0 if up
unsigned char	g_inMenu = 0;				// 0 if game is active, 1 if user is in the menu


//---------------------------------
// app_init()
//		Initializes application window, sets up OpenGL rendering context
//		and initializes population and environmental variables
//---------------------------------
void app_init( void ) {
	// Create window
	WNDCLASSEX wc;
	HINSTANCE hInst = GetModuleHandle( 0 );
	PIXELFORMATDESCRIPTOR pfd;
	int pf;


	debug_log("----------------------------------------------------------------------------\n  Application Init\n----------------------------------------------------------------------------\n");


	wc.cbClsExtra = 0;
	wc.cbSize = sizeof( WNDCLASSEX );
	wc.cbWndExtra = 0;
	wc.hbrBackground = ( HBRUSH ) GetStockObject( 4 );
	wc.hCursor = LoadCursor( 0, IDC_ARROW );
	wc.hIcon = LoadIcon( 0, IDI_WINLOGO );
	wc.hIconSm = wc.hIcon;
	wc.hInstance = hInst;
	wc.lpfnWndProc = MainWndProc;
	wc.lpszClassName = "vsLabyWndClass";
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	RegisterClassEx( &wc );

	g_hMainWnd = CreateWindowEx( WS_EX_APPWINDOW, 
								 "vsLabyWndClass", "Labyrinth - ( C ) Vasas Sándor", 
								 WS_POPUP, 
								 0, 0, 
								 GetSystemMetrics( SM_CXSCREEN ), 
								 GetSystemMetrics( SM_CYSCREEN ), 
								 0, 0, 
								 hInst, 0 );

	ShowWindow( g_hMainWnd, SW_SHOW );
	ShowCursor( 0 );
	SetForegroundWindow( g_hMainWnd );


	// Setup OpenGL rendering context
	g_hDC = GetDC( g_hMainWnd );
	
	pfd.nSize = sizeof ( pfd );
	pfd.nVersion = 1;
	pfd.cDepthBits = 24;
	pfd.cColorBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;

	pf = ChoosePixelFormat( g_hDC, &pfd );
	SetPixelFormat( g_hDC, pf, &pfd );

	g_hRC = wglCreateContext( g_hDC );
	wglMakeCurrent( g_hDC, g_hRC );


	// OpenGL rendering context setup.
	// Now set field of view
	view_setFOV( 100.0f, 0.1f );

	glEnable( GL_DEPTH_TEST );
	glEnable( GL_TEXTURE_2D );

	//LoadEXT_WGL_EXT_swap_control();
	//wglSwapIntervalEXT( 1 );

	LoadOpenGLCore_2_0();
#ifdef EXTENDED_VERSION
	LoadEXT_GL_EXT_framebuffer_object();
#endif

	// Initialize game
	gameLocal_init();
	gameLocal_newGame();

	g_appRunning = 1;
	g_inMenu = 0;
	memset( g_keys, 0, 256 );
}

//---------------------------------
// app_uninit()
//		Shuts down OpenGL, destroys main window
//---------------------------------
void app_uninit( void ) {
	g_appRunning = 0;
}

//---------------------------------
// app_update()
//		Processes keys, updates cell movements and renders scene
//---------------------------------
void app_update( void ) {
	app_processUserInput();

	if ( g_inMenu );
		//menu_update();
	else
		gameLocal_updatePhysics();

	app_render();
}

//---------------------------------
// app_processUserInput()
//		Processes user input
//---------------------------------
void app_processUserInput( void ) {

	if ( g_inMenu );
		//menu_update();
	else
		gameLocal_processUserInput( g_keys );

	if ( g_keys[ VK_ESCAPE ] ) {
		switch ( gameLocal.intro.state ) { 
			case INTRO_PLAYING:		
						gameLocal_introStop();
			break;
			case INTRO_CINEMA:		
						cinematics_stop( &gameLocal.cinematics[ 0 ] );					
			break;
			default:
				app_uninit();
		}
		g_keys[ VK_ESCAPE ] = 0;
	}
}

//---------------------------------
// app_render()
//		Renders the current scene
//---------------------------------
void app_render( void ) {
	//glClearColor( 0.3f, 0.1f, 0.5f, 1.0f );
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
	glLoadIdentity();

	if ( g_inMenu );
		//menu_update();
	else
		gameLocal_render();

	SwapBuffers( g_hDC );
}


//---------------------------------
// app_newgame()
//		called when user clicks new game button.
//		starts a new game
//---------------------------------
void	app_newgame( void ) {
	g_inMenu = 0;

	gameLocal_newGame();
}



//---------------------------------
// WinMain()
//		Application entry point
//---------------------------------
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpstrCmdLine, int nShowCmd ) {

	MSG msg;

	app_init();
	
	do
	{
		if ( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) ) {
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		} else {
			app_update();
		}
	} while ( g_appRunning );


	gameLocal_shutdown();
	wglMakeCurrent( 0, 0 );
	wglDeleteContext( g_hRC );
	DeleteDC( g_hDC );
	DestroyWindow( g_hMainWnd );

	return 0;
}

//---------------------------------
// MainWndProc()
//---------------------------------
LRESULT CALLBACK MainWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
	switch( uMsg ) 
	{
	case WM_KEYDOWN: g_keys[ wParam ] = 1;
	break;
	case WM_KEYUP: g_keys[ wParam ] = 0;
	break;
	}

	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}
