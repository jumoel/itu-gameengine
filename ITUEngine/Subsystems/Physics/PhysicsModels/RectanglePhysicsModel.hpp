#ifndef ITUENGINE_CIRCLEPHYSICSMODEL_H
#define ITUENGINE_CIRCLEPHYSICSMODEL_H

#include <Subsystems/Physics/PhysicsModels/PhysicsModel.hpp>

class StaticRectanglePhysicsModel : StaticObjectModel<Rectangle>
{
public:
	StaticRectanglePhysicsModel(Point &topLeft, float width, float height) : StaticObjectModel()
	{
		Init(Rectangle(topLeft, width, height));
	}

	~StaticRectanglePhysicsModel() {}


private:

};

#endif //ITUENGINE_CIRCLEPHYSICSMODEL_H