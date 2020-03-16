#include "pch.h"
#include "CppUnitTest.h"
#include "../IntersectProject/container.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		TEST_METHOD(TestDot) {
			Dot d0(0, 0);
			Dot* d1 = new Dot(-1.5, -1.131);
			Dot* d2 = new Dot(3.341, 5.000);
			Assert::AreEqual(d0.GetX(), 0.0);
			Assert::AreEqual(d0.GetY(), 0.0);
			Assert::AreEqual(d1->GetX(), -1.5);
			Assert::AreEqual(d1->GetY(), -1.131);
			Assert::AreEqual(d2->GetX(), 3.341);
			Assert::AreEqual(d2->GetY(), 5.0);

			Dot d4(-1.5, -1.131);
			Dot d5(-1.5, -1.132);
			Dot d6(-1.51, -1.131);
			Assert::AreEqual(d1->equals(d4), true);
			Assert::AreEqual(d1->equals(d5), false);
			Assert::AreEqual(d1->equals(d6), false);

			Dot d7(-1.5 + 4.52341 - 4.53341, -1.131);
			Assert::AreNotEqual(d7.GetX(), -1.51);
			Assert::AreEqual(d7.equals(d6), true);
		}

		TEST_METHOD(TestLine) {
			Dot d1(1416, 5333);
			Dot d2(6744, 5);
			Dot d3(8076, 5333);
			Dot d4(6744, -11300);
			Line lineVertical(d4, d2);
			Line lineLevel(d3, d1);
			Line lineSlant1(d1, d2);
			Line lineSlant2(d2, d3);

			Assert::AreEqual(lineVertical.GetC() / lineVertical.GetA(), -6744.0);
			Assert::AreEqual(lineVertical.GetB(), 0.0);
			Assert::AreEqual(lineLevel.GetA(), 0.0);
			Assert::AreEqual(lineLevel.GetC() / lineLevel.GetB(), -5333.0);

			Assert::AreEqual(-lineSlant1.GetA() / lineSlant1.GetB(), -1.0);
			Assert::AreEqual(-lineSlant1.GetC() / lineSlant1.GetB(), 1416.0 + 5333);
			Assert::AreEqual(-lineSlant2.GetA() / lineSlant2.GetB(), 5328.0 / 1332);
			Assert::AreEqual(-lineSlant2.GetC() / lineSlant2.GetB(), 5.0 - 6744 * 5328 / 1332);
		}

		TEST_METHOD(TestSolve) {
			Container* container = new Container();
			Segment* segment = new Segment(Dot(-1, 3), Dot(2, -1));
			Line* line = new Line(Dot(-2, 2), Dot(3, 0));
			Radial* radial = new Radial(Dot(-3,0), Dot(4, 2));

			Solve(container, segment, line);
			Assert::AreEqual(container->Size(), 1);

			Solve(container, segment, radial);
			Assert::AreEqual(container->Size(), 1);

			Solve(container, line, radial);
			Assert::AreEqual(container->Size(), 1);
		}

		TEST_METHOD(TestContainer) {
			Container c;
			Dot d1(5, 4);
			Dot d2(2, 4);
			Dot d3(5, -1);
			Dot d4(5, 4);
			Dot d5(5, 4);
			c.Add(d1);
			c.Add(d2);
			c.Add(d3);
			c.Add(d4);
			c.Add(d5);
			Assert::AreEqual(c.Size(), 3);
		}
	};

}
