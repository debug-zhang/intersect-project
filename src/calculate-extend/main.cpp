#include <fstream>

#include "container.h"

#define DEBUG 0

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

	Container* container = new Container;

	for (int i = 0; i < line; i++) {
		char type;
		Graph* new_graph = NULL;
		input >> type;
		if (type == 'L') {
			int x1, y1, x2, y2;
			input >> x1 >> y1 >> x2 >> y2;
			Dot d1(x1, y1);
			Dot d2(x2, y2);
			new_graph = new Line(d1, d2);

		} else if (type == 'R') {
			int x1, y1, x2, y2;
			input >> x1 >> y1 >> x2 >> y2;
			Dot d1(x1, y1);
			Dot d2(x2, y2);
			new_graph = new Radial(d1, d2);

		} else if (type == 'S') {
			int x1, y1, x2, y2;
			input >> x1 >> y1 >> x2 >> y2;
			Dot d1(x1, y1);
			Dot d2(x2, y2);
			new_graph = new Segment(d1, d2);

		} else if (type == 'C') {
			// TO DO
		}

		container->AddGraph(new_graph);
	}

	output << container->Size() << endl;
	return 0;
}