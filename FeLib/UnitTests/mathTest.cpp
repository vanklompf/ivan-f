#include "stdafx.h"
#include "CppUnitTest.h"
#include "femath.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FeLibTests
{
	TEST_CLASS(mathTests)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			femath::SetSeed(1);
			Assert::AreEqual(1648691334l, femath::Rand());
		}

	};
}

