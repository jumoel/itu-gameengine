#include <SDL.h>
#include <SDL_opengl.h>
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
	int sdl_init_val = SDL_Init(SDL_INIT_VIDEO);
	ASSERT_MSG((sdl_init_val < 0), SDL_GetError());

	/* Fetch the video info */
	const SDL_VideoInfo *sdl_video_info = SDL_GetVideoInfo( );
	ASSERT_MSG(sdl_video_info, SDL_GetError());


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
}

void Window::InitOpenGL()
{
	/* Enable smooth shading */
	glShadeModel( GL_SMOOTH );

	/* Set the background Color*/
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	/* Depth buffer setup */
	glClearDepth( 1.0f );

	/* Enables Depth Testing */
	glEnable( GL_DEPTH_TEST );

	/* The Type Of Depth Test To Do */
	glDepthFunc( GL_LEQUAL );

	/* Really Nice Perspective Calculations */
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void Window::SetVideoMode()
{
	Surface = SDL_SetVideoMode(m_Width, m_Height, m_ColorDepth, m_VideoFlags);

	ASSERT_MSG(Surface, SDL_GetError());
}

void Window::Resize() const
{
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
	gluPerspective(45.0f, ratio, 0.0f, 100.0f);
}

void Window::Resize(int Width, int Height)
{
	SetHeight(Height);
	SetWidth(Width);

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