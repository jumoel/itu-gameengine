#include <Game\HUD.hpp>
#include "GL/glew.h"
#include "GL/wglew.h"
#include <Managers\MediaManager.hpp>


void HUD::draw()
{
	
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
	{	glLoadIdentity();
		glOrtho(0.0f,640.0f,480.0f,0.0f,-100.0f,100.0f);       
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		{
			glLoadIdentity();

			glBegin(GL_QUADS);
			{
				glColor3f(1.0f,1.0f,1.0f);
				glVertex3f( 20.0f, 460.0f,0.0f);
				glVertex3f(140.0f, 460.0f,0.0f);
				glVertex3f(140.0f,380.0f,0.0f);
				glVertex3f( 20.0f,380.0f,0.0f);
			}
			glEnd();
		}
		glPopMatrix();
	}
	glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	
}