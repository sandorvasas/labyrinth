/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#ifndef __VS_QUATERNION_H__
#define __VS_QUATERNION_H__

#include "vector.h"
#include "matrix.h"

/*
===========================================================

	Quaternion class

===========================================================
*/

typedef struct {
	float w, x, y, z;
} vsQuat;



void	quat_set( vsQuat* a, float x, float y, float z, float w );
void	quat_from_rot( vsQuat* a, float rot_x, float rot_y, float rot_z );
void	quat_from_rot_vec( vsQuat* a, vsVec3* rot );
void	quat_equ( vsQuat* a, vsQuat* b );
int		quat_cmp( vsQuat* a, vsQuat* b );
void	quat_mul( vsQuat* a, vsQuat* b );
void	quat_mul_scalar( float s, vsQuat* q );
void	quat_add( vsQuat* a, vsQuat* b );
void	quat_normalize( vsQuat* a );
float	quat_length( vsQuat* a );
void	quat_to_mat3( vsMat3* m, vsQuat* q );
void	quat_rotate_vec3( vsQuat* q, vsVec3* v );
void	quat_calcW( vsQuat* q );
float	quat_dot( vsQuat* a, vsQuat* b );
void	quat_slerp( vsQuat* out, vsQuat* a, vsQuat* b, float t );
void	quat_invert( vsQuat* q );



#endif