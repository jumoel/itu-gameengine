#ifndef ITUENGINE_GRAPHICSSYSTEM_H
#define ITUENGINE_GRAPHICSSYSTEM_H

#include <Managers/SceneGraphManager.hpp>
#include <vector>

class GraphicsSystem
{
public:
	void StartUp();
	void ShutDown();

	void Render();

private:
	void AddToVBORecursive(Object *obj, std::vector<Vector3f> *vectors);
	void InitOpenGL();

	SceneGraphManager *m_SceneGraph;
	std::vector<Vector3f> *m_VectorList;
	GLuint m_VertexBuffer;
	GLuint m_VertexArrayObject;
};

#endif // ITUENGINE_GRAPHICSSYSTEM_H