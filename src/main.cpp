#include <fstream>
#include "core/container.h"
#define DEBUG 1

class _declspec(dllexport) Container;

using namespace std;

int main(int argc, char* argv[]) {
	ifstream input;
	ofstream output;

	if (DEBUG) {
		input.open("input.txt");
		output.open("output.txt");
	} else {
		for (int arg = 0; arg < argc; arg++) {
			if ((string)argv[arg] == "-i") {
				input.open(argv[arg + 1]);
			} else if ((string)argv[arg] == "-o") {
				output.open(argv[arg + 1]);
			}
		}
	}

	int line;
	input >> line;
	Container* container = new Container();

	for (int i = 0; i < line; i++) {
		char type;
		input >> type;
		int x1, y1, x2, y2;
		input >> x1 >> y1 >> x2 >> y2;

		container->AddGraph(type, x1, y1, x2, y2);
	}

	output << container->Size() << endl;
	return 0;
}