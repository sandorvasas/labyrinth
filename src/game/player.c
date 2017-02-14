#include "player.h"
#include "gameLocal.h"
#include "names.h"

//---------------------------------------
//	player_init()
//---------------------------------------
void	player_init( void ) {
	actor_init( &gameLocal.player.actor,
		"player",
		gameLocal_getModel( PLAYER_MODEL ),
		gameLocal_getAnim( PLAYER_ANIM_WALK ),
		gameLocal_getAnim( PLAYER_ANIM_IDLE ),
		gameLocal_getAnim( PLAYER_ANIM_ATTACK ),
		PLAYER_SOUND_STEP1,
		PLAYER_SOUND_STEP2,
		0.43f, 1, 1,
		1.2f, 1.0f, 100.0f );
	gameLocal.player.actor.animTaunt = gameLocal_getAnim( PLAYER_ANIM_ANGRY );
	

	/*actor_init( &gameLocal.player.actor,
		"player",
		gameLocal_getModel( MONSTER_MODEL ),
		gameLocal_getAnim( MONSTER_ANIM_WALK ),
		gameLocal_getAnim( MONSTER_ANIM_IDLE ),
		gameLocal_getAnim( MONSTER_ANIM_ATTACK ),
		MONSTER_SOUND_STEP1,
		MONSTER_SOUND_STEP2, 0.4f,
		1,1,
		1.2f, 3.0f, 500.0f );
	gameLocal.player.actor.animTaunt = gameLocal_getAnim( MONSTER_ANIM_ROAR );
	*/

	md5Model_setShader( &gameLocal.player.actor.model, &gameLocal.shaders[ 1 ] );
	
	// make the model face the camera ( LEFT )
	if ( gameLocal.world.lmap.data[ 1 * gameLocal.world.lmap.height + 2 ] != 0 ) {
		actor_setDirection( &gameLocal.player.actor, ACTOR_DIR_LEFT );
	}
}


//---------------------------------------
//	player_destroy()
//---------------------------------------
void	player_destroy( void ) {
	actor_uninit( &gameLocal.player.actor );
}


//---------------------------------------
//	player_placeMine()
//---------------------------------------
void	player_placeMine( coord_t* coord ) {
	
}


//---------------------------------------
//	player_updatePhysics()
//---------------------------------------
void	player_updatePhysics( void ) {
	actor_updatePhysics( &gameLocal.player.actor );
}


//---------------------------------------
//	player_render()
//---------------------------------------
void	player_render( void ) {
	actor_render( &gameLocal.player.actor );
}
