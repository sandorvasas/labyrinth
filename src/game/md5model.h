/*
==============================================================================================

	Copyright ( C ) 2011 by Sandor Vasas


	MD5 Model Loader
		Reference: 
			http://tfc.duke.free.fr/coding/md5-specs-en.html

==============================================================================================
*/
#ifndef __VS_MD5MODEL_H__
#define __VS_MD5MODEL_H__

#include "..\math\vector.h"
#include "..\math\quaternion.h"
#include "..\sys\shader.h"
#include <stdio.h>


#define _CRT_SECURE_NO_WARNINGS


/*
====================================
	md5Joint_t
====================================
*/
typedef struct {
	char	name[ 64 ];
	int		parentIndex;
	vsVec3	pos;
	vsQuat	orient;
} md5Joint_t;

/*
====================================
	md5Vertex_t
====================================
*/
typedef struct {
	vsVec3	finalPos;
	///vsVec3	finalNormal;
	vsVec3	normal;
	vsVec2	st;
	int		startWeight;
	int		countWeight;
} md5Vertex_t;

/*
====================================
	md5Weight_t
====================================
*/
typedef struct {
	int		jointIndex;
	float	bias;
	vsVec3	pos;
} md5Weight_t;

/*
====================================
	md5Triangle_t
====================================
*/
typedef struct {
	unsigned int	vertIndex[ 3 ];
} md5Triangle_t;


/*
====================================
	md5Mesh_t
====================================
*/
typedef struct {
	int				numVerts;
	int				numTris;
	int				numWeights;

	md5Vertex_t*	vert;
	md5Triangle_t*	tri;
	md5Weight_t*	weights;
} md5Mesh_t;




// ANIM STRUCTS --------------------------------------------------------------------
/*
====================================
	md5JointInfo_t
====================================
*/
typedef struct {
	char	name[ 64 ];
	int		parentIndex;
	int		flags;
	int		startIndex;
} md5JointInfo_t;

/*
====================================
	md5AnimJoint_t
====================================
*/
typedef struct {
	vsVec3	pos;
	vsQuat	orient;
} md5AnimJoint_t;


/*
====================================
	md5Frame_t
====================================
*/
typedef struct {
	vsVec3			boundingBox[ 2 ];
	float*			components;
	md5Joint_t*		skeleton;
} md5Frame_t;

/*
====================================
	Animation Playing Flags
====================================
*/
enum {
	ANIM_PLAY_LOOP = 0x00001,
	ANIM_PLAY_NOW  = 0x00010
};

/*
====================================
	md5Anim_t
====================================
*/
typedef struct {
	char			entityName[ 64 ];

	int				numFrames;
	int				numJoints;
	int				numAnimatedComponents;
	int				frameRate;

	md5Frame_t*		frames;
	md5JointInfo_t*	jointInfos;			
	md5Joint_t*		baseFrame;

	float			duration;
} md5Anim_t;


/*
====================================
	md5Model_t
====================================
*/
typedef struct {
	char			entityName[ 64 ];

	int				numJoints;
	int				numMeshes;

	md5Joint_t*		joints;
	md5Mesh_t*		meshes;

	vsVec3			position;
	vsVec3			scale;
	vsQuat			rotation;

	unsigned int	diffuseMap;
	unsigned int	normalMap;
	shader_t		shader;

	vsVec3			directionVector;

	// anim data
	md5Anim_t*		pAnim;
	md5Anim_t*		pNextAnim;
	int				playOptions;
	int				nextPlayOptions;
	float			currentTime;
	int				currentFrame;
	md5Joint_t*		currentSkeleton;
} md5Model_t;






void		md5Model_clone( md5Model_t* clone, md5Model_t* m );
void		md5Model_load( md5Model_t* M, char* szFileName );
void		md5Model_render( md5Model_t* m );
void		md5Model_renderAnimated( md5Model_t* m, float deltaTime );
void		md5Model_setAnimation( md5Model_t* m, md5Anim_t* anim, int playOptions );
void		md5Model_setPosition( md5Model_t* m, vsVec3* offset );
void		md5Model_setRotation( md5Model_t* m, vsVec3* eulerAnglesRad );
void		md5Model_setRotationQuat( md5Model_t* m, vsQuat* quat );
void		md5Model_scale( md5Model_t* m, vsVec3* scale );
void		md5Model_destroy( md5Model_t* m );
void		md5Model_setShader( md5Model_t* m, shader_t* shader );
void		md5Model_buildModel( md5Model_t* m, md5Joint_t* skeleton );
void		md5Model_calculateNormals( md5Model_t* m );
void		md5Model_convertPointToModelSpace( md5Model_t * m, vsVec3* point );



void		md5Anim_load( md5Anim_t* a, char* szFileName );
void		md5Anim_destroy( md5Anim_t* a );
void		md5Anim_buildFrameSkeleton( md5Anim_t* anim, int frameNum );
void		md5Anim_getMovementDelta( md5Model_t* m, md5Anim_t* a, float time, vsVec3* delta );


#endif