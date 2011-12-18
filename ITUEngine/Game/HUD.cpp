#include <Game\HUD.hpp>
#include "GL/glew.h"
#include "GL/wglew.h"
#include <Managers\MediaManager.hpp>


void HUD::draw()
{
	
	glDisable(GL_LIGHTING);
	//glDisable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0f,640.0f,480.0f,0.0f,-100.0f,100.0f);       
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();


		/* draw HUD */
			//SINGLETONINSTANCE( MediaManager )->Hud->Bind(GL_TEXTURE0);

			glBegin(GL_QUADS);
				
				glColor3f(1.0f,1.0f,1.0f);
				//glTexCoord2f (0.0, 0.0);
				glVertex3f( 0.0f, 480.0f,0.0f);
				//glTexCoord2f (1.0, 0.0);
				glVertex3f(640.0f, 480.0f,0.0f);
				//glTexCoord2f (1.0, 1.0);
				glVertex3f(640.0f,380.0f,0.0f);
				//glTexCoord2f (0.0, 1.0);
				glVertex3f( 0.0f,380.0f,0.0f);
				//glColor3f(1.0f,1.0f,1.0f);
			glEnd();
		glPopMatrix();
	glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	
}