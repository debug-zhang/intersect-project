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

			Dot d8(77940 / 11959, 78005 / 11969);
			Assert::AreEqual(d8.equals(Dot(77940 / 11959, 78005 / 11969)), true);
			Dot d9(77940 / 11959+1.11111111- 1.11111111, 78005 / 11969 +0.33333333- 0.33333333);
			Assert::AreEqual(d9.equals(Dot(77940 / 11959, 78005 / 11969)), true);
			Assert::AreEqual(d9.equals(d8), true);
			Assert::AreEqual(d9.equals(Dot(77940 / 11959 + 1.11111111 - 1.11111111, 
				78005 / 11969 + 0.33333333 - 0.33333333)), true);
			Assert::AreEqual(d9.equals(Dot(77940 / 11959, 78005 / 11969)), true);

			Dot d10(16451 / 16447, 48119 / 48121);
			Assert::AreEqual(d10.equals(Dot(16451 / 16447, 48119 / 48121)), true);
			Dot d11(16451 / 16447 + 0.99999999 - 0.99999999, 48119 / 48121 + 0.000000003 - 0.000000003);
			Assert::AreEqual(d11.equals(Dot(16451 / 16447, 48119 / 48121)), true);
			Assert::AreEqual(d11.equals(d10), true);
			Assert::AreEqual(d11.equals(Dot(16451 / 16447 + 0.99999999 - 0.99999999,
				48119 / 48121 + 0.000000003 - 0.000000003)), true);
			Assert::AreEqual(d11.equals(Dot(16451 / 16447, 48119 / 48121)), true);
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

		TEST_METHOD(TestContainer) {
			Container c;
			Dot d1(5, 4);
			Dot d2(2, 4);
			Dot d3(5, -1);
			Dot d4(5, 4);
			Dot d5(5, 4);
			c.AddDot(d1);
			c.AddDot(d2);
			c.AddDot(d3);
			c.AddDot(d4);
			c.AddDot(d5);
			Assert::AreEqual(c.Size(), 3);
		}

		TEST_METHOD(TestSolve) {
			Container* container = new Container();
			Segment* segment = new Segment(Dot(-1, 3), Dot(2, -1));
			Line* line = new Line(Dot(-2, 2), Dot(3, 0));
			Radial* radial = new Radial(Dot(-3, 0), Dot(4, 2));

			container->IntersectCalculate(segment, line);
			Assert::AreEqual(container->Size(), 1);
			container->IntersectCalculate(segment, radial);
			Assert::AreEqual(container->Size(), 1);
			container->IntersectCalculate(line, radial);
			Assert::AreEqual(container->Size(), 1);


			container = new Container();
			segment = new Segment(Dot(1, 1), Dot(1, -1));
			line = new Line(Dot(2, 2), Dot(2, 0));
			radial = new Radial(Dot(3, 3), Dot(3, 4));

			container->IntersectCalculate(segment, line);
			Assert::AreEqual(container->Size(), 0);
			container->IntersectCalculate(segment, radial);
			Assert::AreEqual(container->Size(), 0);
			container->IntersectCalculate(line, radial);
			Assert::AreEqual(container->Size(), 0);

			container = new Container();
			segment = new Segment(Dot(2, 4), Dot(3, 2));
			line = new Line(Dot(-1, 4), Dot(5, 2));
			radial = new Radial(Dot(2, 5), Dot(-1, 2));

			container->IntersectCalculate(segment, line);
			Assert::AreEqual(container->Size(), 1);
			container->IntersectCalculate(segment, radial);
			Assert::AreEqual(container->Size(), 1);
			container->IntersectCalculate(line, radial);
			Assert::AreEqual(container->Size(), 2);

			container = new Container();
			segment = new Segment(Dot(0, 2), Dot(3, -1));
			line = new Line(Dot(0, 2), Dot(2, 2));
			radial = new Radial(Dot(0, 2), Dot(3, -1));
			container->IntersectCalculate(segment, line);
			Assert::AreEqual(container->Size(), 1);
			container->IntersectCalculate(line, radial);
			Assert::AreEqual(container->Size(), 1);

			container = new Container();
			segment = new Segment(Dot(0, 2), Dot(3, -1));
			line = new Line(Dot(3, -1), Dot(4, 2));
			radial = new Radial(Dot(0, 2), Dot(3, -1));
			container->IntersectCalculate(segment, line);
			Assert::AreEqual(container->Size(), 1);
			container->IntersectCalculate(line, radial);
			Assert::AreEqual(container->Size(), 1);

			container = new Container();
			segment = new Segment(Dot(0, 2), Dot(3, -1));
			line = new Line(Dot(-1, 3), Dot(-5, 0));
			radial = new Radial(Dot(0, 2), Dot(3, -1));
			container->IntersectCalculate(segment, line);
			Assert::AreEqual(container->Size(), 0);
			container->IntersectCalculate(line, radial);
			Assert::AreEqual(container->Size(), 0);

			container = new Container();
			segment = new Segment(Dot(0, 2), Dot(3, -1));
			line = new Line(Dot(4, 2), Dot(5, 0));
			radial = new Radial(Dot(0, 2), Dot(3, -1));
			container->IntersectCalculate(segment, line);
			Assert::AreEqual(container->Size(), 0);
			container->IntersectCalculate(line, radial);
			Assert::AreEqual(container->Size(), 1);
		}
	};

}
