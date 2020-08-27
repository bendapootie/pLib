#pragma once

// Integer equivalent of Vector2
struct Point2
{
public:
	static const Point2 Zero;		// (0, 0)
	static const Point2 One;		// (1, 1)
	static const Point2 UnitX;		// (1, 0)
	static const Point2 UnitY;		// (0, 1)

public:
	int x = 0;
	int y = 0;

	// Default constructor doesn't do any initialization
	Point2() {}
	Point2(int _x, int _y) : x(_x), y(_y) {}
	Point2(const Point2& other) : x(other.x), y(other.y) {}

	// Somewhat hacky functions to get an 'int' pointer to the start of the Point
	const int* Ptr() const { return &x; }
	int* Ptr() { return &x; }

	bool operator == (const Point2& other) const { return (x == other.x) && (y == other.y); }
	bool operator != (const Point2& other) const { return !(operator==(other)); }

	// In-place Point math functions
	void Add(const Point2& rhs) { x += rhs.x; y += rhs.y; }
	void Subtract(const Point2& rhs) { x -= rhs.x; y -= rhs.y; }

	int GetLengthSquared() const { return (x * x) + (y * y); }

	int GetManhattanDistance(const Point2& point) const { return Math::Abs(x - point.x) + Math::Abs(y - point.y); }
	int GetDistanceSquared(const Point2& point) const { return (x - point.x) * (x - point.x) + (y - point.y) * (y - point.y); }

	// Other Point functions
	Point2 PerElementMultiply(const Point2& rhs) const { return Point2(x * rhs.x, y * rhs.y); }
	Point2 PerElementDivide(const Point2& rhs) const { return Point2(x / rhs.x, y / rhs.y); }

	// Point overloaded operators
	Point2 operator + (const Point2& rhs) const { return Point2(x + rhs.x, y + rhs.y); }
	void operator += (const Point2& rhs) { x += rhs.x; y += rhs.y; }
	Point2 operator - (const Point2& rhs) const { return Point2(x - rhs.x, y - rhs.y); }
	void operator -= (const Point2& rhs) { x -= rhs.x; y -= rhs.y; }
	Point2 operator * (const int scale) const { return Point2(x * scale, y * scale); }
	void operator *= (const int scale) { x *= scale; y *= scale; }
};
