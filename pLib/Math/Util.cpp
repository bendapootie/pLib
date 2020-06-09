#include "Precompiled.h"

namespace Math
{
	bool IntersectLineLine(Vector2* output,
		const Vector2 p0, const Vector2 p1,
		const Vector2 p2, const Vector2 p3)
	{
		const float d = (p0.x - p1.x) * (p2.y - p3.y) - (p0.y - p1.y) * (p2.x - p3.x);
		// If d is zero, there is no intersection
		if (d == 0)
		{
			return false;
		}

		if (output != nullptr)
		{
			// Get the x and y
			const float pre = (p0.x * p1.y - p0.y * p1.x);
			const float post = (p2.x * p3.y - p2.y * p3.x);
			output->x = (pre * (p2.x - p3.x) - (p0.x - p1.x) * post) / d;
			output->y = (pre * (p2.y - p3.y) - (p0.y - p1.y) * post) / d;
		}

		return true;
	}


	bool ClosestDistanceBetweenLines(Vector3* output0, Vector3* output1,
		const Vector3& p0, const Vector3& p1,
		const Vector3& p2, const Vector3& p3)
	{
		// Algorithm is ported from the C algorithm of 
		// Paul Bourke at http://local.wasp.uwa.edu.au/~pbourke/geometry/lineline3d/
		Vector3 p02 = p0 - p2;
		Vector3 p32 = p3 - p2;

		if (p32.GetLengthSquared() < Math::FloatEpsilon) {
			return false;
		}
		Vector3 p10 = p1 - p0;
		if (p10.GetLengthSquared() < Math::FloatEpsilon) {
			return false;
		}

		float d0232 = (p02.x * p32.x) + (p02.y * p32.y) + (p02.z * p32.z);
		float d3210 = (p32.x * p10.x) + (p32.y * p10.y) + (p32.z * p10.z);
		float d0210 = (p02.x * p10.x) + (p02.y * p10.y) + (p02.z * p10.z);
		float d3232 = (p32.x * p32.x) + (p32.y * p32.y) + (p32.z * p32.z);
		float d1010 = (p10.x * p10.x) + (p10.y * p10.y) + (p10.z * p10.z);

		float denom = d1010 * d3232 - d3210 * d3210;
		if (Math::Abs(denom) < Math::FloatEpsilon) {
			return false;
		}
		float numer = d0232 * d3210 - d0210 * d3232;

		float mua = numer / denom;
		float mub = (d0232 + d3210 * (mua)) / d3232;

		if (output0 != nullptr)
		{
			output0->x = (float)(p0.x + mua * p10.x);
			output0->y = (float)(p0.y + mua * p10.y);
			output0->z = (float)(p0.z + mua * p10.z);
		}
		if (output1 != nullptr)
		{
			output1->x = (float)(p2.x + mub * p32.x);
			output1->y = (float)(p2.y + mub * p32.y);
			output1->z = (float)(p2.z + mub * p32.z);
		}

		return true;
	}
};
