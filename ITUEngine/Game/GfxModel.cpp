#include <Game/GfxModel.hpp>
#include <iostream>
#include <Managers/MediaManager.hpp>

GfxModel::GfxModel()
{
	numMeshes = 0;
	mMeshes = NULL;
	numMaterials = 0;
	mMaterials = NULL;
	numTriangles = 0;
	mTriangles = NULL;
	numVertices = 0;
	mVertices = NULL;
}

GfxModel::~GfxModel()
{	
	int i;
	for ( i = 0; i < numMeshes; i++ )
		delete[] mMeshes[i].triangleIndices;
	for ( i = 0; i < numMaterials; i++ )
		delete[] mMaterials[i].textureFileName;

	numMeshes = 0;
	if ( mMeshes != NULL )
	{
		delete[] mMeshes;
		mMeshes = NULL;
	}

	numMaterials = 0;
	if ( mMaterials != NULL )
	{
		delete[] mMaterials;
		mMaterials = NULL;
	}

	numTriangles = 0;
	if ( mTriangles != NULL )
	{
		delete[] mTriangles;
		mTriangles = NULL;
	}

	numVertices = 0;
	if ( mVertices != NULL )
	{
		delete[] mVertices;
		mVertices = NULL;
	}
}

/*
void GfxModel::CreateVBO()
{
	GLfloat *verts = new GLfloat[vertices->size()*3];
	GLfloat *color = new GLfloat[material->colors->size()*3];
	GLfloat *uvs = new GLfloat[material->uv->size()*2];

	auto vertex_iter = vertices->begin();
	auto color_iter = material->colors->begin();
	auto uv_iter = material->uv->begin();

	int i = 0;

	while (vertex_iter != vertices->end())
	{
		verts[i] = vertex_iter->x();
		verts[i+1] = vertex_iter->y();
		verts[i+2] = vertex_iter->z();

		vertex_iter++;
		i += 3;
	}

	i = 0;

	while (color_iter != material->colors->end())
	{
		color[i] = color_iter->x();
		color[i+1] = color_iter->y();
		color[i+2] = color_iter->z();

		color_iter++;
		i += 3;
	}

	i = 0;

	while (uv_iter != material->uv->end())
	{
		uvs[i] = uv_iter->u;
		uvs[i+1] = uv_iter->v;

		uv_iter++;
		i += 2;
	}

	glGenBuffersARB(1, &vboId);																				//Generate VBO and get associated ID
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);															//Bind the VBO in order to use it
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, vertices->size()*3*sizeof(float), verts, GL_STATIC_DRAW_ARB);		//Upload data to the VBO


	glGenBuffersARB(1, &cboId);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, cboId);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, material->colors->size()*3*sizeof(float), color, GL_STATIC_DRAW_ARB);

	if(material->texture != NULL)
	{
		// Generate And Bind The Texture Coordinate Buffer
		glGenBuffersARB( 1, &tboId );							// Get A Valid Name
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, tboId);			// Bind The Buffer

		// Load The Data
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, vertices->size()*2*sizeof(float), uvs, GL_STATIC_DRAW_ARB );
	}


	delete [] verts;
	delete [] color;
}
*/


void GfxModel::draw()
{
	GLboolean texEnabled = glIsEnabled( GL_TEXTURE_2D );
	
	// Draw By Group
	for ( int i = 0; i < numMeshes; i++ )
	{		
		int materialIndex = mMeshes[i].materialIndex;
		
		if ( materialIndex >= 0 )
		{
			glMaterialfv( GL_FRONT, GL_AMBIENT, mMaterials[materialIndex].ambient );
			glMaterialfv( GL_FRONT, GL_DIFFUSE, mMaterials[materialIndex].diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, mMaterials[materialIndex].specular );
			glMaterialfv( GL_FRONT, GL_EMISSION, mMaterials[materialIndex].emissive );
			glMaterialf( GL_FRONT, GL_SHININESS, mMaterials[materialIndex].shininess );

			if ( mMaterials[materialIndex].mTexture > 0 )
			{
				glBindTexture( GL_TEXTURE_2D, mMaterials[materialIndex].mTexture );
				glEnable( GL_TEXTURE_2D );
			}
			else
			{
				glDisable( GL_TEXTURE_2D );
			}
		}
		else
		{
			glDisable( GL_TEXTURE_2D );
		}
		glBegin( GL_TRIANGLES );
		{
			for ( int j = 0; j < mMeshes[i].numTriangles; j++ )
			{
				int triangleIndex = mMeshes[i].triangleIndices[j];
				const Triangle* pTri = &mTriangles[triangleIndex];
				for ( int k = 0; k < 3; k++ )
				{
					int index = pTri->verticeIndices[k];

					glNormal3fv( pTri->vertexNormals[k] );
					glTexCoord2f( pTri->sTex[k], pTri->tTex[k] );
					glVertex3fv( mVertices[index].location );
				}
			}
		}
		glEnd();
	}

	if ( texEnabled )
	{
        glEnable( GL_TEXTURE_2D );
	}
    else
	{
        glDisable( GL_TEXTURE_2D );
	}
}
