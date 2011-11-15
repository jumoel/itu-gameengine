#ifndef ITUENGINE_GFX_MODEL_H
#define ITUENGINE_GFX_MODEL_H

#include <vector>

#include <Math/Matrix4x4f.hpp>
#include <Math/Vector3f.hpp>
#include <Game/Material.hpp>

struct Vertex
{
	char boneID;
	float location[3];
};

struct Triangle
{
	float vertexNormals[3][3];
	float sTex[3], tTex[3];
	int verticeIndices[3];
};

struct Mesh
{
	int materialIndex;
	int numTriangles;
	int *triangleIndices;
};

struct Mat
{
	float ambient[4], diffuse[4], specular[4], emissive[4];
	float shininess;
	GLuint mTexture;
	char* textureFileName;
	Texture* tex;
};

class GfxModel
{
public:
	GLuint vboId;
	GLuint cboId;
	GLuint tboId;

	int numVertices;
	Vertex *mVertices;

	int numTriangles;
	Triangle *mTriangles;

	int numMeshes;
	Mesh *mMeshes;

	int numMaterials;
	Mat *mMaterials;

	void SetTexture(Texture* tex);
	GfxModel();
	~GfxModel();

	//void CreateVBO();
	
	void draw();
	
};

#endif
