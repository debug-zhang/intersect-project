#include <fstream>
#include <vector>
#include "core/IOHandler.h"
#include "core/container.h"

#define DEBUG 0

class _declspec(dllexport) Container;

int main(int argc, char* argv[]) {
	string readFile, writeFile;
	Container* container = new Container;
	IOHandler* io;

	try {
		if (DEBUG) {
			readFile = "input.txt";
			writeFile = "output.txt";
		} else {
			for (int arg = 0; arg < argc; arg++) {
				if ((string)argv[arg] == "-i") {
					readFile = argv[arg + 1];
				} else if ((string)argv[arg] == "-o") {
					writeFile = argv[arg + 1];
				}
			}
		}

		io = new IOHandler(readFile, writeFile);

		int line = io->readLine();

		for (int i = 0; i < line; i++) {
			char type = io->readGraphType();
			int x1 = io->readNum();
			int y1 = io->readNum();
			int x2 = io->readNum();
			int y2 = io->readNum();
			container->AddGraph(type, x1, y1, x2, y2);
		}
	}
	catch (exception& e) {
		cout << e.what() << endl;
		return 0;
	}

	io->outputInt(container->Size());
	return 0;
}