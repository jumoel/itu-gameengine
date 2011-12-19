#ifndef ITUENGINE_PLAYERINTERACTION_H
#define ITUENGINE_PLAYERINTERACTION_H

#include <Game/Object.hpp>
#include <Templates/TSingleton.hpp>
#include <Events/Interfaces/IEventListener.hpp>

class PlayerInteraction : public IEventListener
{

SINGLETON(PlayerInteraction)

public:

	void StartUp(Object *playerObject);
	void ShutDown();

	virtual bool HandleEvent( IEventData const & event );
	virtual char const * GetName(void);

private:
	Object* player;
};
#endif