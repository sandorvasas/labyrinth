/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#ifndef __VS_C_TEXTURE_H__
#define __VS_C_TEXTURE_H__

#define _CRT_SECURE_NO_WARNINGS



typedef struct {
	unsigned char rgb[ 3 ];
} rgb_t;
/*
===============================================

	texture_load_bmp()
		Loads a texture from a bmp file and returns its OpenGL id

===============================================
*/
unsigned int	texture_load_bmp( char* szFileName );

#endif