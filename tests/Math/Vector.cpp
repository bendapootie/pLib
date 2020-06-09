#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace pLib_Test
{		
	TEST_CLASS(Test_Math_Vector)
	{
	public:

		TEST_METHOD(Test_Vector2)
		{
			Assert::IsTrue(sizeof(Vector2) == sizeof(float)* 2);

			Vector2 v1(0.5f, 0.25f);
			Vector2 v2(v1);

			Assert::IsTrue(v1 == v2);

			v1.Ptr()[0] = 4.0f;
			v1.Ptr()[1] = 2.5f;
			Assert::IsTrue(v1.x == 4.0f);
			Assert::IsTrue(v1.y == 2.5f);

			Assert::IsTrue(v1 != v2);
		}

		TEST_METHOD(Test_Vector3)
		{
			// TODO: Test RotateYawPitchRoll()

			Vector3 right(Vector3::UnitX);
			Vector3 forward = Vector3::UnitY;
			Vector3 up = Vector3::UnitZ;

			Assert::IsTrue(right.Cross(forward) == up);
			Assert::IsTrue(forward.Cross(up) == right);
			Assert::IsTrue(up.Cross(right) == forward);

			const float vectorEpsilon = 0.00001f;

			// Rotate around x-axis
			Vector3 test = Vector3::UnitY;
			test.RotateAroundXAxis(Math::DegToRad(90.0f));
			Assert::IsTrue(test.GetDistance(Vector3::UnitZ) < vectorEpsilon);

			test = Vector3::UnitY;
			test.RotateAroundAxis(Vector3::UnitX, Math::DegToRad(90.0f));
			Assert::IsTrue(test.GetDistance(Vector3::UnitZ) < vectorEpsilon);

			// Rotate around y-axis
			test = Vector3::UnitZ;
			test.RotateAroundYAxis(Math::DegToRad(90.0f));
			Assert::IsTrue(test.GetDistance(Vector3::UnitX) < vectorEpsilon);

			test = Vector3::UnitZ;
			test.RotateAroundAxis(Vector3::UnitY, Math::DegToRad(90.0f));
			Assert::IsTrue(test.GetDistance(Vector3::UnitX) < vectorEpsilon);

			// Rotate around z-axis
			test = Vector3::UnitX;
			test.RotateAroundZAxis(Math::DegToRad(90.0f));
			Assert::IsTrue(test.GetDistance(Vector3::UnitY) < vectorEpsilon);

			test = Vector3::UnitX;
			test.RotateAroundAxis(Vector3::UnitZ, Math::DegToRad(90.0f));
			Assert::IsTrue(test.GetDistance(Vector3::UnitY) < vectorEpsilon);

			for (float a = -360.0f; a < 360.0f; a += 1.0f)
			{
				const float rad = Math::DegToRad(a);
				const Vector3 test(4.0f * Math::Sin(a), Math::Cos(rad * 4.0f), a * 0.01f);

				Vector3 t1(test);
				Vector3 t2(test);
				t1.RotateAroundAxis(Vector3::UnitX, rad);
				t2.RotateAroundXAxis(rad);
				Assert::IsTrue(t1.GetDistance(t2) < vectorEpsilon);

				t1 = test;
				t2 = test;
				t1.RotateAroundAxis(Vector3::UnitY, rad);
				t2.RotateAroundYAxis(rad);
				Assert::IsTrue(t1.GetDistance(t2) < vectorEpsilon);

				t1 = test;
				t2 = test;
				t1.RotateAroundAxis(Vector3::UnitZ, rad);
				t2.RotateAroundZAxis(rad);
				Assert::IsTrue(t1.GetDistance(t2) < vectorEpsilon);
			}
		}
	};
}