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
	void DeleteGraph(Object* node);

	virtual char const * GetName();

	virtual bool HandleEvent( IEventData const & event );

	Camera* m_CameraObject;
	Object* m_RootNode;

private:
	Uint32 LastTime;
	Uint32 DeltaTime;
};

#endif