/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#include "..\OpenGL\GLexp.h"
#include "gameLocal.h"
#include "labyrinth.h"
#include "..\sys\Texture.h"
#include "..\sys\shader.h"
#include <malloc.h>
#include <math.h>
#include <time.h>
#include "names.h"
#include "..\main.h"


//-------------------------------
//	monster_think()
//		sets moveDir of monster 
//-------------------------------
void	monster_think( monster_t* monster, actor_t* actor ) {
	int		i, r;
	char	coded_dirs;
	coord_t	dirs[ 4 ];
	char	numDir;

	//dirs[ 0 ].x = dirs[ 0 ].y = 0;
	monster_canSee( monster, actor, &dirs[ 0 ] );
	//font_printQ( gameLocal.font1, -0.9f, -0.55f, 0, "dir %d %d", dirs[ 0 ].x, dirs[ 0 ].y );

	// if we see the player, follow him
	if ( dirs[ 0 ].x || dirs[ 0 ].y ) {
		monster->actor.moveDir.x = dirs[ 0 ].x;
		monster->actor.moveDir.y = dirs[ 0 ].y;
		//font_printQ( gameLocal.font1, -0.9f, -0.60f, 0, "latja" );
	} else {
		//monster->actor.moveDir.x = 0;
		//monster->actor.moveDir.y = 0;
		//font_printQ( gameLocal.font1, -0.9f, -0.60f, 0, "nem latja" );
		
		coded_dirs = actor_getPossibleDirections( &monster->actor, gameLocal.world.labModel.map );

		//font_printQ( gameLocal.font1, -0.9f, 0.00f, 0, "up: %d",	(coded_dirs & ACTOR_DIR_UP)? 1 : 0 );
		//font_printQ( gameLocal.font1, -0.9f, 0.05f, 0, "down: %d",	(coded_dirs & ACTOR_DIR_DOWN)? 1 : 0 );
		//font_printQ( gameLocal.font1, -0.9f, 0.10f, 0, "left: %d",	(coded_dirs & ACTOR_DIR_LEFT)? 1 : 0 );
		//font_printQ( gameLocal.font1, -0.9f, 0.15f, 0, "right: %d",	(coded_dirs & ACTOR_DIR_RIGHT)? 1 : 0 );

		numDir = 0;

		if ( coded_dirs & ACTOR_DIR_LEFT )	
			{ dirs[ numDir ].x = -1;	dirs[ numDir++ ].y =  0; }
		if ( coded_dirs & ACTOR_DIR_RIGHT ) 		
			{ dirs[ numDir ].x =  1;	dirs[ numDir++ ].y =  0; }
		if ( coded_dirs & ACTOR_DIR_UP )	
			{ dirs[ numDir ].x =  0;	dirs[ numDir++ ].y = -1; }
		if ( coded_dirs & ACTOR_DIR_DOWN )	
			{ dirs[ numDir ].x =  0;	dirs[ numDir++ ].y =  1; }

	//	font_printQ( gameLocal.font1, -0.9f, -0.05f, 0, "numDir: %d", numDir );
		//font_printQ( gameLocal.font1, -0.9f, -0.10f, 0, "monster->moveDir: %d %d", monster->actor.moveDir.x, monster->actor.moveDir.y );


		// trivial case
		if ( numDir == 1 ) {
			monster->actor.moveDir.x = dirs[ 0 ].x;
			monster->actor.moveDir.y = dirs[ 0 ].y;
			return;
		} else

		if ( numDir == 2 ) {
			// horizontal corridor - - - - - - - - - - - - - - - - - - - - 
			if ( ( ( dirs[ 0 ].x == -1 && dirs[ 1 ].x ==  1 )
			  || ( dirs[ 0 ].x ==  1 && dirs[ 1 ].x == -1 ) )
			  && monster->actor.moveDir.x != 0 )
					return;

			// vertical corridor - - - - - - - - - - - - - - - - - - - - -
			if ( ( ( dirs[ 0 ].y == -1 && dirs[ 1 ].y ==  1 )
			  || ( dirs[ 0 ].y ==  1 && dirs[ 1 ].y == -1 ) )
			  && monster->actor.moveDir.y != 0 )
					return;
					

			// if we are standing, move some random way 		
			r = rand() % 2;
			monster->actor.moveDir.x = dirs[ r ].x;
			monster->actor.moveDir.y = dirs[ r ].y;
		} else

		if ( numDir == 3 ) {
			// horizontal corridor - - - - - - - - - - - - - - - - - - - - 
			if ( ( ( dirs[ 0 ].x ==  1 || dirs[ 1 ].x ==  1 || dirs[ 2 ].x ==  1 )
			  && ( dirs[ 0 ].x == -1 || dirs[ 1 ].x == -1 || dirs[ 2 ].x == -1 ) )
			  && monster->actor.moveDir.x != 0 )
					return;

			// vertical corridor - - - - - - - - - - - - - - - - - - - - -
			if ( ( ( dirs[ 0 ].y ==  1 || dirs[ 1 ].y ==  1 || dirs[ 2 ].y ==  1 )
			  && ( dirs[ 0 ].y == -1 || dirs[ 1 ].y == -1 || dirs[ 2 ].y == -1 ) )
			  && monster->actor.moveDir.y != 0 )
					return;
					

			// if we are standing, move some random way 	
			r = rand() % 3;
			monster->actor.moveDir.x = dirs[ r ].x;
			monster->actor.moveDir.y = dirs[ r ].y;
		} else
			
		if ( numDir == 4 ) {
			// if we are standing, move some random way
			r = rand() % 4;
			monster->actor.moveDir.x = dirs[ r ].x;
			monster->actor.moveDir.y = dirs[ r ].y;
		} else 

		if ( numDir == 0 )
		// there are walls around us
		{
			monster->actor.moveDir.x = 0;
			monster->actor.moveDir.y = 0;
		}
	}
}


//-------------------------------
//	monster_canSee()
//-------------------------------
void	monster_canSee( monster_t* monster, actor_t* actor, coord_t* newDir ) {
	coord_t	a, b;
	int i;

	newDir->x = newDir->y = 0;

	a.x = monster->actor.curCell.x;
	a.y = monster->actor.curCell.y;

	b.x = actor->curCell.x;
	b.y = actor->curCell.y;

	//font_printQ( gameLocal.font1, -0.9f, -0.75f, 0, "monster: %d %d", a.x, a.y );
	//font_printQ( gameLocal.font1, -0.9f, -0.70f, 0, "player: %d %d", b.x, b.y );

	if ( a.x != b.x && a.y != b.y ) 
		return; // they surely cannot see each other

	if ( a.y == b.y && b.x < a.x &&  monster->actor.direction != ACTOR_DIR_LEFT ) {
		for ( i = b.x; i < a.x; i++ )
			if ( ( labMap_getValue( gameLocal.world.labModel.map, i, a.y ) & LM_CORRIDOR ) == 0 )
				return;

		newDir->x = 1;
		newDir->y = 0;
	} else
	if ( a.y == b.y && a.x < b.x &&  monster->actor.direction != ACTOR_DIR_RIGHT ) {
		for ( i = b.x; i > a.x; i-- )
			if ( ( labMap_getValue( gameLocal.world.labModel.map, i, a.y ) & LM_CORRIDOR ) == 0 )
				return;

		newDir->x = -1;
		newDir->y = 0;
	} else
	if ( a.x == b.x && b.y < a.y && monster->actor.direction != ACTOR_DIR_UP ) {
		for ( i = b.y; i < a.y; i++ )
			if ( ( labMap_getValue( gameLocal.world.labModel.map, a.x, i ) & LM_CORRIDOR ) == 0 )
				return;

		newDir->x = 0;
		newDir->y = -1;
	} else
	if ( a.x == b.x && a.y < b.y &&  monster->actor.direction != ACTOR_DIR_DOWN ) {
		for ( i = b.y; i > a.y; i-- )
			if ( ( labMap_getValue( gameLocal.world.labModel.map, a.x, i ) & LM_CORRIDOR ) == 0 )
				return;

		newDir->x = 0;
		newDir->y = 1;
	}
}




// ========================================================================================================================================




//-------------------------------
//	gameLocal_init()
//		Initializes game
//-------------------------------
void	gameLocal_init( void ) {
	gameLocal.font1 = font_create( "Arial Narrow", 30 );
	gameLocal.fps = 60;

	gameLocal_soundInit();
	gameLocal_loadGameData( "data/gamedata.txt" );

#ifdef EXTENDED_VERSION
	// elõször csinálunk egy üres texturát, amire majd renderelünk 
	glGenTextures( 1, &gameLocal.screenTexture );
	glBindTexture( GL_TEXTURE_2D, gameLocal.screenTexture );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 0, GL_RGBA, GL_FLOAT, 0 );

	// depth values
	glGenTextures( 1, &gameLocal.depthTexture );
	glBindTexture( GL_TEXTURE_2D, gameLocal.depthTexture );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0 );

	// normal vector-texture
	glGenTextures( 1, &gameLocal.normalTexture );
	glBindTexture( GL_TEXTURE_2D, gameLocal.normalTexture );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 0, GL_RGBA, GL_FLOAT, 0 );

	// generáljuk a framebuffer object-et, csatoljuk hozzá a texturát
	glGenFramebuffers( 1, &gameLocal.frameBuffer );
	glBindFramebuffer( GL_FRAMEBUFFER, gameLocal.frameBuffer );
	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, gameLocal.depthTexture, 0 );
	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gameLocal.screenTexture, 0 );
	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gameLocal.normalTexture, 0 );

	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
	glBindTexture( GL_TEXTURE_2D, 0 );

	gameLocal.rnmTexture = texture_load_bmp( "data/textures/rnm.bmp" );
	shader_new( &gameLocal.postProcessShader, "data/shaders/postprocess.txt" );

	shader_use( gameLocal.postProcessShader );
	glUniform1i( glGetUniformLocation( gameLocal.postProcessShader, "screenTexture" ), 0 );
	glUniform1i( glGetUniformLocation( gameLocal.postProcessShader, "depthTexture" ), 1 );
	glUniform1i( glGetUniformLocation( gameLocal.postProcessShader, "normalTexture" ), 2 );
	glUniform1i( glGetUniformLocation( gameLocal.postProcessShader, "rnmTexture" ), 3 );
	shader_use( 0 );
#endif
}


//-------------------------------
//	gameLocal_shutdown()
//		shuts down game
//-------------------------------
void	gameLocal_shutdown( void ) {
	int i;
	player_destroy();

	for ( i = 0; i < gameLocal.numModels; i++ )
		md5Model_destroy( &gameLocal.models[ i ] );
		
	for ( i = 0; i < gameLocal.numAnims; i++ )
		md5Anim_destroy( &gameLocal.anims[ i ] );

	free( gameLocal.models );
	free( gameLocal.anims );

	shader_delete( gameLocal.shaders[ 0 ] );

	gameLocal_soundStop( "bgmusic" );
	gameLocal_soundUninit();
}


//-------------------------------
//	gameLocal_newGame()
//		starts a new game
//-------------------------------
void	gameLocal_newGame( void ) {
	vsVec3 R;
	coord_t A, B;
	int i, j;

	gameLocal.time = 0.0f;

	shader_new( &gameLocal.shaders[ 0 ], "data/shaders/labyrinthModel.txt" );
	shader_new( &gameLocal.shaders[ 1 ], "data/shaders/def.txt" );
	shader_new( &gameLocal.shaders[ 2 ], "data/shaders/intro.txt" );

	shader_use( gameLocal.shaders[ 1 ] );
#ifdef EXTENDED_VERSION
	glUniform1i( glGetUniformLocation( gameLocal.shaders[ 1 ], "version" ), 11 );
#else
	glUniform1i( glGetUniformLocation( gameLocal.shaders[ 1 ], "version" ), 10 );
#endif
	shader_use( 0 );

	world_init();
	player_init();

	/*actor_init( &gameLocal.monsters[ 0 ].actor, 
		"monster",
		gameLocal_getModel( MONSTER_MODEL ),
		gameLocal_getAnim( MONSTER_ANIM_WALK ),
		gameLocal_getAnim( MONSTER_ANIM_IDLE ),
		gameLocal_getAnim( MONSTER_ANIM_ATTACK ),
		MONSTER_SOUND_STEP1,
		MONSTER_SOUND_STEP2, 0.4f,

		1, 4, 
		//gameLocal.world.labModel.map->monsterLoc.x - 30000,
		//gameLocal.world.labModel.map->monsterLoc.y - 30000,
		1.0f, 3.0f, 500.0f );
		*/
	

	srand( ( unsigned int )time( 0 ) );
	for ( i = 0; i < NUM_MONSTERS; i++ ) {	
		do {
			j = rand() % ( gameLocal.world.labModel.map->width * gameLocal.world.labModel.map->height );
		} while ( ( gameLocal.world.lmap.data[ j ] & LM_CORRIDOR ) == 0 );

		A.y = j / gameLocal.world.labModel.map->width;
		A.x = j % A.y;
		
		actor_init( &gameLocal.monsters[ i ].actor, 
		"monster",
		gameLocal_getModel( MONSTER_MODEL ),
		gameLocal_getAnim( MONSTER_ANIM_WALK ),
		gameLocal_getAnim( MONSTER_ANIM_IDLE ),
		gameLocal_getAnim( MONSTER_ANIM_ATTACK ),
		MONSTER_SOUND_STEP1,
		MONSTER_SOUND_STEP2, 0.4f,
		A.x, A.y,
		1.2f, 3.0f, 500.0f );
		gameLocal.monsters[ i ].actor.animTaunt = gameLocal_getAnim( MONSTER_ANIM_ROAR );

	}

	gameLocal_soundPlay( "bgmusic", 1 );
	gameLocal_introPlay();
}


//-------------------------------
//	gameLocal_processUserInput()
//	
//-------------------------------
void	gameLocal_processUserInput( unsigned char keys[ 256 ] ) {
	int state = 0;
	int	dir = gameLocal.player.actor.direction;

	if ( gameLocal.intro.state != INTRO_ENDED )
		return;

	if ( keys[ VK_DOWN ]	)  { state = ACTOR_MOVING;	dir = ACTOR_DIR_DOWN; }
	if ( keys[ VK_UP ]		)  { state = ACTOR_MOVING;	dir = ACTOR_DIR_UP;	  }
	if ( keys[ VK_LEFT ]	)  { state = ACTOR_MOVING;	dir = ACTOR_DIR_LEFT; }
	if ( keys[ VK_RIGHT ]	)  { state = ACTOR_MOVING;	dir = ACTOR_DIR_RIGHT;}

	//if ( keys[ VK_CONTROL ] ) {
		//state = ACTOR_ATTACKING;
		//keys[ VK_CONTROL ] = 0;
	//}
	
	if ( state )
		actor_changeState( &gameLocal.player.actor, state, dir );

/*	state = 0;
	dir = gameLocal.monsters[ 0 ].actor.direction;
	if ( keys[ 'S' ]	)  { state = ACTOR_MOVING;	dir = ACTOR_DIR_DOWN; }
	if ( keys[ 'W' ]	)  { state = ACTOR_MOVING;	dir = ACTOR_DIR_UP;	  }
	if ( keys[ 'A' ]	)  { state = ACTOR_MOVING;	dir = ACTOR_DIR_LEFT; }
	if ( keys[ 'D' ]	)  { state = ACTOR_MOVING;	dir = ACTOR_DIR_RIGHT;}

	//if ( keys[ VK_CONTROL ] ) {
		//state = ACTOR_ATTACKING;
		//keys[ VK_CONTROL ] = 0;
	//}
	
	if ( state )
		actor_changeState( &gameLocal.monsters[ 0 ].actor, state, dir );
		*/
	// DEBUG ONLY------------------------------------------------
#ifdef DEBUG_MODE
	if ( keys[ 'T' ] ) {
		gameLocal.player.actor.cameraViewDist = 80.0f;
		gameLocal.player.actor.movementTime = 0.3f;
		//gameLocal.player.actor.cameraAngleXDeg = 90.0f;
	}
	else {
		gameLocal.player.actor.cameraViewDist = 40.0f;
		gameLocal.player.actor.movementTime = 1.0f;
	}
#endif
}


//-------------------------------
//	gameLocal_updatePhysics()
//	
//-------------------------------
void	gameLocal_updatePhysics( void ) {
	static int	counter = 0;
	int			r,  i, x, y;
	char		newPosOK;
	int			state, dir;

	if ( gameLocal.intro.state == INTRO_ENDED ) {
		gameLocal.time += ( 1.0f / gameLocal.fps );

	
		if (  gameLocal.player.actor.curCell.x == gameLocal.world.labModel.map->exitLoc.x 
		   && gameLocal.player.actor.curCell.y == gameLocal.world.labModel.map->exitLoc.y 
		  )
		{
			gameLocal_outroPlay( 1 );
			//return;
		}

		if ( gameLocal.player.actor.curCell.x == gameLocal.monsters[ 0 ].actor.curCell.x
		  && gameLocal.player.actor.curCell.y == gameLocal.monsters[ 0 ].actor.curCell.y ) 
		{
			gameLocal_outroPlay( 0 );
		}
	}

	if ( gameLocal.intro.state != INTRO_CINEMA_THEEND ) {
		world_updatePhysics();
		player_updatePhysics();

		for ( i = 0; i < NUM_MONSTERS; i++ ) 
		{
			if ( gameLocal.intro.state == INTRO_ENDED )
				monster_think( &gameLocal.monsters[ i ], &gameLocal.player.actor );
		
			state = ACTOR_STANDING;
			dir = gameLocal.monsters[ i ].actor.direction;

			if ( gameLocal.monsters[ i ].actor.moveDir.y == -1	)  { state = ACTOR_MOVING;	dir = ACTOR_DIR_DOWN; }
			if ( gameLocal.monsters[ i ].actor.moveDir.y ==  1	)  { state = ACTOR_MOVING;	dir = ACTOR_DIR_UP;	  }
			if ( gameLocal.monsters[ i ].actor.moveDir.x == -1	)  { state = ACTOR_MOVING;	dir = ACTOR_DIR_LEFT; }
			if ( gameLocal.monsters[ i ].actor.moveDir.x ==  1	)  { state = ACTOR_MOVING;	dir = ACTOR_DIR_RIGHT;}
			/*else
			if ( gameLocal.monsters[ i ].actor.moveDir.x == 0 &&
				 gameLocal.monsters[ i ].actor.moveDir.y == 0 )	   { state = ACTOR_STANDI
	*/
			//if ( state )
			actor_changeState( &gameLocal.monsters[ i ].actor, state, dir );
			actor_updatePhysics( &gameLocal.monsters[ i ].actor );
		}
	}

	/*if ( gameLocal.player.actor.curCell.x == gameLocal.world.labModel.map->monsterLoc.x 
	  && gameLocal.player.actor.curCell.y == gameLocal.world.labModel.map->monsterLoc.y ) {
		  gameLocal.intro.state = INTRO_CINEMA_MONSTER;

		  switch ( gameLocal.world.labModel.map->fourth ) {
			  case FOURTH_LOWER_LEFT:	cinematics_loadFromFile( &gameLocal.cinematics[ 1 ], "data/scripts/ocinema2_lowerleft.txt" );	break;
			  case FOURTH_LOWER_RIGHT:	cinematics_loadFromFile( &gameLocal.cinematics[ 1 ], "data/scripts/ocinema2_lowerright.txt" );	break;
			  case FOURTH_UPPER_RIGHT:	cinematics_loadFromFile( &gameLocal.cinematics[ 1 ], "data/scripts/ocinema2_upperright.txt" );
		  }
		  cinematics_play( &gameLocal.cinematics[ 1 ] );
	}
	*/


	/*if ( counter  > 300 ) {
		for ( i = 0; i < NUM_MONSTERS; i++ ) {
			newPosOK = 0;
			while( !newPosOK ) {
				r = rand() % 4;

				x = gameLocal.monsters[ i ].actor.curCell.x;
				y = gameLocal.monsters[ i ].actor.curCell.y;

				switch( r ) {
					case 0 : x++;	break;
					case 1 : x--;	break;
					case 2 : y++;	break;
					case 3 : y--;	break;
				}

				if ( labMap_getValue( gameLocal.world.labModel.map, x, y ) == 1 
					&& gameLocal_getMonsterAt( x, y ) == -1 ) 
							newPosOK = 1;
			}

			switch( r ) {
				case 0 : actor_changeState( &gameLocal.monsters[ i ].actor, ACTOR_MOVING, ACTOR_DIR_LEFT );
				break;
				case 1 : actor_changeState( &gameLocal.monsters[ i ].actor, ACTOR_MOVING, ACTOR_DIR_RIGHT );
				break;
				case 2 : actor_changeState( &gameLocal.monsters[ i ].actor, ACTOR_MOVING, ACTOR_DIR_UP );
				break;
				case 3 : actor_changeState( &gameLocal.monsters[ i ].actor, ACTOR_MOVING, ACTOR_DIR_DOWN );
				break;
			}

			if ( gameLocal.monsters[ i ].actor.curCell.x == gameLocal.player.actor.curCell.x + 1 )
				actor_changeState( &gameLocal.monsters[ i ].actor, ACTOR_ATTACKING, ACTOR_DIR_RIGHT );

			if ( gameLocal.monsters[ i ].actor.curCell.x == gameLocal.player.actor.curCell.x - 1 )
				actor_changeState( &gameLocal.monsters[ i ].actor, ACTOR_ATTACKING, ACTOR_DIR_LEFT );

			if ( gameLocal.monsters[ i ].actor.curCell.y == gameLocal.player.actor.curCell.y + 1 )
				actor_changeState( &gameLocal.monsters[ i ].actor, ACTOR_ATTACKING, ACTOR_DIR_UP );

			if ( gameLocal.monsters[ i ].actor.curCell.y == gameLocal.player.actor.curCell.y - 1 )
				actor_changeState( &gameLocal.monsters[ i ].actor, ACTOR_ATTACKING, ACTOR_DIR_DOWN );


			counter = 0;
		} // foreach monster
	} // COUNTER > 300	*/
}


//-------------------------------
//	gameLocal_render()
//		Renders current game scene
//-------------------------------
void	gameLocal_render( void ) {
	float	x, z;	
	vsVec3	col;
	int		i;

#ifdef EXTENDED_VERSION
	static const GLenum drawbufs[] = { 
		GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1 
	};
#endif

	// print stuff ------------------------------------------------------------------------------		
	vec3_set( &col, 122.f/255.f, 98.f/255.f, 75.f/255.f );

	font_print( gameLocal.font1, -0.97f, -0.90f, &col, "FPS: %d", ( int ) gameLocal.fps );
	if ( gameLocal.intro.state == INTRO_ENDED )
		font_print( gameLocal.font1, 0.90f, -0.90f, &col, "%d:%d", ( int ) ( gameLocal.time / 60.f ), ( int ) ( gameLocal.time ) % 60 );
	font_printQueue();


	switch ( gameLocal.intro.state ) {
		case INTRO_PLAYING:
			gameLocal_introRender();
			gameLocal_countFPS();
			return;
		break;
		case INTRO_CINEMA_THEEND:
			gameLocal_outroRender();
			gameLocal_countFPS();
			return;
		break;

		case INTRO_CINEMA: 
			cinematics_update( &gameLocal.cinematics[ 0 ] );
			if ( gameLocal.cinematics[ 0 ].state == CINEMA_ENDED ) {
				gameLocal.intro.state = INTRO_ENDED;
				gameLocal.time = 0.0f;
			}
		break;

		case INTRO_CINEMA_MONSTER:
			cinematics_update( &gameLocal.cinematics[ 1 ] );
			if ( gameLocal.cinematics[ 1 ].state == CINEMA_ENDED )
				gameLocal.intro.state = INTRO_ENDED;
		break;
		default:
			actor_updateCamera( &gameLocal.player.actor );
	}

#ifdef EXTENDED_VERSION
	glBindTexture( GL_TEXTURE_2D, 0 );
	glBindFramebuffer( GL_FRAMEBUFFER, gameLocal.frameBuffer );
	glDrawBuffers( 2, drawbufs );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
#endif

	// uniform shader variables -----------------------------------------------------------------
	for ( i = 0; i < 2; i++ ) {
		shader_use( gameLocal.shaders[ i ] );
		glUniform1f( glGetUniformLocation( gameLocal.shaders[ i ] , "time" ), gameLocal.time );

		glUniform3fv( glGetUniformLocation( gameLocal.shaders[ i ], "lightPos0" ), 3, ( const float * )&gameLocal.world.lights[ 0 ] );

		if ( gameLocal.intro.state == INTRO_CINEMA )
			glUniform3fv( glGetUniformLocation( gameLocal.shaders[ i ], "viewPos" ), 3, ( const float * )&gameLocal.cinematics[ 0 ].currentPos );
		else
		if ( gameLocal.intro.state == INTRO_CINEMA_MONSTER )
			glUniform3fv( glGetUniformLocation( gameLocal.shaders[ i ], "viewPos" ), 3, ( const float * )&gameLocal.cinematics[ 1 ].currentPos );
		else
			glUniform3fv( glGetUniformLocation( gameLocal.shaders[ i ], "viewPos" ), 3, ( const float * )&gameLocal.player.actor.cameraPosition );
	}
	shader_use( 0 );

	world_render();	
	player_render();
	
	for ( i = 0; i < NUM_MONSTERS; i++ )
		actor_render( &gameLocal.monsters[ i ].actor );

	//gameLocal.player.actor.model.diffuseMap = gameLocal.screenTexture;

#ifdef EXTENDED_VERSION
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
	glBindTexture( GL_TEXTURE_2D, 0 );

	glLoadIdentity();

	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glOrtho( -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f );
	glPushMatrix();

	glColor4f( 1.f, 1.f, 1.f, 1.f );

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, gameLocal.screenTexture );

	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D, gameLocal.depthTexture );

	glActiveTexture( GL_TEXTURE2 );
	glBindTexture( GL_TEXTURE_2D, gameLocal.normalTexture );

	glActiveTexture( GL_TEXTURE3 );
	glBindTexture( GL_TEXTURE_2D, gameLocal.rnmTexture );

	shader_use( gameLocal.postProcessShader );
	glBegin( GL_QUADS );
		glMultiTexCoord2f( GL_TEXTURE0, 0.0f, 0.0f );		glVertex3f( -1.0f,  1.0f, -0.5f );
		glMultiTexCoord2f( GL_TEXTURE0, 1.0f, 0.0f );		glVertex3f(  1.0f,  1.0f, -0.5f );
		glMultiTexCoord2f( GL_TEXTURE0, 1.0f, 1.0f );		glVertex3f(  1.0f, -1.0f, -0.5f );
		glMultiTexCoord2f( GL_TEXTURE0, 0.0f, 1.0f );		glVertex3f( -1.0f, -1.0f, -0.5f );
	glEnd();
	shader_use( 0 );

	for ( i = 0; i < 4; i++ ) {
		glActiveTexture( GL_TEXTURE0 + i );
		glBindTexture( GL_TEXTURE_2D, 0 );
	}

	glPopMatrix();
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
#endif
	
	gameLocal_countFPS();
}


//-------------------------------
//	gameLocal_countFPS()
//		Called in gameLocal_render(), this function counts frames and calculates FPS
//-------------------------------
void	gameLocal_countFPS( void ) {
	static float fps_count = 60.0f;
	static long	 lastTime = 0;
	long		 curTime = GetTickCount();

	fps_count++;

	if ( curTime - lastTime >= 1000 ) {
		gameLocal.fps = ( float ) fps_count;
		lastTime = curTime;
		fps_count = 0.0f;
	}
}


//-------------------------------
//	gameLocal_loadGameData()
//-------------------------------
int	gameLocal_loadGameData( const char* szFileName ) {
	FILE * f;
	char line[ 128 ];
	int i;
	vsVec3 r1, r2;
	
	f = fopen( szFileName, "r" );

	if ( !f ) 
		return -1;

	while ( !feof( f ) ) {
		fgets( line, 128, f );

		if ( strstr( line, "numModels" ) ) {
			sscanf( line, "numModels %d", &gameLocal.numModels );
			gameLocal.models = ( md5Model_t ** ) malloc( sizeof( md5Model_t ) * gameLocal.numModels ); 
		} else

		if ( strstr( line, "numAnims" ) ) {
			sscanf( line, "numAnims %d", &gameLocal.numAnims );
			gameLocal.anims = ( md5Anim_t * ) malloc( sizeof( md5Anim_t ) * gameLocal.numAnims ); 
		} else

		if ( strstr( line, "numSounds" ) ) {
			sscanf( line, "numSounds %d", &gameLocal.numSounds );
			gameLocal.sounds = ( sound_t * ) malloc( sizeof( sound_t ) * gameLocal.numSounds ); 
		} else

		if ( strstr( line, "models" ) ) {

			for ( i = 0; i < gameLocal.numModels; i++ ) {
			//	gameLocal.models[ i ] = ( md5Model_t* ) malloc( sizeof( md5Model_t ) * gameLocal.numModels );
				fscanf( f," %s %s", 
					gameLocal.models[ i ].entityName, 
					line );
				md5Model_load( &gameLocal.models[ i ], line );
			}			
		} else

		if ( strstr( line, "anims" ) ) {

			for ( i = 0; i < gameLocal.numAnims; i++ ) {
				fscanf( f," %s %s", 
					gameLocal.anims[ i ].entityName, 
					line );
				md5Anim_load( &gameLocal.anims[ i ], line );
			}
		} else

		if ( strstr( line, "sounds" ) ) {

			for ( i = 0; i < gameLocal.numSounds; i++ ) {
				fscanf( f," %s %s", 
					gameLocal.sounds[ i ].entityName, 
					line );
				gameLocal_soundLoad( gameLocal.sounds[ i ].entityName, line );
			}
		}
	}

	fclose( f );
	return 0;
}

//-------------------------------
//	gameLocal_getModel()
//-------------------------------
md5Model_t*	gameLocal_getModel( const char* entityName ) {
	int i;
	md5Model_t* sample = ( md5Model_t* ) 0;

	for ( i = 0; i < gameLocal.numModels; i++ ) 
		if ( strcmp( entityName, gameLocal.models[ i ].entityName ) == 0 ) {
			sample = &gameLocal.models[ i ];
			return sample;
		}

	if ( !sample )
		return sample;
/*
	gameLocal.models = ( md5Model_t** ) realloc( gameLocal.models, ( ++gameLocal.numModels ) * sizeof( md5Model_t* ) );
	gameLocal.models[ gameLocal.numModels - 1 ] = md5Model_clone( sample );

	return  gameLocal.models[ gameLocal.numModels - 1 ];
*/}

//-------------------------------
//	gameLocal_getAnim()
//-------------------------------
md5Anim_t*	gameLocal_getAnim( const char* entityName ) {
	int i;

	for ( i = 0; i < gameLocal.numAnims; i++ ) 
		if ( strcmp( entityName, gameLocal.anims[ i ].entityName ) == 0 )
			return &gameLocal.anims[ i ];

	return ( md5Anim_t* ) 0;
}


//-------------------------------
//	gameLocal_getSound()
//-------------------------------
sound_t*	gameLocal_getSound( const char* entityName ) {
	int i;

	for ( i = 0; i < gameLocal.numSounds; i++ ) 
		if ( strcmp( entityName, gameLocal.sounds[ i ].entityName ) == 0 )
			return &gameLocal.sounds[ i ];

	return ( sound_t* ) 0;
}


//-------------------------------
//	gameLocal_getActor()
//-------------------------------
actor_t*	gameLocal_getActor( const char* entityName ) {
	int i;

	if ( strcmp( entityName, gameLocal.player.actor.entityName ) == 0 )
		return &gameLocal.player.actor;

	for ( i = 0; i < NUM_MONSTERS; i++ ) 
		if ( strcmp( entityName, gameLocal.monsters[ i ].actor.entityName ) == 0 )
			return &gameLocal.monsters[ i ].actor;

	return ( actor_t* ) 0;
}

//-------------------------------
//	gameLocal_getMonsterAt()
//-------------------------------
int	gameLocal_getMonsterAt( int x, int y ) {
	int i;

	for ( i = 0; i < NUM_MONSTERS; i++ )
		if ( gameLocal.monsters[ i ].actor.curCell.x == x && gameLocal.monsters[ i ].actor.curCell.y == y )
			return i;

	return ( -1 );
}


//-----------------------------------------------------------------------------
//		Sound ( FMOD )
//-----------------------------------------------------------------------------
//-------------------------------
//	gameLocal_soundInit
//-------------------------------
void	gameLocal_soundInit( void ) {
	FMOD_System_Create( &gameLocal.soundSystem );
	FMOD_System_Init( gameLocal.soundSystem, 32, FMOD_INIT_NORMAL, 0 );
}


//-------------------------------
//	gameLocal_soundLoad()
//-------------------------------
void	gameLocal_soundLoad( char* entityName, char* szFileName ) {
	static int channel = 0;
	FMOD_System_CreateStream( gameLocal.soundSystem, szFileName, FMOD_HARDWARE | FMOD_2D, 0, &gameLocal_getSound( entityName )->handle );
	gameLocal_getSound( entityName )->channel = ( FMOD_CHANNEL* )channel++;
}

//-------------------------------
//	gameLocal_soundStartMusic
//-------------------------------
void	gameLocal_soundPlay( char* entityName, char bLooping ) {
	int i;

	for ( i = 0; i < gameLocal.numSounds; i++ ) 
		if ( strcmp( gameLocal.sounds[ i ].entityName, entityName ) == 0 ) {
			FMOD_Sound_SetMode( gameLocal.sounds[ i ].handle, FMOD_LOOP_OFF + bLooping );
			FMOD_System_PlaySound( gameLocal.soundSystem, FMOD_CHANNEL_FREE, gameLocal.sounds[ i ].handle, 0, &gameLocal.sounds[ i ].channel );
			return;
		}
}

//-------------------------------
//	gameLocal_soundStopMusic
//-------------------------------
void	gameLocal_soundStop( char* entityName ) {
	int i;

	for ( i = 0; i < gameLocal.numSounds; i++ ) 
		if ( strcmp( gameLocal.sounds[ i ].entityName, entityName ) == 0 ) {
			FMOD_Sound_Release( gameLocal.sounds[ i ].handle );
			return;
		}
	
}

//-------------------------------
//	gameLocal_soundUninit
//-------------------------------
void	gameLocal_soundUninit( void ) {
	FMOD_System_Close( gameLocal.soundSystem );
	FMOD_System_Release( gameLocal.soundSystem );
}

//-------------------------------
//	gameLocal_introPlay
//-------------------------------
void	gameLocal_introPlay( void ) {

	gameLocal.intro.state = INTRO_PLAYING;

	gameLocal.intro.time = 0.0f;
	gameLocal.intro.startTime = 
	gameLocal.intro.lastTime  = ( float ) GetTickCount() * 0.001f;

	gameLocal.intro.data = ( unsigned int * ) malloc( sizeof( unsigned int ) * 1 );
	*( gameLocal.intro.data )		= texture_load_bmp( "data/textures/pres.bmp" );	// texture
	/**( ( unsigned int* )gameLocal.intro.data + 4 )	= texture_load_bmp( "data/textures/pres2.bmp" );	// texture 2
	*( ( unsigned int* )gameLocal.intro.data + 8 )  = texture_load_bmp( "data/textures/pres3.bmp" );	// texture 3
	*( ( unsigned int* )gameLocal.intro.data + 12 ) = 0;												// with alpha = 0, black screen*/

	if ( gameLocal.world.lmap.data[ 1 * gameLocal.world.lmap.height + 2 ] != 0 )
		cinematics_loadFromFile( &gameLocal.cinematics[ 0 ], "data/scripts/cinema1.txt" );

}

//-------------------------------
//	gameLocal_introStop
//-------------------------------
void	gameLocal_introStop( void ) {
	gameLocal.intro.state = INTRO_CINEMA;
	//free( gameLocal.intro.data );
	cinematics_play( &gameLocal.cinematics[ 0 ] );
}

//-------------------------------
//	gameLocal_introRender
//-------------------------------
void	gameLocal_introRender( void ) {
	const float	 stateLen = 7.0f;
	float		 alpha;
	unsigned int tex;
	int			 state; 
	float		 subState;


	gameLocal.intro.lastTime = gameLocal.intro.time;
	gameLocal.intro.time = ( float )( GetTickCount() * 0.001f ) - gameLocal.intro.startTime;

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glOrtho( -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f );
	glPushMatrix();
	

	

	// decide which logo to display
	state = ( int ) floorf( gameLocal.intro.time / stateLen ) * 10;

	if ( state > 20 ) {
		gameLocal_introStop();
	} else {
		shader_use( gameLocal.shaders[ 2 ] );

		tex = *gameLocal.intro.data;

		subState = fmod( gameLocal.intro.time, stateLen ) / stateLen;

		if ( subState <= 0.25f ) alpha = subState * 4.0f;
		else
		if ( subState > 0.25f && subState <= 0.50f ) alpha = 1.0f;
		else
		if ( subState > 0.50f && subState <= 0.75f ) alpha = 1.0f - ( subState - 0.50f ) * 4.0f;
		else
		if ( subState > 0.75f ) alpha = 0.0f;

		glActiveTexture( GL_TEXTURE0 );
		glUniform1i( glGetUniformLocation( gameLocal.shaders[ 2 ], "tex" ), 0 );
		glBindTexture( GL_TEXTURE_2D, tex );

		glBegin( GL_QUADS );
			glMultiTexCoord2f( GL_TEXTURE0, 0.0f, 1.0f );		glVertex3f( -0.30f,  -0.3f, alpha + state );
			glMultiTexCoord2f( GL_TEXTURE0, 1.0f, 1.0f );		glVertex3f(  0.30f,  -0.3f, alpha + state );
			glMultiTexCoord2f( GL_TEXTURE0, 1.0f, 0.0f );		glVertex3f(  0.30f,   0.3f, alpha + state );
			glMultiTexCoord2f( GL_TEXTURE0, 0.0f, 0.0f );		glVertex3f( -0.30f,   0.3f, alpha + state );
		glEnd();

		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, 0 );

		shader_use( 0 );
	}

	glPopMatrix();
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
	glDisable( GL_BLEND );
}


//-------------------------------
//	gameLocal_introPlay
//-------------------------------
void	gameLocal_outroPlay( char happyEnd ) {

	gameLocal.intro.state = INTRO_CINEMA_THEEND;

	gameLocal.intro.time = 0.0f;
	gameLocal.intro.startTime = 
	gameLocal.intro.lastTime  = ( float ) GetTickCount() * 0.001f;

	gameLocal.intro.data = ( unsigned int * ) malloc( sizeof( unsigned int ) + sizeof( char ) );
	*( gameLocal.intro.data )		= texture_load_bmp( "data/textures/outro.bmp" );	// texture
	*( gameLocal.intro.data + sizeof( unsigned int ) ) = happyEnd;

}
//-------------------------------
//	gameLocal_introStop
//-------------------------------
void	gameLocal_outroStop( void ) {
	app_uninit();
}

//-------------------------------
//	gameLocal_outroRender
//-------------------------------
void	gameLocal_outroRender( void ) {
	const float	 stateLen = 7.0f;
	float		 alpha;
	unsigned int tex;
	int			 state; 
	float		 subState;


	gameLocal.intro.lastTime = gameLocal.intro.time;
	gameLocal.intro.time = ( float )( GetTickCount() * 0.001f ) - gameLocal.intro.startTime;

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glOrtho( -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f );
	glPushMatrix();

	// decide which logo to display
	state = ( int ) ( floorf( gameLocal.intro.time / stateLen ) + ( 1 - *( gameLocal.intro.data + sizeof( unsigned int ) ) ) ) * 10;

	if ( state > ( 1 - *( gameLocal.intro.data + sizeof( unsigned int ) ) ) * 10 ) {
		gameLocal_outroStop();
	} else {
		shader_use( gameLocal.shaders[ 2 ] );

		tex = *gameLocal.intro.data;

		subState = fmod( gameLocal.intro.time, stateLen ) / stateLen;

		if ( subState <= 0.25f ) alpha = subState * 4.0f;
		else
		if ( subState > 0.25f && subState <= 0.50f ) alpha = 1.0f;
		else
		if ( subState > 0.50f && subState <= 0.75f ) alpha = 1.0f - ( subState - 0.50f ) * 4.0f;
		else
		if ( subState > 0.75f ) alpha = 0.0f;

		glActiveTexture( GL_TEXTURE0 );
		glUniform1i( glGetUniformLocation( gameLocal.shaders[ 2 ], "tex" ), 0 );
		glBindTexture( GL_TEXTURE_2D, tex );

		glBegin( GL_QUADS );
			glMultiTexCoord2f( GL_TEXTURE0, 0.0f, 1.0f );		glVertex3f( -0.30f,  -0.3f, alpha + state );
			glMultiTexCoord2f( GL_TEXTURE0, 1.0f, 1.0f );		glVertex3f(  0.30f,  -0.3f, alpha + state );
			glMultiTexCoord2f( GL_TEXTURE0, 1.0f, 0.0f );		glVertex3f(  0.30f,   0.3f, alpha + state );
			glMultiTexCoord2f( GL_TEXTURE0, 0.0f, 0.0f );		glVertex3f( -0.30f,   0.3f, alpha + state );
		glEnd();

		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, 0 );

		shader_use( 0 );
	}

	glPopMatrix();
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
	glDisable( GL_BLEND );

	font_print( gameLocal.font1, -0.05f, 0.5f, 0, "%d : %d", ( int ) ( gameLocal.time / 60.f ), ( int ) ( gameLocal.time ) % 60 );
}



