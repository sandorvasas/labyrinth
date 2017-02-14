/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#ifndef __VS_MATRIX_H__
#define __VS_MATRIX_H__

#include "vector.h"


typedef struct {
	float m[ 9 ];
} vsMat3;

typedef struct {
	float m[ 16 ];
} vsMat4;



/*
===============================================

	vsMat3

===============================================
*/
void	mat3_set( vsMat3* m, float m0, float m3, float m6, 
							 float m1, float m4, float m7, 
							 float m2, float m5, float m8 );
int		mat3_cmp( vsMat3* m, vsMat3* n );
void	mat3_equ( vsMat3* m, vsMat3* n );
void	mat3_identity( vsMat3* e );
void	mat3_transpose( vsMat3* e );	
void	mat3_mul_mat3(  vsMat3* m, vsMat3* n );
void	mat3_mul_vector( vsVec3* v, vsMat3* m );
void	mat3_mul_scalar( vsMat3* m, float s );
void	mat3_add_mat3( vsMat3* m, vsMat3* n );
void	mat3_add_scalar( vsMat3* m, float s );
void	mat3_to_mat4( vsMat4* e, vsMat3* m );


/*
===============================================

	vsMat4

===============================================
*/
void	mat4_set( vsMat4* m, float m0, float m4, float m8,  float m12, 
							 float m1, float m5, float m9,  float m13, 
							 float m2, float m6, float m10, float m14, 
							 float m3, float m7, float m11, float m15  );
int		mat4_cmp( vsMat4* m, vsMat4* n );
void	mat4_equ( vsMat4* m, vsMat4* n );
void	mat4_identity( vsMat4* e );
void	mat4_transpose( vsMat4* e );	
void	mat4_mul_mat4( vsMat4* m, vsMat4* n );
//void	mat4_mul_vector(  vsMat4* m, vsVec3* v );
void	mat4_mul_scalar( vsMat4* m, float s );
void	mat4_add_mat4( vsMat4* m, vsMat4* n );
void	mat4_add_scalar( vsMat4* m, float s );
void	mat4_to_mat3( vsMat3* e, vsMat4* m );



#endif