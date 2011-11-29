#include <Game/Material.hpp>


Material::Material()
{
	this->colors = new std::list<Vector3f>();
	this->uv = new std::list<TexCoord>();
	this->texture = NULL;
	this->spec = new float[4];

	shininess = 0.0f;
	diffuse = new float[4];
	specular = new float[4];
	emissive = new float[4];
	ambient = new float[4];

	for(int i = 0; i < 4; i++)
	{
		diffuse[i] = 0.0f;
		specular[i] = 0.0f;
		emissive[i] = 0.0f;
		ambient[i] = 0.0f;
		spec[i] = 0.0f;
	}
	this->shine = 0.0f;
	
	shader = aiShadingMode_Gouraud;

}


Material::~Material()
{
	delete this->colors;
	delete this->uv;
	delete [] this->spec;
}
