/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#include "matrix.h"



/*
===============================================

	vsMat3

===============================================
*/
void	mat3_set( vsMat3* m, float m0, float m3, float m6, 
							 float m1, float m4, float m7, 
							 float m2, float m5, float m8 ) {
	m->m[ 0 ] = m0;
	m->m[ 1 ] = m1;
	m->m[ 2 ] = m2;

	m->m[ 3 ] = m3;
	m->m[ 4 ] = m4;
	m->m[ 5 ] = m5;

	m->m[ 6 ] = m6;
	m->m[ 7 ] = m7;
	m->m[ 8 ] = m8;
}

int		mat3_cmp( vsMat3* m, vsMat3* n ) {
	return ( int ) ( m->m[ 0 ] == n->m[ 0 ] &&
					 m->m[ 1 ] == n->m[ 1 ] &&
					 m->m[ 2 ] == n->m[ 2 ] &&
					 m->m[ 3 ] == n->m[ 3 ] &&
					 m->m[ 4 ] == n->m[ 4 ] &&
					 m->m[ 5 ] == n->m[ 5 ] &&
					 m->m[ 6 ] == n->m[ 6 ] &&
					 m->m[ 7 ] == n->m[ 7 ] &&
					 m->m[ 8 ] == n->m[ 8 ] );
					 
}

void	mat3_equ( vsMat3* m, vsMat3* n ) {
	m->m[ 0 ] = n->m[ 0 ];
	m->m[ 1 ] = n->m[ 1 ];
	m->m[ 2 ] = n->m[ 2 ];
	m->m[ 3 ] = n->m[ 3 ];
	m->m[ 4 ] = n->m[ 4 ];
	m->m[ 5 ] = n->m[ 5 ];
	m->m[ 6 ] = n->m[ 6 ];
	m->m[ 7 ] = n->m[ 7 ];
	m->m[ 8 ] = n->m[ 8 ];
	m->m[ 9 ] = n->m[ 9 ];
}

void	mat3_identity( vsMat3* e ) { 
	e->m[ 0 ] = 1.0f; e->m[ 3 ] = 0.0f; e->m[ 6 ] = 0.0f; 
	e->m[ 1 ] = 0.0f; e->m[ 4 ] = 1.0f; e->m[ 7 ] = 0.0f; 
	e->m[ 2 ] = 0.0f; e->m[ 5 ] = 0.0f; e->m[ 8 ] = 1.0f; 
} 


void	mat3_transpose( vsMat3* e ) { 
	vsMat3 t;
	unsigned char i;

	t.m[ 0 ] = e->m[ 0 ];
	t.m[ 4 ] = e->m[ 4 ];
	t.m[ 8 ] = e->m[ 8 ];

	t.m[ 1 ] = e->m[ 3 ];
	t.m[ 2 ] = e->m[ 6 ];
	t.m[ 3 ] = e->m[ 1 ];
	t.m[ 5 ] = e->m[ 7 ];
	t.m[ 6 ] = e->m[ 2 ];
	t.m[ 7 ] = e->m[ 5 ];

	for ( i = 0; i < 9; i++ )
		e->m[ i ] = t.m[ i ];
} 


void	mat3_mul_mat3(  vsMat3* m, vsMat3* n ) { 
	int y, x, k;
	float s;
	vsMat3 E;

	for ( y = 0; y < 3; y++ )
	for ( x = 0; x < 3; x++ ) {
		s = 0.0f;
		for ( k = 0; k < 3; k++ ) {
			s += m->m[ 3 * k + y ] * n->m[ 3 * x + k ];
		}
		E.m[ 3 * x + y ] = s;
	}

	for ( k = 0; k < 9; k++ )
		m->m[ k ] = E.m[ k ];
} 


void	mat3_mul_vector( vsVec3* v, vsMat3* m ) { 
	vsVec3 a;

	a.x = m->m[ 0 ] * v->x +  m->m[ 3 ] * v->y +  m->m[ 6 ] * v->z;
	a.y = m->m[ 1 ] * v->x +  m->m[ 4 ] * v->y +  m->m[ 7 ] * v->z;
	a.z = m->m[ 2 ] * v->x +  m->m[ 5 ] * v->y +  m->m[ 8 ] * v->z;

	vec3_equ( v, &a ); 
} 


void	mat3_mul_scalar( vsMat3* m, float s ) {
	unsigned char i;

	for ( i = 0; i < 9; i++ )
		m->m[ i ] *= s;
} 


void	mat3_add_mat3(  vsMat3* m, vsMat3* n ) { 
	unsigned char i;

	for ( i = 0; i < 9; i++ )
		m->m[ i ] += n->m[ i ];
} 


void	mat3_add_scalar( vsMat3* m, float s ) { 
	unsigned char i;

	for ( i = 0; i < 9; i++ )
		m->m[ i ] += s;
} 


void	mat3_to_mat4( vsMat4* e, vsMat3* m ) { 
	e->m[ 0 ] = m->m[ 0 ];
	e->m[ 1 ] = m->m[ 1 ];
	e->m[ 2 ] = m->m[ 2 ];
	e->m[ 3 ] = 0.0f;

	e->m[ 4 ] = m->m[ 3 ];
	e->m[ 5 ] = m->m[ 4 ];
	e->m[ 6 ] = m->m[ 5 ];
	e->m[ 7 ] = 0.0f;
	
	e->m[ 8 ] = m->m[ 6 ];
	e->m[ 9 ] = m->m[ 7 ];
	e->m[ 10 ] = m->m[ 8 ];
	e->m[ 11 ] = 0.0f;

	e->m[ 12 ] = 0.0f;
	e->m[ 13 ] = 0.0f;
	e->m[ 14 ] = 0.0f;
	e->m[ 15 ] = 1.0f;
} 




/*
===============================================

	vsMat4

===============================================
*/
void	mat4_set( vsMat4* m, float m0, float m4, float m8,  float m12, 
							 float m1, float m5, float m9,  float m13, 
							 float m2, float m6, float m10, float m14, 
							 float m3, float m7, float m11, float m15 ) {
	m->m[ 0 ] = m0;
	m->m[ 1 ] = m1;
	m->m[ 2 ] = m2;
	m->m[ 3 ] = m3;
	
	m->m[ 4 ] = m4;
	m->m[ 5 ] = m5;
	m->m[ 6 ] = m6;
	m->m[ 7 ] = m7;

	m->m[ 8 ] = m8;
	m->m[ 9 ] = m9;
	m->m[ 10 ] = m10;
	m->m[ 11 ] = m11;
	
	m->m[ 12 ] = m12;
	m->m[ 13 ] = m13;
	m->m[ 14 ] = m14;
	m->m[ 15 ] = m15;
}

int		mat4_cmp( vsMat4* m, vsMat4* n ) {
	return ( int ) ( m->m[ 0 ] == n->m[ 0 ] &&
					 m->m[ 1 ] == n->m[ 1 ] &&
					 m->m[ 2 ] == n->m[ 2 ] &&
					 m->m[ 3 ] == n->m[ 3 ] &&
					 m->m[ 4 ] == n->m[ 4 ] &&
					 m->m[ 5 ] == n->m[ 5 ] &&
					 m->m[ 6 ] == n->m[ 6 ] &&
					 m->m[ 7 ] == n->m[ 7 ] &&
					 m->m[ 8 ] == n->m[ 8 ] &&
					 m->m[ 9 ] == n->m[ 9 ] &&
					 m->m[10 ] == n->m[10 ] &&
					 m->m[11 ] == n->m[11 ] &&
					 m->m[12 ] == n->m[12 ] &&
					 m->m[13 ] == n->m[13 ] &&
					 m->m[14 ] == n->m[14 ] &&
					 m->m[15 ] == n->m[15 ] );
}

void	mat4_equ( vsMat4* m, vsMat4* n ) {
	m->m[ 0 ] = n->m[ 0 ];
	m->m[ 1 ] = n->m[ 1 ];
	m->m[ 2 ] = n->m[ 2 ];
	m->m[ 3 ] = n->m[ 3 ];
	m->m[ 4 ] = n->m[ 4 ];
	m->m[ 5 ] = n->m[ 5 ];
	m->m[ 6 ] = n->m[ 6 ];
	m->m[ 7 ] = n->m[ 7 ];
	m->m[ 8 ] = n->m[ 8 ];
	m->m[ 9 ] = n->m[ 9 ];
	m->m[10 ] = n->m[10 ];
	m->m[11 ] = n->m[11 ];
	m->m[12 ] = n->m[12 ];
	m->m[13 ] = n->m[13 ];
	m->m[14 ] = n->m[14 ];
	m->m[15 ] = n->m[15 ];
}

void	mat4_identity( vsMat4* e ) {
	e->m[ 0 ] = 1.0f; e->m[ 4 ] = 0.0f; e->m[ 8 ] = 0.0f; e->m[12 ] = 0.0f; 
	e->m[ 1 ] = 0.0f; e->m[ 5 ] = 1.0f; e->m[ 9 ] = 0.0f; e->m[13 ] = 0.0f; 
	e->m[ 2 ] = 0.0f; e->m[ 6 ] = 0.0f; e->m[10 ] = 1.0f; e->m[14 ] = 0.0f; 
	e->m[ 3 ] = 0.0f; e->m[ 7 ] = 0.0f; e->m[11 ] = 0.0f; e->m[15 ] = 1.0f; 
} 

/*0 4 8  12
1 5 9  13
2 6 10 14
3 7 11 15*/
void	mat4_transpose( vsMat4* e ) { 
	vsMat4 t;
	unsigned char i;

	t.m[ 0 ] = e->m[ 0 ];
	t.m[ 5 ] = e->m[ 4 ];
	t.m[ 10 ] = e->m[ 8 ];
	t.m[ 15 ] = e->m[ 15 ];

	t.m[ 1 ] = e->m[ 4 ];
	t.m[ 2 ] = e->m[ 8 ];
	t.m[ 3 ] = e->m[ 12 ];
	t.m[ 4 ] = e->m[ 1 ];
	t.m[ 6 ] = e->m[ 9 ];
	t.m[ 7 ] = e->m[ 13 ];
	t.m[ 8 ] = e->m[ 2 ];
	t.m[ 9 ] = e->m[ 6 ];
	t.m[ 11 ] = e->m[ 14 ];
	t.m[ 12 ] = e->m[ 3 ];
	t.m[ 13 ] = e->m[ 7 ];
	t.m[ 14 ] = e->m[ 11 ];

	for ( i = 0; i < 16; i++ )
		e->m[ i ] = t.m[ i ];
} 


void	mat4_mul_mat4( vsMat4* m, vsMat4* n ) { 
	int y, x, k;
	float s;
	vsMat4 E;

	for ( y = 0; y < 4; y++ )
	for ( x = 0; x < 4; x++ ) {
		s = 0.0f;
		for ( k = 0; k < 4; k++ ) {
			s += m->m[ 4 * k + y ] * n->m[ 4 * x + k ];
		}
		E.m[ 4 * x + y ] = s;
	}

	for ( k = 0; k < 16; k++ )
		m->m[ k ] = E.m[ k ];
} 


//void	mat4_mul_vector( vsVec4* e, vsMat4* m, vsVec3* v ) { 
//} 


void	mat4_mul_scalar( vsMat4* m, float s ) { 
	unsigned char i;

	for ( i = 0; i < 16; i++ )
		m->m[ i ] *= s;
} 


void	mat4_add_mat4( vsMat4* m, vsMat4* n ) { 
	unsigned char i;

	for ( i = 0; i < 16; i++ )
		m->m[ i ] += n->m[ i ];
} 


void	mat4_add_scalar( vsMat4* m, float s ) { 
	unsigned char i;

	for ( i = 0; i < 16; i++ )
		m->m[ i ] += s;
} 


void	mat4_to_mat3( vsMat3* e, vsMat4* m ) { 
	e->m[ 0 ] = m->m[ 0 ];
	e->m[ 1 ] = m->m[ 1 ];
	e->m[ 2 ] = m->m[ 2 ];

	e->m[ 3 ] = m->m[ 4 ];
	e->m[ 4 ] = m->m[ 5 ];
	e->m[ 5 ] = m->m[ 6 ];
	
	e->m[ 6 ] = m->m[ 8 ];
	e->m[ 7 ] = m->m[ 9 ];
	e->m[ 8 ] = m->m[ 10 ];
} 

