#include "path.h"
#include <stdio.h>

void path_find_recurse( char values[ 33 ][ 33 ], coord_t* dest, coord_t* pos ) 

{
	coord_t newPos;

	if ( pos->x == dest->x && pos->y == dest->y )
		return;

		if ( pos->y > 0 ) {
			if ( values[ pos->y - 1][ pos->x ] != -1 ) {
				values[ pos->y - 1 ][ pos->x ]++;
				newPos.x = pos->x;
				newPos.y = pos->y - 1;
				path_find_recurse( values, dest, &newPos );
			}
		}

		if ( pos->x > 0 ) {
			if ( values[ pos->y ][ pos->x - 1 ] != -1 )
				values[ pos->y ][ pos->x - 1 ]++; {
				newPos.x = pos->x - 1;
				newPos.y = pos->y;
				path_find_recurse( values, dest, &newPos );
			}

		}

		if ( pos->y < 33-1 ) {
			if ( values[ pos->y + 1][ pos->x ] != -1 ) {
				values[ pos->y + 1 ][ pos->x ]++;
				newPos.x = pos->x;
				newPos.y = pos->y + 1;
				path_find_recurse( values, dest, &newPos );
			}
		}

		if ( pos->x < 33-1 ) {
			if ( values[ pos->y ][ pos->x + 1 ] != -1 ) {
				values[ pos->y ][ pos->x + 1 ]++;
				newPos.x = pos->x + 1;
				newPos.y = pos->y;
				path_find_recurse( values, dest, &newPos );
			}
		}		
}

void	path_find( path_t* path, coord_t* A, coord_t* B, labModel_t* lab ) {
	char	values[ 33 ][ 33 ];
	int		y, x;
	coord_t pos;
	FILE * f;

	// initialization ----------------------------------
	for ( y = 0; y < 33; y++ )
	for ( x = 0; x < 33; x++ ) {
		if ( labMap_getValue( lab->map, x, y ) == 1 )
			values[ y ][ x ] = -1;
		else
			values[ y ][ x ] = 0;
	}


	pos.x = B->x;
	pos.y = B->y;

	path_find_recurse( values, A, B );

	f = fopen( "valueTable.txt", "w+" );

	for ( y = 0; y < 33; y++ ) {
		for ( x = 0; x < 33; x++ ) 
			fprintf( f, "%d ", values[ y ][ x ] );

		fprintf( f, "\n" );
	}

	fclose( f );
}



/*==========================
	ga_init()
==========================*/
void	ga_init( ga_t* ga ) {
	
}

/*==========================
	ga_uninit()
==========================*/
void	ga_uninit( ga_t* ga ) {
	
}

/*==========================
	ga_crossOver()
==========================*/
void	ga_crossOver( ga_t* ga, const genome_t* mum, const genome_t* dad, genome_t* baby1, genome_t* baby2 ) {
	
}

/*==========================
	ga_mutate()
==========================*/
void	ga_mutate( ga_t* ga, genome_t* g ) {
	
}

/*==========================
	ga_roulette()
==========================*/
int		ga_roulette( ga_t* ga ) {
	
}

/*==========================
	ga_evalAllFitness()
==========================*/
void	ga_evalAllFitness( ga_t* ga ) {
	
}

/*==========================
	ga_epoch()
==========================*/
void	ga_epoch( ga_t* ga ) {
	
}

/*==========================
	ga_solutionFound()
==========================*/
int		ga_solutionFound( ga_t* ga ) {
	
}


