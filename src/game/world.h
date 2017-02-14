/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#ifndef __VS_WORLD_H__
#define __VS_WORLD_H__

#include "labyrinth.h"


/*
===============================================

	world_t

===============================================
*/
typedef struct {
	labMap_t		lmap;
	labModel_t		labModel;
	vsVec3			lights[ 8 ];
} world_t;


void	world_render( void );
void	world_init( void );
void	world_apocalypse( void );
void	world_updatePhysics( void );

#endif