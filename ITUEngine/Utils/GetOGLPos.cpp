#include <Utils/GetOGLPos.hpp>
#include "GL/glew.h"
#include "GL/wglew.h"
#include <Math/Vector3f.hpp>
#include <stdio.h>
#include <Managers/InputManager.hpp>
Vector3f GetOGLPos::GetPos(float mousex, float mousey)	
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLint winX, winY;
	float winZ; //winZ is between 0 (near plane) and 1 (far plane).
    GLdouble posX, posY, posZ;
 
	

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
 
	winX = mousex;
	winY = mousey;
		
	winY = (float)viewport[3] - winY; 
    glReadPixels( int(winX), int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	
	std::cout<<"winX:"<<winX<<" , winY:"<<winY<<" , winZ:"<<winZ<<" , posX:"<<posX<<" , posY:"<<posY<<" , posZ:"<<posZ<<std::endl;
	
    return Vector3f(posX, posY, posZ);
}