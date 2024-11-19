#include "pch.h"
#include "CppUnitTest.h"
#include "../10.2B/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Student a[1] = { "adsa", 1, IT, 5, 5, 5 };



			Assert::AreEqual(5.0, findMark(a, 0));
		}
	};
}
