#ifndef ITUENGINE_GEOMETRICFIGURES2D_H
#define ITUENGINE_GEOMETRICFIGURES2D_H

struct Point
{
public:
	//Do not use this, to initialize use other constructors 
	Point() {}

	Point(float x, float y) : X(x), Y(y) {}
	Point(Point &point) : X(point.X), Y(point.Y) {}

	float X, Y;
};

struct Line
{
public:
	//Do not use this, to initialize use other constructors 
	Line() {}

	Line(Point a, Point b) : A(a), B(b) {}
	Line(Line &line) : A(line.A), B(line.B) {}
	~Line() { delete &A; delete &B; }

	Point A, B;
};

struct Circle
{
public:
	//Do not use this, to initialize use other constructors 
	Circle() {}

	Circle(Point center, float radius) : Center(center), Radius(radius) {}
	Circle(Circle &circle) : Center(circle.Center), Radius(circle.Radius) {}
	~Circle() { delete &Center; }

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

	~Rectangle() { delete &MinXY; }

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