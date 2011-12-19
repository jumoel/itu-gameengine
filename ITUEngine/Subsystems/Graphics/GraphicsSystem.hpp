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

	SceneGraphManager *m_SceneGraph;

private:
	void InitOpenGL();
	void RenderRecursive(Object *obj);

};

#endif // ITUENGINE_GRAPHICSSYSTEM_H