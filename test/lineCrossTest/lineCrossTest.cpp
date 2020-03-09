#include "pch.h"
#include "CppUnitTest.h"
#include "../../src/generic.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lineCrossTest {
	TEST_CLASS(lineCrossTest) {
public:
	TEST_METHOD(TestDot) {
		Dot d0(0, 0);
		Dot* d1 = new Dot(-1.5, -1.131);
		Dot* d2 = new Dot(3.341, 5.000);
		Assert::AreEqual(d0.getX(), 0.0);
		Assert::AreEqual(d0.getY(), 0.0);
		Assert::AreEqual(d1->getX(), -1.5);
		Assert::AreEqual(d1->getY(), -1.131);
		Assert::AreEqual(d2->getX(), 3.341);
		Assert::AreEqual(d2->getY(), 5.0);

		Dot d4(-1.5, -1.131);
		Dot d5(-1.5, -1.132);
		Dot d6(-1.51, -1.131);
		Assert::AreEqual(d1->equals(d4), true);
		Assert::AreEqual(d1->equals(d5), false);
		Assert::AreEqual(d1->equals(d6), false);
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
		Line lineVertical2(5, 0, -4614);
		Line lineLevel2(0, -124, 61313);
		Line lineSlant3(-6.0, -4.0, 12000);

		Assert::AreEqual(lineVertical.getC() / lineVertical.getA(), -6744.0);
		Assert::AreEqual(lineVertical.getB(), 0.0);
		Assert::AreEqual(lineLevel.getA(), 0.0);
		Assert::AreEqual(lineLevel.getC() / lineLevel.getB(), -5333.0);

		Assert::AreEqual(-lineSlant1.getA() / lineSlant1.getB(), -1.0);
		Assert::AreEqual(-lineSlant1.getC() / lineSlant1.getB(), 1416.0 + 5333);
		Assert::AreEqual(-lineSlant2.getA() / lineSlant2.getB(), 5328.0 / 1332);
		Assert::AreEqual(-lineSlant2.getC() / lineSlant2.getB(), 5.0 - 6744 * 5328 / 1332);

		Assert::AreEqual(lineVertical2.getC() / lineVertical2.getA(), -4614.0 / 5);
		Assert::AreEqual(lineVertical2.getB(), 0.0);
		Assert::AreEqual(lineLevel2.getA(), 0.0);
		Assert::AreEqual(lineLevel2.getC() / lineLevel2.getB(), -61313.0 / 124);
		Assert::AreEqual(lineSlant3.getA() / lineSlant3.getB(), -6.0 / -4.0);
		Assert::AreEqual(lineSlant3.getC() / lineSlant3.getB(), 12000.0 / -4.0);
	}TEST_METHOD(TestCircle) {
		Circle c(0.143, -42.11, 79817.2542);
		Assert::AreEqual(c.getA(), 0.143);
		Assert::AreEqual(c.getB(), -42.11);
		Assert::AreEqual(c.getC(), 79817.2542);
	}
	TEST_METHOD(TestSolve) {
		//圆和圆
		{
			cout << "circle test" << endl;
			Graph* c1 = new Circle(3, 4, 5);
			cout << "circle(0,y,2)" << endl;
			for (int y = 10; y >= -3; y--) {
				vector<Dot> res;
				Circle* c2 = new Circle(0, y, 2);
				res = solve(c1, c2);
				cout << "y=" << y << "," << "(" << res.size() << ")" << endl;
				for (Dot d : res) cout << d.getX() << d.getY() << endl;
			}
			cout << "circle(-3,y,1)" << endl;
			for (int y = 5; y >= 3; y--) {
				vector<Dot> res;
				Circle* c2 = new Circle(-3, y, 1);
				res = solve(c1, c2);
				cout << "y=" << y << "," << "(" << res.size() << ")" << endl;
				for (Dot d : res) cout << d.getX() << d.getY() << endl;
			}
			cout << "circle(3,y,2)" << endl;
			for (int y = 5; y >= 3; y--) {
				vector<Dot> res;
				Circle* c2 = new Circle(3, y, 2);
				res = solve(c1, c2);
				cout << "y=" << y << "," << "(" << res.size() << ")" << endl;
				for (Dot d : res) cout << d.getX() << d.getY() << endl;
			}
		}
		//线和线
		{
			cout << "line test" << endl;
			Graph* l1 = new Line(0, 4, -4);
			Graph* l2 = new Line(-1, 0, -2);
			Graph* l3 = new Line(2, 4, 8);
			vector<Dot> res;
			res.push_back(solve(l1, l2)[0]);
			res.push_back(solve(l1, l3)[0]);
			res.push_back(solve(l3, l2)[0]);
			for (Dot d : res) cout << d.getX() << d.getY() << endl;
		}
		//圆和线
		{
			cout << "circle-line test" << endl;
			Graph* c = new Circle(3, 4, 5);
			//斜线
			for (int h = 16; h >= 7; h--) {
				Graph* l = new Line(1, 1, -h);
				vector<Dot> res;
				res = solve(c, l);
				cout << "h=" << h << "," << "(" << res.size() << ")" << endl;
				for (Dot d : res) cout << d.getX() << d.getY() << endl;
			}
			//垂线
			for (int h = 18; h >= 14; h-=2) {
				Graph* l = new Line(12, 0, -h);
				vector<Dot> res;
				res = solve(c, l);
				cout << "h=" << h << "," << "(" << res.size() << ")" << endl;
				for (Dot d : res) cout << d.getX() << d.getY() << endl;
			}
			//水平线
			for (int h = 2; h >= -6; h -= 2) {
				Graph* l = new Line(0,2, -h);
				vector<Dot> res;
				res = solve(c, l);
				cout << "h=" << h << "," << "(" << res.size() << ")" << endl;
				for (Dot d : res) cout << d.getX() << d.getY() << endl;
			}
		}
		//超出100000的情况
		{
			Dot d1(-100000, 0);
			Dot d2(100000, 0);
			Dot d3(-100000, 1);
			Dot d4(100000, 2);
			Graph* l1 = new Line(d1, d2);
			Graph* l2 = new Line(d3, d4);
			vector<Dot> res;
			res = solve(l1, l2);
			Assert::AreEqual((int)res.size(), 1);
			Assert::AreEqual(res[0].getX(), -300000.0);
		}
	}
	};
}
