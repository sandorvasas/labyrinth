/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#include "quaternion.h"
#include "matrix.h"
#include <math.h>

void	quat_set( vsQuat* a, float x, float y, float z, float w ) {
	a->x = x;
	a->y = y;
	a->z = z;
	a->w = w;
}


void	quat_from_rot( vsQuat* a, float rot_x, float rot_y, float rot_z ) {
	vsQuat x, y, z;
	
	quat_set( &x, sinf( rot_x * 0.5f ), 0.0f, 0.0f, cosf( rot_x * 0.5f ) );
	quat_set( &y, 0.0f, sinf( rot_y * 0.5f ), 0.0f, cosf( rot_y * 0.5f ) );
	quat_set( &z, 0.0f, 0.0f, sinf( rot_z * 0.5f ), cosf( rot_z * 0.5f ) );

	// a = x * y * z;
	quat_mul( &x, &y );
	quat_mul( &x, &z );
	quat_equ( a, &x );
	quat_normalize( a );
}


void	quat_from_rot_vec( vsQuat* a, vsVec3* rot ) {
	quat_from_rot( a, rot->x, rot->y, rot->z );
}


void	quat_equ( vsQuat* a, vsQuat* b ) {
	a->x = b->x;
	a->y = b->y;
	a->z = b->z;
	a->w = b->w;
}


int		quat_cmp( vsQuat* a, vsQuat* b ) {
	return ( int )( a->x == b->x &&
					a->y == b->y &&
					a->z == b->z &&
					a->w == b->w );
}


void	quat_mul( vsQuat* a, vsQuat* b ) {
	vsQuat c;

	c.x = a->w * b->x + a->x * b->w + a->y * b->z - a->z * b->y;
	c.y = a->w * b->y + a->y * b->w + a->z * b->x - a->x * b->z;
	c.z = a->w * b->z + a->z * b->w + a->x * b->y - a->y * b->x;
	c.w = a->w * b->w - a->x * b->x - a->y * b->y - a->z * b->z;

	quat_equ( a, &c );
}

void	quat_mul_scalar( float s, vsQuat* q ) {
	q->x *= s;
	q->y *= s;
	q->z *= s;
	q->w *= s;
}

void	quat_normalize( vsQuat* a ) {
	float l = quat_length( a );

	if ( l > 0.0f ) {
		l = 1.0f / l;
		a->x *= l;
		a->y *= l;
		a->z *= l;
		a->w *= l;
	}
}


float	quat_length( vsQuat* a ) {
	return sqrtf( a->x * a->x + a->y * a->y + a->z * a->z + a->w * a->w );
}


void	quat_to_mat3( vsMat3* m, vsQuat* q ) {
	float x, y, z, w, xy, wy, wz, yz, xz, wx;
	// extract coordinates to shorten matrix form
	x = q->x;
	y = q->y;
	z = q->z;
	w = q->w;

	wy = w * y;
	xy = x * y;
	wz = w * z;
	yz = y * z;
	xz = x * z;
	wx = w * x;

	// this matrix is the result of the three-matrix form of the conversion
	mat3_set( m, 
		1.f-2.f*(y*y+z*z),		2.f*(xy-wz),			2.f*(xz+wy),
		2.f*(xy+wz),			1.f-2.f*(x*x+z*z),		2.f*(yz-wx),
		2.f*(xz-wy),			2.f*(yz+wx),			1.f-2.f*(x*x+y*y) );
}


void	quat_rotate_vec3( vsQuat* q, vsVec3* v ) {
	vsMat3 m;

	quat_to_mat3( &m, q );
	mat3_mul_vector( v, &m );
}

void	quat_calcW( vsQuat* q ) {
	float a = 1.0f - q->x*q->x - q->y*q->y - q->z*q->z;

	if ( a < 0.0f )
		q->w = 0.0f;
	else
		q->w = -sqrtf( a );
}

float	quat_dot( vsQuat* a, vsQuat* b ) {
	return a->x*b->x + a->y*b->y + a->z*b->z + a->w*b->w;
}

void	quat_add( vsQuat* a, vsQuat* b ) {
	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
	a->w += b->w;
}

void	quat_slerp( vsQuat* out, vsQuat* a, vsQuat* b, float t ) {
	float cosAngle = quat_dot( a, b ) ;
	float angle;
	float sinAngle;
	float f1, f2;
	vsQuat A, B, b2;

	if ( t <= 0.0f ) {
		out = a;
		return;
	}

	if ( t >= 1.0f ) {
		out = b;
		return;
	}

	// angle > 90deg or angle < -90deg
	if ( cosAngle < 0.0f ) {
		quat_equ( &b2, b );
		quat_mul_scalar( -1.0f, &b2 );
		cosAngle *= -1.0f;
	}
	else 
		quat_equ( &b2, b );

	angle = acosf( cosAngle );
	sinAngle = 1.0f / sinf( angle );

	// if angle is not small
	if ( cosAngle < 0.9999f ) {
		f1 = sinf( ( 1.0f - t ) * angle ) * sinAngle;
		f2 = sinf( t * angle ) * sinAngle;
	}
	// interpolate linearly because slerp gives false(?) / bad(?) results this near
	else {
		f1 = 1.0f - t;
		f2 = t;
	}



	quat_equ( &A, a );
	quat_mul_scalar( f1, &A );

	quat_equ( &B, &b2 );
	quat_mul_scalar( f2, &B );

	quat_add( &A, &B );
	quat_equ( out, &A );
}


void	quat_invert( vsQuat* q ) {
	q->x = -q->x;
	q->y = -q->y;
	q->z = -q->z;
}