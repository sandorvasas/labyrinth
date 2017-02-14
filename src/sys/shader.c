/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#include "shader.h"
#include <stdio.h>
#include "..\OpenGL\GLexp.h"
#include <malloc.h>

//-------------------------------
//	shader_new()
//-------------------------------
void	shader_new( shader_t* shader, char* szFileName ) {
	FILE		*f;
				//	[ numLines ][ numCharacters ]

	const int	maxNumLines = 200;
	const int	maxNumChars = 200;
	char		line[ 200 ];
	char**		frag_code;
	char**		vert_code;
	char		numFragLines, numVertLines;
	unsigned int vid, fid;
	int			i, j;

	frag_code = ( char** ) malloc( maxNumLines * sizeof( char* ) );
	vert_code = ( char** ) malloc( maxNumLines * sizeof( char* ) );
	
	for ( j = 0; j < maxNumLines; j++ ) {
		frag_code[ j ] = ( char* ) malloc( maxNumChars * sizeof( char ) );
		vert_code[ j ] = ( char* ) malloc( maxNumChars * sizeof( char ) );
		for ( i = 0; i < maxNumChars; i++ ) 
			frag_code[ j ][ i ] = vert_code[ j ][ i ] = 0;
	}

	if ( !(f = fopen( szFileName, "r" )) ) {
		*shader = 0;
		return;
	}

	// loop through file
	while( !feof( f ) )
	{
		fgets( line, maxNumChars, f );
		if ( strstr( line, "#FRAGMENT_SHADER_BEGIN" ) ) {
			numFragLines = 0;
			do {
				fgets( frag_code[ numFragLines++ ], maxNumChars, f );
			} while ( !strstr( frag_code[ numFragLines-1 ], "#FRAGMENT_SHADER_END" ) );
			numFragLines -= 1;
		}
		if ( strstr( line, "#VERTEX_SHADER_BEGIN" ) ) {
			numVertLines = 0;
			do {
				fgets( vert_code[ numVertLines++ ], maxNumChars, f );
			} while ( !strstr( vert_code[ numVertLines-1 ], "#VERTEX_SHADER_END" ) );
			numVertLines -= 1;
		}
	}

	fclose( f );

	fid = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fid, numFragLines, ( const GLchar** )frag_code, 0 );
	glCompileShader( fid );

	vid = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vid, numVertLines, ( const GLchar** )vert_code, 0 );
	glCompileShader( vid );

	*shader = glCreateProgram();
	glAttachShader( *shader, fid );
	glAttachShader( *shader, vid );
	glLinkProgram( *shader );

	for ( j = 0; j < maxNumLines; j++ ) {
		free( vert_code[ j ] );
		free( frag_code[ j ] );
	}

	free( vert_code );
	free( frag_code );
}

//-------------------------------
//	shader_delete()
//-------------------------------
void	shader_delete( shader_t shader ) {
	glDeleteShader( shader );
}

//-------------------------------
//	shader_use()
//-------------------------------
void	shader_use( shader_t shader ) {
	glUseProgram( shader );
}


