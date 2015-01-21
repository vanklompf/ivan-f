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

		TEST_METHOD(TestV2Operator_Add)
		{
			v2 point1(1, -1);
			v2 point2(2, 3);
			v2 sum = point1 + point2;

			Assert::AreEqual(3, sum.X);
			Assert::AreEqual(2, sum.Y);
		}

		TEST_METHOD(TestV2Operator_AssignAdd)
		{
			v2 point1(1, -1);
			v2 point2(2, 3);
			point2 += point1;

			Assert::AreEqual(3, point2.X);
			Assert::AreEqual(2, point2.Y);
		}

		TEST_METHOD(TestV2Operator_Sub)
		{
			v2 point1(1, -1);
			v2 point2(2, 3);
			v2 sub = point2 - point1;

			Assert::AreEqual(1, sub.X);
			Assert::AreEqual(4, sub.Y);
		}

		TEST_METHOD(TestV2Operator_AssignSub)
		{
			v2 point1(1, -1);
			v2 point2(2, 3);
			point2 -= point1;

			Assert::AreEqual(1, point2.X);
			Assert::AreEqual(4, point2.Y);
		}

		TEST_METHOD(TestV2Operator_Negate)
		{
			v2 point(1, -3);
			v2 neg = -point;

			Assert::AreEqual(-1, neg.X);
			Assert::AreEqual(3, neg.Y);
		}

		TEST_METHOD(TestV2Operator_ScalarMul)
		{
			v2 point(2, -3);
			v2 mul = point * 4;

			Assert::AreEqual(8, mul.X);
			Assert::AreEqual(-12, mul.Y);
		}

		TEST_METHOD(TestV2Operator_AssignScalarMul)
		{
			v2 point(2, -3);
			point *= 4;

			Assert::AreEqual(8, point.X);
			Assert::AreEqual(-12, point.Y);
		}

		TEST_METHOD(TestV2Operator_ScalarDiv)
		{
			v2 point(8, -12);
			v2 mul = point / 4;

			Assert::AreEqual(2, mul.X);
			Assert::AreEqual(-3, mul.Y);
		}

		TEST_METHOD(TestV2Operator_AssignScalarDiv)
		{
			v2 point(8, -12);
			point /= 4;

			Assert::AreEqual(2, point.X);
			Assert::AreEqual(-3, point.Y);
		}

		TEST_METHOD(TestV2Operator_FloatMul)
		{
			v2 point(2, -3);
			v2 mul = point * 4.01;

			Assert::AreEqual(8, mul.X);
			Assert::AreEqual(-12, mul.Y);
		}

		TEST_METHOD(TestV2Operator_AssignFloatMul)
		{
			v2 point(2, -3);
			point *= 4.01;

			Assert::AreEqual(8, point.X);
			Assert::AreEqual(-12, point.Y);
		}

		TEST_METHOD(TestV2Operator_FloatDiv)
		{
			v2 point(8, -12);
			v2 mul = point / 3.99;

			Assert::AreEqual(2, mul.X);
			Assert::AreEqual(-3, mul.Y);
		}

		TEST_METHOD(TestV2Operator_AssignFloatDiv)
		{
			v2 point(8, -12);
			point /= 3.99;

			Assert::AreEqual(2, point.X);
			Assert::AreEqual(-3, point.Y);
		}

		TEST_METHOD(TestV2Operator_Eq)
		{
			v2 point1(1, 2);
			v2 point2(1, 2);
			v2 point3(3, 4);

			Assert::IsTrue(point1 == point2);
			Assert::IsFalse(point1 == point3);
		}

		TEST_METHOD(TestV2Operator_Neq)
		{
			v2 point1(1, 2);
			v2 point2(1, 2);
			v2 point3(3, 4);

			Assert::IsFalse(point1 != point2);
			Assert::IsTrue(point1 != point3);
		}

		TEST_METHOD(TestV2Operator_ShiftLeft)
		{
			v2 point(2, 1);
			v2 shift = point << 2;

			Assert::AreEqual(8, shift.X);
			Assert::AreEqual(4, shift.Y);
		}

		TEST_METHOD(TestV2Operator_AssignShiftLeft)
		{
			v2 point(2, 1);
			point <<= 2;

			Assert::AreEqual(8, point.X);
			Assert::AreEqual(4, point.Y);
		}

		TEST_METHOD(TestV2Operator_ShiftRight)
		{
			v2 point(8, 4);
			v2 shift = point >> 2;

			Assert::AreEqual(2, shift.X);
			Assert::AreEqual(1, shift.Y);
		}

		TEST_METHOD(TestV2Operator_AssignShiftRight)
		{
			v2 point(8, 4);
			point >>= 2;

			Assert::AreEqual(2, point.X);
			Assert::AreEqual(1, point.Y);
		}

	};
}