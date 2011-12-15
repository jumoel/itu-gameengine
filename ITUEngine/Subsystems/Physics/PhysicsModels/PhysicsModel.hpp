#ifndef ITUENGINE_PHYSICSMODEL_H
#define ITUENGINE_PHYSICSMODEL_H

#include <Math/GeometricFigures2D.hpp>
#include <assert.h>
#include <Templates/TSingleton.hpp>
#include <Game/PathPlanner.hpp>
#include <vector>
#include <Vector2f.hpp>
#include <Events/Interfaces/IEventListener.hpp>
#include <Managers/EventManager.hpp>

#define RECTANGULARSHAPE 1
#define CIRCULARSHAPE 2

//Moving Object Types
#define PLAYERTYPE 10
#define CRITTERTYPE 11

//Maximum movementSpeeds
#define MAXIMUMPLAYERSPEED 1.0f
#define MAXIMUMCRITTERSPEED 0.1f


class PhysicsModel
{
public:

	PhysicsModel(int shape, bool isStationary) : m_IsStationary(isStationary), m_Shape(shape) { }

	~PhysicsModel() 
	{
		delete &m_CircularRepresentation;
		delete &m_RectangularRepresentation;
	}
	
	const int GetShape()
	{
		return m_Shape;
	}

	void InitializeAsRectangle(Rectangle &rectangularRepresentation)
	{
		//Copy the geometric representation.
		m_RectangularRepresentation = Rectangle(rectangularRepresentation);
	}

	void InitializeAsCircle(Circle &circularRepresentation)
	{
		//Copy the geometric representation.
		m_CircularRepresentation = Circle(circularRepresentation);		
	}

	Rectangle* GetRectangularRepresentation()
	{
		return &m_RectangularRepresentation;
	}

	Circle* GetCircularRepresentation()
	{
		return &m_CircularRepresentation;
	}

	Point* GetPosition()
	{
		if(m_Shape == RECTANGULARSHAPE)
		{
			return &(m_RectangularRepresentation.MinXY);
		}
		else if(m_Shape == CIRCULARSHAPE)
		{
			return &(m_CircularRepresentation.Center);
		}

		assert(false && "Failed to get the position because the shape is defined wrong.");
		return 0;
	}

protected:
	Circle m_CircularRepresentation;
	Rectangle m_RectangularRepresentation;

	bool m_IsStationary;
	const int m_Shape;
};

class StaticObjectModel : public PhysicsModel
{
public:
	StaticObjectModel(int shape) : PhysicsModel(shape, true)
	{

	}

	~StaticObjectModel()
	{

	}

protected:

};

class MovingObjectModel : public PhysicsModel
{
public:
	MovingObjectModel(int shape, int type, Point &dir) 
		: PhysicsModel(shape, false), m_Direction(dir), m_Type(type)
	{
		//No movement on construction
		m_MovementSpeed = 0.0f;

		//Set to null
		m_TargetPosition = NULL;
		m_Path = NULL;
	}

	~MovingObjectModel()
	{
		delete &m_CirclePhantom;
		delete &m_RectanglePhantom;
		delete m_TargetPosition;
		delete m_Path;
	}

	void InitializeAsCircle(Circle &geoRep)
	{
		//Copy the geometric representation.
		m_CircularRepresentation = Circle(geoRep);		
		m_CirclePhantom = Circle(geoRep);
		m_TargetPosition = new Point(m_CircularRepresentation.Center);
	}

	void InitializeAsRectangle(Rectangle &geoRep)
	{
		//Copy the geometric representation.
		m_RectangularRepresentation = Rectangle(geoRep);
		m_RectanglePhantom = Rectangle(geoRep);
		m_TargetPosition = new Point(m_RectangularRepresentation.MinXY);
	}

	Circle* GetCirclePhantom()
	{
		return &m_CirclePhantom;
	}
	
	Rectangle* GetRectanglePhantom()
	{
		return &m_RectanglePhantom;
	}

	Point* GetDirection()
	{
		return &m_Direction;
	}

	Point* GetTargetPosition()
	{
		return m_TargetPosition;
	}

	void SetTargetPosition(Point *target)
	{
		if(m_Path != NULL)
		{
			delete m_Path;
		}

		m_Path = SINGLETONINSTANCE(PathPlanner)->aStar(target->X, target->Y, GetPosition()->X, GetPosition()->Y);

		delete m_TargetPosition;
		m_TargetPosition = target;

		SetDirection();
	}

	void SetDirection()
	{
		if(m_Path != NULL && !m_Path->empty())
		{
			auto next = m_Path->at(0);

			auto pos = GetPosition();

			Point tempDirection = next - pos;

			m_Direction = tempDirection.GetNormalizedPoint();
		}
	}

	void RecalculatePath()
	{
		//Only do stuff if the path contains elements.
		if(m_Path != NULL && !m_Path->empty())
		{
			auto next = m_Path->at(0);

			Point tempDirection = &next - GetPosition();

			tempDirection = tempDirection.GetNormalizedPoint();

			Point oppositDirection = m_Direction.GetNegatedPoint();

			//If direction got negated, we overshot our target or if we have reached our next goal
			if(tempDirection == &oppositDirection || next == GetPosition())
			{
				m_Path->erase(m_Path->begin());

				if(m_Path->empty())
				{
					m_MovementSpeed = 0;
				}
				else
				{
					next = m_Path->at(0);
					auto pos = GetPosition();

					Point newDirection = next - pos;
					m_Direction = newDirection.GetNormalizedPoint();
				}

			}
		}
	}

	void SetMovementSpeed(float movement)
	{
		m_MovementSpeed = movement;
	}

	void SetMaxMovementSpeed()
	{
		if(m_Type == PLAYERTYPE)
		{
			m_MovementSpeed = MAXIMUMPLAYERSPEED;
		}
		else if(m_Type == CRITTERTYPE)
		{
			m_MovementSpeed = MAXIMUMCRITTERSPEED;
		}
		else
		{
			//Should not occur.
			m_MovementSpeed = 0.0f;
		}
	}

	std::vector<Point>* GetPath()
	{
		return m_Path;
	}

	float GetMovementSpeed()
	{
		return m_MovementSpeed;
	}
	
	void HandleCollsion()
	{
		m_MovementSpeed = 0;
	}

protected:
	Point m_Direction;
	float m_MovementSpeed;
	int m_Type;

	Point *m_TargetPosition;
	std::vector<Point> *m_Path;

	Circle m_CirclePhantom;
	Rectangle m_RectanglePhantom;
};

#endif //ITUENGINE_PHYSICSMODEL_H