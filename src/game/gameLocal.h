/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#ifndef __VS_GAME_LOCAL_H__
#define __VS_GAME_LOCAL_H__

#include "actor.h"
#include "world.h"
#include "..\sys\printer.h"
#include "..\sys\shader.h"
#include "player.h"
#include "labyrinth.h"
#include "cinematics.h"
#include "..\sys\sys.h"

#include "..\fmod\fmod.h"
#pragma comment ( lib, "fmodex_vc.lib" )

/*
===============================================
	monster_t
===============================================
*/
typedef struct {
	actor_t			actor;
	int				state;
	coord_t			destination;
} monster_t;


void	monster_think( monster_t* monster, actor_t* actor );
char	monster_canSee( monster_t* monster, actor_t* actor );


/*
===============================================
	intro_t
===============================================
*/
enum {
	INTRO_PLAYING		 = 1,
	INTRO_CINEMA,
	INTRO_CINEMA_MONSTER,
	INTRO_CINEMA_THEEND,
	INTRO_ENDED
};

typedef struct {
	int				state;
	float			time;
	float			startTime;
	float			lastTime;
	unsigned int*	data;
} intro_t;


/*
===============================================
	sound_t
===============================================
*/
typedef struct {
	char			entityName[ 64 ];
	FMOD_SOUND*		handle;
	FMOD_CHANNEL*	channel;
} sound_t;

#define NUM_MONSTERS 1

/*
===============================================

	gameLocal

===============================================
*/
struct {
	player_t		player;
	world_t			world;
	float			time;
	font_t			font1;
	shader_t		shaders[ 3 ];
	float			fps;
	monster_t		monsters[ NUM_MONSTERS ];
	intro_t			intro;
	cc_t			cinematics[ 1 ];

	int				numModels;
	int				numAnims;
	md5Model_t*		models;
	md5Anim_t*		anims;

	//	Sound --------------------------
	FMOD_SYSTEM*	soundSystem;
	int				numSounds;
	sound_t*		sounds;

#ifdef EXTENDED_VERSION
	unsigned int	frameBuffer;
	unsigned int	renderBuffer;
	unsigned int	screenTexture;
	unsigned int	depthTexture;
	unsigned int	normalTexture;
	unsigned int	rnmTexture;
	unsigned int	postProcessShader;
#endif
} gameLocal;


// general -----------------------------------------------------
void		gameLocal_init( void );
void		gameLocal_shutdown( void );
void		gameLocal_newGame( void );
void		gameLocal_processUserInput( unsigned char keys[ 256 ] );
void		gameLocal_updatePhysics( void );
void		gameLocal_render( void );
void		gameLocal_countFPS( void );
int			gameLocal_loadGameData( const char* szFileName );
md5Model_t*	gameLocal_getModel( const char* entityName );
md5Anim_t*	gameLocal_getAnim( const char* entityName );
sound_t*	gameLocal_getSound( const char* entityName );
actor_t*	gameLocal_getActor( const char* entityName );
int			gameLocal_getMonsterAt( int x, int y );

// sound -------------------------------------------------------
void		gameLocal_soundInit( void );
void		gameLocal_soundPlay( char* entityName, char bLooping );
void		gameLocal_soundStop( char* entityName );
void		gameLocal_soundLoad( char* entityName, char* szFileName );
void		gameLocal_soundUninit( void );


// cinematics --------------------------------------------------
void		gameLocal_introPlay( void );
void		gameLocal_introStop( void );
void		gameLocal_introRender( void );
void		gameLocal_outroPlay( char happyEnd );
void		gameLocal_outroStop( void );
void		gameLocal_outroRender( void );


#endif