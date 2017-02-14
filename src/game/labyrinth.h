/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

==============================================================================================
*/
#ifndef __VS_LABYRINTH_H__
#define __VS_LABYRINTH_H__

#define _CRT_SECURE_NO_WARNINGS

#include "vertex.h"
#include "..\sys\shader.h"



/*
===============================================
	coord_t
		Coordinate on the labyrinth
===============================================
*/
typedef struct {
	int		x, y;
} coord_t;



enum {
	LM_WALL = 0,
	LM_CORRIDOR = 1,
	LM_MINE = 2
	//..etc
};

enum {
	FOURTH_UPPER_RIGHT = 0,
	FOURTH_LOWER_RIGHT = 1,
	FOURTH_LOWER_LEFT  = 2
};

/*
=================================================
	labMap_t
		Contains map of labyrinth
=================================================
*/
typedef struct {
	int				width;
	int				height;
	unsigned char*	data;

	coord_t			monsterLoc;
	coord_t			exitLoc;
	int				fourth;				// 0: UPPER RIGHT, 1: LOWER RIGHT, 2: LOWER LEFT
} labMap_t;



void	labMap_set( labMap_t* lmap, int width, int height );
void	labMap_generate_DFS( labMap_t* lmap );
void	labMap_generate_GT( labMap_t* lmap );
void	labMap_destroy( labMap_t* lmap );
void	labMap_saveToFile( labMap_t* lmap, char* szFileName );
short	labMap_getValue( labMap_t* map, int x, int y );


enum {
	LABTEX_WALL_DIFF = 0,
	LABTEX_WALL_NORM,
	LABTEX_WALL_PARA,
	LABTEX_FLOOR_DIFF,
	LABTEX_FLOOR_NORM,
	LABTEX_FLOOR_PARA
};


/*
=================================================
	labModel_t
		3D model generated from a labMap_t structure
=================================================
*/
#define NUM_LABTEX 6
typedef struct {
	int				numVertices;
	int				numTriangles;
	vertex_t*		vert;
	triangle_t*		triangles;

	// Vertex Buffer Objects
	//unsigned int	vertBuf;
	//unsigned int	indexBuf;

	labMap_t*		map;
	vsVec3			scale;
	vsVec3			offset;

	unsigned int	textures[ NUM_LABTEX ];
	shader_t*		shader;
	int				texLoc[ NUM_LABTEX ];
} labModel_t;


void	labModel_create( labMap_t* lmap, labModel_t* lmodel, vsVec3* offset, vsVec3* scale  );
void	labModel_translate( labModel_t* lmodel );
void	labModel_render( labModel_t* lmodel );
void	labModel_destroy( labModel_t* lmodel );
void	labModel_addQuad( labModel_t* lmodel, vsVec3 p[ 4 ], vsVec3* scale, vsVec3* offset, vsVec3* n );
void	labModel_setShader( labModel_t* lmodel, shader_t* shader );
void	labModel_getCell( labModel_t* l, vsVec3* p, int* x, int* y );
void	labModel_getCenterOfCell( labModel_t* l, int x, int y, vsVec3* center );


#endif