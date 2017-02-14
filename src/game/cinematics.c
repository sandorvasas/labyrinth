#include "cinematics.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "gameLocal.h"
#include "..\OpenGL\GLexp.h"



//----------------------------------------
//	cinematics_loadFromFile()
//----------------------------------------
int		cinematics_loadFromFile( cc_t* cc, char* szFileName ) {
	FILE * f;
	char line[ 128 ];
	int i;
	vsVec3 r1, r2;
	
	f = fopen( szFileName, "r" );

	if ( !f ) 
		return -1;

	while ( !feof( f ) ) {
		fgets( line, 128, f );

		if ( strstr( line, "numEvents" ) ) {
			sscanf( line, "numEvents %d", &cc->numEvents );
			cc->events = ( ccEvent_t * ) malloc( sizeof( ccEvent_t ) * cc->numEvents ); 
		} else

		if ( strstr( line, "event" ) ) {
			sscanf( line, "event %d", &i );
			i--;
			fscanf( f, " startTime %f", &cc->events[ i ].startTime );
			fscanf( f, " length %f", &cc->events[ i ].length );

			fscanf( f, " entity %s", &cc->events[ i ].entityName );
			fscanf( f, " anim %s", &cc->events[ i ].animName );
			fscanf( f, " actorDir %s", line );
			
			if ( strcmp( line, "left" ) == 0 )	cc->events[ i ].actorDir = ACTOR_DIR_LEFT;	else
			if ( strcmp( line, "right" ) == 0 ) cc->events[ i ].actorDir = ACTOR_DIR_RIGHT;	else
			if ( strcmp( line, "up" ) == 0 )	cc->events[ i ].actorDir = ACTOR_DIR_UP;	else
			if ( strcmp( line, "down" ) == 0 )	cc->events[ i ].actorDir = ACTOR_DIR_DOWN;	else
				cc->events[ i ].actorDir = -1;

			fscanf( f," startPos %f %f %f", 
				&cc->events[ i ].startPos.x,
				&cc->events[ i ].startPos.y,
				&cc->events[ i ].startPos.z );

			fscanf( f," endPos %f %f %f", 
				&cc->events[ i ].endPos.x,
				&cc->events[ i ].endPos.y,
				&cc->events[ i ].endPos.z );

			fscanf( f, " startRot %f %f %f", &r1.x, &r1.y, &r1.z );
			fscanf( f, " endRot %f %f %f", &r2.x, &r2.y, &r2.z );

			vec3_mul( DEG_TO_RAD, &r1 );
			vec3_mul( DEG_TO_RAD, &r2 );
			
			quat_from_rot( &cc->events[ i ].startRot, r1.x, r1.y, r1.z );
			quat_from_rot( &cc->events[ i ].endRot, r2.x, r2.y, r2.z );

			if ( strcmp( cc->events[ i ].entityName, "sound" ) == 0 )
				cc->events[ i ].length = 0.2f;	/* we store a boolean value in length, in which 0.2f value 
												   indicates that the playing of the sound hasn't started yet */
		}
	}

	fclose( f );
	return 0;
}


//----------------------------------------
//	cinematics_play()
//----------------------------------------
void	cinematics_play( cc_t* cc ) {
	int i;
	cc->currentTime = 0.0f;
	cc->state = CINEMA_PLAYING;

	for ( i = 0; i < cc->numEvents; i++ )
		if ( !strcmp( "sound", cc->events[ i ].entityName ) )
			cc->events[ i ].length = 0.2f;
}

//----------------------------------------
//	cinematics_stop()
//----------------------------------------
void	cinematics_stop( cc_t* cc ) {
	cc->state = CINEMA_ENDED;
}


//----------------------------------------
//	cinematics_update()
//----------------------------------------
void	cinematics_update( cc_t* cc ) {
	int		sti;
	float	acc;
	float	relTime;
	vsQuat	rot;
	vsVec3	pos;
	vsMat4	m4;
	vsMat3	m3;
	int		i;
	int		numActiveEvents = 0;
	actor_t*	actor;
	md5Anim_t*	anim;
	sound_t*	snd;

	cc->currentTime += 1.0f / gameLocal.fps;


	for ( i = 0; i < cc->numEvents; i++ ) {
		if ( cc->events[ i ].startTime <= cc->currentTime &&
			 cc->currentTime <= cc->events[ i ].startTime + cc->events[ i ].length ) {
				numActiveEvents++;

				relTime = ( cc->currentTime - cc->events[ i ].startTime ) / cc->events[ i ].length;

				vec3_lerp( &cc->currentPos, &cc->events[ i ].startPos, &cc->events[ i ].endPos, relTime );
				quat_slerp( &rot, &cc->events[ i ].startRot, &cc->events[ i ].endRot, relTime );

				if ( strcmp( cc->events[ i ].entityName, "camera" ) == 0 ) {
					quat_to_mat3( &m3, &rot );
					mat3_to_mat4( &m4, &m3 );

					glMatrixMode( GL_MODELVIEW );
					glMultMatrixf( m4.m );
					mat4_identity( &m4 );
					m4.m[ 12 ] = -cc->currentPos.x;
					m4.m[ 13 ] = -cc->currentPos.y;
					m4.m[ 14 ] = -cc->currentPos.z;

					glMultMatrixf( m4.m );
				} else
				if ( strcmp( cc->events[ i ].entityName, "sound" ) == 0 &&
					 cc->events[ i ].length == 0.2f ) {
					gameLocal_soundPlay( cc->events[ i ].animName, cc->events[ i ].actorDir == ACTOR_DIR_UP );
					cc->events[ i ].length = 0.201f;	// means the sound is being played
				} else
				{
					actor = gameLocal_getActor( cc->events[ i ].entityName );
					if ( actor ) {
						if ( strcmp( cc->events[ i ].animName, "none" ) != 0 ) {
							anim = gameLocal_getAnim( cc->events[ i ].animName );

							if ( anim )
								actor_setCustomAnim( actor, anim, ( cc->events[ i ].actorDir == -1 )? actor->direction : cc->events[ i ].actorDir );
						}

						md5Model_setPosition( &actor->model, &cc->currentPos );
						//md5Model_setRotationQuat( &actor->model, &rot );
					}
				}
				
		}
	}


	if ( !numActiveEvents ) {
		cinematics_stop( cc );
		return;
	}
}


//----------------------------------------
//	cinematics_destroy()
//----------------------------------------
void	cinematics_destroy( cc_t* cc ) {
	if ( cc->numEvents > 0 )
		free( cc->events );
}


