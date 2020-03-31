#include "CppUnitTest.h"

import Cpu;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameBoyEmulatorTests
{
	TEST_CLASS(GameBoyEmulatorTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(1, 1);
		}
	};
}
