#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace pLib_Test
{		
	TEST_CLASS(Test_Math_Util)
	{
	public:

		TEST_METHOD(Test_IntersectLineLine)
		{
			Vector2 p0, p1, p2, p3;
			Vector2 intersectPoint = Vector2::Zero;
			pCircularQueue<int, 4> p;

			const int msgSize = 1024;
			wchar_t msg[msgSize];

			for (float a0 = 0.0f; a0 < Math::Pi * 2.0f; a0 += 0.1f)
			{
				Math::SinCos(a0, p0.x, p0.y);
				p1 = p0 * 2.0f;
				for (float a1 = 0.0f; a1 < Math::Pi * 2.0f; a1 += 0.1f)
				{
					Math::SinCos(a1, p2.x, p2.y);
					p3 = p2 * 2.0f;

					// Skip lines that are parallel or nearly parallel
					const float dot = p0.Dot(p2);
					if (Math::Abs(dot) < 0.9999f)
					{
						bool intersects = Math::IntersectLineLine(&intersectPoint, p0, p1, p2, p3);

						// All these tests should intersect at (0, 0)

						const Vector2 correctAnswer(0.0f, 0.0f);
						float error = intersectPoint.GetDistance(correctAnswer);
						Assert::IsTrue(intersects && (error < Math::FloatEpsilon),
							Test_IntersectLineLine_GetMsg(msg, msgSize, p0, p1, p2, p3, intersects, intersectPoint));
					}
				}
			}

			// Test parallel lines
			p0 = Vector2(1.0f, 1.0f);
			p2 = Vector2(3.5f, 3.75f);
			for (float x = -5.0f; x <= 5.0f; x += 0.25f)
			{
				for (float y = -5.0f; y <= 5.0f; y += 0.25f)
				{
					Vector2 delta(x, y);
					if (delta != Vector2::Zero)
					{
						p1 = p0 + delta;
						p3 = p2 + delta;
						bool intersects = Math::IntersectLineLine(&intersectPoint, p0, p1, p2, p3);
						Assert::IsFalse(intersects, L"These lines are parallel and shouldn't return an intersect point");
					}
				}
			}
		}

	private:
		static const wchar_t* Test_IntersectLineLine_GetMsg(
			wchar_t* msg, const int msgSize,
			const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3,
			const bool intersects, const Vector2& intersectPoint)
		{
			if (intersects)
			{
				swprintf(msg, msgSize, L"(%0.2f, %0.2f)->(%0.2f, %0.2f) intersects (%0.2f, %0.2f)->(%0.2f, %0.2f) at (%0.2f, %0.2f)",
					p0.x, p0.y, p1.x, p1.y,
					p2.x, p2.y, p3.x, p3.y,
					intersectPoint.x, intersectPoint.y);
			}
			else
			{
				swprintf(msg, msgSize, L"(%0.2f, %0.2f)->(%0.2f, %0.2f) does not intersect (%0.2f, %0.2f)->(%0.2f, %0.2f)",
					p0.x, p0.y, p1.x, p1.y,
					p2.x, p2.y, p3.x, p3.y,
					intersectPoint.x, intersectPoint.y);
			}
			return msg;
		}
	};
}