#include "Graph.h"
#include <vector>

int main(int argc, char* argv[]) {
	ifstream input;
	ofstream output;
	for (int arg = 0; arg < argc; arg++) {
		if ((string)argv[arg] == "-i") {
			input.open(argv[arg + 1]);
		} else if ((string)argv[arg] == "-o") {
			output.open(argv[arg + 1]);
		}
	}

	int line;
	input >> line;

	Container* container = new Container;
	vector<Graph*> graphs;

	for (int i = 0; i < line; i++) {
		char type;
		input >> type;
		if (type == 'L') {
			int x1, y1, x2, y2;
			input >> x1 >> y1 >> x2 >> y2;
			Dot d1(x1, y1);
			Dot d2(x2, y2);
			Line* l = new Line(d1, d2);
			for (Graph* graph : graphs) {
				solve(container, graph, l);
			}
			graphs.push_back(l);
		} else if (type == 'C') {
			int m, n, r;
			input >> m >> n >> r;
			Circle* c = new Circle(m, n, r);
			for (Graph* graph : graphs) {
				solve(container, graph, c);
			}
			graphs.push_back(c);
		}
	}

	output << container->size() << endl;
	cout << "total: " << container->size() << endl;
	return 0;
}