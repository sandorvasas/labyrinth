#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "MD5Model.h"
#include "..\sys\texture.h"
#include "..\OpenGL\GLexp.h"
#include "..\sys\sys.h"
#include "..\sys\printer.h"
#include "gameLocal.h"
#include <math.h>


//----------------------------------------------
//	md5Model_load()
//----------------------------------------------
void md5Model_clone( md5Model_t* clone, md5Model_t* m ) {
	int i, j;

	//md5Model_t * clone = ( md5Model_t* ) malloc( sizeof( md5Model_t ) );

	strcpy( clone->entityName, m->entityName );
	clone->numJoints = m->numJoijnts;
	clone->numMeshes = m->numMeshes;
	
	vec3_equ( &clone->position, &m->position );
	vec3_equ( &clone->scale, &m->scale );
	quat_equ( &clone->rotation, &m->rotation );

	clone->diffuseMap = m->diffuseMap;
	clone->normalMap = m->normalMap;
	clone->shader = m->shader;
	
	vec3_equ( &clone->directionVector, &m->directionVector );
	clone->pAnim = m->pAnim;
	clone->pNextAnim = m->pNextAnim;
	clone->playOptions = m->playOptions;
	clone->nextPlayOptions = m->nextPlayOptions;
	clone->currentTime = m->currentTime;
	clone->currentFrame = m->currentFrame;
	clone->currentSkeleton = m->currentSkeleton;

	clone->meshes = ( md5Mesh_t* ) malloc( sizeof( md5Mesh_t ) * clone->numMeshes );
	for ( i = 0; i < clone->numMeshes; i++ ) {
		clone->meshes[ i ].numTris = m->meshes[ i ].numTris;
		clone->meshes[ i ].numVerts = m->meshes[ i ].numVerts;
		clone->meshes[ i ].numWeights = m->meshes[ i ].numWeights;

		clone->meshes[ i ].tri = ( md5Triangle_t* ) malloc( clone->meshes[ i ].numTris * sizeof( md5Triangle_t ) );
		for ( j = 0; j < clone->meshes[ i ].numTris; j++ ) {
			clone->meshes[ i ].tri[ j ].vertIndex[ 0 ] = m->meshes[ i ].tri[ j ].vertIndex[ 0 ];
			clone->meshes[ i ].tri[ j ].vertIndex[ 1 ] = m->meshes[ i ].tri[ j ].vertIndex[ 1 ];
			clone->meshes[ i ].tri[ j ].vertIndex[ 2 ] = m->meshes[ i ].tri[ j ].vertIndex[ 2 ];
		}

		clone->meshes[ i ].vert = ( md5Vertex_t* ) malloc( clone->meshes[ i ].numVerts * sizeof( md5Vertex_t ) );
		for ( j = 0; j < clone->meshes[ i ].numVerts; j++ ) {
			clone->meshes[ i ].vert[ j ].countWeight = m->meshes[ i ].vert[ j ].countWeight;
			clone->meshes[ i ].vert[ j ].startWeight = m->meshes[ i ].vert[ j ].startWeight;

			vec2_equ( &clone->meshes[ i ].vert[ j ].st, &m->meshes[ i ].vert[ j ].st );
			vec3_equ( &clone->meshes[ i ].vert[ j ].finalPos, &m->meshes[ i ].vert[ j ].finalPos );
			vec3_equ( &clone->meshes[ i ].vert[ j ].normal, &m->meshes[ i ].vert[ j ].normal );
		}

		clone->meshes[ i ].weights = ( md5Weight_t* ) malloc( clone->meshes[ i ].numWeights * sizeof( md5Weight_t ) );
		for ( j = 0; j < clone->meshes[ i ].numWeights; j++ ) {
			clone->meshes[ i ].weights[ j ].bias = m->meshes[ i ].weights[ j ].bias;
			clone->meshes[ i ].weights[ j ].jointIndex = m->meshes[ i ].weights[ j ].jointIndex;
			vec3_equ( &clone->meshes[ i ].weights[ j ].pos, &m->meshes[ i ].weights[ j ].pos );
		}
	}
}

//----------------------------------------------
//	md5Model_load()
//----------------------------------------------
void	md5Model_load( md5Model_t* M, char* szFileName ) {
	FILE		*f;
	char		line[ 256 ];
	char		fname[ 128 ];
	int			meshIndex;
	md5Mesh_t*	pm;
	int			i, j, k;
	vsVec3		v;

	M->pAnim = ( md5Anim_t* ) 0;
	vec3_set( &M->directionVector, 0.0f, 0.0f, -1.0f );
	vec3_set( &M->position, 0.f, 0.f, 0.f );
	vec3_set( &M->scale, 0.15f, 0.15f, 0.15f );
	quat_from_rot( &M->rotation, -PI* 0.5f, 0.0f, 0.0f );
	

	if ( ( f = fopen( szFileName, "r" ) ) == 0 ) {
		debug_log( "could not open model file: %s", szFileName );
		return;
	}

	debug_log("LOADING MD5MESH FILE...\n-------------------------\n");


	while ( !feof( f ) )
	{
		fgets( line, 256, f );

		if ( strstr( line, "numJoints" ) ) {
			sscanf( line, "numJoints %d", &M->numJoints );
			M->joints		   = ( md5Joint_t* ) malloc( sizeof( md5Joint_t ) * M->numJoints );
			M->currentSkeleton = ( md5Joint_t* ) malloc( sizeof( md5Joint_t ) * M->numJoints );
		}
		else
		if ( strstr( line, "numMeshes" ) ) {
			sscanf( line, "numMeshes %d", &M->numMeshes );
			M->meshes = ( md5Mesh_t* ) malloc( sizeof( md5Mesh_t ) * M->numMeshes );
			meshIndex = 0;
		}
		else
		if ( strstr( line, "diffusemap" ) ) {
			sscanf( line, "diffusemap \"%s\"", fname );
			fname[ strlen(fname)-1 ] = '\0';
			M->diffuseMap = texture_load_bmp( fname );
		}
		else
		if ( strstr( line, "normalmap" ) ) {
			//memset( fname, 0, 128 );
			sscanf( line, "normalmap \"%s\"", fname );
			fname[ strlen(fname)-1 ] = '\0';
			M->normalMap = texture_load_bmp( fname );
		}
		else
		if ( strstr( line, "shader" ) ) {
			//memset( fname, 0, 128 );
			sscanf( line, "shader \"%s\"", fname );
			fname[ strlen(fname)-1 ] = '\0';
			shader_new( &M->shader, fname );
		}
		else
		if ( strstr( line, "joints {" ) ) {

			for ( j = 0; j < M->numJoints; j++ )
			{
				fgets( line, 256, f );
					sscanf( line, "	\"%s	%d ( %f %f %f ) ( %f %f %f )", 
						M->joints[ j ].name,
						&M->joints[ j ].parentIndex,
						&M->joints[ j ].pos.x,
						&M->joints[ j ].pos.y,
						&M->joints[ j ].pos.z,
						&M->joints[ j ].orient.x,
						&M->joints[ j ].orient.y,
						&M->joints[ j ].orient.z );

					M->joints[ j ].name[ strlen(M->joints[ j ].name)-1 ] = '\0';

					quat_calcW( &M->joints[ j ].orient );
					quat_normalize( &M->joints[ j ].orient );
			}
		}
		else
		if ( strstr( line, "mesh {" ) ) {

			pm = &M->meshes[ meshIndex ];
			pm->numVerts = -1;
			while ( !strstr( line, "}" ) ) 
			{
				fgets( line, 256, f );

				if ( strstr( line, "numverts" ) ) {
					sscanf( line, "	numverts %d", &pm->numVerts );
					pm->vert = ( md5Vertex_t* ) malloc( sizeof( md5Vertex_t ) * pm->numVerts );

					for ( i = 0; i < pm->numVerts; i++ ) 
					{
						fscanf( f, "	vert %d ( %f %f ) %d %d", 
							&j, 
							&pm->vert[ i ].st.x, 
							&pm->vert[ i ].st.y, 
							&pm->vert[ i ].startWeight, 
							&pm->vert[ i ].countWeight );
						pm->vert[ i ].st.y = 1.0f - pm->vert[ i ].st.y;
					}
				} 
				else
				if ( strstr( line, "numtris" ) ) {
					sscanf( line, "	numtris %d", &pm->numTris );
					pm->tri = ( md5Triangle_t* ) malloc( sizeof( md5Triangle_t ) * pm->numTris );

					for ( i = 0; i < pm->numTris; i++ ) 
					{
						fscanf( f, "	tri %d %d %d %d", 
							&j, 
							&pm->tri[ i ].vertIndex[ 0 ],
							&pm->tri[ i ].vertIndex[ 1 ],
							&pm->tri[ i ].vertIndex[ 2 ] );
					}
				} 
				else
				if ( strstr( line, "numweights" ) ) {
					sscanf( line, "	numweights %d", &pm->numWeights );
					pm->weights = ( md5Weight_t* ) malloc( sizeof( md5Weight_t ) * pm->numWeights );

					for ( i = 0; i < pm->numWeights; i++ ) 
					{
						fscanf( f, "	weight %d %d %f ( %f %f %f )", 
							&j, 
							&pm->weights[ i ].jointIndex,
							&pm->weights[ i ].bias,
							&pm->weights[ i ].pos.x,
							&pm->weights[ i ].pos.y,
							&pm->weights[ i ].pos.z );
					}
				} 
				
			}	
			meshIndex++;
		}
	}

	// setup bindpose skeleton ---------------------------------------------------------------
	md5Model_buildModel( M, M->joints );


	// calculate vertex normals --------------------------------------------------------------------------------------
	md5Model_calculateNormals( M );
	
	fclose( f );
}

//----------------------------------------------
//	md5Model_calculateNormals()
//----------------------------------------------
void	md5Model_calculateNormals( md5Model_t* m ) {
	int			i, j, k;
	vsVec3		v, p[ 3 ], q[ 2 ];
	vsVec3*		faceNormals;
	vsQuat		Q;
	md5Mesh_t*	pm;

	for ( i = 0; i < m->numMeshes; i++ ) {
		pm = &m->meshes[ i ];

		faceNormals = ( vsVec3* ) malloc( sizeof( vsVec3 ) * pm->numTris );

		// calculate face-normals
		for ( j = 0; j < pm->numTris; j++ ) {
			p[ 0 ] = pm->vert[ pm->tri[ j ].vertIndex[ 0 ] ].finalPos;
			p[ 1 ] = pm->vert[ pm->tri[ j ].vertIndex[ 1 ] ].finalPos;
			p[ 2 ] = pm->vert[ pm->tri[ j ].vertIndex[ 2 ] ].finalPos;

			vec3_equ( &q[ 0 ], &p[ 1 ] );
			vec3_equ( &q[ 1 ], &p[ 2 ] );
			vec3_sub( &q[ 0 ], &p[ 0 ] );
			vec3_sub( &q[ 1 ], &p[ 0 ] );

			vec3_cross( &q[ 0 ], &q[ 1 ] );jj

			vec3_equ( &faceNormals[ j ], &q[ 0 ] );
		}

		// calculate per-vertex normals
		for ( j = 0; j < pm->numVerts; j++ ) {

			vec3_set( &v, 0.f, 0.f, 0.f );
			for ( k = 0; k < pm->numTris; k++ ) {

				if ( j == pm->tri[ k ].vertIndex[ 0 ] 
				  || j == pm->tri[ k ].vertIndex[ 1 ] 
				  || j == pm->tri[ k ].vertIndex[ 2 ] )
					  vec3_add( &v, &faceNormals[ k ] );
			}

			vec3_equ( &pm->vert[ j ].normal, &v );

			/*for ( k = pm->vert[ j ].countWeight-1; k > 0 ; k-- ) {
				quat_equ( &Q, &m->joints[ pm->weights[ pm->vert[ j ].startWeight + k ].jointIndex ].orient );
				quat_invert( &Q );
				//quat_rotate_vec3( &Q, &pm->vert[ j ].normal );
			}*/
				
			vec3_normalize( &pm->vert[ j ].normal );
		}

		free( faceNormals );
	}
}

//----------------------------------------------
//	md5Model_buildBindposeSkeleton()
//----------------------------------------------
void	md5Model_buildModel( md5Model_t* M, md5Joint_t* skeleton ) {
	md5Mesh_t*	pm;
	md5Weight_t*pw;
	md5Joint_t* pj;
	vsVec3		v;
	int			i, j, k;
	
	for ( i = 0; i < M->numMeshes; i++ ) {
		pm = &M->meshes[ i ];

		for ( j = 0; j < pm->numVerts; j++ ) {
			vec3_set( &pm->vert[ j ].finalPos, 0.0f, 0.0f, 0.0f );

			for ( k = pm->vert[ j ].startWeight; 
				  k < pm->vert[ j ].startWeight + pm->vert[ j ].countWeight; 
				  k++ )
			{
				pw = &pm->weights[ k ];
				pj = &skeleton[ pw->jointIndex ];

				// finalPos += (jointPos + Q*weightPos) * weightBias
				vec3_equ( &v, &pw->pos );
				quat_rotate_vec3( &pj->orient, &v );
				vec3_add( &v, &pj->pos );
				vec3_mul( pw->bias, &v );

				vec3_add( &pm->vert[ j ].finalPos, &v );
				
				//quat_rotate_vec3( &pj->orient, &pm->vert[ j ].finalNormal );
			}

			pm->vert[ j ].finalPos.x *= M->scale.x;
			pm->vert[ j ].finalPos.y *= M->scale.y;
			pm->vert[ j ].finalPos.z *= M->scale.z;
			
			quat_rotate_vec3( &M->rotation, &pm->vert[ j ].finalPos );
			//quat_rotate_vec3( &M->rotation, &pm->vert[ j ].finalNormal );
			//vec3_normalize( &pm->vert[ j ].finalNormal );
			vec3_add( &pm->vert[ j ].finalPos, &M->position );
		}
	}

	//md5Model_calculateNormals( M );
}


//----------------------------------------------
//	md5Model_render()
//----------------------------------------------
void	md5Model_render( md5Model_t* m ) {
	int i, j;
	md5Mesh_t* pm;

	/*for ( i = 0; i < m->numMeshes; i++ ) {
		pm = &m->meshes[ i ];
		glColor3f( 0.0f, 1.0f, 0.0f );
		glBegin( GL_LINES );
		for ( j = 0; j < pm->numVerts; j++ ) {
			
				glVertex3fv( ( const float* )&pm->vert[ j ].finalPos );
				glVertex3f( pm->vert[ j ].finalPos.x + pm->vert[ j ].normal.x,
							pm->vert[ j ].finalPos.y + pm->vert[ j ].normal.y,
							pm->vert[ j ].finalPos.z + pm->vert[ j ].normal.z );

			
		}
		glEnd();
	}*/

	shader_use( m->shader );

	for ( i = 0; i < m->numMeshes; i++ ) {
		pm = &m->meshes[ i ];

		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_NORMAL_ARRAY );
	
		glVertexPointer( 3, GL_FLOAT, sizeof( md5Vertex_t ), pm->vert );
		glNormalPointer( GL_FLOAT, sizeof( md5Vertex_t ), &pm->vert[0].normal );

		glActiveTexture( GL_TEXTURE0 );
		glUniform1i( glGetUniformLocation( m->shader, "tex0" ), 0 );

		glBindTexture( GL_TEXTURE_2D, m->diffuseMap );
		glClientActiveTexture( GL_TEXTURE0 );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glTexCoordPointer( 2, GL_FLOAT, sizeof( md5Vertex_t ), &pm->vert[0].st );

		glActiveTexture( GL_TEXTURE1 );
		glUniform1i( glGetUniformLocation( m->shader, "tex0_n" ), 1 );
		glBindTexture( GL_TEXTURE_2D, m->normalMap );

		glDrawElements( GL_TRIANGLES, 3 * pm->numTris, GL_UNSIGNED_INT, ( void * ) pm->tri );

		//glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	
		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, 0 );
		glClientActiveTexture( GL_TEXTURE0 );
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );

		glActiveTexture( GL_TEXTURE1 );
		glBindTexture( GL_TEXTURE_2D, 0 );
		glActiveTexture( GL_TEXTURE2 );
		glBindTexture( GL_TEXTURE_2D, 0 );
		glActiveTexture( GL_TEXTURE3 );
		glBindTexture( GL_TEXTURE_2D, 0 );
		//glClientActiveTexture( GL_TEXTURE1 );
		//glDisableClientState( GL_TEXTURE_COORD_ARRAY );

		glDisableClientState( GL_NORMAL_ARRAY );
		glDisableClientState( GL_VERTEX_ARRAY );
	}

	shader_use( 0 );
}


//----------------------------------------------
//	md5Model_renderAnimated()
//----------------------------------------------
void	md5Model_renderAnimated( md5Model_t* m, float deltaTime ) {
	float frameTime;
	float time;
	int	  frame1, frame2;
	md5Anim_t *anim1, *anim2;
	float t;
	int	  i;

	if ( m->pAnim == 0 ) {
		md5Model_render( m );
		return;
	} 

	md5Model_buildModel( m, m->currentSkeleton );
	md5Model_render( m );

	m->currentTime += deltaTime;

	anim1 = anim2 = m->pAnim;

	if ( m->currentTime > m->pAnim->duration ) {
		if ( m->playOptions & ANIM_PLAY_LOOP )		
			m->currentTime = 0.0f;
		else {
			if ( m->pNextAnim != 0 ) {
				anim1 = m->pAnim = m->pNextAnim;
				m->pNextAnim = 0;
				m->playOptions = m->nextPlayOptions;
				m->nextPlayOptions = 0;
				m->currentTime = 0.0f;
			}
			else
				m->currentTime = m->pAnim->duration;
		}
	}

	// frame1 * frameTime <= currentTime <= frame2 * frameTime
	time = ( m->currentTime  ) * ( float )anim1->frameRate;
	frame1 = ( int ) floorf( time );
	frame2 = ( int ) ceilf( time );

	t = time - ( float )frame1;

	if ( frame2 >= anim1->numFrames )
		if ( m->playOptions & ANIM_PLAY_LOOP )
			frame2 = 0;
		else
			frame2 = anim1->numFrames - 1;

	if ( frame1 >= anim1->numFrames )
		if ( m->playOptions & ANIM_PLAY_LOOP )
			frame1 = 0;
		else
			frame1 = anim1->numFrames - 1;

	m->currentFrame = frame2;


	/*font_printQ( gameLocal.font1, -0.9f, 0.55f, 0, "frameRate: %d", m->pAnim->frameRate );
	font_printQ( gameLocal.font1, -0.9f, 0.50f, 0, "Current Frame: %d", m->currentFrame );
	font_printQ( gameLocal.font1, -0.9f, 0.45f, 0, "Current Time: %f", m->currentTime );
	font_printQ( gameLocal.font1, -0.9f, 0.40f, 0, "t: %f", t );
	*/

	// interpolate skeleton
	for ( i = 0; i < m->numJoints; i++ ) {
		vec3_lerp(  &m->currentSkeleton[ i ].pos,    &anim1->frames[ frame1 ].skeleton[ i ].pos,    &anim1->frames[ frame2 ].skeleton[ i ].pos,    t );
		quat_slerp( &m->currentSkeleton[ i ].orient, &anim1->frames[ frame1 ].skeleton[ i ].orient, &anim1->frames[ frame2 ].skeleton[ i ].orient, t );
	}
}


//----------------------------------------------
//	md5Model_setAnimation()
//		Parameter "repeat" can be 1 or 0.
//----------------------------------------------
void	md5Model_setAnimation( md5Model_t* m, md5Anim_t* anim, int playOptions ) {
	int i = 0;
	//fixme
	if ( playOptions & ANIM_PLAY_NOW  || m->pAnim == 0 ) {
		m->pAnim = anim;
		m->pNextAnim = 0;
		m->playOptions = playOptions;
		m->nextPlayOptions = 0;
		m->currentTime = 0.0f;
		m->currentFrame = 0;
	} else {
			m->pNextAnim = anim;
			m->nextPlayOptions = playOptions;
	}

	/*if ( anim )
		for ( i = 0; i < m->numJoints; i++ ) {
			memcpy( &m->currentSkeleton[ i ], &m->pAnim->frames[ 0 ].skeleton[ i ], sizeof( md5Joint_t ) );
		}*/
}


//----------------------------------------------
//	md5Model_translate()
//----------------------------------------------
void	md5Model_setPosition( md5Model_t* m, vsVec3* offset ) {
	vec3_equ( &m->position, offset );
}


//----------------------------------------------
//	md5Model_setRotation()
//----------------------------------------------
void	md5Model_setRotation( md5Model_t* m, vsVec3* eulerAnglesRad ) {
	vsQuat base, q;
	quat_from_rot_vec( &q, eulerAnglesRad );
	quat_normalize( &q );

	quat_from_rot( &base, -PI* 0.5f, 0.0f, -PI*0.5f );
	quat_equ( &m->rotation, &base );
	quat_mul( &m->rotation, &q );
	//quat_equ( &m->rotation, &q );
	quat_normalize( &m->rotation );

	/*vec3_set( &m->directionVector, 0.0f, 0.0f, -1.0f );
	quat_rotate_vec3( &m->rotation, &m->directionVector );
	vec3_normalize( &m->directionVector );*/
}

//----------------------------------------------
//	md5Model_setRotationQuat()
//----------------------------------------------
void	md5Model_setRotationQuat( md5Model_t* m, vsQuat* quat ) {
	vsQuat base;

	quat_from_rot( &base, -PI* 0.5f, 0.0f, -PI*0.5f );
	quat_equ( &m->rotation, &base );
	quat_mul( &m->rotation, quat );
	quat_normalize( &m->rotation );
}


//----------------------------------------------
//	md5Model_scale()
//----------------------------------------------
void	md5Model_scale( md5Model_t* m, vsVec3* scale ) {
	m->scale.x *= scale->x;
	m->scale.y *= scale->y;
	m->scale.z *= scale->z;
}


//----------------------------------------------
//	md5Model_destroy()
//----------------------------------------------
void	md5Model_destroy( md5Model_t* m ) {
	int i;
	
	for ( i = 0; i < m->numMeshes; i++ )
	{
		free( m->meshes[ i ].vert );
		free( m->meshes[ i ].tri );
		free( m->meshes[ i ].weights );
	}

	free( m->meshes );
	free( m->joints );

	if ( m->shader )
		shader_delete( m-> shader );
}

//----------------------------------------------
//	md5Model_setShader()
//----------------------------------------------
void	md5Model_setShader( md5Model_t* m, shader_t* shader ) {
	m->shader = *shader;
}

//----------------------------------------------
//	md5Model_convertToPointToModelSpace()
//----------------------------------------------
void	md5Model_convertPointToModelSpace( md5Model_t * m, vsVec3* point ) {
	point->x *= m->scale.x;
	point->y *= m->scale.y;
	point->z *= m->scale.z;

	quat_rotate_vec3( &m->rotation, point );
	vec3_add( point, &m->position );
}


//----------------------------------------------
//	md5Anim_load()
//----------------------------------------------
void	md5Anim_load( md5Anim_t* a, char* szFileName ) {
	FILE		*f;
	char		line[ 256 ];
	int			i, Fi = 0;	// Fi: current frame index

	if ( ( f = fopen( szFileName, "r" ) ) == 0 ) {
		debug_log( "could not open anim file: %s", szFileName );
		return;
	}

	debug_log("LOADING MD5ANIM FILE...\n-------------------------\n");

	while ( !feof( f ) )
	{
		fgets( line, 256, f );

		if ( strstr( line, "numJoints" ) ) {
			sscanf( line, "numJoints %d", &a->numJoints );
			a->jointInfos = ( md5JointInfo_t* ) malloc( sizeof( md5JointInfo_t ) * a->numJoints );
			a->baseFrame  = ( md5Joint_t* )		malloc( sizeof( md5Joint_t )	 * a->numJoints );
		}
		else
		if ( strstr( line, "numFrames" ) ) {
			sscanf( line, "numFrames %d", &a->numFrames );
			a->frames = ( md5Frame_t* ) malloc( sizeof( md5Frame_t ) * a->numFrames );
		}
		else
		if ( strstr( line, "frameRate" ) ) {
			sscanf( line, "frameRate %d", &a->frameRate );
		}
		else
		if ( strstr( line, "numAnimatedComponents" ) ) {
			sscanf( line, "numAnimatedComponents %d", &a->numAnimatedComponents );
		}
		else
		if ( strstr( line, "hierarchy {" ) ) {
			for ( i = 0; i < a->numJoints; i++ ) {
				fgets( line, 256, f );
				sscanf( line, "	\"%s %d %d %d", 
					&a->jointInfos[ i ].name, 
					&a->jointInfos[ i ].parentIndex,
					&a->jointInfos[ i ].flags,
					&a->jointInfos[ i ].startIndex );
				a->jointInfos[ i ].name[ strlen( a->jointInfos[ i ].name ) - 1 ] = '\0';	// deleting " at the end;
			}
		}
		else
		if ( strstr( line, "bounds {" ) ) {
			for ( i = 0; i < a->numFrames; i++ ) {
				fgets( line, 256, f );
				sscanf( line, " ( %f %f %f ) ( %f %f %f )", 
					&a->frames[ i ].boundingBox[ 0 ].x, 
					&a->frames[ i ].boundingBox[ 0 ].y, 
					&a->frames[ i ].boundingBox[ 0 ].z, 
					&a->frames[ i ].boundingBox[ 1 ].x, 
					&a->frames[ i ].boundingBox[ 1 ].y, 
					&a->frames[ i ].boundingBox[ 1 ].z );

			}
		}
		else
		if ( strstr( line, "baseframe" ) ) {
			for ( i = 0; i < a->numJoints; i++ ) {
				fgets( line, 256, f );
				sscanf( line, " ( %f %f %f ) ( %f %f %f )", 
					&a->baseFrame[ i ].pos.x, 
					&a->baseFrame[ i ].pos.y, 
					&a->baseFrame[ i ].pos.z, 
					&a->baseFrame[ i ].orient.x, 
					&a->baseFrame[ i ].orient.y, 
					&a->baseFrame[ i ].orient.z );
			}
		}
		else
		if ( strstr( line, "frame" ) ) {
			sscanf_s( line, "frame %d {", &Fi );
			a->frames[ Fi ].components = ( float* ) malloc( sizeof( float ) * a->numAnimatedComponents );
			for ( i = 0; i < a->numAnimatedComponents; i++ ) {
				fscanf( f, "%f", &a->frames[ Fi ].components[ i ] );
			}
			md5Anim_buildFrameSkeleton( a, Fi );
		}
	}

	a->duration = ( 1.0f / ( float ) a->frameRate ) * a->numFrames;
}


//----------------------------------------------
//	md5Anim_destroy()
//----------------------------------------------
void	md5Anim_destroy( md5Anim_t* a ) {
	int i;
	if ( a->numFrames > 0 ) {
		for ( i = 0; i < a->numFrames; i++ ) {
			free( a->frames[ i ].skeleton );
		}

		free( a->frames );
		free( a->baseFrame );
		free( a->jointInfos );
	}
}

//----------------------------------------------
//	md5Anim_buildFrameSkeleton()
//----------------------------------------------
void	md5Anim_buildFrameSkeleton( md5Anim_t* anim, int frameNum ) {
	int i, j;
	md5Frame_t *  pf = &anim->frames[ frameNum ];
	md5Joint_t *  pj;
	vsQuat		  q;

	pf->skeleton = ( md5Joint_t* ) malloc( sizeof( md5Joint_t ) * anim->numJoints );

	for ( i = 0; i < anim->numJoints; i++ ) {
		 
		 pj = &pf->skeleton[ i ];

		 vec3_equ( &pj->pos, &anim->baseFrame[ i ].pos );
		 quat_equ( &pj->orient, &anim->baseFrame[ i ].orient );
		 pf->skeleton[ i ].parentIndex = anim->jointInfos[ i ].parentIndex;

		 j = anim->jointInfos[ i ].startIndex;

		 if ( anim->jointInfos[ i ].flags & 1 )
			 pj->pos.x = pf->components[ j++ ];

		 if ( anim->jointInfos[ i ].flags & 2 )
			 pj->pos.y = pf->components[ j++ ];

		 if ( anim->jointInfos[ i ].flags & 4 )
			 pj->pos.z = pf->components[ j++ ];

		 if ( anim->jointInfos[ i ].flags & 8 )
			 pj->orient.x = pf->components[ j++ ];

		 if ( anim->jointInfos[ i ].flags & 16 )
			 pj->orient.y = pf->components[ j++ ];

		 if ( anim->jointInfos[ i ].flags & 32 )
			 pj->orient.z = pf->components[ j++ ];

		 quat_calcW( &pf->skeleton[ i ].orient );

		 // if has a parent, transform joint by parent's transformation
		 if ( pj->parentIndex != -1 ) {
			 quat_rotate_vec3( &pf->skeleton[ pj->parentIndex ].orient, &pj->pos );
			 vec3_add( &pj->pos, &pf->skeleton[ pj->parentIndex ].pos );

			 quat_equ( &q, &pf->skeleton[ pj->parentIndex ].orient );
			 quat_mul( &q, &pj->orient );
			 quat_equ( &pj->orient, &q );
			 quat_normalize( &pj->orient );
		 }
	}
}

//----------------------------------------
//	md5Anim_getMovementDelta()
//----------------------------------------
void	md5Anim_getMovementDelta( md5Model_t* m, md5Anim_t* a, float time, vsVec3* delta ) {
	float ftime = time * a->frameRate;
	int frame1 = ( int ) floorf ( ftime ) % a->numFrames;
	int frame2 = ( frame1 + 1 ) % a->numFrames;

	if ( frame2 >= a->numFrames ) {
		//vec3_set( delta, 0.f, 0.f, 0.f );
		//return;
		frame2 = 0;
	}

	//if ( frame1 >= a->numFrames ) 
		//frame1 = 0;

	//if ( ftime >= a->duration * a->frameRate )
		//ftime = 0.0f; //a->duration * a->frameRate;
		
	if ( a->jointInfos[ 0 ].flags == 0 ) {
		vec3_set( delta, 0.f, 0.f, 0.f );
		return;
	}

	
	vec3_lerp( delta, &a->frames[ frame1 ].skeleton[ 0 ].pos, &a->frames[ frame2 ].skeleton[ 0 ].pos, ftime- ( float )frame1 );
	vec3_sub( delta, &a->frames[ 0 ].skeleton[ 0 ].pos );

	md5Model_convertPointToModelSpace( m, delta );
	vec3_sub( delta, &m->position );
}



/*


	

*/

	
	