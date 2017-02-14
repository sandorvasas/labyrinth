#include "vertex.h"




void	vertex_set_pnt( vertex_t* v, float x, float y, float z, float nx, float ny, float nz, float s, float t ) {
	vec3_set( &v->pos, x, y, z );
	vec3_set( &v->normal, nx, ny, nz );
	vec2_set( &v->uv, s, t );
}

void	vertex_set_pn( vertex_t* v, float x, float y, float z, float nx, float ny, float nz ) {
	vec3_set( &v->pos, x, y, z );
	vec3_set( &v->normal, nx, ny, nz );
	vec2_set( &v->uv, 0.0f, 0.0f );
}

void	vertex_set( vertex_t* v, float x, float y, float z ) {
	vec3_set( &v->pos, x, y, z );
	vec3_set( &v->normal, 0.0f, 0.0f, 0.0f );
	vec2_set( &v->uv, 0.0f, 0.0f );
}