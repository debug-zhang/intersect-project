#include "pch.h"
#include "CppUnitTest.h"
#include "../src/core/container.h"
#include "../src/core/exception.h"
#include "../src/core/IOHandler.h"
#define OPENFILE() {\
	ofstr.open("input.txt");\
}
#define CLOSEFILE(){\
	ofstr.close();\
}
#define WRITE(ARG) {\
	ofstr << ARG << endl;\
	ofstr.seekp(0);\
	io->reset();\
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest {
	TEST_CLASS(UnitTest) {
public:
	std::ofstream ofstr;
	TEST_METHOD(TestNotIntegerException) {
		IOHandler* io = new IOHandler("input.txt","output.txt");
		OPENFILE();
		WRITE("wordsssss");
		auto func0 = [&] {io->readNum(); };
		Assert::ExpectException<not_integer_exception>(func0);
		WRITE("-4.1");
		auto func1 = [&] {io->readNum(); };
		Assert::ExpectException<not_integer_exception>(func1);
		WRITE("0.136");
		auto func2 = [&] {io->readNum(); };
		Assert::ExpectException<not_integer_exception>(func2);
		WRITE("12");
		Assert::AreEqual(io->readNum(), 12);
		CLOSEFILE();
	}
	TEST_METHOD(TestNotValidIntegerException) {
		IOHandler* io = new IOHandler("input.txt", "output.txt");
		OPENFILE();
		WRITE("0");
		auto func0 = [&] {io->readLine(); };
		Assert::ExpectException<not_valid_integer_exception>(func0);
		WRITE("1");
		Assert::AreEqual(io->readLine(), 1);
		CLOSEFILE();
	}
	TEST_METHOD(TestNotCharException) {
		// unused exception
		// pass
		Assert::IsTrue(true);
	}
	TEST_METHOD(TestUndefinedGraphException) {
		IOHandler* io = new IOHandler("input.txt", "output.txt");
		OPENFILE();
		WRITE("K");
		auto func1 = [&] {io->readGraphType(); };
		Assert::ExpectException<undefined_graph_exception>(func1);
		WRITE("l");
		auto func2 = [&] {io->readGraphType(); };
		Assert::ExpectException<undefined_graph_exception>(func2);
		WRITE("R");
		Assert::AreEqual(io->readGraphType(), 'R');
		CLOSEFILE();
	}
	TEST_METHOD(TestOverRangeException) {
		IOHandler* io = new IOHandler("input.txt", "output.txt");
		OPENFILE();
		WRITE("-100000");
		auto func = [&] {io->readNum(); };
		Assert::ExpectException<over_range_exception>(func);
		WRITE("99999");
		Assert::AreEqual(io->readNum(), 99999);
		CLOSEFILE();
	}
	TEST_METHOD(TestDotSuperpositionException) {
		Dot d0(4.123, 0.1341);
		Dot d1(3.123 + 0.9 + 0.1, -8.1341 + 8.2682);
		auto func0 = [&] {Graph* g = new Line(d0, d1); };
		Assert::ExpectException<dot_superposition_exception>(func0);
		auto func1 = [&] {Graph* g = new Segment(d0, d1); };
		Assert::ExpectException<dot_superposition_exception>(func1);
		auto func2 = [&] {Graph* g = new Radial(d0, d1); };
		Assert::ExpectException<dot_superposition_exception>(func2);
	}
	TEST_METHOD(TestInfinateIntersectException) {
		Dot d0(0, 0);
		Dot d1(1, 1);
		Dot d2(2, 2);
		Dot d3(3, 3);
		auto func = [&] {
			Container* c = new Container();
			Graph* s = new Segment(d0, d2);
			Graph* r = new Radial(d1, d3);
			c->IntersectCalculate(s, r);
		};
		Assert::ExpectException<infinate_intersect_exception>(func);
	}
	TEST_METHOD(TestFileNotExistException) {
		// ×¢ÒâÉ¾³ýinput.txtÎÄ¼þ
		auto func = [&] {		IOHandler* io = new IOHandler("input.txt", "output.txt");};
		Assert::ExpectException<file_not_exist_exception>(func);
	}
	};
}