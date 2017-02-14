/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#ifndef __VS_CINEMATICS_H__
#define __VS_CINEMATICS_H__

#include "..\math\vector.h"
#include "..\math\quaternion.h"


enum {
	CINEMA_ENDED = 0,
	CINEMA_PLAYING = 1
};

/*
===============================================
	ccEvent_t
===============================================
*/
typedef struct {
	char	entityName[ 64 ];
	char	animName[ 64 ];
	int		actorDir;
	float	length;
	float	startTime;
	vsVec3	startPos;
	vsVec3	endPos;
	vsQuat	startRot;
	vsQuat	endRot;
} ccEvent_t;



/*
===============================================
	cinematicCamera_t
	 ( cc_t )
===============================================
*/
typedef struct {
	ccEvent_t*			events;
	int					numEvents;
	float				currentTime;
	vsVec3				currentPos;
	int					state;
} cinematicCamera_t, cc_t;


int			cinematics_loadFromFile( cc_t* cc, char* szFileName );
void		cinematics_play( cc_t* cc );
void		cinematics_stop( cc_t* cc );
void		cinematics_update( cc_t* cc );
void		cinematics_destroy( cc_t* cc );

#endif