/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#ifndef __VS_VERTEX_H__
#define __VS_VERTEX_H__

#include "..\math\vector.h"


/*
=================================================
	vertex_t
		( 32B size )
=================================================
*/
typedef struct {
	vsVec3		pos;
	vsVec3		normal;
	vsVec2		uv;
	//vsVec3		tangent;

/*	enum {
		Offset_pos = 0,
		Offset_normal = 12,
		Offset_uv = 24,
		//Offset_tangent = 32
	};*/
} vertex_t;

void	vertex_set_pnt( vertex_t* v, float x, float y, float z, float nx, float ny, float nz, float s, float t );
void	vertex_set_pn( vertex_t* v, float x, float y, float z, float nx, float ny, float nz );
void	vertex_set( vertex_t* v, float x, float y, float z );


typedef struct {
	unsigned int	a, b, c;			// indices to vertices
} triangle_t;

#endif