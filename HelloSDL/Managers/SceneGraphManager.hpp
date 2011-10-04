#ifndef ITUENGINE_SCENEGRAPHMANAGER_H
#define ITUENGINE_SCENEGRAPHMANAGER_H

#include <Game/Camera.h>
#include <Game/Object.h>
#include <Game/FPSCalculator.hpp>

#include "SDL.h"

#include <vector>


class SceneGraphManager
{
public:
	SceneGraphManager(Camera *Camera, Object *RootNode);
	~SceneGraphManager();

	void Render(Uint32 CurrentTime, bool vboOn);

	void RenderVBO();

	Camera* CameraObject;
	Object* RootNode;

private:
	void RenderObject(Object *obj);
	void RenderObjectVBO(Object *obj);

	void RenderSingleObjectVBO(Object *obj);

	std::vector<float> vertex_list;

	Uint32 LastTime;
	Uint32 DeltaTime;
};

#endif