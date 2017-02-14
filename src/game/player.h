/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#ifndef __VS_PLAYER_H__
#define __VS_PLAYER_H__


#include "actor.h"
#include "labyrinth.h"



/*
====================================
	player_t
====================================
*/
typedef struct {
	actor_t			actor;

	// bomb -----------------------
	coord_t			bombCoord;
	float			bombCounter;

} player_t;


void	player_init( void );
void	player_destroy( void );
void	player_placeMine( coord_t* coord );
void	player_updatePhysics( void );
void	player_render( void );


#endif