#ifndef ITUENGINE_PHYSICSMODEL_H
#define ITUENGINE_PHYSICSMODEL_H

#include <Math/GeometricFigures2D.hpp>
#include <assert.h>
#include <Templates/TSingleton.hpp>
#include <Game/PathPlanner.hpp>
#include <vector>
#include <Math/Vector2f.hpp>
#include <Events/Interfaces/IEventListener.hpp>
#include <Managers/EventManager.hpp>


class Object;

#define RECTANGULARSHAPE 1
#define CIRCULARSHAPE 2

//Moving Object Types
#define PLAYERTYPE 10
#define CRITTERTYPE 11

//Maximum movementSpeeds
#define MAXIMUMPLAYERSPEED 5.0f
#define MAXIMUMCRITTERSPEED 1.5f


class PhysicsModel
{
public:

	PhysicsModel(int shape, bool isStationary) : m_IsStationary(isStationary), m_Shape(shape) { }

	~PhysicsModel() 
	{
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

	void virtual InitializeAsCircle(Circle &circularRepresentation)
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

	void SetPosition(Point pos)
	{
		if(m_Shape == RECTANGULARSHAPE)
		{
			m_RectangularRepresentation.setPos(pos.X, pos.Y);
		}
		else if(m_Shape == CIRCULARSHAPE)
		{
			m_CircularRepresentation.setPos(pos.X, pos.Y);
		}
		else
		{
			assert(false && "Failed to get the position because the shape is defined wrong.");
		}
	}

	void SetPosition(float x, float y)
	{
		if(m_Shape == RECTANGULARSHAPE)
		{
			m_RectangularRepresentation.setPos(x, y);
		}
		else if(m_Shape == CIRCULARSHAPE)
		{
			m_CircularRepresentation.setPos(x, y);
		}
		else
		{
			assert(false && "Failed to get the position because the shape is defined wrong.");
		}
	}

	void scale(float x, float y)
	{
		if(m_Shape == RECTANGULARSHAPE)
		{
			m_RectangularRepresentation.scale(x,y);

		}
		else if(m_Shape == CIRCULARSHAPE)
		{
			m_CircularRepresentation.scale(x,y);
		}
		else
		{
			assert(false && "Failed to get the position because the shape is defined wrong.");
		}
	}

	void virtual SetDirection(float x, float y);
	void virtual SetTargetPosition(Point *target){}

	void debug()
	{
		if(m_Shape == RECTANGULARSHAPE)
		{
			std::cout << "Rectangle min: " << m_RectangularRepresentation.MinXY.X << ", " << m_RectangularRepresentation.MinXY.Y << std::endl;
			Point center;
			center.X = m_RectangularRepresentation.MinXY.X + m_RectangularRepresentation.Width/2.0f;
			center.Y = m_RectangularRepresentation.MinXY.Y + m_RectangularRepresentation.Height/2.0f;
			std::cout << "Rectangle center: " << center.X << ", " << center.Y << std::endl;
			std::cout << "Rectangle width: " << m_RectangularRepresentation.Width << std::endl;
			std::cout << "Rectangle height: " << m_RectangularRepresentation.Height << std::endl;
			std::cout << "Rectangle Max: " << m_RectangularRepresentation.MaxX << ", " << m_RectangularRepresentation.MaxY << std::endl;
		}
		else if(m_Shape == CIRCULARSHAPE)
		{
			std::cout << "Circle center: " << m_CircularRepresentation.Center.X << ", " << m_CircularRepresentation.Center.Y << std::endl;
			std::cout << "Circle radius: " << m_CircularRepresentation.Radius << std::endl;
		}
		else
		{
			assert(false && "Failed to get the position because the shape is defined wrong.");
		}
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
	MovingObjectModel(int shape, int type, Point &dir, Object* owner) 
		: PhysicsModel(shape, false), m_Direction(dir), m_Type(type), m_Owner(owner)
	{
		//No movement on construction
		m_MovementSpeed = 0.0f;

		//Set to null
		m_TargetPosition = NULL;
		m_Path = NULL;
	}

	~MovingObjectModel()
	{
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

		if(!SINGLETONINSTANCE(PathPlanner)->evaluateCoordinate(&(target->X), &(target->Y)))
		{
			m_Path = new std::vector<Point>();
			target->X = GetPosition()->X;
			target->Y = GetPosition()->Y;
			m_Path->push_back(Point(*target));
		}
		else
		{
			m_Path = SINGLETONINSTANCE(PathPlanner)->aStar(target->X, target->Y, GetPosition()->X, GetPosition()->Y);
		}

		delete m_TargetPosition;
		m_TargetPosition = target;

		calcDirection();
	}

	void calcDirection();

	void SetDirection(float x, float y);

	void RecalculatePath();

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

	Object* GetOwner()
	{
		return m_Owner;
	}
	
	void HandleCollsion()
	{
		m_MovementSpeed = 0;
	}
	
protected:
	Point m_Direction;
	float m_MovementSpeed;
	int m_Type;

	Object* m_Owner;
	Point *m_TargetPosition;
	std::vector<Point> *m_Path;

	Circle m_CirclePhantom;
	Rectangle m_RectanglePhantom;
};

#endif //ITUENGINE_PHYSICSMODEL_H