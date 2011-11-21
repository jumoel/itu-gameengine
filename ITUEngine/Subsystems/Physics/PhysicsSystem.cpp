#include <Subsystems/Physics/PhysicsSystem.hpp>
#include "PhysicsModels/RectanglePhysicsModel.hpp"
#include "PhysicsModels/CirclePhysicsModel.hpp"
#include "PhysicsModels/PhysicsModel.hpp"
#include <Math/CollisionDetection2D.hpp>
#include <iostream>

void PhysicsSystem::StartUp()
{
	m_StaticObjects = new std::vector<StaticRectanglePhysicsModel*>();
	m_MovingObjects = new std::vector<MovingCirclePhysicsModel*>();


	// Insert test data
	
	//Rectangles:
	//MinXY = 0,0 - Height: 10 - Width 1
	//MinXY = 1,0 - Height: 1 - Width 18
	//MinXY = 1,9 - Height: 1 - Width 18
	//MinXY = 19,0 - Height: 10 - Width 1

	//Circles: Assumed to be moving
	//Center = (5,6) - Radius: 1 - Direction: (1,1)
	//Center = (7,3) - Radius: 1 - Direction: (1,1)
	//Center = (10,5) - Radius: 1 - Direction: (-1,-1)


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
		
		MoveCircleObject(phantom, movingObjectIterator, deltaT);
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
				std::cout << "Collision occurred between circle phantom at: (" << phantom->Center.X << ", " << phantom->Center.X << ") and rectangle (MinX: " << staticElement->MinX << ", MinY: " << staticElement->MinY << ")" << std::endl;
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
				std::cout << "Collision occurred between circle phantom at: (" << phantom->Center.X << ", " << phantom->Center.X << ") and circle at: ( " << movingElement->Center.X << ", " << movingElement->Center.Y << ")" << std::endl;
			}
		}
	}
}

void PhysicsSystem::Step(unsigned int deltaT)
{
	std::vector<MovingCirclePhysicsModel*>::iterator movingObjectIterator;
	//Move real Objects

	//Move phantoms
	for(movingObjectIterator = m_MovingObjects->begin(); 
		movingObjectIterator != m_MovingObjects->end();
		movingObjectIterator++)
	{
		auto geoRep = (*movingObjectIterator)->GetGeometricRepresentation();

		MoveCircleObject(geoRep, movingObjectIterator, deltaT);
	}

	//Check for collisions with stuff
	for(movingObjectIterator = m_MovingObjects->begin(); 
		movingObjectIterator != m_MovingObjects->end();
		movingObjectIterator++)
	{
		auto geoRep = (*movingObjectIterator)->GetGeometricRepresentation();
		std::vector<MovingCirclePhysicsModel*>::iterator movingObject2Iterator;
		std::vector<StaticRectanglePhysicsModel*>::iterator staticObjectIterator;

		//First check static objects
		for(staticObjectIterator = m_StaticObjects->begin(); 
			staticObjectIterator != m_StaticObjects->end();
			staticObjectIterator++)
		{
			auto staticElement = (*staticObjectIterator)->GetGeometricRepresentation();
			if(CollisionDetection2D::Intersection(*staticElement, *geoRep))
			{
				//Handle collision
				std::cout << "Collision occurred between circle at: (" << geoRep->Center.X << ", " << geoRep->Center.X << ") and rectangle (MinX: " << staticElement->MinX << ", MinY: " << staticElement->MinY << ")" << std::endl;
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
			if(CollisionDetection2D::Intersection(*movingElement, *geoRep))
			{
				//Handle collision
				std::cout << "Collision occurred between circle at: (" << geoRep->Center.X << ", " << geoRep->Center.X << ") and circle at: ( " << movingElement->Center.X << ", " << movingElement->Center.Y << ")" << std::endl;
			}
		}
	}
}

void PhysicsSystem::AddMovingCircleObject( MovingCirclePhysicsModel *movingObject )
{
	m_MovingObjects->push_back(movingObject);
}

void PhysicsSystem::AddStaticRectangleObject( StaticRectanglePhysicsModel *staticObject )
{
	m_StaticObjects->push_back(staticObject);
}

void PhysicsSystem::MoveCircleObject( Circle *circle, std::vector<MovingCirclePhysicsModel*>::iterator movingObjectIterator, unsigned int deltaT )
{
	circle->Center.X = (*movingObjectIterator)->GetGeometricRepresentation()->Center.X 
		+ (*movingObjectIterator)->GetDirection()->X * (*movingObjectIterator)->GetMovementSpeed() * deltaT;
	circle->Center.Y = (*movingObjectIterator)->GetGeometricRepresentation()->Center.Y 
		+ (*movingObjectIterator)->GetDirection()->Y * (*movingObjectIterator)->GetMovementSpeed() * deltaT;
}
