#pragma once

namespace Math
{
	// Test if two lines intersect.
	// Lines are described by two points.  One line by (p0->p1) and the other by (p2->p3)
	// If lines intersect, 'true' is returned and if 'output' is not null, it will be set to the position of the intersection
	// If lines don't intersect, 'false' is returned and 'output' is undefined
	bool IntersectLineLine(Vector2* output, const Vector2 p0, const Vector2 p1, const Vector2 p2, const Vector2 p3);

	// Finds the closest point between two lines in 3d.
	// Lines are described by two points.  One line by (p0->p1) and the other by (p2->p3)
	// If there is one solution, 'true' is returned and 'output0' and 'output1' will be set
	// to the points on each of the lines that is the closest to the other.
	// If there are no solutions or multiple, 'false' is returned and the outputs are undefined.
	bool ClosestDistanceBetweenLines(Vector3* output0, Vector3* output1, const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3);
};
