#include <Subsystems/Graphics/GraphicsSystem.hpp>
#include <Managers/MediaManager.hpp>
#include <Game/SceneData.hpp>
#include <stdio.h>
#include <vector>
#include <Assertion.hpp>
#include <Utils/ShaderUtils.hpp>

void GraphicsSystem::StartUp()
{
	// Some lines below need to be commented out to work for Emil, QQ. Need to research!

	this->InitOpenGL();
	SINGLETONINSTANCE(MediaManager)->StartUp();

	m_SceneGraph = createGraph();
	m_VectorList = new std::vector<Vector3f>();

	AddToVBORecursive(m_SceneGraph->RootNode, m_VectorList);

	//std::cout << "Size: " << m_VectorList->size() << std::endl;

	auto verts = new std::vector<float>();

	//m_VectorList->push_back(Vector3f(0.75f, 0.75f, 0.0f)); 
	
	
		
	verts->push_back( 0.75f); verts->push_back( 0.75f); verts->push_back(0.0f); verts->push_back(1.0f);
	verts->push_back( 0.75f); verts->push_back(-0.75f); verts->push_back(0.0f); verts->push_back(1.0f);
	verts->push_back(-0.75f); verts->push_back(-0.75f); verts->push_back(0.0f); verts->push_back(1.0f);
	

	for (auto it = m_VectorList->begin(); it != m_VectorList->end(); ++it)
	{
		verts->push_back(it->x());
		//std::cout << it->x() << std::endl;
		verts->push_back(it->y());
		//std::cout << it->y() << std::endl;
		verts->push_back(it->z());
		//std::cout << it->z() << std::endl;
	}
	
	

	// Setup passthrough shaders
	const std::string strVertexShader(
		"#version 330\n"
		"layout(location = 0) in vec4 position;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = position;\n"
		"}\n"
	);

	const std::string strFragmentShader(
		"#version 330\n"
		"out vec4 outputColor;\n"
		"void main()\n"
		"{\n"
		"   outputColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
		"}\n"
	);

	std::vector<GLuint> shaderList;

    shaderList.push_back(ShaderUtils::CreateShader(GL_VERTEX_SHADER, strVertexShader));
    shaderList.push_back(ShaderUtils::CreateShader(GL_FRAGMENT_SHADER, strFragmentShader));

    theProgram = ShaderUtils::CreateProgram(shaderList);

    std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
	// End shader setup

	//glEnableClientState(GL_VERTEX_ARRAY);
	if(verts->size() > 0)
	{
		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, verts->size() * sizeof(float), &verts->front(), GL_STATIC_DRAW_ARB);
		
	}
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	//glVertexPointer(3, GL_FLOAT, 0, (char *) NULL);

	//glDrawArrays( GL_TRIANGLES, 0, verts->size()/3 );
	//glDisableClientState( GL_VERTEX_ARRAY );

	glGenVertexArrays(1, &m_VertexArrayObject);
	glBindVertexArray(m_VertexArrayObject);
}

void GraphicsSystem::InitOpenGL()
{
	/* Enable smooth shading */
	// glShadeModel( GL_SMOOTH );

	/* Set the backgroundColor*/
	// glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	/* Depth buffer setup */
	// glClearDepth( 1.0f );

	// glEnable( GL_DEPTH_TEST );

	// glDepthFunc( GL_LEQUAL );

	/* Really Nice Perspective Calculations */
	// glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void GraphicsSystem::AddToVBORecursive(Object *obj, std::vector<Vector3f> *vectors)
{
	int k = 0;
	std::vector<Vector3f> *v_list = new vector<Vector3f>();
	
	// By Group
	if(obj->gfx->numMeshes > 0)
	{
		for ( int i = 0; i < obj->gfx->numMeshes; i++ )
		{		
			/*int materialIndex = obj->gfx->mMeshes[i].materialIndex;
		
			if ( materialIndex >= 0 )
			{
				glMaterialfv( GL_FRONT, GL_AMBIENT, obj->gfx->mMaterials[materialIndex].ambient );
				glMaterialfv( GL_FRONT, GL_DIFFUSE, obj->gfx->mMaterials[materialIndex].diffuse );
				glMaterialfv( GL_FRONT, GL_SPECULAR, obj->gfx->mMaterials[materialIndex].specular );
				glMaterialfv( GL_FRONT, GL_EMISSION, obj->gfx->mMaterials[materialIndex].emissive );
				glMaterialf( GL_FRONT, GL_SHININESS, obj->gfx->mMaterials[materialIndex].shininess );

				if ( obj->gfx->mMaterials[materialIndex].mTexture > 0 )
				{
					glBindTexture( GL_TEXTURE_2D, obj->gfx->mMaterials[materialIndex].mTexture );
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
			}*/

			for ( int j = 0; j < obj->gfx->mMeshes[i].numTriangles; j++ )
			{
				int triangleIndex = obj->gfx->mMeshes[i].triangleIndices[j];
				//const Triangle* pTri = &obj->gfx->mTriangles[triangleIndex];
				for ( int k = 0; k < 3; k++ )
				{
					int index =  obj->gfx->mTriangles[triangleIndex].verticeIndices[k]; //pTri->verticeIndices[k];
					//std::cout << "index: " << index << std::endl;
					//glNormal3fv( pTri->vertexNormals[k] );
					//glTexCoord2f( pTri->sTex[k], pTri->tTex[k] );
					//glVertex3fv( obj->gfx->mVertices[index].location );
					Vector3f temp;
					temp.SetX(obj->gfx->mVertices[index].location[0]);
					temp.SetY(obj->gfx->mVertices[index].location[1]);
					temp.SetZ(obj->gfx->mVertices[index].location[2]);
					temp = obj->transformation->MultiplyWithVector(temp);
					//std::cout << "Vertex.x: " << temp.x() << std::endl;
					//std::cout << "Vertex.y: " << temp.y() << std::endl;
					//std::cout << "Vertex.z: " << temp.z() << std::endl;
					v_list->push_back(temp);
				}
			}
		}
	}
	/*
	for(int i = 0; i < obj->gfx->numVertices; i++)
	{
		Vector3f temp;
		temp.SetX(obj->gfx->mVertices[k].location[0]);
		temp.SetY(obj->gfx->mVertices[k].location[1]);
		temp.SetZ(obj->gfx->mVertices[k].location[2]);
		v_list->push_back(temp);
	}
	*/
	for (auto it = v_list->begin(); it != v_list->end(); ++it)
	{
		vectors->push_back(*it);
	}

	for (auto it = obj->children->begin(); it != obj->children->end(); ++it)
	{
		AddToVBORecursive(&(*it), vectors);
	}
}

void GraphicsSystem::Render()
{

	// Clear the window
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear( GL_COLOR_BUFFER_BIT); //  | GL_DEPTH_BUFFER_BIT 
	
	Camera *CameraObject = m_SceneGraph->CameraObject;

	gluLookAt(
		CameraObject->Position.x(), CameraObject->Position.y(), CameraObject->Position.z(), 
		CameraObject->LookAt.x(), CameraObject->LookAt.y(), CameraObject->LookAt.z(), 
		CameraObject->Up.x(), CameraObject->Up.y(), CameraObject->Up.z()
		);
		
	glUseProgram(theProgram);

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glDisableVertexAttribArray(0);
	glUseProgram(0);

	SDL_GL_SwapBuffers();
}

void GraphicsSystem::ShutDown()
{

}