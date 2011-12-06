#ifndef ITUENGINE_GEOMETRICFIGURES2D_H
#define ITUENGINE_GEOMETRICFIGURES2D_H
#include <Vector2f.hpp>
#include <cmath>

struct Point
{
public:
	//Do not use this, to initialize use other constructors 
	Point() {}

	Point(Point &point) : X(point.X), Y(point.Y) {}
	Point(Vector2f vect) : X(vect.x()), Y(vect.y()) {}
	Point(float x, float y) : X(x), Y(y) {}

	Point operator -(Point *point)
	{
		return Point((this->X-point->X), (this->Y-point->Y));
	}

	bool operator ==(Point *point)
	{
		float epsilon =  0.00001f;
		float diffX = this->X - point->X;
		float diffY = this->Y - point->Y;

		if((-epsilon > diffX) || (diffX > epsilon))
		{
			return false;
		}

		if((-epsilon > diffY) || (diffY > epsilon))
		{
			return false;
		}

		return true;
	}

	Point GetNormalizedPoint()
	{
		float length = GetLength();
		return Point(X/length, Y/length);
	}

	float GetLength()
	{
		return sqrt(X*X + Y*Y);
	}

	Point GetNegatedPoint()
	{
		return Point(-1*X, -1*Y);
	}

	float X, Y;
};

struct Line
{
public:
	//Do not use this, to initialize use other constructors 
	Line() {}

	Line(Point a, Point b) : A(a), B(b) {}
	Line(Line &line) : A(line.A), B(line.B) {}
	~Line() 
	{ 
		//delete &A; delete &B; 
	}

	Point A, B;
};

struct Circle
{
public:
	//Do not use this, to initialize use other constructors 
	Circle() {}

	Circle(Point center, float radius) : Center(center), Radius(radius) {}
	Circle(Circle &circle) : Center(circle.Center), Radius(circle.Radius) {}
	~Circle() 
	{ 
		//delete &Center; 
	}

	Point Center;
	float Radius;
};

struct Rectangle
{
public:
	//Do not use this, to initialize use other constructors 
	Rectangle() {}

	Rectangle(Point minXY, float width, float height) : MinXY(minXY), Width(width), Height(height)
	{
		Init();
	}

	Rectangle(Rectangle &rectangle) : MinXY(rectangle.MinXY), Width(rectangle.Width), Height(rectangle.Height) 
	{
		Init();
	}

	~Rectangle() 
	{ 
		//delete &MinXY; 
	}

	Point MinXY;
	float Width, Height, MinY, MaxY, MinX, MaxX;

private:
	void Init() 
	{
		MinX = MinXY.X;
		MaxX = MinXY.X + Width;

		MinY = MinXY.Y;
		MaxY = MinXY.Y + Height;
	}
};

#endif //ITUENGINE_GEOMETRICFIGURES2D_H