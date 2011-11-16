#ifndef ITUENGINE_PHYSICSMODEL_H
#define ITUENGINE_PHYSICSMODEL_H

#include <Math/GeometricFigures2D.hpp>

template <typename T>
class PhysicsModel
{
public:

	PhysicsModel(bool isStationary) : isStatic(isStationary) 
	{
	}

	~PhysicsModel()
	{
		delete &geometricRepresentation;
	}

	void Init(T &geoRep)
	{
		//Copy the geometric representation.
		geometricRepresentation = T(geoRep);		
	}

	T* GetGeometricRepresentation()
	{
		return &geometricRepresentation;
	}

protected:
	T geometricRepresentation;

	bool isStatic;
};

template <typename T>
class StaticObjectModel : PhysicsModel<T>
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
class MovingObjectModel : PhysicsModel<T>
{
public:
	MovingObjectModel(Point &pos, Point &dir) : PhysicsModel(false), position(pos), direction(dir),
	{
		targetPosition = NULL;
	}

	~MovingObjectModel()
	{
		delete &phantom;
		delete &position;
		delete &direction;
		delete &targetPosition;
	}

	void Init(T &geoRep)
	{
		//Copy the geometric representation.
		geometricRepresentation = T(geoRep);		
		phantom = T(geoRep);
	}

	T* GetPhantom()
	{
		return &phantom;
	}

	Point* GetPosition()
	{
		return &position;
	}

	Point* GetDirection()
	{
		return &direction;
	}

	Point* GetTargetPosition()
	{
		return &targetPosition;
	}

protected:
	Point position;
	Point direction;
	Point targetPosition;

	T phantom;
};



#endif //ITUENGINE_PHYSICSMODEL_H