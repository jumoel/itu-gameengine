#include <Subsystems/Physics/PhysicsSystem.hpp>
#include "PhysicsModels/RectanglePhysicsModel.hpp"
#include "PhysicsModels/CirclePhysicsModel.hpp"
#include "PhysicsModels/PhysicsModel.hpp"
#include <Math/CollisionDetection2D.hpp>

void PhysicsSystem::StartUp()
{
	m_StaticObjects = new std::vector<StaticRectanglePhysicsModel*>();
	m_MovingObjects = new std::vector<MovingCirclePhysicsModel*>();
}

void PhysicsSystem::ShutDown()
{
	delete m_StaticObjects;
	delete m_MovingObjects;
}

void PhysicsSystem::PhantomStep(unsigned int deltaT)
{
	std::vector<MovingCirclePhysicsModel*>::iterator movingObjectIterator;

	//Move phantoms
	for(movingObjectIterator = m_MovingObjects->begin(); 
		movingObjectIterator != m_MovingObjects->end();
		movingObjectIterator++)
	{
		auto phantom = (*movingObjectIterator)->GetPhantom();
		
		phantom->Center.X = (*movingObjectIterator)->GetGeometricRepresentation()->Center.X 
							+ (*movingObjectIterator)->GetDirection()->X * (*movingObjectIterator)->GetMovementSpeed() * deltaT;
		phantom->Center.Y = (*movingObjectIterator)->GetGeometricRepresentation()->Center.Y 
							+ (*movingObjectIterator)->GetDirection()->Y * (*movingObjectIterator)->GetMovementSpeed() * deltaT;
	}

	//Check for collisions with stuff
	for(movingObjectIterator = m_MovingObjects->begin(); 
		movingObjectIterator != m_MovingObjects->end();
		movingObjectIterator++)
	{
		auto phantom = (*movingObjectIterator)->GetPhantom();
		std::vector<MovingCirclePhysicsModel*>::iterator movingObject2Iterator;
		std::vector<StaticRectanglePhysicsModel*>::iterator staticObjectIterator;

		//First check static objects
		for(staticObjectIterator = m_StaticObjects->begin(); 
			staticObjectIterator != m_StaticObjects->end();
			staticObjectIterator++)
		{
			auto staticElement = (*staticObjectIterator)->GetGeometricRepresentation();
			if(CollisionDetection2D::Intersection(*staticElement, *phantom))
			{
				//Handle collision
			}
		}

		//Then check other moving objects
		for(movingObject2Iterator = m_MovingObjects->begin(); 
			movingObject2Iterator != m_MovingObjects->end();
			movingObjectIterator++)
		{
			if((*movingObjectIterator) == (*movingObject2Iterator))
			{
				continue;
			}

			auto movingElement = (*movingObject2Iterator)->GetPhantom();
			if(CollisionDetection2D::Intersection(*movingElement, *phantom))
			{
				//Handle collision
			}
		}

	}
}

void PhysicsSystem::Step(unsigned int deltaT)
{
	//Move real Objects

}

void PhysicsSystem::AddMovingCircleObject( MovingCirclePhysicsModel *movingObject )
{
	m_MovingObjects->push_back(movingObject);
}

void PhysicsSystem::AddStaticRectangleObject( StaticRectanglePhysicsModel *staticObject )
{
	m_StaticObjects->push_back(staticObject);
}
