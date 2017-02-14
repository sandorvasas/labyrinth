/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#ifndef __VS_ACTOR_H__
#define __VS_ACTOR_H__

#include "world.h"
#include "..\math\vector.h"
#include "labyrinth.h"
#include "md5model.h"


/*
===============================================

	actor_t

===============================================
*/
enum {
	ACTOR_INITIAL = -1,
	ACTOR_STANDING = 0,
	ACTOR_MOVING,
	ACTOR_ATTACKING,
	ACTOR_TAUNTING,
	ACTOR_CUSTOM_ANIM
};

enum {
	ACTOR_DIR_UP 	= 1,		// +Z
	ACTOR_DIR_DOWN	= 2,		// -Z
	ACTOR_DIR_LEFT	= 4,		// -X
	ACTOR_DIR_RIGHT	= 8			// +X
};


typedef struct {
	char			entityName[ 64 ];

	vsVec3			currentPosition;
	int				direction;
	coord_t			curCell;
	coord_t			destCell;

	float			cameraViewDist;
	float			cameraAngleXDeg;
	vsVec3			cameraPosition;

	md5Model_t		model;
	md5Anim_t*		animWalk;
	md5Anim_t*		animStand;
	md5Anim_t*		animAttack;
	md5Anim_t*		animTaunt;
	md5Anim_t*		animCustom;


	// state between cells ----
	vsVec3			origin;
	vsVec3			destination;
	coord_t			moveDir;
	float			currentTime;

	float			movementTime;
	float			attackTime;

	float			currentAnimSpeed;

	// sounds -----------------
	float			stepTime;
	char*			soundStep1;
	char*			soundStep2;
	char			curStep;
	float			stepTimeCount;

	char			state;

	// game variables ---------
	char			living;
	float			maxHealth;
	float			health;
} actor_t;



void	actor_init( actor_t * actor, char* name, md5Model_t* model, md5Anim_t* walkAnim, md5Anim_t* standAnim, md5Anim_t* attackAnim,
					char* soundStep1, char* soundStep2, float timeBetweenSteps,
					int cellX, int cellY, float movementTime, float attackTime, float maxHealth );
void	actor_uninit( actor_t * actor );
void	actor_changeState( actor_t * actor, int state, int dir );
void	actor_setCustomAnim( actor_t* actor, md5Anim_t* anim, int dir );
void	actor_updatePhysics( actor_t * actor );
void	actor_updateCamera( actor_t* actor );
void	actor_render( actor_t* actor );
void	actor_setDirection( actor_t* actor, int dir );
void	actor_damage( actor_t* actor, float damage );
char	actor_getPossibleDirections( actor_t* actor, labMap_t* lmap );

/*
===============================================
	view_setFOV()
===============================================
*/
void	view_setFOV( float fov_degrees, float nearPlane );

#endif