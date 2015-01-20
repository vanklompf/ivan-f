#include "stdafx.h"
#include "CppUnitTest.h"
#include "v2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FeLibTests
{
	TEST_CLASS(v2Tests)
	{
	public:

		TEST_METHOD(TestV2Ctor)
		{
			v2 point(1, -1);

			Assert::AreEqual(1, point.X);
			Assert::AreEqual(-1, point.Y);
		}

		TEST_METHOD(TestV2Operator_add)
		{
			v2 point1(1, -1);
			v2 point2(2, 3);
			v2 sum = point1 + point2;

			Assert::AreEqual(3, sum.X);
			Assert::AreEqual(2, sum.Y);
		}
	};
}