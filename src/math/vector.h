/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#ifndef __VS_VECTOR_H__
#define __VS_VECTOR_H__


#define PI  3.1415926536f
#define DEG_TO_RAD 0.01745329251994329576923690768489f
#define RAD_TO_DEG 57.295779513082320876798154814105f


/*
===============================================

	vsVec2

===============================================
*/
typedef struct {
	float x, y;
} vsVec2;

void	vec2_set( vsVec2* a, float x, float y );
void	vec2_equ( vsVec2* a, vsVec2* b );
int		vec2_cmp( vsVec2* a, vsVec2* b );
float	vec2_dist( vsVec2* a, vsVec2* b );
void	vec2_add( vsVec2* a, vsVec2* b );
void	vec2_sub( vsVec2* a, vsVec2* b );
void	vec2_add_scalar( vsVec2* a, float b );
void	vec2_mul( float a, vsVec2* b );
float	vec2_dot( vsVec2* a, vsVec2* b );
float	vec2_length( vsVec2* e );
void	vec2_normalize( vsVec2* n );



/*
===============================================

	vsVec3

===============================================
*/
typedef struct {
	float x, y, z;
} vsVec3;

void	vec3_set( vsVec3* a, float x, float y, float z );
void	vec3_equ( vsVec3* a, vsVec3* b );
int		vec3_cmp( vsVec3* a, vsVec3* b );
float	vec3_dist( vsVec3* a, vsVec3* b );
void	vec3_add( vsVec3* a, vsVec3* b );
void	vec3_sub( vsVec3* a, vsVec3* b );
void	vec3_add_scalar( vsVec3* a, float b );
void	vec3_mul( float a, vsVec3* b );
float	vec3_dot( vsVec3* a, vsVec3* b );
void	vec3_cross( vsVec3* a, vsVec3* b );
float	vec3_length( vsVec3* e );
void	vec3_normalize( vsVec3* n );
void	vec3_lerp( vsVec3* out, vsVec3* a, vsVec3* b, float t );


#endif