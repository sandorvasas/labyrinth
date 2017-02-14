#include "plane.h"


//------------------------------------------------
//	plane_setf()
//------------------------------------------------
void	plane_setf( plane_t* s, float a, float b, float c, float d ) {
	s->d = d;
	s->c = c;
	s->b = b;
	s->a = a;
}

//------------------------------------------------
//	plane_set_n()
//------------------------------------------------
void	plane_set_n( plane_t* s, vsVec3* n, vsVec3* p0 ) {
	s->a = n->x;
	s->b = n->y;
	s->c = n->z;
	s->d = -vec3_dot( n, p0 );
}

//------------------------------------------------
//	plane_projectVector()
//		V' = V - (N.V)*N;
//------------------------------------------------
void	plane_projectVector( plane_t* s, vsVec3* v ) {
	vsVec3 a;
	float NdotV = s->a * v->x + s->b * v->y + s->c * v->z;
	vec3_set( &a, NdotV * s->a, NdotV * s->b, NdotV * s->c );

	vec3_sub( v, &a );
}

//------------------------------------------------
//	plane_distance()
//------------------------------------------------
float	plane_distance( plane_t* s, vsVec3* p ) {
	vsVec3 n;
	vec3_set( &n, s->a, s->b, s->c );
	return ( vec3_dot( &n, p ) );
}

//------------------------------------------------
//	plane_classify()
//------------------------------------------------
int		plane_classify( plane_t* s, vsVec3* p ) {
	float d = plane_distance( s, p );

	if ( d > 0.0f ) return 1;
	if ( d < 0.0f ) return -1;

	return 0;
}