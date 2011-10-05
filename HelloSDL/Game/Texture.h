#ifndef ITUENGINE_TEXTURE_H
#define ITUENGINE_TEXTURE_H

#include <iostream>
#include "SDL.h"
#include "GL/glew.h"


class TexCoord                                 // Texture Coordinate Class
{
public:
    float u;									// U Component
    float v;									// V Component

	TexCoord(){}
	TexCoord(float uIn, float vIn){ u = uIn; v = vIn; }
	~TexCoord(){}
};

class Texture
{
public:
	char *name;
	GLubyte *imageData;                             // Image Data (Up To 32 Bits)
    GLuint  bpp;                                    // Image Color Depth In Bits Per Pixel
    GLuint  width;                                  // Image Width
    GLuint  height;                                 // Image Height
    GLuint  texID;

	Texture();
	~Texture();
};

#endif

