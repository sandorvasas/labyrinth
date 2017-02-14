/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#ifndef __VS_C_PLANE_H__
#define __VS_C_PLANE_H__

#include "vector.h"

/*
=================================================
	plane_t
=================================================
*/
typedef struct {
	float a, b, c, d;
} plane_t;


void	plane_setf( plane_t* s, float a, float b, float c, float d );
void	plane_set_n( plane_t* s, vsVec3* n, vsVec3* p0 );
void	plane_projectVector( plane_t* s, vsVec3* v );
float	plane_distance( plane_t* s, vsVec3* p );
int		plane_classify( plane_t* s, vsVec3* p );

#endif