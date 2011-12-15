#include <Subsystems/Physics/PhysicsSystem.hpp>
#include "PhysicsModels/PhysicsModel.hpp"
#include <Math/CollisionDetection2D.hpp>
#include <iostream>

//#define PHYSICS_DEBUG

void PhysicsSystem::StartUp()
{
	m_StaticObjects = new std::vector<StaticObjectModel*>();
	m_MovingObjects = new std::vector<MovingObjectModel*>();

	//TODO: Initialize Properly
	int mapWidth = 40;
	SINGLETONINSTANCE(PathPlanner)->StartUp(mapWidth);

#ifdef PHYSICS_DEBUG
	// Insert test data

	//Rectangles:
	//MinXY = 0,0 - Width 1 - Height: 10
	auto staticTestItem1 = new StaticObjectModel(RECTANGULARSHAPE);
	staticTestItem1->InitializeAsRectangle(Rectangle(Point(0.0f, 0.0f), 1.0f, 10.0f));
	m_StaticObjects->push_back(staticTestItem1);

	//MinXY = 1,0 - Width 18 - Height: 1
	auto staticTestItem2 = new StaticObjectModel(RECTANGULARSHAPE);
	staticTestItem2->InitializeAsRectangle(Rectangle(Point(1.0f, 0.0f), 18.0f, 1.0f));
	m_StaticObjects->push_back(staticTestItem2);
	
	//MinXY = 1,9 - Width 18 - Height: 1
	auto staticTestItem3 = new StaticObjectModel(RECTANGULARSHAPE);
	staticTestItem3->InitializeAsRectangle(Rectangle(Point(1.0f, 9.0f), 18.0f, 1.0f));
	m_StaticObjects->push_back(staticTestItem3);
	
	//MinXY = 19,0 - Width 1 - Height: 10
	auto staticTestItem4 = new StaticObjectModel(RECTANGULARSHAPE);
	staticTestItem4->InitializeAsRectangle(Rectangle(Point(19.0f, 0.0f), 1.0f, 10.0f));
	m_StaticObjects->push_back(staticTestItem4);

	//Circles: moving
	//Center = (5,6) - Radius: 1 - Direction: (1,1)
	auto movingTestItem1 = new MovingObjectModel(CIRCULARSHAPE, PLAYERTYPE, Point(1.0f, 1.0f));
	movingTestItem1->InitializeAsCircle(Circle(Point(5.0f, 6.0f), 1.0f));
	m_MovingObjects->push_back(movingTestItem1);

	//Center = (7,3) - Radius: 1 - Direction: (1,1)

	auto movingTestItem2 = new MovingObjectModel(CIRCULARSHAPE, CRITTERTYPE, Point(1.0f, 1.0f));
	movingTestItem2->InitializeAsCircle( Circle(Point(7.0f, 3.0f), 1.0f) );
	m_MovingObjects->push_back(movingTestItem2);

	//Center = (10,5) - Radius: 1 - Direction: (-1,-1)
	auto movingTestItem3 = new MovingObjectModel(CIRCULARSHAPE, CRITTERTYPE, Point(-1.0f, -1.0f) );
	movingTestItem3->InitializeAsCircle( Circle(Point(10.0f, 5.0f), 1.0f) );
	m_MovingObjects->push_back(movingTestItem3);

	SetStaticPathMap();

	movingTestItem1->SetTargetPosition(new Point(15.0f, 6.0f));

	movingTestItem2->SetTargetPosition(new Point(12.0f, 7.0f));
#endif
}

void PhysicsSystem::ShutDown()
{
	delete m_StaticObjects;
	delete m_MovingObjects;
}

void PhysicsSystem::PhantomStep(unsigned int deltaT)
{
	std::vector<MovingObjectModel*>::iterator movingObjectIterator;

	//Move phantoms
	for(movingObjectIterator = m_MovingObjects->begin(); 
		movingObjectIterator != m_MovingObjects->end();
		movingObjectIterator++)
	{
		auto path = (*movingObjectIterator)->GetPath();
		if(path != NULL && !path->empty())
		{
			//Set Movement Speeds
			(*movingObjectIterator)->SetMaxMovementSpeed();
		}
		else
		{
			//Path is exhausted, or not path exists, DO NOT MOVE !
			(*movingObjectIterator)->SetMovementSpeed(0.0f);
		}

		if((*movingObjectIterator)->GetShape() == CIRCULARSHAPE)
		{
			Circle* phantom = (*movingObjectIterator)->GetCirclePhantom();

			MoveCircleObject(phantom, movingObjectIterator, deltaT);
		}

		if((*movingObjectIterator)->GetShape() == RECTANGULARSHAPE)
		{
			//Moving Rectangles 
			//NOT IMPLEMENTED
		}
	}

	//Check for collisions with stuff
	for(movingObjectIterator = m_MovingObjects->begin(); 
		movingObjectIterator != m_MovingObjects->end();
		movingObjectIterator++)
	{
		Circle* circlePhantom = NULL;
		Rectangle* rectanglePhantom = NULL;

		if((*movingObjectIterator)->GetShape() == CIRCULARSHAPE)
		{
			circlePhantom = (*movingObjectIterator)->GetCirclePhantom();
		}

		if((*movingObjectIterator)->GetShape() == RECTANGULARSHAPE)
		{
			rectanglePhantom = (*movingObjectIterator)->GetRectanglePhantom();
		}
		 
		std::vector<MovingObjectModel*>::iterator movingObject2Iterator;
		std::vector<StaticObjectModel*>::iterator staticObjectIterator;

		//First check static objects
		for(staticObjectIterator = m_StaticObjects->begin(); 
			staticObjectIterator != m_StaticObjects->end();
			staticObjectIterator++)
		{
			Circle* staticCircle = NULL;
			Rectangle* staticRectangle = NULL;

			if((*staticObjectIterator)->GetShape() == CIRCULARSHAPE)
			{
				staticCircle = (*staticObjectIterator)->GetCircularRepresentation();
			}

			if((*staticObjectIterator)->GetShape() == RECTANGULARSHAPE)
			{
				staticRectangle = (*staticObjectIterator)->GetRectangularRepresentation();
			}

			if(	CollisionDetection2D::Intersection(staticCircle, circlePhantom) ) //Rectangle to Rectangle not implemented
			{
				//Handle collision
				(*movingObjectIterator)->HandleCollsion();
				std::cout << "Collision occurred between circle phantom at: (" << circlePhantom->Center.X << ", " << circlePhantom->Center.Y << ") and static circle at: (" << staticCircle->Center.X << ", " << staticCircle->Center.Y << ")" << std::endl;
			}
			if( CollisionDetection2D::Intersection(staticRectangle, circlePhantom) )
			{
				//Handle collision
				(*movingObjectIterator)->HandleCollsion();
				std::cout << "Collision occurred between circle phantom at: (" << circlePhantom->Center.X << ", " << circlePhantom->Center.Y << ") and static rectangle at (MinX: " << staticRectangle->MinX << ", MinY: " << staticRectangle->MinY << ")" << std::endl;
			}

			if( CollisionDetection2D::Intersection(staticCircle, rectanglePhantom) )
			{
				//Handle collision
				(*movingObjectIterator)->HandleCollsion();
				std::cout << "Collision occurred between static circle at: (" << staticCircle->Center.X << ", " << staticCircle->Center.Y << ") and rectangle phantom at (MinX: " << rectanglePhantom->MinX << ", MinY: " << rectanglePhantom->MinY << ")" << std::endl;
			}
		}

		//Then check other moving objects
		for(movingObject2Iterator = m_MovingObjects->begin(); 
			movingObject2Iterator != m_MovingObjects->end();
			movingObject2Iterator++)
		{
			if((*movingObjectIterator) == (*movingObject2Iterator))
			{
				continue;
			}

			Circle* movingCircle = NULL;
			Rectangle* movingRectangle = NULL;

			if((*movingObject2Iterator)->GetShape() == CIRCULARSHAPE)
			{
				movingCircle = (*movingObject2Iterator)->GetCirclePhantom();
			}

			if((*movingObject2Iterator)->GetShape() == RECTANGULARSHAPE)
			{
				movingRectangle = (*movingObject2Iterator)->GetRectanglePhantom();
			}

			if(	CollisionDetection2D::Intersection(movingCircle, circlePhantom) ) //Rectangle to Rectangle not implemented
			{
				//Handle collision
				(*movingObjectIterator)->HandleCollsion();
				std::cout << "Collision occurred between circle phantom at: (" << movingCircle->Center.X << ", " << movingCircle->Center.Y << ") and circle phantom at: (" << circlePhantom->Center.X << ", " << circlePhantom->Center.Y << ")" << std::endl;
			}
			if( CollisionDetection2D::Intersection(movingRectangle, circlePhantom) )
			{
				//Handle collision
				(*movingObjectIterator)->HandleCollsion();
				std::cout << "Collision occurred between circle phantom at: (" << circlePhantom->Center.X << ", " << circlePhantom->Center.Y << ") and rectangle phantom at (MinX: " << movingRectangle->MinX << ", MinY: " << movingRectangle->MinY << ")" << std::endl;
			}

			if( CollisionDetection2D::Intersection(movingCircle, rectanglePhantom) )
			{
				//Handle collision
				(*movingObjectIterator)->HandleCollsion();
				std::cout << "Collision occurred between circle phantom at: (" << movingCircle->Center.X << ", " << movingCircle->Center.Y << ") and rectangle phantom at (MinX: " << rectanglePhantom->MinX << ", MinY: " << rectanglePhantom->MinY << ")" << std::endl;
			}
		}
	}
}

void PhysicsSystem::Step(unsigned int deltaT)
{	
	//Check Phantom collisions
	PhantomStep(deltaT);

	//Check real collisions
	std::vector<MovingObjectModel*>::iterator movingObjectIterator;
	
	//Move real Objects
	for(movingObjectIterator = m_MovingObjects->begin(); 
		movingObjectIterator != m_MovingObjects->end();
		movingObjectIterator++)
	{
		if((*movingObjectIterator)->GetShape() == CIRCULARSHAPE)
		{
			Circle* geoRep = (*movingObjectIterator)->GetCircularRepresentation();

			MoveCircleObject(geoRep, movingObjectIterator, deltaT);
		}

		if((*movingObjectIterator)->GetShape() == RECTANGULARSHAPE)
		{
			//Moving Rectangles 
			//NOT IMPLEMENTED
		}
	}

	//Update path finding map
	SetDynamicPathMap();
	SINGLETONINSTANCE(PathPlanner)->DrawDebug();

	//Check for collisions with stuff
	for(movingObjectIterator = m_MovingObjects->begin(); 
		movingObjectIterator != m_MovingObjects->end();
		movingObjectIterator++)
	{
		Circle* circle = NULL;
		Rectangle* rectangle = NULL;

		if((*movingObjectIterator)->GetShape() == CIRCULARSHAPE)
		{
			circle = (*movingObjectIterator)->GetCircularRepresentation();
		}

		if((*movingObjectIterator)->GetShape() == RECTANGULARSHAPE)
		{
			rectangle = (*movingObjectIterator)->GetRectangularRepresentation();
		}

		std::vector<MovingObjectModel*>::iterator movingObject2Iterator;
		std::vector<StaticObjectModel*>::iterator staticObjectIterator;

		//First check static objects
		for(staticObjectIterator = m_StaticObjects->begin(); 
			staticObjectIterator != m_StaticObjects->end();
			staticObjectIterator++)
		{
			Circle* staticCircle = NULL;
			Rectangle* staticRectangle = NULL;

			if((*staticObjectIterator)->GetShape() == CIRCULARSHAPE)
			{
				staticCircle = (*staticObjectIterator)->GetCircularRepresentation();
			}

			if((*staticObjectIterator)->GetShape() == RECTANGULARSHAPE)
			{
				staticRectangle = (*staticObjectIterator)->GetRectangularRepresentation();
			}

			if(	CollisionDetection2D::Intersection(staticCircle, circle) ) //Rectangle to Rectangle not implemented
			{
				//Handle collision
				std::cout << "Collision occurred between circle at: (" << circle->Center.X << ", " << circle->Center.Y << ") and static circle at: (" << staticCircle->Center.X << ", " << staticCircle->Center.Y << ")" << std::endl;
			}
			if( CollisionDetection2D::Intersection(staticRectangle, circle) )
			{
				//Handle collision
				std::cout << "Collision occurred between circle at: (" << circle->Center.X << ", " << circle->Center.Y << ") and static rectangle at (MinX: " << staticRectangle->MinX << ", MinY: " << staticRectangle->MinY << ")" << std::endl;
			}

			if( CollisionDetection2D::Intersection(staticCircle, rectangle) )
			{
				//Handle collision
				std::cout << "Collision occurred between static circle at: (" << staticCircle->Center.X << ", " << staticCircle->Center.Y << ") and rectangle at (MinX: " << rectangle->MinX << ", MinY: " << rectangle->MinY << ")" << std::endl;
			}
		}

		//Then check other moving objects
		for(movingObject2Iterator = m_MovingObjects->begin(); 
			movingObject2Iterator != m_MovingObjects->end();
			movingObject2Iterator++)
		{
			if((*movingObjectIterator) == (*movingObject2Iterator))
			{
				continue;
			}

			Circle* movingCircle = NULL;
			Rectangle* movingRectangle = NULL;

			if((*movingObject2Iterator)->GetShape() == CIRCULARSHAPE)
			{
				movingCircle = (*movingObject2Iterator)->GetCircularRepresentation();
			}

			if((*movingObject2Iterator)->GetShape() == RECTANGULARSHAPE)
			{
				movingRectangle = (*movingObject2Iterator)->GetRectangularRepresentation();
			}

			if(	CollisionDetection2D::Intersection(movingCircle, circle) ) //Rectangle to Rectangle not implemented
			{
				//Handle collision
				std::cout << "Collision occurred between circle at: (" << movingCircle->Center.X << ", " << movingCircle->Center.Y << ") and circle at: (" << circle->Center.X << ", " << circle->Center.Y << ")" << std::endl;
			}
			if( CollisionDetection2D::Intersection(movingRectangle, circle) )
			{
				//Handle collision
				std::cout << "Collision occurred between circle at: (" << circle->Center.X << ", " << circle->Center.Y << ") and rectangle at (MinX: " << movingRectangle->MinX << ", MinY: " << movingRectangle->MinY << ")" << std::endl;
			}

			if( CollisionDetection2D::Intersection(movingCircle, rectangle) )
			{
				//Handle collision
				std::cout << "Collision occurred between circle at: (" << movingCircle->Center.X << ", " << movingCircle->Center.Y << ") and rectangle at (MinX: " << rectangle->MinX << ", MinY: " << rectangle->MinY << ")" << std::endl;
			}
		}

		//If we reach the next point in our path, Set new direction.
		(*movingObjectIterator)->RecalculatePath();
	}
}

void PhysicsSystem::AddMovingObject( MovingObjectModel *movingObject )
{
	m_MovingObjects->push_back(movingObject);
}

void PhysicsSystem::AddStaticObject( StaticObjectModel *staticObject )
{
	m_StaticObjects->push_back(staticObject);
}

void PhysicsSystem::MoveCircleObject( Circle *circle, std::vector<MovingObjectModel*>::iterator movingObjectIterator, unsigned int deltaT )
{
	circle->Center.X = (*movingObjectIterator)->GetCircularRepresentation()->Center.X 
		+ (*movingObjectIterator)->GetDirection()->X * (*movingObjectIterator)->GetMovementSpeed() * deltaT;
	circle->Center.Y = (*movingObjectIterator)->GetCircularRepresentation()->Center.Y 
		+ (*movingObjectIterator)->GetDirection()->Y * (*movingObjectIterator)->GetMovementSpeed() * deltaT;
}

void PhysicsSystem::SetDynamicPathMap()
{
	std::vector<std::vector<int>> *map = new std::vector<std::vector<int>>(MAP_SIZE, std::vector<int>(MAP_SIZE, 0));

	std::vector<MovingObjectModel*>::iterator dynamicObjectIterator;
	for(dynamicObjectIterator = m_MovingObjects->begin(); 
		dynamicObjectIterator != m_MovingObjects->end();
		dynamicObjectIterator++)
	{
		float posx = (*dynamicObjectIterator)->GetPosition()->X;
		float posy = (*dynamicObjectIterator)->GetPosition()->Y;

		float targetPosX = (*dynamicObjectIterator)->GetTargetPosition()->X;
		float targetPosY = (*dynamicObjectIterator)->GetTargetPosition()->Y;

		int x = SINGLETONINSTANCE(PathPlanner)->ConvertToPlanningMapCoordinate(posx);
		int y = SINGLETONINSTANCE(PathPlanner)->ConvertToPlanningMapCoordinate(posy);

		int targetX = SINGLETONINSTANCE(PathPlanner)->ConvertToPlanningMapCoordinate(targetPosX);
		int targetY = SINGLETONINSTANCE(PathPlanner)->ConvertToPlanningMapCoordinate(targetPosY);

		if((*dynamicObjectIterator)->GetShape() == CIRCULARSHAPE)
		{
			//NOTE: Right now a player is always 1 node large in the Path Finding algorithm.
			map->at(targetX)[targetY] = TARGET;
			map->at(x)[y] = PLAYER;
		}
		else if((*dynamicObjectIterator)->GetShape() == RECTANGULARSHAPE)
		{
			//NOT IMPLEMENTED
		}
	}

	SINGLETONINSTANCE(PathPlanner)->UpdateDynamicMap(map);
}

void PhysicsSystem::SetStaticPathMap()
{
	std::vector<std::vector<int>> *map = new std::vector<std::vector<int>>(MAP_SIZE, std::vector<int>(MAP_SIZE, 0));

	std::vector<StaticObjectModel*>::iterator staticObjectIterator;
	for(staticObjectIterator = m_StaticObjects->begin(); 
		staticObjectIterator != m_StaticObjects->end();
		staticObjectIterator++)
	{
		float posx = (*staticObjectIterator)->GetPosition()->X;
		float posy = (*staticObjectIterator)->GetPosition()->Y;

		int x = SINGLETONINSTANCE(PathPlanner)->ConvertToPlanningMapCoordinate(posx);
		int y = SINGLETONINSTANCE(PathPlanner)->ConvertToPlanningMapCoordinate(posy);

		if((*staticObjectIterator)->GetShape() == CIRCULARSHAPE)
		{
			auto circle = (*staticObjectIterator)->GetCircularRepresentation();
			int radius = circle->Radius;

			for (unsigned int i = -radius; i <= radius; i++ )
			{
				for (unsigned int j = -radius; j <= radius; j++)
				{
					map->at(x + i)[y + j] = BLOCKED;
				}
			}
		}
		else if((*staticObjectIterator)->GetShape() == RECTANGULARSHAPE)
		{
			auto rectangle = (*staticObjectIterator)->GetRectangularRepresentation();
			int width = rectangle->Width;
			int height = rectangle->Height;

			for (unsigned int i = 0; i < width; i++ )
			{
				for (unsigned int j = 0; j < height; j++)
				{
					map->at(x + i)[y + j] = BLOCKED;
				}
			}
		}
	}
}
