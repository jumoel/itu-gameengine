#include <Math/CollisionDetection2D.hpp>
#include <Math/GeometricFigures2D.hpp>
#include <cstdlib>

float CollisionDetection2D::DistanceSquared( Point *p1, Point *p2 )
{
	//Check for NULL input
	if(p1 == NULL || p2 == NULL) 
	{
		return -1;
	}

	float x = p1->X - p2->X;
	float y = p1->Y - p2->Y;

	return x * x + y * y;
}

float CollisionDetection2D::DistanceSquared( Point *point, Rectangle *rectangle )
{
	//Check for NULL input
	if(point == NULL || rectangle == NULL) 
	{
		return -1;
	}

	// Find the closest point to the point within the rectangle
	Point closestPoint(GetValueBetween(point->X, rectangle->MinX, rectangle->MaxX), GetValueBetween(point->Y, rectangle->MinY, rectangle->MaxY));

	// Calculate the distance between the point and this closest point
	return DistanceSquared(&closestPoint, point);
}

bool CollisionDetection2D::Intersection( Point *point, Rectangle *rectangle )
{
	//Check for NULL input
	if(point == NULL || rectangle == NULL) 
	{
		return false;
	}

	if(rectangle->MinX <= point->X && point->X <= rectangle->MaxX)
	{
		if(rectangle->MinY <= point->Y && point->Y <= rectangle->MaxY)
		{
			return true;
		}
	}

	return false;
}

bool CollisionDetection2D::Intersection( Point *point, Circle *circle )
{
	//Check for NULL input
	if(point == NULL || circle == NULL) 
	{
		return false;
	}

	//Get the Squared distance between centers
	float centerDistanceSquared = DistanceSquared(point, (circle->Center));

	// If the distance is less than the radius, an intersection occurs.
	return (circle->Radius * circle->Radius) > centerDistanceSquared;
}

bool CollisionDetection2D::Intersection( Circle *circle, Rectangle *rectangle )
{
	return Intersection(rectangle, circle);
}

bool CollisionDetection2D::Intersection( Rectangle *rectangle, Circle *circle )
{
	//Check for NULL input
	if(rectangle == NULL || circle == NULL) 
	{
		return false;
	}

	//Get the Squared distance
	float distanceSquared = DistanceSquared((circle->Center), rectangle);

	// If the distance is less than the circle's radius, an intersection occurs
	return distanceSquared < (circle->Radius * circle->Radius);
}

bool CollisionDetection2D::Intersection( Circle *c1, Circle *c2 )
{
	//Check for NULL input
	if(c1 == NULL || c2 == NULL) 
	{
		return false;
	}

	//Get the Squared distance between centers
	float centerDistanceSquared = DistanceSquared((c1->Center), (c2->Center));

	// Add the 2 radii together
	float radii = c1->Radius + c2->Radius;

	// If the distance is less than the radii, an intersection occurs.
	return (radii * radii) > centerDistanceSquared;
}

// GetValueBetween(value, min, max) - limits value to the range min..max
float CollisionDetection2D::GetValueBetween( float Value, float min, float max )
{
	if(Value <= min)
	{
		return min;
	} 
	
	if(Value >= max)
	{
		return max;
	}

	return Value;
}
