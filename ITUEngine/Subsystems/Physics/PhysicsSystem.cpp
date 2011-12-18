#include <Subsystems/Physics/PhysicsSystem.hpp>
#include "PhysicsModels/PhysicsModel.hpp"
#include <Math/CollisionDetection2D.hpp>
#include <Game/Object.hpp>
#include <iostream>

//#define PHYSICS_DEBUG

void PhysicsSystem::StartUp()
{
	m_StaticObjects = new std::vector<StaticObjectModel*>();
	m_MovingObjects = new std::vector<MovingObjectModel*>();
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
				#ifdef PHYSICS_DEBUG
				std::cout << "Collision occurred between circle phantom at: (" << circlePhantom->Center.X << ", " << circlePhantom->Center.Y << ") and static circle at: (" << staticCircle->Center.X << ", " << staticCircle->Center.Y << ")" << std::endl;
				#endif

			}
			if( CollisionDetection2D::Intersection(staticRectangle, circlePhantom) )
			{
				//Handle collision
				(*movingObjectIterator)->HandleCollsion();
				#ifdef PHYSICS_DEBUG
				std::cout << "Collision occurred between circle phantom at: (" << circlePhantom->Center.X << ", " << circlePhantom->Center.Y << ") and static rectangle at (MinX: " << staticRectangle->MinX << ", MinY: " << staticRectangle->MinY << ")" << std::endl;
				#endif
			}

			if( CollisionDetection2D::Intersection(staticCircle, rectanglePhantom) )
			{
				//Handle collision
				(*movingObjectIterator)->HandleCollsion();
				#ifdef PHYSICS_DEBUG
				std::cout << "Collision occurred between static circle at: (" << staticCircle->Center.X << ", " << staticCircle->Center.Y << ") and rectangle phantom at (MinX: " << rectanglePhantom->MinX << ", MinY: " << rectanglePhantom->MinY << ")" << std::endl;
				#endif
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
				#ifdef PHYSICS_DEBUG
				std::cout << "Collision occurred between circle phantom at: (" << movingCircle->Center.X << ", " << movingCircle->Center.Y << ") and circle phantom at: (" << circlePhantom->Center.X << ", " << circlePhantom->Center.Y << ")" << std::endl;
				#endif
			}
			if( CollisionDetection2D::Intersection(movingRectangle, circlePhantom) )
			{
				//Handle collision
				(*movingObjectIterator)->HandleCollsion();
				#ifdef PHYSICS_DEBUG
				std::cout << "Collision occurred between circle phantom at: (" << circlePhantom->Center.X << ", " << circlePhantom->Center.Y << ") and rectangle phantom at (MinX: " << movingRectangle->MinX << ", MinY: " << movingRectangle->MinY << ")" << std::endl;
				#endif
			}

			if( CollisionDetection2D::Intersection(movingCircle, rectanglePhantom) )
			{
				//Handle collision
				(*movingObjectIterator)->HandleCollsion();
				#ifdef PHYSICS_DEBUG
				std::cout << "Collision occurred between circle phantom at: (" << movingCircle->Center.X << ", " << movingCircle->Center.Y << ") and rectangle phantom at (MinX: " << rectanglePhantom->MinX << ", MinY: " << rectanglePhantom->MinY << ")" << std::endl;
				#endif
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
				#ifdef PHYSICS_DEBUG
				std::cout << "Collision occurred between circle at: (" << circle->Center.X << ", " << circle->Center.Y << ") and static circle at: (" << staticCircle->Center.X << ", " << staticCircle->Center.Y << ")" << std::endl;
				#endif
			}
			if( CollisionDetection2D::Intersection(staticRectangle, circle) )
			{
				//Handle collision
				#ifdef PHYSICS_DEBUG
				std::cout << "Collision occurred between circle at: (" << circle->Center.X << ", " << circle->Center.Y << ") and static rectangle at (MinX: " << staticRectangle->MinX << ", MinY: " << staticRectangle->MinY << ")" << std::endl;
				#endif
			}

			if( CollisionDetection2D::Intersection(staticCircle, rectangle) )
			{
				//Handle collision
				#ifdef PHYSICS_DEBUG
				std::cout << "Collision occurred between static circle at: (" << staticCircle->Center.X << ", " << staticCircle->Center.Y << ") and rectangle at (MinX: " << rectangle->MinX << ", MinY: " << rectangle->MinY << ")" << std::endl;
				#endif
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
				#ifdef PHYSICS_DEBUG
				std::cout << "Collision occurred between circle at: (" << movingCircle->Center.X << ", " << movingCircle->Center.Y << ") and circle at: (" << circle->Center.X << ", " << circle->Center.Y << ")" << std::endl;
				#endif
			}
			if( CollisionDetection2D::Intersection(movingRectangle, circle) )
			{
				//Handle collision
				#ifdef PHYSICS_DEBUG
				std::cout << "Collision occurred between circle at: (" << circle->Center.X << ", " << circle->Center.Y << ") and rectangle at (MinX: " << movingRectangle->MinX << ", MinY: " << movingRectangle->MinY << ")" << std::endl;
				#endif
			}

			if( CollisionDetection2D::Intersection(movingCircle, rectangle) )
			{
				//Handle collision
				#ifdef PHYSICS_DEBUG
				std::cout << "Collision occurred between circle at: (" << movingCircle->Center.X << ", " << movingCircle->Center.Y << ") and rectangle at (MinX: " << rectangle->MinX << ", MinY: " << rectangle->MinY << ")" << std::endl;
				#endif
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
	//(*movingObjectIterator)->Move(circle, deltaT);

	float secondDivisionFactor = 0.001f;

	if((*movingObjectIterator)->GetOwner() == NULL)
	{
		circle->Center->X = (*movingObjectIterator)->GetCircularRepresentation()->Center->X 
		+ (*movingObjectIterator)->GetDirection()->X * (*movingObjectIterator)->GetMovementSpeed() * (deltaT * secondDivisionFactor);
		circle->Center->Y = (*movingObjectIterator)->GetCircularRepresentation()->Center->Y 
		+ (*movingObjectIterator)->GetDirection()->Y * (*movingObjectIterator)->GetMovementSpeed() * (deltaT * secondDivisionFactor);	
	}
	else
	{
		float tempX = (*movingObjectIterator)->GetCircularRepresentation()->Center->X 
		+ (*movingObjectIterator)->GetDirection()->X * (*movingObjectIterator)->GetMovementSpeed() * (deltaT * secondDivisionFactor);
		float tempY = (*movingObjectIterator)->GetCircularRepresentation()->Center->Y 
		+ (*movingObjectIterator)->GetDirection()->Y * (*movingObjectIterator)->GetMovementSpeed() * (deltaT * secondDivisionFactor);
		
		(*movingObjectIterator)->GetOwner()->SetPos2D(tempX,tempY);
	}
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

	delete map;
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
			radius = SINGLETONINSTANCE(PathPlanner)->ConvertToPlanningMapCoordinate(radius);

			for (int i = -radius; i <= radius; i++ )
			{
				for (int j = -radius; j <= radius; j++)
				{
					if (x + i < MAP_SIZE && y + j < MAP_SIZE)
					{
						map->at(x + i)[y + j] = BLOCKED;
					}
				}
			}
		}
		else if((*staticObjectIterator)->GetShape() == RECTANGULARSHAPE)
		{
			auto rectangle = (*staticObjectIterator)->GetRectangularRepresentation();
			int width = SINGLETONINSTANCE(PathPlanner)->ConvertToPlanningMapCoordinate(rectangle->Width);
			int height = SINGLETONINSTANCE(PathPlanner)->ConvertToPlanningMapCoordinate(rectangle->Height);

			for (int i = 0; i < width; i++ )
			{
				for (int j = 0; j < height; j++)
				{
					if (x + i < MAP_SIZE && y + j < MAP_SIZE)
					{
						map->at(x + i)[y + j] = BLOCKED;
					}
				}
			}
		}
	}
	SINGLETONINSTANCE(PathPlanner)->UpdateDynamicMap(map);

	delete map;

	//Refresh moving objects path...
	std::vector<MovingObjectModel*>::iterator dynamicObjectIterator;
	for(dynamicObjectIterator = m_MovingObjects->begin(); 
		dynamicObjectIterator != m_MovingObjects->end();
		dynamicObjectIterator++)
	{
		float targetPosX = (*dynamicObjectIterator)->GetTargetPosition()->X;
		float targetPosY = (*dynamicObjectIterator)->GetTargetPosition()->Y;

		(*dynamicObjectIterator)->SetTargetPosition(new Point(targetPosX, targetPosY));
	}
}
