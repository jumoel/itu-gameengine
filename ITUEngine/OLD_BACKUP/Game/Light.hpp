#ifndef ITUENGINE_LIGHT_H
#define ITUENGINE_LIGHT_H

class Light
{
public:
	bool inUse;
	int lightIndex;

	void enable(bool On);

	void setPos(float x, float y, float z);
	float getPosValue(char coord);

	void setAmbient(float r, float g, float b, float a);
	void setDiffuse(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);

	Light();
	~Light();
	
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float emissive[4];

	float pos[3];
};

#endif