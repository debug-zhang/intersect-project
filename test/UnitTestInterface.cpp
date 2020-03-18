#include "pch.h"
#include "CppUnitTest.h"
#include "../IntersectProject/core/container.h"

class _declspec(dllexport) Container;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		TEST_METHOD(TestAddGraphAndSize) {
			Container* container = new Container();
			container->AddGraph('S', -1, 3, 2, -1);
			container->AddGraph('L', -2, 2, 3, 0);
			container->AddGraph('R', -3, 0, 4, 2);
			Assert::AreEqual(container->Size(), 1);

			container = new Container();
			container->AddGraph('S', 1, 1, 1, -1);
			container->AddGraph('L', 2, 2, 2, 0);
			container->AddGraph('R', 3, 3, 3, 4);
			Assert::AreEqual(container->Size(), 0);

			container = new Container();
			container->AddGraph('S', 2, 4, 3, 2);
			container->AddGraph('L', -1, 4, 5, 2);
			container->AddGraph('R', 2, 5, -1, 2);
			Assert::AreEqual(container->Size(), 2);

			container = new Container();
			container->AddGraph('S', 0, 2, 3, -1);
			container->AddGraph('L', 0, 2, 2, 2);
			container->AddGraph('R', 0, 2, 3, -1);
			Assert::AreEqual(container->Size(), 1);

			container = new Container();
			container->AddGraph('S', 0, 2, 3, -1);
			container->AddGraph('L', 3, -1, 4, 2);
			container->AddGraph('R', 0, 2, 3, -1);
			Assert::AreEqual(container->Size(), 1);

			container = new Container();
			container->AddGraph('S', 0, 2, 3, -1);
			container->AddGraph('L', -1, 3, -5, 0);
			container->AddGraph('R', 0, 2, 3, -1);
			Assert::AreEqual(container->Size(), 0);

			container = new Container();
			container->AddGraph('S', 0, 2, 3, -1);
			container->AddGraph('L', 4, 2, 5, 0);
			container->AddGraph('R', 0, 2, 3, -1);
			Assert::AreEqual(container->Size(), 1);

			container = new Container();
			container->AddGraph('S', 0, 2, 3, -1);
			container->AddGraph('L', 0, 2, 3, -1);
			container->AddGraph('R', 0, 2, 3, -1);
			Assert::AreEqual(container->Size(), 0);

			container = new Container();
			container->AddGraph('S', 4, 2, 5, 0);
			container->AddGraph('L', 4, 2, 5, 0);
			container->AddGraph('R', 4, 2, 5, 0);
			Assert::AreEqual(container->Size(), 0);
		}
	};

}
