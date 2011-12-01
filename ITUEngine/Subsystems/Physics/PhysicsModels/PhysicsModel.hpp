#ifndef ITUENGINE_PHYSICSMODEL_H
#define ITUENGINE_PHYSICSMODEL_H

#include <Math/GeometricFigures2D.hpp>
#include <assert.h>

#define RECTANGULARSHAPE 1
#define CIRCULARSHAPE 2

class PhysicsModel
{
public:

	PhysicsModel(int shape, bool isStationary) : m_IsStationary(isStationary), m_Shape(shape) { }

	~PhysicsModel() { }
	
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
	MovingObjectModel(int shape, float movementSpeed, Point &dir) : PhysicsModel(shape, false), m_Direction(dir)
	{
		m_MovementSpeed = movementSpeed;
		
		//Set to null
		m_TargetPosition = 0;
	}

	~MovingObjectModel()
	{
		delete &m_CirclePhantom;
		delete m_TargetPosition;
	}

	void InitializeAsCircle(Circle &geoRep)
	{
		//Copy the geometric representation.
		m_CircularRepresentation = Circle(geoRep);		
		m_CirclePhantom = Circle(geoRep);
	}

	void InitializeAsRectangle(Rectangle &geoRep)
	{
		//Copy the geometric representation.
		m_RectangularRepresentation = Rectangle(geoRep);
		m_RectanglePhantom = Rectangle(geoRep);
	}

	Circle* GetCirclePhantom()
	{
		return &m_CirclePhantom;
	}
	
	Rectangle* GetRectanglePhantom()
	{
		return &m_RectanglePhantom;
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
		delete m_TargetPosition;
		m_TargetPosition = target;
	}

	float GetMovementSpeed()
	{
		return m_MovementSpeed;
	}

protected:
	Point m_Direction;
	Point *m_TargetPosition;
	float m_MovementSpeed;

	Circle m_CirclePhantom;
	Rectangle m_RectanglePhantom;
};

#endif //ITUENGINE_PHYSICSMODEL_H