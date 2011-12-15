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

	Circle(Point center, float radius) : Center(center), Radius(radius), initialRadius(radius) {}
	Circle(Circle &circle) : Center(circle.Center), Radius(circle.Radius), initialRadius(circle.Radius) {}
	~Circle() 
	{ 
		//delete &Center; 
	}

	void setPos(float x, float y)
	{
		Center.X = x;
		Center.Y = y;
	}

	void scale(float x, float y)
	{
		float temp = x;
		if(temp < y)
		{
			temp = y;
		}
		Radius = initialRadius * temp;
	}

	Point Center;
	float Radius;
	float initialRadius;
};

struct Rectangle
{
public:
	//Do not use this, to initialize use other constructors 
	Rectangle() {}

	Rectangle(Point minXY, float width, float height) : MinXY(minXY), Width(width), Height(height), initialWidth(width), initialHeight(height)
	{
		Init();
	}

	Rectangle(Rectangle &rectangle) : MinXY(rectangle.MinXY), Width(rectangle.Width), Height(rectangle.Height), initialWidth(rectangle.Width), initialHeight(rectangle.Height) 
	{
		Init();
	}

	~Rectangle() 
	{ 
		//delete &MinXY; 
	}

	void setPos(float x, float y)
	{
		MinXY.X = x - Width/2.0f;
		MinXY.Y = y - Height/2.0f;
		MinX = MinXY.X;
		MaxX = MinXY.X + Width;

		MinY = MinXY.Y;
		MaxY = MinXY.Y + Height;
	}

	void scale(float x, float y)
	{
		Point temp;
		temp.X = MinXY.X + Width/2.0f;
		temp.Y = MinXY.Y + Height/2.0f;
		Height = initialHeight * y;
		Width = initialWidth * x;

		MinXY.X = temp.X - Width/2.0f;
		MinXY.Y = temp.Y - Height/2.0f;
		MinX = MinXY.X;
		MaxX = MinXY.X + Width;

		MinY = MinXY.Y;
		MaxY = MinXY.Y + Height;
	}

	Point MinXY;
	float Width, Height, MinY, MaxY, MinX, MaxX, initialWidth, initialHeight;

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