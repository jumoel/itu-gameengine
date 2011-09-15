/*
 * This is template created for Game Engines 2011 based on the SDL examples from http://nehe.gamedev.net/
 */

#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_opengl.h"

#include "SceneData.h"

/* screen width, height, and bit depth */
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP     16

/* Define our booleans */
#define TRUE  1
#define FALSE 0

Uint32 start;
Uint32 last;
float degree = 0.0f;

#define DEGREES_PER_MS (180.0f / 1000.0f)
#define SPEED (2.0f / 1000.0f)

bool qd, wd, ed;
bool ad,sd, dd;
bool zd, xd, cd;

GLfloat x, y, z;

SDL_Surface *surface;

/* function to release/destroy our resources and restoring the old desktop */
void Quit( int returnCode )
{
	/* clean up the window */
	SDL_Quit( );

	/* and exit appropriately */
	exit( returnCode );
}

/* function to reset our viewport after a window resize */
int resizeWindow( int width, int height )
{
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

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	return( TRUE );
}

/* function to handle key press events */
void handleKeyPress( SDL_keysym *keysym, Uint8 eventtype )
{
	SDLKey key = keysym->sym;
	
	qd = (eventtype == SDL_KEYDOWN) && (key == SDLK_q);	
	wd = (eventtype == SDL_KEYDOWN) && (key == SDLK_w);	
	ed = (eventtype == SDL_KEYDOWN) && (key == SDLK_e);
	
	ad = (eventtype == SDL_KEYDOWN) && (key == SDLK_a);	
	sd = (eventtype == SDL_KEYDOWN) && (key == SDLK_s);	
	dd = (eventtype == SDL_KEYDOWN) && (key == SDLK_d);
	
	zd = (eventtype == SDL_KEYDOWN) && (key == SDLK_z);	
	xd = (eventtype == SDL_KEYDOWN) && (key == SDLK_x);	
	cd = (eventtype == SDL_KEYDOWN) && (key == SDLK_c);
	
	return;
}

/* general OpenGL initialization function */
int initGL( GLvoid )
{
	start = SDL_GetTicks();
	last = SDL_GetTicks();

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

	return( TRUE );
}

/* Here goes our drawing code */
int drawGLScene( GLvoid )
{
	Uint32 now = SDL_GetTicks();

	Uint32 diff = now - last;

	last = now;

	degree += DEGREES_PER_MS * (float)diff;

	if (degree > 360.f)
	{
		degree = 0.0f;
	}

	if (zd) { y -= (float)diff * SPEED; }
	if (cd) { y += (float)diff * SPEED; }
	if (wd) { z += (float)diff * SPEED; }
	if (sd) { z -= (float)diff * SPEED; }
	if (ad) { x += (float)diff * SPEED; }
	if (dd) { x -= (float)diff * SPEED; }

	/* Clear The Screen And The Depth Buffer */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glLoadIdentity();

	glTranslatef(x, y, z);

	glTranslatef(0.0f, 0.0f, -12.0f);
	
	/* HERE you should put your code in order to do render something on the screen, use lighting, modify the camera position etc... */
	glRotatef(degree, 0.0f, 1.0f, 0.0f);
	
	glBegin(GL_TRIANGLE_FAN);

    glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0, 2, 0);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1, 0, -1);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1, 0, -1);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1, 0, 1);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1, 0, 1);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1, 0, -1);

    glEnd();

	/* Draw it to the screen */
	SDL_GL_SwapBuffers( );

	return( TRUE );
}

int main( int argc, char **argv )
{
	/* Flags to pass to SDL_SetVideoMode */
	int videoFlags;
	/* main loop variable */
	int done = FALSE;
	/* used to collect events */
	SDL_Event event;
	/* this holds some info about our display */
	const SDL_VideoInfo *videoInfo;


	/* initialize SDL */
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		fprintf( stderr, "Video initialization failed: %s\n",
			 SDL_GetError( ) );
		Quit( 1 );
	}

	/* Fetch the video info */
	videoInfo = SDL_GetVideoInfo( );

	if ( !videoInfo )
	{
		fprintf( stderr, "Video query failed: %s\n",
			 SDL_GetError( ) );
		Quit( 1 );
	}

	/* the flags to pass to SDL_SetVideoMode */
	videoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
	videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
	videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */
	videoFlags |= SDL_RESIZABLE;       /* Enable window resizing */

	/* This checks to see if surfaces can be stored in memory */
	if ( videoInfo->hw_available )
	videoFlags |= SDL_HWSURFACE;
	else
	videoFlags |= SDL_SWSURFACE;

	/* This checks if hardware blits can be done */
	if ( videoInfo->blit_hw )
	videoFlags |= SDL_HWACCEL;

	/* Sets up OpenGL double buffering */
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	/* get a SDL surface */
	surface = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
				videoFlags );

	/* Verify there is a surface */
	if ( !surface )
	{
		fprintf( stderr,  "Video mode set failed: %s\n", SDL_GetError( ) );
		Quit( 1 );
	}

	/* initialize OpenGL */
	initGL( );

	/* resize the initial window */
	resizeWindow( SCREEN_WIDTH, SCREEN_HEIGHT );

	/* wait for events */ 
	while ( !done )
	{
		/* handle the events in the queue */

		while ( SDL_PollEvent( &event ) )
		{
			switch( event.type )
			{
			  
			case SDL_VIDEORESIZE:
				/* handle resize event */
				surface = SDL_SetVideoMode( event.resize.w,
							event.resize.h,
							16, videoFlags );
				if ( !surface )
				{
					fprintf( stderr, "Could not get a surface after resize: %s\n", SDL_GetError( ) );
					Quit( 1 );
				}
				resizeWindow( event.resize.w, event.resize.h );
				break;

			case SDL_QUIT:
				/* handle quit requests */
				done = TRUE;
				break;

			case SDL_KEYDOWN:
				handleKeyPress(&event.key.keysym, event.type);
				break;

			case SDL_KEYUP:
				handleKeyPress(&event.key.keysym, event.type);
				break;

			default:
				break;
			}
		}
		
		/* draw the scene */
		drawGLScene( );
	}

	/* clean ourselves up and exit */
	Quit( 0 );

	/* Should never get here */
	return( 0 );
}