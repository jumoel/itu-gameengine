#ifndef ITUENGINE_COLLISIONDETECTION2D_H
#define ITUENGINE_COLLISIONDETECTION2D_H

#include <Math/GeometricFigures2D.hpp>

class CollisionDetection2D
{
public:
	//DistanceSquared
	static float DistanceSquared(Point *p1, Point *p2);
	static float DistanceSquared(Point *point, Rectangle *rectangle);


	//Intersection

	/* SUGGESTIONS, BUT NOT NEEDED !
	static bool Intersection(Point point, Line line);
	static bool Intersection(Line l1, Line l2);
	static bool Intersection(Line line, Rectangle rectangle);
	static bool Intersection(Rectangle r1, Rectangle r2);
	static bool Intersection(Line line, Circle circle);
	*/

	static bool Intersection(Point *point, Rectangle *rectangle);
	static bool Intersection(Point *point, Circle *circle);
	static bool Intersection(Rectangle *rectangle, Circle *circle);
	static bool Intersection(Circle *circle, Rectangle *rectangle);
	static bool Intersection(Circle *c1, Circle *c2);

private:
	//Helper
	static float GetValueBetween(float Value, float min, float max);
};

#endif //ITUENGINE_COLLISIONDETECTION2D_H