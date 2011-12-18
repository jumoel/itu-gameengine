#ifndef ITUENGINE_SCENEGRAPHMANAGER_H
#define ITUENGINE_SCENEGRAPHMANAGER_H

#include <Game/Camera.hpp>
#include <Game/Object.hpp>
#include <Game/FPSCalculator.hpp>

#include "SDL.h"

#include <vector>
#include <Events/Interfaces/IEventListener.hpp>


class SceneGraphManager : public IEventListener
{
public:
	SceneGraphManager(Camera *Camera, Object *RootNode);
	~SceneGraphManager();

	//void Render(Uint32 CurrentTime, bool vboOn);

	virtual char const * GetName();

	virtual bool HandleEvent( IEventData const & event );

	Camera* m_CameraObject;
	Object* m_RootNode;

private:
	//void RenderObject(Object *obj);
	//void RenderObjectVBO(Object *obj);

	Uint32 LastTime;
	Uint32 DeltaTime;
};

#endif