#ifndef ITUENGINE_GEOMETRICFIGURES2D_H
#define ITUENGINE_GEOMETRICFIGURES2D_H

struct Point
{
public:
	Point(float x, float y) : X(x), Y(y) {}
	Point(Point &point) : X(point.X), Y(point.Y) {}

	float X, Y;
};

struct Line
{
public:
	Line(Point a, Point b) : A(a), B(b) {}

	Point A, B;
};

struct Circle
{
public:
	Circle(Point center, float radius) : Center(center), Radius(radius) {}

	Point Center;
	float Radius;
};

struct Rectangle
{
public:
	Rectangle(Point topLeft, float width, float height) : TopLeft(topLeft), Width(width), Height(height)
	{
		Left = TopLeft.X;
		Right = TopLeft.X + Width;

		Top = TopLeft.Y;
		Bottom = TopLeft.Y + Height;
	}

	Point TopLeft;
	float Width, Height, Top, Bottom, Left, Right;
};

#endif //ITUENGINE_GEOMETRICFIGURES2D_H