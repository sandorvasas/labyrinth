#include "world.h"
#include "gameLocal.h"
#include "labyrinth.h"

//-----------------------------------
//	world_init()
//-----------------------------------
void	world_init( void ) {
	vsVec3 off, scale;
	int i, j;
	coord_t A;
	float x, y;

	labMap_set( &gameLocal.world.lmap, 33, 33 );
	//labMap_generate_DFS( &gameLocal.world.lmap );
	labMap_generate_GT( &gameLocal.world.lmap );
	//labMap_saveToFile( &gameLocal.world.lmap, "maze.bmp" );

	vec3_set( &off, -10.0f, 0.0f, -10.0f );
	vec3_set( &scale, 12.0f, 16.0f, 12.0f );
	labModel_create( &gameLocal.world.lmap, &gameLocal.world.labModel, &off, &scale );
	labModel_setShader( &gameLocal.world.labModel, &gameLocal.shaders[ 0 ] );

	vec3_set( &gameLocal.world.lights[ 0 ], -10.0f, 25.0f, 10.0f );

	for ( i = 0; i < 8; i++ ) {
		do {
				j = rand() % ( gameLocal.world.labModel.map->width * gameLocal.world.labModel.map->height );
		} while ( gameLocal.world.lmap.data[ j ] !=  1 );

		A.y = j / gameLocal.world.labModel.map->width;
		A.x = j % A.y;

		x = gameLocal.world.labModel.scale.x * ( float )A.x;
		y = gameLocal.world.labModel.scale.y * ( float )A.y;

		vec3_set( &gameLocal.world.lights[ i ], x, 10.0f, y );
	}
}


//-----------------------------------
//	world_render()
//-----------------------------------
void	world_render( void ) {
	vsVec3 v;
	labModel_render( &gameLocal.world.labModel );

	//vec3_equ( &v, &gameLocal.actor.hmodel.directionVector );
	//vec3_mul( 10.0f, &v );
	vec3_equ( &gameLocal.world.lights[ 0 ], &gameLocal.player.actor.currentPosition );
	//vec3_add( &gameLocal.world.lights[ 0 ], &v );
	gameLocal.world.lights[ 0 ].y += 15.0f;
}


//-----------------------------------
//	world_apocalypse()
//-----------------------------------
void	world_apocalypse( void ) {
	labModel_destroy( &gameLocal.world.labModel );
}


//-----------------------------------
//	world_updatePhysics()
//-----------------------------------
void	world_updatePhysics( void ) {
}