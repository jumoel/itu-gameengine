#include <Subsystems/Graphics/GraphicsSystem.hpp>
#include <Game/SceneData.hpp>
#include <stdio.h>
#include <vector>
#include <Assertion.hpp>
#include <Utils/ShaderUtils.hpp>
#include <Globals.hpp>



void GraphicsSystem::StartUp()
{
	// Some lines below need to be commented out to work for Emil, QQ. Need to research!

	this->InitOpenGL();

	m_SceneGraph = createGraph();
	m_VectorList = new std::vector<Vector3f>();

	AddToVBORecursive(m_SceneGraph->RootNode, m_VectorList);

	auto verts = new std::vector<float>();

	verts->push_back( 0.75f); verts->push_back( 0.75f); verts->push_back(0.0f); verts->push_back(1.0f);
	verts->push_back( 0.75f); verts->push_back(-0.75f); verts->push_back(0.0f); verts->push_back(1.0f);
	verts->push_back(-0.75f); verts->push_back(-0.75f); verts->push_back(0.0f); verts->push_back(1.0f);

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

	// glEnableClientState(GL_VERTEX_ARRAY);

	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, verts->size() * sizeof(float), &verts->front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

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
	std::vector<Vector3f> *v_list = obj->gfx->vertices;
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
/*
	Camera *CameraObject = m_SceneGraph->CameraObject;

	gluLookAt(
		CameraObject->Position.x(), CameraObject->Position.y(), CameraObject->Position.z(), 
		CameraObject->LookAt.x(), CameraObject->LookAt.y(), CameraObject->LookAt.z(), 
		CameraObject->Up.x(), CameraObject->Up.y(), CameraObject->Up.z()
		);
*/
	glUseProgram(theProgram);

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glDisableVertexAttribArray(0);
	glUseProgram(0);

	SDL_WM_GrabInput(SDL_GrabMode::SDL_GRAB_ON);
	SDL_ShowCursor(0);
	/* draw HUD */
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,640,480,0,-5,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*
	glBegin(GL_QUADS);
		glColor3f(1,0,0);
		glVertex3f( 0.5, 0.1,-1.0);
		glVertex3f(-0.0, 0.1,-1.0);
		glVertex3f(-0.0,-0.0,-1.0);
		glVertex3f( 0.5,-0.0,-1.0);
	glEnd();
	*/
	float mousex = g_Engine->mousex;
	float mousey = g_Engine->mousey;
	float mouseW = 10.0;
	float mouseH = 10.0;
	float offset = 0.0;


	float x1 = mousex;
	float y1 = mousey;
	float x2 = mousex+mouseW;
	float y2 = mousey+mouseH;



	
	
	std::cout<<x2<<","<<y2<<std::endl;
	/* draw Mouse */
	glBegin(GL_QUADS);
		glColor3f(1,0,0);
		glVertex3f(x2,y1,1.0);
		glVertex3f(x1,y1,1.0);
		glVertex3f(x1,y2,1.0);
		glVertex3f(x2,y2,1.0);
	glEnd();
	
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	SDL_GL_SwapBuffers();
}

void GraphicsSystem::ShutDown()
{

}