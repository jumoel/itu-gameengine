#ifndef ITUENGINE_GRAPHICSSYSTEM_H
#define ITUENGINE_GRAPHICSSYSTEM_H

#include <Managers/SceneGraphManager.hpp>
#include <vector>
#include <assimp.hpp>      // C++ importer interface
#include <aiScene.h>       // Output data structure
#include <aiPostProcess.h> // Post processing flags

class GraphicsSystem
{
public:
	void StartUp();
	void ShutDown();

	void Render();

private:
	void AddToVBORecursive(Object *obj, std::vector<Vector3f> *vectors);
	void AddAssimpModelToVBORecursive(const aiScene* scene, const aiNode* node, std::vector<Vector3f> *vectors);
	void InitOpenGL();
	void RenderRecursive(Object *obj);

	SceneGraphManager *m_SceneGraph;
	std::vector<Vector3f> *m_VectorList;
	GLuint m_VertexBuffer;
	GLuint m_VertexArrayObject;

	GLuint theProgram;
};

#endif // ITUENGINE_GRAPHICSSYSTEM_H