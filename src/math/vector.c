#include "vector.h"
#include <math.h>

/*
========================================================
	vsVec2 Functions
========================================================
*/
void	vec2_set( vsVec2* a, float x, float y ) {
	a->x = x;
	a->y = y;
}

void	vec2_equ( vsVec2* a, vsVec2* b ) {
	a->x = b->x;
	a->y = b->y;
}

int	vec2_cmp( vsVec2* a, vsVec2* b ) {
	return ( int )( a->x == b->x && a->y == b->y );
}

float	vec2_dist( vsVec2* a, vsVec2* b ) {
	vsVec2 d;
	vec2_equ( &d, a );
	vec2_sub( &d, b );
	return sqrtf( d.x * d.x + d.y * d.y );
}

void	vec2_add( vsVec2* a, vsVec2* b ) {
	a->x += b->x;
	a->y += b->y;
}

void	vec2_sub( vsVec2* a, vsVec2* b ) {
	a->x -= b->x;
	a->y -= b->y;
}

void	vec2_add_scalar( vsVec2* a, float b ) {
	a->x += b;
	a->y += b;
}

void	vec2_mul( float s, vsVec2* a ) {
	a->x *= s;
	a->y *= s;
}

float	vec2_dot( vsVec2* a, vsVec2* b ) {
	return ( a->x * b->x + a->y * b->y );
}


float	vec2_length( vsVec2* e ) {
	return sqrtf( e->x * e->x + e->y * e->y );
}

void	vec2_normalize( vsVec2* n ) {
	vec2_mul( 1.0f / vec2_length( n ), n );
}


/*
========================================================
	vsVec3 Functions
========================================================
*/
void	vec3_set( vsVec3* a, float x, float y, float z ) {
	a->x = x;
	a->y = y;
	a->z = z;
}

void	vec3_equ( vsVec3* a, vsVec3* b ) {
	a->x = b->x;
	a->y = b->y;
	a->z = b->z;
}

int		vec3_cmp( vsVec3* a, vsVec3* b ) {
	return ( int )( a->x == b->x && a->y == b->y && a->z == b->z );
}

float	vec3_dist( vsVec3* a, vsVec3* b ) {
	vsVec3 d;
	vec3_equ( &d, a );
	vec3_sub( &d, b );
	return sqrtf( d.x * d.x + d.y * d.y + d.z * d.z );
}

void	vec3_add( vsVec3* a, vsVec3* b ) {
	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
}

void	vec3_sub(  vsVec3* a, vsVec3* b ) {
	a->x -= b->x;
	a->y -= b->y;
	a->z -= b->z;
}

void	vec3_add_scalar( vsVec3* a, float b ) {
	a->x += b;
	a->y += b;
	a->z += b;
}

void	vec3_mul( float s, vsVec3* a ) {
	a->x *= s;
	a->y *= s;
	a->z *= s;
}

float	vec3_dot( vsVec3* a, vsVec3* b ) {
	return ( a->x * b->x + a->y * b->y + a->z * b->z );
}

void	vec3_cross( vsVec3* a, vsVec3* b ) {
	vsVec3 e;
	e.x = a->y * b->z - a->z * b->y;
	e.y = a->z * b->x - a->x * b->z;
	e.z = a->x * b->y - a->y * b->x;
	vec3_equ( a, &e );
}

float	vec3_length( vsVec3* e ) {
	return sqrtf( e->x * e->x + e->y * e->y + e->z * e->z );
}

void	vec3_normalize( vsVec3* n ) {
	vec3_mul( 1.0f / vec3_length( n ), n );
}


void	vec3_lerp( vsVec3* out, vsVec3* a, vsVec3* b, float t )
{
	if ( t >= 1.0f ) 
		vec3_equ( out, b );
	else
	if ( t <= 0.0f )
		vec3_equ( out, a );
	else
	{
		out->x = a->x * ( 1.0f - t ) + b->x * t;
		out->y = a->y * ( 1.0f - t ) + b->y * t;
		out->z = a->z * ( 1.0f - t ) + b->z * t;
	}
}

