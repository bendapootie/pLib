#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace pLib_Test
{		
	TEST_CLASS(Test_Math_Matrix)
	{
	public:

		TEST_METHOD(Test_Matrix)
		{
			// TODO: Test transformations, operations, conversions to/from quaternions/transforms
			Assert::IsTrue(sizeof(Matrix) == 16 * sizeof(float));
		}
	};
}