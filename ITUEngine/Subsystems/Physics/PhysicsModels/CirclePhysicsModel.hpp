#ifndef ITUENGINE_CIRCLEPHYSICSMODEL_H
#define ITUENGINE_CIRCLEPHYSICSMODEL_H

#include <Subsystems/Physics/PhysicsModels/PhysicsModel.hpp>

class MovingCirclePhysicsModel : public MovingObjectModel<Circle>
{
public:
	MovingCirclePhysicsModel(float movementSpeed, Point &pos, Point &dir, float radius) : MovingObjectModel(movementSpeed, pos, dir)
	{
		Init(Circle(pos, radius));
	}
	
	~MovingCirclePhysicsModel() {}

private:

};

class StaticCirclePhysicsModel : public StaticObjectModel<Circle>
{
public:
	StaticCirclePhysicsModel(Point &pos, float radius) : StaticObjectModel()
	{
		Init(Circle(pos, radius));
	}

	~StaticCirclePhysicsModel() {}

private:

};

#endif //ITUENGINE_CIRCLEPHYSICSMODEL_H