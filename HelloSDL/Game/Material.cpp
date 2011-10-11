#include <Game/Material.hpp>


Material::Material()
{
	this->colors = new std::list<Vector3f>();
	this->uv = new std::list<TexCoord>();
	this->texture = NULL;
	this->spec = new float[4];
	for(int i = 0; i < 4; i++)
	{
		spec[i] = 0.0f;
	}
	this->shine = 0.0f;
}


Material::~Material()
{
	delete this->colors;
	delete this->uv;
	delete [] this->spec;
}
