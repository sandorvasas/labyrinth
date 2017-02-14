#include "Texture.h"
#include <Windows.h>
#include <stdio.h>
#include "..\OpenGL\GLexp.h"

unsigned int texture_load_bmp( char* szFileName ) {
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	FILE*			 f;
	unsigned int	 id, i, j, w, h, mipmap;
	rgb_t			*img, *img2;

	if ( ( f = fopen( szFileName, "rb" ) ) == (FILE*)0 )
		return 0;

	fread( &bmfh, sizeof( bmfh ), 1, f );
	fread( &bmih, sizeof( bmih ), 1, f );

	fseek( f, bmfh.bfOffBits, SEEK_SET );

	w = bmih.biWidth;
	h = bmih.biHeight;

	img = ( rgb_t* ) malloc( w * h * 3 );

	for ( i = 0; i < w * h; i++ ) {
		fread( &img[ i ].rgb[ 2 ], 1, 1, f );
		fread( &img[ i ].rgb[ 1 ], 1, 1, f );
		fread( &img[ i ].rgb[ 0 ], 1, 1, f );
	}
	
	fclose( f );

	
	glGenTextures( 1, &id );
	glBindTexture( GL_TEXTURE_2D, id );
	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img );

	mipmap = 0;
	do
	{
		w /= 2;
		h /= 2;
		mipmap++;

		img2 = ( rgb_t* ) malloc( w * h * 3 );

		//resize image
		for ( i = 0; i < w; i++ ) 
		for ( j = 0; j < h; j++ ) 
		{
			img2[ i * h + j ].rgb[ 0 ] = img[ 2*(  i*2 * h + j ) ].rgb[ 0 ];
			img2[ i * h + j ].rgb[ 1 ] = img[ 2*(  i*2 * h + j ) ].rgb[ 1 ];
			img2[ i * h + j ].rgb[ 2 ] = img[ 2*(  i*2 * h + j ) ].rgb[ 2 ];
		}

		free( img );

		img = img2;

		glTexImage2D( GL_TEXTURE_2D, mipmap, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img );

	} while ( w > 1 && h > 1 );

	glBindTexture( GL_TEXTURE_2D, 0 );
	free( img );

	return id;
}



