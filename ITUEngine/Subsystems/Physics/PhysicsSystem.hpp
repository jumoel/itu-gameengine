#ifndef ITUENGINE_PHYSICSSYSTEM_H
#define ITUENGINE_PHYSICSSYSTEM_H

#include <Subsystems/Physics/PhysicsModels/PhysicsModel.hpp>
#include <vector>
#include <Math/GeometricFigures2D.hpp>

class PhysicsSystem
{
public:
	PhysicsSystem() {}
	~PhysicsSystem() {}

	void StartUp();
	void ShutDown();

	void PhantomStep();
	void Step();

protected:
	
private:
	std::vector<StaticObjectModel<GeometricFigure>> *m_StaticObjects;
	std::vector<MovingObjectModel<GeometricFigure>> *m_MovingObjects;
};

#endif //ITUENGINE_PHYSICSSYSTEM_H