#ifndef ITUENGINE_CIRCLEPHYSICSMODEL_H
#define ITUENGINE_CIRCLEPHYSICSMODEL_H

#include <Subsystems/Physics/PhysicsModels/PhysicsModel.hpp>

class MovingCirclePhysicsModel : MovingObjectModel<Circle>
{
public:
	MovingCirclePhysicsModel(Point &pos, Point &dir, float radius) : PhysicsModel(pos, dir)
	{
		Init(Circle(pos, radius));
	}
	
	~MovingCirclePhysicsModel() {}

private:

};

#endif //ITUENGINE_CIRCLEPHYSICSMODEL_H