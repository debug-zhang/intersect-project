#include <fstream>
#include <vector>
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
	vector<Graph*> graphs;

	for (int i = 0; i < line; i++) {
		char type;
		Graph* graph1 = NULL;
		input >> type;
		if (type == 'L') {
			int x1, y1, x2, y2;
			input >> x1 >> y1 >> x2 >> y2;
			Dot d1(x1, y1);
			Dot d2(x2, y2);
			graph1 = new Line(d1, d2);

		} else if (type == 'R') {
			int x1, y1, x2, y2;
			input >> x1 >> y1 >> x2 >> y2;
			Dot d1(x1, y1);
			Dot d2(x2, y2);
			graph1 = new Radial(d1, d2);

		} else if (type == 'S') {
			int x1, y1, x2, y2;
			input >> x1 >> y1 >> x2 >> y2;
			Dot d1(x1, y1);
			Dot d2(x2, y2);
			graph1 = new Segment(d1, d2);

		} else if (type == 'C') {
			// TO DO
		}

		if (graph1 != NULL) {
			for (Graph* graph2 : graphs) {
				Solve(container, graph1, graph2);
			}
			graphs.push_back(graph1);
		}
	}

	output << container->Size() << endl;
	// cout << "total: " << container->Size() << endl;
	return 0;
}