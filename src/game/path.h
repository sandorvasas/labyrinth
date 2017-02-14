/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas

		Genetic Algorithm-based path finder
			used to coordinate the enemy monster to the player

==============================================================================================
*/
#ifndef __VS_PATH_FINDER_H__
#define __VS_PATH_FINDER_H__


#include "labyrinth.h"


/*
===============================================
	coord_t
		Coordinate on the labyrinth
===============================================
*/
typedef struct {
	int		x, y;
} coord_t;

/*
===============================================
	path_t
		Contains the coordinates of each point of the path.
===============================================
*/
typedef struct {
	int			length;			// length of the path = number of points
	coord_t*	points;
} path_t;


void	path_find( path_t* path, coord_t* A, coord_t* B, labModel_t* lab );



/*
==============================================================================================

	Genetic Algorithm code

==============================================================================================
*/

/*
===============================================
	genome_t
===============================================
*/
typedef struct {
	path_t		chromosome;
	float		fitness;
} genome_t;


/*
===============================================
	ga_t
		Genetic Algorithm struct
===============================================
*/
typedef struct {
	genome_t*		population;
	int				numPop;
	float			bestFitness;
	float			avgFitness;
	float			totalFitness;
	int				generation;

	float			crossOverRate;
	float			mutationRate;

	coord_t			pointA;
	coord_t			pointB;
} ga_t;


void	ga_init( ga_t* ga );
void	ga_uninit( ga_t* ga );
void	ga_crossOver( ga_t* ga, const genome_t* mum, const genome_t* dad, genome_t* baby1, genome_t* baby2 );
void	ga_mutate( ga_t* ga, genome_t* g );
int		ga_roulette( ga_t* ga );
void	ga_evalAllFitness( ga_t* ga );
void	ga_epoch( ga_t* ga );
int		ga_solutionFound( ga_t* ga );	// returns true if solution found


#endif