#include <Managers/SceneGraphManager.hpp>
#include <SDL.h>
#include "GL/glew.h"
#include <iostream>
#include <memory>
#include <Events/EventData/EventData.hpp>
#include <Math/Vector3f.hpp>
#include <Templates/TSingleton.hpp>
#include "MediaManager.hpp"
#include <Subsystems/Physics/PhysicsSystem.hpp>
#include <Subsystems/Physics/PhysicsModels/PhysicsModel.hpp>
#include <Abstractions/Time.hpp>

SceneGraphManager::SceneGraphManager(Camera *CameraObject, Object *RootNode) :
	m_CameraObject(CameraObject),
	m_RootNode(RootNode),
	LastTime(0),
	DeltaTime(0)
{
	safeAddListener(EventListenerPointer(this), EventType("mouseClickHUDEvent"));
}

SceneGraphManager::~SceneGraphManager()
{
	delete m_CameraObject;
	DeleteGraph(m_RootNode);
}

void SceneGraphManager::DeleteGraph(Object* node)
{
	if(node->children->size() > 0)
	{
		for (auto it = node->children->begin(); it != node->children->end(); ++it)
		{
			DeleteGraph(&(*it));
		}
	}
	//delete node;
}

char const * SceneGraphManager::GetName()
{
	return "SceneGraphManager";
}

bool SceneGraphManager::HandleEvent( IEventData const & event )
{
	shared_ptr<EventData<Vector3f>> data = dynamic_pointer_cast<EventData<Vector3f>, IEventData>(event.Copy());
	auto val = data->GetValue();

	//If inside defined box... DO:

	Rectangle physicsBox(Point(-0.5f, -0.5f), 1.0f, 1.0f);

	auto box = new Object();
	box->Name = "HUDBox";
	box->model =  SINGLETONINSTANCE( MediaManager )->boxModel;
	StaticObjectModel* tempStaticObject = new StaticObjectModel(RECTANGULARSHAPE);
	box->physicsModel = tempStaticObject;
	box->physicsModel->InitializeAsRectangle(physicsBox);
	SINGLETONINSTANCE(PhysicsSystem)->AddStaticObject(tempStaticObject);

	srand(Time::GetCurrentMS());
	float x = (float)(rand() % 400) / 10.0f;
	float y = (float)(rand() % 400) / 10.0f;

	box->SetPos2D(x, y);
	box->SetScale(2.0f, 2.0f, 5.0f);

	m_RootNode->children->push_back(*box);

	SINGLETONINSTANCE(PhysicsSystem)->SetStaticPathMap();


	return true;
}