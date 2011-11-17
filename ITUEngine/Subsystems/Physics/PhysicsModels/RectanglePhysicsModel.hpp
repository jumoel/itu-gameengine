#ifndef ITUENGINE_RECTANGLEPHYSICSMODEL_H
#define ITUENGINE_RECTANGLEPHYSICSMODEL_H

#include <Subsystems/Physics/PhysicsModels/PhysicsModel.hpp>

class StaticRectanglePhysicsModel : public StaticObjectModel<Rectangle>
{
public:
	StaticRectanglePhysicsModel(Point &topLeft, float width, float height) : StaticObjectModel()
	{
		Init(Rectangle(topLeft, width, height));
	}

	~StaticRectanglePhysicsModel() {}


private:

};

#endif //ITUENGINE_RECTANGLEPHYSICSMODEL_H
