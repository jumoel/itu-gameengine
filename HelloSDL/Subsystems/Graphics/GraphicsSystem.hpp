#ifndef ITUENGINE_GRAPHICSSYSTEM_H
#define ITUENGINE_GRAPHICSSYSTEM_H

#include <Managers/SceneGraphManager.hpp>

class GraphicsSystem
{
public:
	void StartUp();
	void ShutDown();

private:
	SceneGraphManager *m_SceneGraph;
};

#endif // ITUENGINE_GRAPHICSSYSTEM_H