/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#include <Windows.h>
#include <math.h>
#include "actor.h"
#include "..\math\vector.h"
#include "..\math\matrix.h"
#include "..\math\quaternion.h"
#include "..\math\plane.h"
#include "world.h"
#include "..\OpenGL\GL.h"
#include "..\sys\sys.h"
#include "gameLocal.h"
#include "..\sys\printer.h"


/*
-----------------------------------
	actor_init()
		Initializes actor with some default values.
-----------------------------------
*/
void	actor_init( actor_t * actor, char* name, md5Model_t* model, md5Anim_t* walkAnim, md5Anim_t* standAnim, md5Anim_t* attackAnim,
					char* soundStep1, char* soundStep2, float timeBetweenSteps,
					int cellX, int cellY, float movementTime, float attackTime, float maxHealth ) {
	vsVec3 center;

	strcpy( actor->entityName, name );
	actor->destCell.x = actor->curCell.x = cellX;
	actor->destCell.y = actor->curCell.y = cellY;
	actor->state = ACTOR_INITIAL;

	labModel_getCenterOfCell( &gameLocal.world.labModel, actor->curCell.x, actor->curCell.y, &center ); 
	vec3_equ( &actor->currentPosition,		&center ); 
	vec3_equ( &actor->origin,				&center ); 
	vec3_equ( &actor->destination,			&center );
	
	actor->moveDir.x = 0;
	actor->moveDir.y = 0;

	actor->movementTime = movementTime;
	actor->attackTime = attackTime;
	actor->cameraViewDist = 40.0f;
	actor->cameraAngleXDeg = 65.0f;

	// sound
	actor->stepTime = timeBetweenSteps;
	actor->soundStep1 = soundStep1;
	actor->soundStep2 = soundStep2;

	actor->animAttack	= attackAnim;
	actor->animWalk		= walkAnim;
	actor->animStand	= standAnim;
	actor->animTaunt	= 0;
	md5Model_clone( &actor->model, model );

	actor->model.pAnim = 0;
	actor->currentAnimSpeed = 1.0f;

	actor->maxHealth = actor->health = maxHealth;
	actor->living = 1;

	actor_changeState( actor, ACTOR_STANDING, ACTOR_DIR_UP );
}

/*
-----------------------------------
	actor_uninit()
		Frees memory
-----------------------------------
*/
void	actor_uninit( actor_t * actor ) {
}

/*
-----------------------------------
	actor_changeState()
-----------------------------------
*/
void	actor_changeState( actor_t * actor, int state, int dir ) {
	labModel_t* L = &gameLocal.world.labModel;
	vsVec3		center;
	int			x, y;

	if ( actor->state == state )
		return;

	// -----------------------------------------------------------------------------------------------------------------------

	switch ( state ) {
	
	// -----------------------------------------------------------------------------------------------------------------------

		case ACTOR_MOVING:
				x = actor->curCell.x;
				y = actor->curCell.y;
				// get destination point
				switch ( dir ) {
					case ACTOR_DIR_UP:		y++;	break;
					case ACTOR_DIR_DOWN:	y--;	break;
					case ACTOR_DIR_LEFT:	x++;	break;
					case ACTOR_DIR_RIGHT:	x--;	break;
				} // end of sub-switch

				if ( ( labMap_getValue( L->map, x, y ) & LM_CORRIDOR ) == 1 ) {
						actor->destCell.x = x;
						actor->destCell.y = y;			
						actor->state = state;
						actor->direction = dir;

						labModel_getCenterOfCell( L, actor->destCell.x, actor->destCell.y, &actor->destination );
						labModel_getCenterOfCell( L, actor->curCell.x,  actor->curCell.y,  &center );

						vec3_equ( &actor->origin, &center );

						//actor->animWalk->frameRate = ( int ) ( actor->animWalk->numFrames / actor->movementTime );
						actor->currentTime = 0.0f;
				}
		break;

		// -----------------------------------------------------------------------------------------------------------------------

		case ACTOR_ATTACKING:
				if ( actor->state != ACTOR_MOVING ) {
					actor->state = state;
					actor->direction = dir;
					//actor->animAttack->frameRate = ( int ) ( actor->animAttack->numFrames / actor->attackTime );
					actor->currentTime = 0.0f;
					
					x = actor->curCell.x;
					y = actor->curCell.y;
					/*
					// get destination point
					switch ( dir ) {
						case ACTOR_DIR_UP:		y++;	break;
						case ACTOR_DIR_DOWN:	y--;	break;
						case ACTOR_DIR_LEFT:	x++;	break;
						case ACTOR_DIR_RIGHT:	x--;	break;
					} // end of sub-switch

					x = min( max( x, 0 ), L->map->width - 1 );
					y = min( max( y, 0 ), L->map->height - 1 );
					*/
					//actor->destCell.x = x;
					//actor->destCell.y = y;	
				}
		break;

		// -----------------------------------------------------------------------------------------------------------------------

		case ACTOR_STANDING:
				actor->state = state;
				actor->direction = dir;
				actor->destCell.x = actor->curCell.x;
				actor->destCell.y = actor->curCell.y;
		break;

		case ACTOR_TAUNTING:
				actor->state = state;
				actor->direction = dir;
				actor->destCell.x = actor->curCell.x;
				actor->destCell.y = actor->curCell.y;
		break;

	} // end of switch
}

void	actor_setCustomAnim( actor_t* actor, md5Anim_t* anim, int dir ) {
	if ( actor->state == ACTOR_CUSTOM_ANIM && actor->animCustom == anim )
		return;

	actor->animCustom = anim;
	actor->state = ACTOR_CUSTOM_ANIM;
	actor->direction = dir;
}

/*
-----------------------------------
	actor_updatePhysics()
-----------------------------------
*/
void	actor_updatePhysics( actor_t * actor ) {
	vsVec3 modelPos, modelRot;
	vsVec3 center, delta;
	int x, y;
	float t;

	// ----------------------------------------------------------------------------------------------------------
	if ( actor->state == ACTOR_STANDING ) {
		if ( actor->model.pAnim != actor->animStand ) {	
			if ( actor->model.pAnim != 0 ) {
				md5Anim_getMovementDelta( &actor->model, actor->model.pAnim, actor->model.currentTime, &delta );
				vec3_equ( &modelPos, &actor->currentPosition );
				vec3_sub( &modelPos, &delta );
			}
			actor->currentAnimSpeed = 1.0f;
			md5Model_setAnimation( &actor->model, actor->animStand, ANIM_PLAY_NOW | ANIM_PLAY_LOOP );
		} 
		else
		vec3_equ( &modelPos, &actor->origin );
	} else
	// ----------------------------------------------------------------------------------------------------------
	if ( actor->state == ACTOR_MOVING ) 
	{
		if ( actor->model.pAnim != actor->animWalk ) { 
			md5Model_setAnimation( &actor->model, actor->animWalk,  ANIM_PLAY_LOOP | ANIM_PLAY_NOW );
			actor->currentAnimSpeed =  actor->model.pAnim->duration / actor->movementTime;
			actor->stepTimeCount = 0.0f;
			actor->curStep = 0;
		}

		actor->currentTime += 1.0f * actor->currentAnimSpeed / gameLocal.fps;
		actor->stepTimeCount += 1.0f / gameLocal.fps;

		if ( actor->stepTimeCount >= actor->stepTime )
		{
			actor->stepTimeCount = 0.0f;
			actor->curStep = 1 - actor->curStep;

			if ( actor->curStep == 0 )
				gameLocal_soundPlay( actor->soundStep1, 0 );
			else
				gameLocal_soundPlay( actor->soundStep2, 0 );
		}

		// if destination reached, stop -------------------------------------------------------------------------
		if ( actor->currentTime >= actor->movementTime )
	    {
			actor->currentTime = actor->movementTime;

			labModel_getCell( &gameLocal.world.labModel, &actor->destination, &x, &y );
			labModel_getCenterOfCell( &gameLocal.world.labModel, x, y, &center );

			vec3_equ( &actor->currentPosition, &center );
			vec3_equ( &actor->origin, &center );

			actor->curCell.x = x;
			actor->curCell.y = y;

			actor_changeState( actor, ACTOR_STANDING, actor->direction );
			//return;
		} 
			// LERP through path of actor movement ------------------------------------------------------------------
			t = actor->currentTime / actor->movementTime;
			actor->currentPosition.x = actor->origin.x * ( 1.f - t ) + actor->destination.x * t;
			actor->currentPosition.y = actor->origin.y * ( 1.f - t ) + actor->destination.y * t;
			actor->currentPosition.z = actor->origin.z * ( 1.f - t ) + actor->destination.z * t;
		
	
			// set model position to current actor position ---------------------------------------------------------
			md5Anim_getMovementDelta( &actor->model, actor->model.pAnim, actor->model.currentTime, &delta );
			vec3_equ( &modelPos, &actor->currentPosition );
			vec3_sub( &modelPos, &delta );	
		
	} else
	// ----------------------------------------------------------------------------------------------------------
	if ( actor->state == ACTOR_ATTACKING ) 
	{
		if ( actor->model.pAnim != actor->animAttack ) { 
			md5Model_setAnimation( &actor->model, actor->animAttack,  ANIM_PLAY_NOW | ANIM_PLAY_LOOP );
			actor->currentAnimSpeed = actor->model.pAnim->duration / actor->attackTime;
		}

		actor->currentTime += 1.0f / gameLocal.fps;

		if ( actor->currentTime >= actor->attackTime ) {
			actor_changeState( actor, ACTOR_STANDING, actor->direction );
			return;
		}

		md5Anim_getMovementDelta( &actor->model, actor->model.pAnim, actor->model.currentTime, &delta );
		vec3_equ( &modelPos, &actor->currentPosition );
		vec3_sub( &modelPos, &delta );
		//vec3_equ( &modelPos, &actor->origin );
	} else
	// ----------------------------------------------------------------------------------------------------------
	if ( actor->state == ACTOR_TAUNTING ) 
	{
		if ( actor->model.pAnim != actor->animTaunt && actor->animTaunt != 0 ) { 
			md5Model_setAnimation( &actor->model, actor->animTaunt,  ANIM_PLAY_NOW | ANIM_PLAY_LOOP );
			actor->currentAnimSpeed = 1.0f;
		}

		actor->currentTime += 1.0f / gameLocal.fps;

		if ( actor->currentTime >= actor->model.pAnim->duration ) {
			actor_changeState( actor, ACTOR_STANDING, actor->direction );
			return;
		}

		md5Anim_getMovementDelta( &actor->model, actor->model.pAnim, actor->model.currentTime, &delta );
		vec3_equ( &modelPos, &actor->currentPosition );
		vec3_sub( &modelPos, &delta );
	} else
	// ----------------------------------------------------------------------------------------------------------
	if ( actor->state == ACTOR_CUSTOM_ANIM ) 
	{
		if ( actor->model.pAnim != actor->animCustom && actor->animCustom != 0 ) { 
			md5Model_setAnimation( &actor->model, actor->animCustom,  ANIM_PLAY_NOW | ANIM_PLAY_LOOP );
			actor->currentAnimSpeed = 1.0f;
		}

		actor->currentTime += 1.0f / gameLocal.fps;

		if ( actor->currentTime >= actor->model.pAnim->duration ) {
			actor_changeState( actor, ACTOR_STANDING, actor->direction );
			return;
		}

		md5Anim_getMovementDelta( &actor->model, actor->model.pAnim, actor->model.currentTime, &delta );
		vec3_equ( &modelPos, &actor->currentPosition );
		vec3_sub( &modelPos, &delta );
	}


	// set model rotation ----------------------------------------------------------------------------------------
	switch ( actor->direction ) {
	case ACTOR_DIR_UP:		vec3_set( &modelRot, 0.0f, 0.0f, 0.0f );
	break;

	case ACTOR_DIR_DOWN:	vec3_set( &modelRot, 0.0f, 0.0f, PI   );
	break;

	case ACTOR_DIR_LEFT:	vec3_set( &modelRot, 0.0f, 0.0f, PI * 0.5f  );
	break;

	case ACTOR_DIR_RIGHT:	vec3_set( &modelRot, 0.0f, 0.0f, -PI * 0.5f  );
	break;
	}

	md5Model_setRotation( &actor->model, &modelRot );
	md5Model_setPosition( &actor->model, &modelPos );
	//md5Model_buildModel( &actor->model, actor->model.joints );
}

/*
-----------------------------------
	actor_update()
		Updates camera view direction
-----------------------------------
*/
void	actor_updateCamera( actor_t* actor ) {
	vsQuat x;
	vsMat3 m3;
	vsMat4 m4;
	vsVec3 viewDir;

	quat_from_rot( &x, DEG_TO_RAD * actor->cameraAngleXDeg, PI, 0.0f );
	quat_to_mat3( &m3, &x );

	// calculate camera position
	viewDir.x = m3.m[ 6 ];
	viewDir.y = m3.m[ 7 ];
	viewDir.z = -m3.m[ 8 ];
	vec3_normalize( &viewDir );

	actor->cameraPosition.x = actor->currentPosition.x - viewDir.x * actor->cameraViewDist;
	actor->cameraPosition.y = actor->currentPosition.y - viewDir.y * actor->cameraViewDist;
	actor->cameraPosition.z = actor->currentPosition.z - viewDir.z * actor->cameraViewDist;

	// update opengl modelview matrix
	glMatrixMode( GL_MODELVIEW );
	mat4_identity( &m4 );
	// translate matrix to cameraPos
	m4.m[ 12 ] = 0.0f;
	m4.m[ 13 ] = -4.0f;
	m4.m[ 14 ] = -actor->cameraViewDist;
	glMultMatrixf( m4.m );

	// quat -> matrix & apply to gl
	mat3_to_mat4( &m4, &m3 );	
	glMultMatrixf( m4.m );


	mat4_identity( &m4 );
	// translate matrix to actorPosition
	m4.m[ 12 ] = -actor->currentPosition.x;
	m4.m[ 13 ] = -actor->currentPosition.y;
	m4.m[ 14 ] = -actor->currentPosition.z;
	glMultMatrixf( m4.m );
}

//------------------------------------------------
//	actor_render()
//		Renders actor model
//------------------------------------------------
void	actor_render( actor_t* actor ) {
	md5Model_renderAnimated( &actor->model, 1.0f / gameLocal.fps * actor->currentAnimSpeed );
}

//------------------------------------------------
//	actor_setDirection()
//------------------------------------------------
void	actor_setDirection( actor_t* actor, int dir ) {
	actor->direction = dir;
}


//------------------------------------------------
//	actor_damage()
//------------------------------------------------
void	actor_damage( actor_t* actor, float damage ) {
	actor->health -= damage;
	if ( actor->health <= 0.0f )
		actor->living = 0;
}

//------------------------------------------------
//	actor_getPossibleDirections()
//------------------------------------------------
char	actor_getPossibleDirections( actor_t* actor, labMap_t* lmap ) {
	char val = 0;

	val = ACTOR_DIR_LEFT | ACTOR_DIR_RIGHT | ACTOR_DIR_UP | ACTOR_DIR_DOWN;

	if ( actor->destCell.x > 0 )
		if ( !( labMap_getValue( lmap, actor->destCell.x - 1, actor->destCell.y ) & LM_CORRIDOR ) )
			val ^= ACTOR_DIR_LEFT;

	if ( actor->destCell.y > 0 )
		if ( !( labMap_getValue( lmap, actor->destCell.x, actor->destCell.y - 1 ) & LM_CORRIDOR ) )
			val ^= ACTOR_DIR_UP;

	if ( actor->destCell.x < lmap->width - 1 )
		if ( !( labMap_getValue( lmap, actor->destCell.x + 1, actor->destCell.y ) & LM_CORRIDOR ) )
			val ^= ACTOR_DIR_RIGHT;

	if ( actor->destCell.y < lmap->height - 1 )
		if ( !( labMap_getValue( lmap, actor->destCell.x, actor->destCell.y + 1 ) & LM_CORRIDOR ) )
			val ^= ACTOR_DIR_DOWN;

	return val;
}

//=========================================================================================================
/*
-----------------------------------
	view_setFOV()
		Helper function to setup the projection matrix with infinite far plane
		Parameters:
			fov:		Field of View in degrees
			nearPlane:	distance of the nearPlane from viewer

	Reference: Eric Lengyel: Projection Matrix Tricks ( presentation at GDC2007 )
		[ url: http://www.terathon.com/gdc07_lengyel.pdf ]
-----------------------------------
*/
void	view_setFOV( float fov_degrees, float nearPlane ) {
	float e = 1.0f / tanf( fov_degrees * 0.5f * DEG_TO_RAD );	
	float a = ( float )( GetSystemMetrics( SM_CYSCREEN ) ) / ( float )( GetSystemMetrics( SM_CXSCREEN ) );	// aspect

	vsMat4 m;

	mat4_set( &m, e,	0.0f,	0.0f,	0.0f,
				  0.f,	e/a,	0.0f,	0.0f,
				  0.0f, 0.0f,	-1.0f,	-2.f*nearPlane,
				  0.0f, 0.0f,	-1.0f,	0.0f );

	glMatrixMode( GL_PROJECTION );
	glLoadMatrixf( m.m );
	glMatrixMode( GL_MODELVIEW );
}
