#include <fstream>
#include <vector>
#include "core/IOHandler.h"
#include "core/container.h"

#define DEBUG 1

class _declspec(dllexport) Container;

int main(int argc, char* argv[]) {
	IOHandler io(argc, argv, DEBUG);

	int line = io.readLine();

	Container* container = new Container;

	for (int i = 0; i < line; i++) {
		char type = io.readGraphType();
		int x1 = io.readNum();
		int y1 = io.readNum();
		int x2 = io.readNum();
		int y2 = io.readNum();
		container->AddGraph(type, x1, y1, x2, y2);
	}

	//todo: catch and handle or just eject
	io.outputInt(container->Size());
	return 0;
}