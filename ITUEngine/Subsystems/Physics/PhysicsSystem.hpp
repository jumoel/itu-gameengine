#ifndef ITUENGINE_PHYSICSSYSTEM_H
#define ITUENGINE_PHYSICSSYSTEM_H

#include <Subsystems/Physics/PhysicsModels/PhysicsModel.hpp>
#include <Templates/TSingleton.hpp>
#include <vector>


class PhysicsSystem
{
	SINGLETON( PhysicsSystem )
public:

	void StartUp();
	void ShutDown();

	void PhantomStep(unsigned int deltaT);

	void MoveCircleObject( Circle *circle, std::vector<MovingObjectModel*>::iterator movingObjectIterator, unsigned int deltaT );

	void Step(unsigned int deltaT);

	void SetDynamicPathMap();
	void SetStaticPathMap();


	void AddMovingObject(MovingObjectModel *movingObject);
	void AddStaticObject(StaticObjectModel *staticObject);

protected:
	
private:
	std::vector<StaticObjectModel*> *m_StaticObjects;
	std::vector<MovingObjectModel*> *m_MovingObjects;
};

#endif //ITUENGINE_PHYSICSSYSTEM_H