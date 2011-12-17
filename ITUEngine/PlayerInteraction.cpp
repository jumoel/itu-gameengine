#include <PlayerInteraction.hpp>
#include <Events/EventData/EventData.hpp>
#include <Events/Interfaces/IEventData.hpp>
#include <Math\GeometricFigures2D.hpp>
#include <memory>

void PlayerInteraction::StartUp(Object *playerObject)
{
	this->player = playerObject;
	safeAddListener(EventListenerPointer(this), EventType("mouseClickPositionEvent"));
}

void PlayerInteraction::ShutDown()
{
	
}

bool PlayerInteraction::HandleEvent(IEventData const & eventData)
{
	shared_ptr<EventData<Vector3f>> data = dynamic_pointer_cast<EventData<Vector3f>, IEventData>(eventData.Copy());

	Vector3f val = data->GetValue();
	
	player->physicsModel->SetTargetPosition(&Point(val.x(), val.y()));

	return true;
}