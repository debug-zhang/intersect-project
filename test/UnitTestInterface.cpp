#include "pch.h"
#include "CppUnitTest.h"
#include "../src/core/container.h"
#include "../src/core/exception.h"
#include "../src/core/IOHandler.h"

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
			container->AddGraph('S', 1, 2, 3, 5);
			container->AddGraph('L', 1, 2, 5, 5);
			container->AddGraph('R', 3, 5, 5, 5);
			Assert::AreEqual(container->Size(), 3);
		}

		TEST_METHOD(TestDelete) {
			Container* container = new Container();
			
			container->AddGraph('S', -1, 3, 2, -1);
			Assert::AreEqual((int)container->GetGraphs()->size(), 1);
			auto func0 = [&] {container->DeleteGraph('R', -1, 3, 2, -1); };
			Assert::ExpectException<graph_not_exist>(func0);
			auto func1 = [&] {container->DeleteGraph('L', -1, 3, 2, -1); };
			Assert::ExpectException<graph_not_exist>(func1);
			container->DeleteGraph('S', -1, 3, 2, -1);
			auto func2 = [&] {container->DeleteGraph('S', -1, 3, 2, -1); };
			Assert::ExpectException<graph_not_exist>(func2);
			Assert::AreEqual((int)container->GetGraphs()->size(), 0);

			container->AddGraph('L', -2, 2, 3, 0);
			Assert::AreEqual((int)container->GetGraphs()->size(), 1);
			auto func3 = [&] {container->DeleteGraph('S', -2, 2, 3, 0); };
			Assert::ExpectException<graph_not_exist>(func3);
			auto func4 = [&] {container->DeleteGraph('R', -2, 2, 3, 0); };
			Assert::ExpectException<graph_not_exist>(func4);
			container->DeleteGraph('L', -2, 2, 3, 0);
			auto func5 = [&] {container->DeleteGraph('L', -2, 2, 3, 0); };
			Assert::ExpectException<graph_not_exist>(func5);
			Assert::AreEqual((int)container->GetGraphs()->size(), 0);

			container->AddGraph('R', -3, 0, 4, 2);
			Assert::AreEqual((int)container->GetGraphs()->size(), 1);
			auto func6 = [&] {container->DeleteGraph('L', -3, 0, 4, 2); };
			Assert::ExpectException<graph_not_exist>(func6);
			auto func7 = [&] {container->DeleteGraph('S', -3, 0, 4, 2); };
			Assert::ExpectException<graph_not_exist>(func7);
			container->DeleteGraph('R', -3, 0, 4, 2);
			auto func8 = [&] {container->DeleteGraph('R', -3, 0, 4, 2); };
			Assert::ExpectException<graph_not_exist>(func8);
			Assert::AreEqual((int)container->GetGraphs()->size(), 0);
		}
	};

}
