#ifndef ITUENGINE_PHYSICSSYSTEM_H
#define ITUENGINE_PHYSICSSYSTEM_H

#include <Subsystems/Physics/PhysicsModels/PhysicsModel.hpp>
#include <vector>
#include "PhysicsModels/RectanglePhysicsModel.hpp"
#include "PhysicsModels/CirclePhysicsModel.hpp"

class PhysicsSystem
{
public:
	PhysicsSystem() {}
	~PhysicsSystem() {}

	void StartUp();
	void ShutDown();

	void PhantomStep(unsigned int deltaT);
	void Step(unsigned int deltaT);

	void AddMovingCircleObject(MovingCirclePhysicsModel *movingObject);
	void AddStaticRectangleObject(StaticRectanglePhysicsModel *staticObject);

protected:
	
private:
	std::vector<StaticRectanglePhysicsModel*> *m_StaticObjects;
	std::vector<MovingCirclePhysicsModel*> *m_MovingObjects;
};

#endif //ITUENGINE_PHYSICSSYSTEM_H