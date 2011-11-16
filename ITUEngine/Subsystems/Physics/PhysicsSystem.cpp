#include <Subsystems/Physics/PhysicsSystem.hpp>

void PhysicsSystem::StartUp()
{
	m_StaticObjects = new std::vector<StaticObjectModel<GeometricFigure>>();
	m_MovingObjects = new std::vector<MovingObjectModel<GeometricFigure>>();
}

void PhysicsSystem::ShutDown()
{
	delete m_StaticObjects;
	delete m_MovingObjects;
}

void PhysicsSystem::PhantomStep()
{
	//Move phantoms, and check for collisions with stuff
}

void PhysicsSystem::Step()
{
	//Move real Objects

}
