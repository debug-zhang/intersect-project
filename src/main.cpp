#include <fstream>
#include <vector>
#include "IOHandler.h"
#include "core/container.h"
#define DEBUG 1

class _declspec(dllexport) Container;

int main(int argc, char* argv[]) {
	IOHandler io(argc, argv, DEBUG);

	int line = io.readInt();

	Container* container = new Container;

	for (int i = 0; i < line; i++) {
		char type = io.readChar();
		int x1 = io.readInt();
		int y1 = io.readInt();
		int x2 = io.readInt();
		int y2 = io.readInt();
		container->AddGraph(type, x1, y1, x2, y2);
	}

	io.outputInt(container->Size());
	return 0;
}