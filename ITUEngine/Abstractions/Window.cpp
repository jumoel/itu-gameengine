#include <SDL.h>
//#include <SDL_opengl.h>
#include <GL/glew.h>
#include <Abstractions/Window.hpp>
#include <Assertion.hpp>

void Window::StartUp()
{
	m_Width = 640;
	m_Height = 480;
	m_ColorDepth = 16;

	//////////////////////////////////////////////////////////////////////////

	InitSDL();

	SetVideoMode();

	InitOpenGL();

	Resize();
}

void Window::ShutDown()
{
	SDL_Quit();
}

void Window::InitSDL()
{
	std::string errormessage;

	int sdl_init_val = SDL_Init(SDL_INIT_VIDEO);
	errormessage = SDL_GetError();
	ASSERT_MSG(sdl_init_val == 0, errormessage.c_str());

	/* Fetch the video info */
	const SDL_VideoInfo *sdl_video_info = SDL_GetVideoInfo();
	errormessage = SDL_GetError();
	ASSERT_MSG(sdl_video_info, errormessage.c_str());

	/* the flags to pass to SDL_SetVideoMode */
	m_VideoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
	m_VideoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
	m_VideoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */
	m_VideoFlags |= SDL_RESIZABLE;       /* Enable window resizing */

	/* This checks to see if surfaces can be stored in memory */
	if (sdl_video_info->hw_available)
	{
		m_VideoFlags |= SDL_HWSURFACE;
	}
	else
	{
		m_VideoFlags |= SDL_SWSURFACE;
	}

	/* This checks if hardware blits can be done */
	if (sdl_video_info->blit_hw)
	{
		m_VideoFlags |= SDL_HWACCEL;
	}

	/* Sets up OpenGL double buffering */
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Disably VSync
	SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 0);
}

void Window::InitOpenGL()
{
	glewExperimental = GL_TRUE;
	GLenum glew_status = glewInit();
	std::string errormessage = (const char*) glewGetErrorString(glew_status);
	ASSERT_MSG(glew_status == GLEW_OK, errormessage.c_str());
}

void Window::SetVideoMode()
{
	Surface = SDL_SetVideoMode(m_Width, m_Height, m_ColorDepth, m_VideoFlags);

	ASSERT_MSG(Surface, SDL_GetError());
}

void Window::Resize()
{
	SetVideoMode();

	int height = m_Height;
	int width = m_Width;

	GLfloat ratio;
	if (height == 0)
	{
		height = 1;
	}

	ratio = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, ratio, 5.0f, 100.0f);
}

void Window::SetWindowTitle(char *Title)
{
	SDL_WM_SetCaption(Title, "");
}

void Window::Resize(int Width, int Height)
{
	SetWidth(Width);
	SetHeight(Height);

	Resize();
}



void Window::SetHeight(int Height)
{
	m_Height = Height;
}

int Window::Height() const
{
	return m_Height;
}

int Window::Width() const
{
	return m_Width;
}

void Window::SetWidth(int Width)
{
	m_Width = Width;
}