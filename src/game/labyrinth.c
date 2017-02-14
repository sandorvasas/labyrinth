#include <malloc.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#include "..\OpenGL\GLexp.h"
#include "..\sys\sys.h"
#include "..\sys\texture.h"
#include "..\math\plane.h"
#include "actor.h"
#include "labyrinth.h"
#include "gameLocal.h"


//------------------------------------------------
//	labMap_set()
//------------------------------------------------
void labMap_set( labMap_t* lmap, int width, int height ) {
	lmap->width = width;
	lmap->height = height;
}


//------------------------------------------------
//	l_isDeadEnd()
//		checks if a position is a deadend, or not
//------------------------------------------------
unsigned char l_isDeadEnd( labMap_t* lmap, int x, int y ) {
	int deads = 0;

	deads += ( x-2 > 0 )?				lmap->data[   y   * lmap->width + x-2 ] & LM_CORRIDOR	: 1;
	deads += ( y-2 > 0 )?				lmap->data[ (y-2) * lmap->width + x   ]	& LM_CORRIDOR	: 1;
	deads += ( x+2 < lmap->width-1 )?	lmap->data[   y   * lmap->width + x+2 ] & LM_CORRIDOR	: 1;
	deads += ( y+2 < lmap->height-1)?   lmap->data[ (y+2) * lmap->width + x   ] & LM_CORRIDOR	: 1;

	return ( deads == 4 );
}

//------------------------------------------------
//	l_isVisited()
//		checks if a position is visited or not
//------------------------------------------------
unsigned char l_isVisited( labMap_t* lmap, int x, int y ) {
	if ( x >= lmap->width-1 )	return 1;
	if ( x < 0 )				return 1;
	if ( y >= lmap->height-1)	return 1;
	if ( y < 0 )				return 1;

	return ( lmap->data[ y * lmap->width + x ] & LM_CORRIDOR );
}

//------------------------------------------------
//	l_setVisited()
//		labels position as visited
//------------------------------------------------
void l_setVisited( labMap_t* lmap, int x, int y ) {
	lmap->data[ y * lmap->width + x ] |= LM_CORRIDOR;
}

//------------------------------------------------
//	l_placeRoom()
//------------------------------------------------
void l_placeRoom( labMap_t* lmap ) {
	// we place a room somewhere away from the player's start position
	// first, decide in which fourth of the labyrinth the room will be located
	lmap->fourth = rand() % 3;	

	switch ( lmap->fourth ) {
		case FOURTH_UPPER_RIGHT: 
			l_setVisited( lmap, lmap->width-2, 1 );
			l_setVisited( lmap, lmap->width-3, 1 );
			l_setVisited( lmap, lmap->width-4, 1 );
			l_setVisited( lmap, lmap->width-2, 2 );
			l_setVisited( lmap, lmap->width-3, 2 );
			l_setVisited( lmap, lmap->width-4, 2 );
			l_setVisited( lmap, lmap->width-2, 3 );
			l_setVisited( lmap, lmap->width-3, 3 );
			l_setVisited( lmap, lmap->width-4, 3 );
			l_setVisited( lmap, lmap->width-1, 2 );
			lmap->monsterLoc.x = lmap->width - 3;
			lmap->monsterLoc.y = 2;
			lmap->exitLoc.x = lmap->width - 1;
			lmap->exitLoc.y = 2;
		break;

		case FOURTH_LOWER_RIGHT: 
			l_setVisited( lmap, lmap->width-2, lmap->height - 2 );
			l_setVisited( lmap, lmap->width-3, lmap->height - 2 );
			l_setVisited( lmap, lmap->width-4, lmap->height - 2 );
			l_setVisited( lmap, lmap->width-2, lmap->height - 3 );
			l_setVisited( lmap, lmap->width-3, lmap->height - 3 );
			l_setVisited( lmap, lmap->width-4, lmap->height - 3 );
			l_setVisited( lmap, lmap->width-2, lmap->height - 4 );
			l_setVisited( lmap, lmap->width-3, lmap->height - 4 );
			l_setVisited( lmap, lmap->width-4, lmap->height - 4 );
			l_setVisited( lmap, lmap->width-3, lmap->height - 1 );
			lmap->monsterLoc.x = lmap->width - 3;
			lmap->monsterLoc.y = lmap->height - 3;
			lmap->exitLoc.x = lmap->width - 3;
			lmap->exitLoc.y = lmap->height - 1;
		break;

		case FOURTH_LOWER_LEFT: 
			l_setVisited( lmap, 1, lmap->height - 2 );
			l_setVisited( lmap, 2, lmap->height - 2 );
			l_setVisited( lmap, 3, lmap->height - 2 );
			l_setVisited( lmap, 1, lmap->height - 3 );
			l_setVisited( lmap, 2, lmap->height - 3 );
			l_setVisited( lmap, 3, lmap->height - 3 );
			l_setVisited( lmap, 1, lmap->height - 4 );
			l_setVisited( lmap, 2, lmap->height - 4 );
			l_setVisited( lmap, 3, lmap->height - 4 );
			l_setVisited( lmap, 0, lmap->height - 3 );
			lmap->exitLoc.x = 0;
			lmap->exitLoc.y = lmap->height - 3;
		break;
	}
}

//------------------------------------------------
//	labMap_gen_recursive()
//		Recursive function for generating the map using Depth-First Search Algorithm
//------------------------------------------------
void	labMap_gen_recursive_DFS( labMap_t* lmap, int x, int y ) {
	unsigned char k;

	l_setVisited( lmap, x, y );
	
	k = rand() % 4;
	while ( !l_isDeadEnd( lmap, x, y ) ) 
	{
		if ( k == 0 && !l_isVisited( lmap, x-2, y ) ) // LEFT
		{
			l_setVisited( lmap, x-1, y );
			labMap_gen_recursive_DFS( lmap, x-2, y );
		} else

		if ( k == 1 && !l_isVisited( lmap, x+2, y ) ) // RIGHT
		{
			l_setVisited( lmap, x+1, y );
			labMap_gen_recursive_DFS( lmap, x+2, y );
		} else

		if ( k == 2 && !l_isVisited( lmap, x, y-2 ) ) // TOP
		{
			l_setVisited( lmap, x, y-1 );
			labMap_gen_recursive_DFS( lmap, x, y-2 );
		} else

		if ( k == 3 && !l_isVisited( lmap, x, y+2 ) ) // BOTTOM
		{
			l_setVisited( lmap, x, y+1 );
			labMap_gen_recursive_DFS( lmap, x, y+2 );
		}

		k = rand() % 4;
	}
}

//------------------------------------------------
//	labMap_generate_DFS()
//		Generates the labyrinth. 
//		Call this function, the above is not visible from outside this file.
//------------------------------------------------
void	labMap_generate_DFS( labMap_t* lmap ) {
	int i;
	int fourth;
	srand( ( unsigned int ) time( 0 ) );

	lmap->data = ( unsigned char* ) malloc( lmap->width * lmap->height );
	for ( i = 0; i < lmap->width * lmap->height; i++ )
		lmap->data[ i ] = 0;

	labMap_gen_recursive_DFS( lmap, 1, 1 );

	l_placeRoom( lmap );
}


//------------------------------------------------
//	labMap_generate_GT()
//		Growing Tree Algorithm
//------------------------------------------------
void	labMap_generate_GT( labMap_t* lmap ) {
	coord_t* list;
	coord_t	 opps[ 4 ];
	int		 numOpps;
	int		 numCoords = 1;
	int		 selected;
	int		 selectionMode;
	int		 i, j, k;
	char	 ok;

	lmap->data = ( unsigned char* ) malloc( lmap->width * lmap->height );
	for ( i = 0; i < lmap->width * lmap->height; i++ )
		lmap->data[ i ] = 0;

	list = ( coord_t* ) malloc( sizeof( coord_t ) * numCoords );
	list[ 0 ].x = 1;
	list[ 0 ].y = 1;

	srand( ( int ) time( NULL ) );

	while ( numCoords > 0 ) {
		if ( numCoords == 1 )
			selected = 0;
		else {
			selectionMode = rand() % 4;

			switch ( selectionMode ) {
				case 0:	selected = rand() % numCoords;
				break;
				case 1: selected = numCoords - 1;
				break;
				case 2: selected = rand() % ( numCoords / 2 );
				break;
				case 3:	selected = min( ( numCoords / 2 + ( rand() % ( numCoords / 2 ) ) ), numCoords - 1 );
				break;
			}
		}

		// remove element if dead end
		if ( l_isDeadEnd( lmap, list[ selected ].x, list[ selected ].y ) ) {

			lmap->data[ list[ selected ].y * lmap->width + list[ selected ].x ] |= LM_MINE;

			if ( numCoords - 1 <= 0 )
				break; //fixme

			// remove element
			for ( i = selected; i < numCoords - 1; i++ )
				list[ i ] = list[ i + 1 ];

			list = ( coord_t* ) realloc( list, sizeof( coord_t ) * --numCoords );
		} else {
			numOpps = 0;
			// check LEFT
			if (  !l_isVisited( lmap, list[ selected ].x - 2, list[ selected ].y ) 
			   /*&& !l_isVisited( lmap, list[ selected ].x - 1, list[ selected ].y ) */) {
			   opps[ numOpps ].x = list[ selected ].x - 2;
			   opps[ numOpps++ ].y = list[ selected ].y;
			}
			// check RIGHT
			if (  !l_isVisited( lmap, list[ selected ].x + 2, list[ selected ].y ) 
			  /* && !l_isVisited( lmap, list[ selected ].x + 1, list[ selected ].y )*/ ) {
			   opps[ numOpps ].x = list[ selected ].x + 2;
			   opps[ numOpps++ ].y = list[ selected ].y;
			}
			// check UP
			if (  !l_isVisited( lmap, list[ selected ].x, list[ selected ].y + 2 ) 
			  /* && !l_isVisited( lmap, list[ selected ].x, list[ selected ].y + 1 )*/ ) {
			   opps[ numOpps ].x = list[ selected ].x;
			   opps[ numOpps++ ].y = list[ selected ].y + 2;
			}
			// check DOWN
			if (  !l_isVisited( lmap, list[ selected ].x, list[ selected ].y - 2 ) 
			  /* && !l_isVisited( lmap, list[ selected ].x, list[ selected ].y - 1 )*/ ) {
			   opps[ numOpps ].x = list[ selected ].x;
			   opps[ numOpps++ ].y = list[ selected ].y - 2;
			}

			k = rand() % numOpps;

			list = ( coord_t* ) realloc( list, sizeof( coord_t ) * ++numCoords );
			list[ numCoords - 1 ].x = opps[ k ].x;
			list[ numCoords - 1 ].y = opps[ k ].y;
			
			l_setVisited( lmap, ( list[ selected ].x + opps[ k ].x ) / 2, ( list[ selected ].y + opps[ k ].y ) / 2 );
			l_setVisited( lmap, opps[ k ].x, opps[ k ].y );
		}
	}

	l_placeRoom( lmap );
	
	srand( ( int ) time( 0 ) );
	for ( i = 1; i < lmap->height-1; i++ )
	for ( j = 1; j < lmap->width-1; j++ )
	{
		numOpps = 0;
		if ( j < lmap->width-1 )
			if ( lmap->data[ i * lmap->width + j + 1 ] == LM_WALL ) {
				opps[ numOpps ].x = j + 1;
				opps[ numOpps++ ].y = i;
			}

		if ( j > 0 )
			if ( lmap->data[ i * lmap->width + j - 1 ] == LM_WALL ) {
				opps[ numOpps ].x = j - 1;
				opps[ numOpps++ ].y = i;
			}

		if ( i < lmap->height-1 )
			if ( lmap->data[ ( i + 1 ) * lmap->width + j ] == LM_WALL ) {
				opps[ numOpps ].x = j;
				opps[ numOpps++ ].y = i + 1;
			}

		if ( i > 0 )
			if ( lmap->data[ ( i - 1 ) * lmap->width + j ] == LM_WALL ) {
				opps[ numOpps ].x = j;
				opps[ numOpps++ ].y = i - 1;
			}

		if ( numOpps > 2 )
		{
			if ( rand() % 3 == 0 ) {		
				ok = 0;
				while ( !ok ) {
					k = rand() % numOpps;
					if ( opps[ k ].x > 0 && opps[ k ].y > 0 &&
						 opps[ k ].x < lmap->width - 1 && opps[ k ].y < lmap->height - 1 )
						 ok = 1;
				}
				if ( opps[ k ].x != lmap->width - 2 && opps[ k ].x != 1 &&
					 opps[ k ].y != lmap->height - 2 && opps[ k ].y != 1 )
					lmap->data[ opps[ k ].y * lmap->width + opps[ k ].x ] |= LM_CORRIDOR;
			}
		}
	}
	
	free( list );
}


//------------------------------------------------
//	labMap_destroy()
//		Frees up memory allocated by the labyrinthMap
//------------------------------------------------
void	labMap_destroy( labMap_t* lmap ) {
	free( lmap->data );
	lmap->width = 0;
	lmap->height = 0;
}

//------------------------------------------------
//	labMap_saveFile()
//		Saves the labyrinth as a .bmp picture
//------------------------------------------------
void	labMap_saveToFile( labMap_t* lmap, char* szFileName ) {
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	FILE* f;
	unsigned int i;
	unsigned char B;

	bmfh.bfSize = sizeof( bmfh ) + sizeof( bmih ) + lmap->height * lmap->width * 3;
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfType = 'MB';
	bmfh.bfOffBits = sizeof( bmfh ) + sizeof( bmih );

	bmih.biSize = sizeof( bmih );
	bmih.biWidth = lmap->width;
	bmih.biHeight = lmap->height;
	bmih.biPlanes = 1;
	bmih.biBitCount = 24;
	bmih.biCompression = BI_RGB;
	bmih.biSizeImage = 0;
	bmih.biXPelsPerMeter = lmap->width;
	bmih.biYPelsPerMeter = lmap->height;
	bmih.biClrImportant = 0;
	bmih.biClrUsed = 0;

	f = fopen( szFileName, "wb+" );

	fwrite( &bmfh, sizeof( bmfh ), 1, f );
	fwrite( &bmih, sizeof( bmih ), 1, f );
	
	for ( i = 0; i < lmap->width * lmap->height; i++ ) {
		if ( lmap->data[ i ] == 0 ) 
			B = 0;
		else						
			B = 255;

		fwrite( &B, 1, 1, f );
		fwrite( &B, 1, 1, f );
		fwrite( &B, 1, 1, f );
	}

	fclose( f );
}

//------------------------------------------------
//	labMap_getValue()
//------------------------------------------------
short	labMap_getValue( labMap_t* map, int x, int y ) {
	// if out of bounds
	if ( x < 0 || y < 0 || x >= map->width || y >= map->height )
	{
		return -1;
	}
	return ( short ) map->data[ y * map->width + x ];
}



/*
===========================================================
	Labyrinth Model
===========================================================
*/
//------------------------------------------------
//	labModel_create()
//------------------------------------------------
void	labModel_create( labMap_t* lmap, labModel_t* lmodel, vsVec3* offset, vsVec3* scale ) {
	int x, y, off;
	float dx, dy;
	vsVec3 p[ 4 ], normal;

	/// fixme
	lmodel->textures[ LABTEX_FLOOR_DIFF ]	= texture_load_bmp( "data/textures/floor.bmp" );
	lmodel->textures[ LABTEX_FLOOR_NORM ]	= texture_load_bmp( "data/textures/floor_n.bmp" );
	lmodel->textures[ LABTEX_FLOOR_PARA ]	= texture_load_bmp( "data/textures/floor_h.bmp" );
	lmodel->textures[ LABTEX_WALL_DIFF ]	= texture_load_bmp( "data/textures/wall.bmp" );
	lmodel->textures[ LABTEX_WALL_NORM ]	= texture_load_bmp( "data/textures/wall_n.bmp" );
	lmodel->textures[ LABTEX_WALL_PARA ]	= texture_load_bmp( "data/textures/wall_h.bmp" );
	

	lmodel->numTriangles = 0;
	lmodel->numVertices = 0;

	lmodel->map = lmap;
	vec3_equ( &lmodel->scale, scale );
	vec3_equ( &lmodel->offset, offset );

	for ( y = 0; y < lmap->height; y++ ) 
	{
		off = y * lmap->width;
	
		for ( x = 0; x < lmap->width; x++ ) 
		{
			// FLOOR 
			if ( lmap->data[ off + x ] != 0 ) {
				// Add quad
				dx = 0.5f;
				dy = 0.5f;
				vec3_set( &p[ 0 ], ( float )(x - dx), 0.0f, ( float )(y - dy) );
				vec3_set( &p[ 1 ], ( float )(x + dx), 0.0f, ( float )(y - dy) );
				vec3_set( &p[ 2 ], ( float )(x + dx), 0.0f, ( float )(y + dy) );
				vec3_set( &p[ 3 ], ( float )(x - dx), 0.0f, ( float )(y + dy) );
				vec3_set( &normal, 0.0f, 1.0f, 0.0f );
				labModel_addQuad( lmodel, p, scale, offset, &normal );
			} else {
			// CEILING
				// Add quad
				dx = 0.5f;
				dy = 0.5f;
				vec3_set( &p[ 0 ], ( float )(x - dx), 1.0f, ( float )(y - dy) );
				vec3_set( &p[ 1 ], ( float )(x + dx), 1.0f, ( float )(y - dy) );
				vec3_set( &p[ 2 ], ( float )(x + dx), 1.0f, ( float )(y + dy) );
				vec3_set( &p[ 3 ], ( float )(x - dx), 1.0f, ( float )(y + dy) );
				vec3_set( &normal, 0.0f, 1.0f, 0.0f );
				labModel_addQuad( lmodel, p, scale, offset, &normal );
			}

			// wall: 1, path: 0
			if ( lmap->data[ off + x ] != 0 ) {
				//	0 
				//  1 
				if ( labMap_getValue( lmap, x, y + 1 ) == 0 ) {
					dx = 0.5f;
					dy = 0.5f;
					vec3_set( &p[ 0 ], ( float )(x - dx), 0.0f, ( float )(y + dy) );
					vec3_set( &p[ 1 ], ( float )(x + dx), 0.0f, ( float )(y + dy) );
					vec3_set( &p[ 2 ], ( float )(x + dx), 1.0f, ( float )(y + dy) );
					vec3_set( &p[ 3 ], ( float )(x - dx), 1.0f, ( float )(y + dy) );
					vec3_set( &normal, 0.0f, 0.0f, -1.0f ); //
					labModel_addQuad( lmodel, p, scale, offset, &normal );
				}
				//	0 1 
				if ( labMap_getValue( lmap, x + 1, y ) == 0 ) {
					dx = 0.5f;
					dy = 0.5f;
					vec3_set( &p[ 0 ], ( float )(x + dx), 0.0f, ( float )(y - dy) );
					vec3_set( &p[ 1 ], ( float )(x + dx), 0.0f, ( float )(y + dy) );
					vec3_set( &p[ 2 ], ( float )(x + dx), 1.0f, ( float )(y + dy) );
					vec3_set( &p[ 3 ], ( float )(x + dx), 1.0f, ( float )(y - dy) );
					vec3_set( &normal, -1.0f, 0.0f, 0.0f );//
					labModel_addQuad( lmodel, p, scale, offset, &normal );
				}

				//	1
				//  0 
				if ( labMap_getValue( lmap, x, y - 1 ) == 0 ) {
					dx = 0.5f;
					dy = 0.5f;
					vec3_set( &p[ 0 ], ( float )(x - dx), 0.0f, ( float )(y - dy) );
					vec3_set( &p[ 1 ], ( float )(x + dx), 0.0f, ( float )(y - dy) );
					vec3_set( &p[ 2 ], ( float )(x + dx), 1.0f, ( float )(y - dy) );
					vec3_set( &p[ 3 ], ( float )(x - dx), 1.0f, ( float )(y - dy) );
					vec3_set( &normal, 0.0f, 0.0f, 1.0f );//
					labModel_addQuad( lmodel, p, scale, offset, &normal );
				}
				//	1 0 
				if ( labMap_getValue( lmap, x - 1, y ) == 0 ) {
					dx = 0.5f;
					dy = 0.5f;
					vec3_set( &p[ 0 ], ( float )(x - dx), 0.0f, ( float )(y - dy) );
					vec3_set( &p[ 1 ], ( float )(x - dx), 0.0f, ( float )(y + dy) );
					vec3_set( &p[ 2 ], ( float )(x - dx), 1.0f, ( float )(y + dy) );
					vec3_set( &p[ 3 ], ( float )(x - dx), 1.0f, ( float )(y - dy) );
					vec3_set( &normal, 1.0f, 0.0f, 0.0f );
					labModel_addQuad( lmodel, p, scale, offset, &normal );
				}
			}

			//win32_msgbox( "vert: %f %f %f", lmodel->vert[ lmodel->numVertices - 1 ].pos.x,  lmodel->vert[ lmodel->numVertices - 1 ].pos.y,  lmodel->vert[ lmodel->numVertices - 1 ].pos.z );
		}
	}

	/*win32_msgbox( "numVertices: %d", lmodel->numVertices );
	win32_msgbox( "numTriangles: %d", lmodel->numTriangles );
	glGenBuffers( 2, &lmodel->vertBuf );
	glBindBuffer( GL_ARRAY_BUFFER, lmodel->vertBuf );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertex_t ) * lmodel->numVertices, lmodel->vert, GL_STATIC_DRAW );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, lmodel->indexBuf );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( triangle_t ) * lmodel->numTriangles, lmodel->triangles, GL_STATIC_DRAW );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );*/
}

//------------------------------------------------
//	labModel_translate()
//------------------------------------------------
void	labModel_addQuad( labModel_t* lmodel, vsVec3 p[ 4 ], vsVec3* scale, vsVec3* offset, vsVec3* n ) {
	float t;

	if ( n->y == 0.0f ) 
		t = scale->y / scale->x;
	else 
		t = 1.0f;

	lmodel->vert = ( vertex_t* ) realloc( lmodel->vert, ( lmodel->numVertices + 4 ) * sizeof( vertex_t ) );
	vertex_set_pnt( &lmodel->vert[ lmodel->numVertices++ ], p[0].x * scale->x, p[0].y * scale->y, p[0].z * scale->z, n->x, n->y, n->z, 0.0f, 0.0f ) ;
	vertex_set_pnt( &lmodel->vert[ lmodel->numVertices++ ], p[1].x * scale->x, p[1].y * scale->y, p[1].z * scale->z, n->x, n->y, n->z, 1.0f, 0.0f );
	vertex_set_pnt( &lmodel->vert[ lmodel->numVertices++ ], p[2].x * scale->x, p[2].y * scale->y, p[2].z * scale->z, n->x, n->y, n->z, 1.0f, t );
	vertex_set_pnt( &lmodel->vert[ lmodel->numVertices++ ], p[3].x * scale->x, p[3].y * scale->y, p[3].z * scale->z, n->x, n->y, n->z, 0.0f, t );
	
	vec3_add( &lmodel->vert[ lmodel->numVertices - 4 ].pos, offset );
	vec3_add( &lmodel->vert[ lmodel->numVertices - 3 ].pos, offset );
	vec3_add( &lmodel->vert[ lmodel->numVertices - 2 ].pos, offset );
	vec3_add( &lmodel->vert[ lmodel->numVertices - 1 ].pos, offset );
	
	lmodel->triangles = ( triangle_t* ) realloc( lmodel->triangles, ( lmodel->numTriangles + 2 ) * sizeof( triangle_t ) );
	lmodel->triangles[ lmodel->numTriangles ].a		= lmodel->numVertices - 4;
	lmodel->triangles[ lmodel->numTriangles ].b		= lmodel->numVertices - 3;
	lmodel->triangles[ lmodel->numTriangles++ ].c	= lmodel->numVertices - 2;
	lmodel->triangles[ lmodel->numTriangles ].a		= lmodel->numVertices - 2;
	lmodel->triangles[ lmodel->numTriangles ].b		= lmodel->numVertices - 1;
	lmodel->triangles[ lmodel->numTriangles++ ].c	= lmodel->numVertices - 4;	
}


//------------------------------------------------
//	labModel_translate()
//------------------------------------------------
void	labModel_translate( labModel_t* lmodel ) {
}

//------------------------------------------------
//	labModel_render()
//------------------------------------------------
void	labModel_render( labModel_t* lmodel ) {
	int i;

	shader_use( *lmodel->shader );


	//glBindBuffer( GL_ARRAY_BUFFER, lmodel->vertBuf );	
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );
	
	glVertexPointer( 3, GL_FLOAT, sizeof( vertex_t ), lmodel->vert );
	glNormalPointer( GL_FLOAT, sizeof( vertex_t ), &lmodel->vert[0].normal );


	// texture wall 0 ---------------------------------------------------
	glClientActiveTexture( GL_TEXTURE0 );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glTexCoordPointer( 2, GL_FLOAT, sizeof( vertex_t ), &lmodel->vert[0].uv );


	for ( i = 0; i < NUM_LABTEX; i++ ) {
		glActiveTexture( GL_TEXTURE0 + i );
		glBindTexture( GL_TEXTURE_2D, lmodel->textures[ i ] );
	}
	

	//glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, lmodel->indexBuf );
	glDrawElements( GL_TRIANGLES, 3 * lmodel->numTriangles, GL_UNSIGNED_INT, ( void * ) lmodel->triangles );
	//glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	
	// disable texture units -------------------------------------------
	for ( i = 0; i < NUM_LABTEX; i++ ) {
		glActiveTexture( GL_TEXTURE0 + i );
		glBindTexture( GL_TEXTURE_2D, 0 );
	}

	glClientActiveTexture( GL_TEXTURE0 );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState( GL_NORMAL_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );
	//glBindBuffer( GL_ARRAY_BUFFER, 0 );

	shader_use( 0 );
}


//------------------------------------------------
//	labModel_destroy()
//------------------------------------------------
void	labModel_destroy( labModel_t* lmodel ) {

	free( lmodel->vert );
	 free( lmodel->triangles );
	labMap_destroy( lmodel->map );

	//glDeleteBuffers( 2, &lmodel->vertBuf );
}

//------------------------------------------------
//	labModel_setShader()
//------------------------------------------------
void	labModel_setShader( labModel_t* lmodel, shader_t* shader ) {
	int i;

	lmodel->shader			= shader;
	lmodel->texLoc[ LABTEX_WALL_DIFF ]	= glGetUniformLocation( *shader, "texWallDiff" );
	lmodel->texLoc[ LABTEX_WALL_NORM ]	= glGetUniformLocation( *shader, "texWallNorm" );
	lmodel->texLoc[ LABTEX_WALL_PARA ]	= glGetUniformLocation( *shader, "texWallPara" );
	lmodel->texLoc[ LABTEX_FLOOR_DIFF ]	= glGetUniformLocation( *shader, "texFloorDiff" );
	lmodel->texLoc[ LABTEX_FLOOR_NORM ]	= glGetUniformLocation( *shader, "texFloorNorm" );
	lmodel->texLoc[ LABTEX_FLOOR_PARA ]	= glGetUniformLocation( *shader, "texFloorPara" );

	shader_use( *shader );
	for ( i = 0; i < NUM_LABTEX; i++ )
		glUniform1i( lmodel->texLoc[ i ], i );
	shader_use( 0 );
}

//------------------------------------------------
//	labModel_getCell()
//------------------------------------------------
void	labModel_getCell( labModel_t* l, vsVec3* p, int* x, int* y ) {
	*x = ( int ) ceilf( ( p->x - l->offset.x ) /  l->scale.x - 0.5f ) ;
	*y = ( int ) ceilf( ( p->z - l->offset.z ) /  l->scale.z - 0.5f ) ;

	// if out of bounds
	if ( *x < 0 || *y < 0 || *x >= l->map->width || *y >= l->map->height )
	{
		*x = -1;
		*y = -1;
	}
}

//------------------------------------------------
//	labModel_getCenterOfCell()
//------------------------------------------------
void	labModel_getCenterOfCell( labModel_t* l, int x, int y, vsVec3* center ) {
	float fx = (float) x * l->scale.x + l->offset.x;
	float fy = (float) l->offset.y;
	float fz = (float) y * l->scale.z + l->offset.z;

	vec3_set( center, fx, fy, fz );
}