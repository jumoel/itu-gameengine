#ifndef ITUENGINE_SCENEGRAPHMANAGER_H
#define ITUENGINE_SCENEGRAPHMANAGER_H

#include "Camera.h"
#include "Object.h"

class SceneGraphManager
{
public:
	SceneGraphManager(Camera *Camera, Object *RootNode);
	~SceneGraphManager();

	void Render();

	Camera *CameraObject;
	Object *RootNode;

private:
	void RenderObject(Object *obj);
};

#endif