#ifndef ITUENGINE_PHYSICSMODEL_H
#define ITUENGINE_PHYSICSMODEL_H

#include <Math/GeometricFigures2D.hpp>

template <typename T>
class PhysicsModel
{
public:

	PhysicsModel(bool isStationary) : m_IsStationary(isStationary) { }

	~PhysicsModel()
	{
		delete &m_GeometricRepresentation;
	}

	void Init(T &geometricRepresentation)
	{
		//Copy the geometric representation.
		m_GeometricRepresentation = T(geometricRepresentation);		
	}

	T* GetGeometricRepresentation()
	{
		return &m_GeometricRepresentation;
	}

protected:
	T m_GeometricRepresentation;

	bool m_IsStationary;
};

template <typename T>
class StaticObjectModel : public PhysicsModel<T>
{
public:
	StaticObjectModel() : PhysicsModel(true)
	{

	}

	~StaticObjectModel()
	{

	}

protected:

};

template <typename T>
class MovingObjectModel : public PhysicsModel<T>
{
public:
	MovingObjectModel(float movementSpeed, Point &pos, Point &dir) : PhysicsModel(false), m_Position(pos), m_Direction(dir)
	{
		m_MovementSpeed = movementSpeed;
		
		//Set to null
		m_TargetPosition = 0;
	}

	~MovingObjectModel()
	{
		delete &m_Phantom;
		delete &m_Position;
		delete &m_Direction;
		delete m_TargetPosition;
	}

	void Init(T &geoRep)
	{
		//Copy the geometric representation.
		m_GeometricRepresentation = T(geoRep);		
		m_Phantom = T(geoRep);
	}

	T* GetPhantom()
	{
		return &m_Phantom;
	}

	Point* GetPosition()
	{
		return &m_Position;
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
	Point m_Position;
	Point m_Direction;
	Point *m_TargetPosition;
	float m_MovementSpeed;

	T m_Phantom;
};

#endif //ITUENGINE_PHYSICSMODEL_H