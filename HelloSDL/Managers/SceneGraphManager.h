#ifndef ITUENGINE_SCENEGRAPHMANAGER_H
#define ITUENGINE_SCENEGRAPHMANAGER_H

#include "../Game/Camera.h"
#include "../Game/Object.h"
#include "../Game/FPSCalculator.h"

#include "SDL.h"

class SceneGraphManager
{
public:
	SceneGraphManager(Camera *Camera, Object *RootNode);
	~SceneGraphManager();

	void Render(Uint32 CurrentTime);

	Camera *CameraObject;
	Object *RootNode;

private:
	void RenderObject(Object *obj);

	Uint32 LastTime;
	Uint32 DeltaTime;
};

#endif