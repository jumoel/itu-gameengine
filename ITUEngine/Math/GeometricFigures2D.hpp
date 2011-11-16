#ifndef ITUENGINE_GEOMETRICFIGURES2D_H
#define ITUENGINE_GEOMETRICFIGURES2D_H

struct GeometricFigure
{
	
};

struct Point : GeometricFigure
{
public:
	Point(float x, float y) : X(x), Y(y) {}
	Point(Point &point) : X(point.X), Y(point.Y) {}

	float X, Y;
};

struct Line : GeometricFigure
{
public:
	Line(Point a, Point b) : A(a), B(b) {}
	Line(Line &line) : A(line.A), B(line.B) {}

	Point A, B;
};

struct Circle : GeometricFigure
{
public:
	Circle(Point center, float radius) : Center(center), Radius(radius) {}
	Circle(Circle &circle) : Center(circle.Center), Radius(circle.Radius) {}

	Point Center;
	float Radius;
};

struct Rectangle : GeometricFigure
{
public:
	Rectangle(Point topLeft, float width, float height) : TopLeft(topLeft), Width(width), Height(height)
	{
		Init();
	}

	Rectangle(Rectangle &rectangle) : TopLeft(rectangle.TopLeft), Width(rectangle.Width), Height(rectangle.Height) 
	{
		Init();
	}

	Point TopLeft;
	float Width, Height, Top, Bottom, Left, Right;

private:
	void Init() 
	{
		Left = TopLeft.X;
		Right = TopLeft.X + Width;

		Top = TopLeft.Y;
		Bottom = TopLeft.Y + Height;
	}
};

#endif //ITUENGINE_GEOMETRICFIGURES2D_H