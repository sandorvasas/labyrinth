/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas


	GLSL Shader helper functions

==============================================================================================
*/
#ifndef __VS_C_SHADER_H__
#define __VS_C_SHADER_H__

#define _CRT_SECURE_NO_WARNINGS


typedef unsigned int shader_t;

/*
===============================================

	shader_new()
		Loads a GLSL fragment & vertex shader from file.
		Structure:
			#FRAGMENT_SHADER
				< frag_code >
			#VERTEX_SHADER
				< vert_code >

===============================================
*/
void	shader_new( shader_t* shader, char* szFileName );
void	shader_delete( shader_t shader );
void	shader_use( shader_t shader );

#endif