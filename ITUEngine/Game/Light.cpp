#include <Game/Light.hpp>
#include <SDL.h>
#include <GL/glew.h>



Light::Light()
{
	for(int i = 0; i < 4; i++)
	{
		if(i < 3)
		{
			ambient[i] = 0.0f;
			diffuse[i] = 0.0f;
			specular[i] = 0.0f;
			emissive[i] = 0.0f;
			pos[i] = 0.0f;
		}
		else
		{
			ambient[i] = 1.0f;
			diffuse[i] = 1.0f;
			specular[i] = 1.0f;
			emissive[i] = 1.0f;
		}
	}

	inUse = false;
	lightIndex = 0;
}


Light::~Light()
{
}


void Light::enable(bool On)
{
	if(On)
	{
		switch ( lightIndex ) {
			case 0 :

				glEnable(GL_LIGHT0);

				break;

			case 1 : 
				glEnable(GL_LIGHT1);
				break;

			case 2 :
				glEnable(GL_LIGHT2);
				break;

			case 3 :
				glEnable(GL_LIGHT3);
				break;

			case 4 :
				glEnable(GL_LIGHT4);
				break;

			case 5 :
				glEnable(GL_LIGHT5);
				break;

			case 6 :
				glEnable(GL_LIGHT6);
				break;

			case 7 :
				glEnable(GL_LIGHT7);
				break;

		}
		inUse = true;
	}
	else
	{
		switch ( lightIndex ) {
			case 0 :
				glDisable(GL_LIGHT0);
				break;

			case 1 : 
				glDisable(GL_LIGHT1);
				break;

			case 2 :
				glDisable(GL_LIGHT2);
				break;

			case 3 :
				glDisable(GL_LIGHT3);
				break;

			case 4 :
				glDisable(GL_LIGHT4);
				break;

			case 5 :
				glDisable(GL_LIGHT5);
				break;

			case 6 :
				glDisable(GL_LIGHT6);
				break;

			case 7 :
				glDisable(GL_LIGHT7);
				break;

		}
		inUse = false;
	}
}

void Light::setPos(float x, float y, float z)
{
	pos[0] = x; pos[1] = y; pos[2] = z;

		switch ( lightIndex ) {
			case 0 :
				glLightfv(GL_LIGHT0, GL_POSITION, pos);
				break;

			case 1 : 
				glLightfv(GL_LIGHT1, GL_POSITION, pos);
				break;

			case 2 :
				glLightfv(GL_LIGHT2, GL_POSITION, pos);
				break;

			case 3 :
				glLightfv(GL_LIGHT3, GL_POSITION, pos);
				break;

			case 4 :
				glLightfv(GL_LIGHT4, GL_POSITION, pos);
				break;

			case 5 :
				glLightfv(GL_LIGHT5, GL_POSITION, pos);
				break;

			case 6 :
				glLightfv(GL_LIGHT6, GL_POSITION, pos);
				break;

			case 7 :
				glLightfv(GL_LIGHT7, GL_POSITION, pos);
				break;

		}

}
	


void Light::setAmbient(float r, float g, float b, float a)
{
	ambient[0] = r; ambient[1] = g; ambient[2] = b; ambient[3] = a;

		switch ( lightIndex ) {
			case 0 :
				glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
				break;

			case 1 : 
				glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
				break;

			case 2 :
				glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
				break;

			case 3 :
				glLightfv(GL_LIGHT3, GL_AMBIENT, ambient);
				break;

			case 4 :
				glLightfv(GL_LIGHT4, GL_AMBIENT, ambient);
				break;

			case 5 :
				glLightfv(GL_LIGHT5, GL_AMBIENT, ambient);
				break;

			case 6 :
				glLightfv(GL_LIGHT6, GL_AMBIENT, ambient);
				break;

			case 7 :
				glLightfv(GL_LIGHT7, GL_AMBIENT, ambient);
				break;

		}
}
	


void Light::setDiffuse(float r, float g, float b, float a)
{
	diffuse[0] = r; diffuse[1] = g; diffuse[2] = b; diffuse[3] = a;

		switch ( lightIndex ) {
			case 0 :
				glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
				break;

			case 1 : 
				glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
				break;

			case 2 :
				glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
				break;

			case 3 :
				glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
				break;

			case 4 :
				glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse);
				break;

			case 5 :
				glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuse);
				break;

			case 6 :
				glLightfv(GL_LIGHT6, GL_DIFFUSE, diffuse);
				break;

			case 7 :
				glLightfv(GL_LIGHT7, GL_DIFFUSE, diffuse);
				break;

		}
}



void Light::setSpecular(float r, float g, float b, float a)
{
	specular[0] = r; specular[1] = g; specular[2] = b; specular[3] = a;

		switch ( lightIndex ) {
			case 0 :
				glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
				break;

			case 1 : 
				glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
				break;

			case 2 :
				glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
				break;

			case 3 :
				glLightfv(GL_LIGHT3, GL_SPECULAR, specular);
				break;

			case 4 :
				glLightfv(GL_LIGHT4, GL_SPECULAR, specular);
				break;

			case 5 :
				glLightfv(GL_LIGHT5, GL_SPECULAR, specular);
				break;

			case 6 :
				glLightfv(GL_LIGHT6, GL_SPECULAR, specular);
				break;

			case 7 :
				glLightfv(GL_LIGHT7, GL_SPECULAR, specular);
				break;

		}
}

