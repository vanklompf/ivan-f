#include "stdafx.h"
#include "CppUnitTest.h"
#include "femath.h"

#include <random>
#include <map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

static const uint32_t NN1 = 624;

namespace FeLibTests
{
TEST_CLASS(randomTests)
{
private:
  static const uint32_t SEED = 123456;

  template <long(*TFunc)()>
  void testRandomRangeMacro(uint32_t range)
  {
	  int count = 0;
	  int circuit_breaker = 0;
	  std::vector<bool> check(range);
	  do
	  {
		  long rnd = TFunc();
		  Assert::IsTrue(rnd < range);
		  if (!check[rnd])
		  {
			  check[rnd] = true;
			  count++;
		  }

		  if (circuit_breaker++ > 100000)
		  {
			  Assert::Fail(L"Random range to narrow");
		  }
	  } while (count < range);
  }

public:
  TEST_METHOD_INITIALIZE(methodName) { femath::SetSeed(SEED); }

  TEST_METHOD(TestRandomBasic)
  {

    Assert::AreEqual(545331265l, femath::Rand());

    std::mt19937 generator(SEED);
    Assert::AreEqual(545331265l, (long)generator() & 0x7FFFFFFF);
  }

  TEST_METHOD(TestRandomRange10)
  {
    const int RANGE = 10;
    int count = 0;
    std::vector<bool> check(RANGE);
    do
    {
      long rnd = femath::RandN(RANGE);
      Assert::IsTrue(rnd < RANGE);
      if (!check[rnd])
      {
        check[rnd] = true;
        count++;
      }
    } while (count < RANGE);
  }

  TEST_METHOD(TestRandomRange100)
  {
    const int RANGE = 100;
    int count = 0;
	int circuit_breaker = 0;
	std::vector<bool> check(RANGE);
    do
    {
      long rnd = femath::RandN(RANGE);
      Assert::IsTrue(rnd < RANGE);
      if (!check[rnd])
      {
        check[rnd] = true;
        count++;
      }

    } while (count < RANGE);
  }

  TEST_METHOD(TestRandomRangeMacro2) 
  { 
	testRandomRangeMacro<femath::RandT<2> >(2);
  }

  TEST_METHOD(TestRandomRangeMacro4)
  {
	  testRandomRangeMacro<RAND_4>(4);
  }

  TEST_METHOD(TestRandomRangeMacro8)
  {
	  testRandomRangeMacro<RAND_8>(8);
  }

  TEST_METHOD(TestRandomRangeMacro16)
  {
	  testRandomRangeMacro<RAND_16>(16);
  }

  TEST_METHOD(TestRandomRangeMacro32)
  {
	  testRandomRangeMacro<RAND_32>(32);
  }

  TEST_METHOD(TestRandGood)
  {
	  Assert::AreEqual(1l, femath::RandGood(3));
  }
};
}
