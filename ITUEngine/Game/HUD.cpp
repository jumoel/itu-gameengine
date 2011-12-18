#include <Game\HUD.hpp>
#include "GL/glew.h"
#include "GL/wglew.h"

void HUD::draw()
{
	
	glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0,640,480,0,-5,1);       
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


	/* draw HUD */
	
	glBegin(GL_QUADS);
		glColor3f(1,0,0);
		glVertex3f( 0.5, 0.1,-1.0);
		glVertex3f(-0.0, 0.1,-1.0);
		glVertex3f(-0.0,-0.0,-1.0);
		glVertex3f( 0.5,-0.0,-1.0);
	glEnd();
	
	glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
	
}