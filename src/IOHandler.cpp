#include "IOHandler.h"

IOHandler::IOHandler(int argc, char* argv[], bool DEBUG) {
	if (DEBUG) {
		ifstream.open("input.txt");
		ofstream.open("output.txt");
	} else {
		for (int arg = 0; arg < argc; arg++) {
			if ((string)argv[arg] == "-i") {
				ifstream.open(argv[arg + 1]);
			} else if ((string)argv[arg] == "-o") {
				ofstream.open(argv[arg + 1]);
			}
		}
	}
}

int IOHandler::readInt() {
	int res;
	ifstream >> res;
	return res;
}

char IOHandler::readChar() {
	char res;
	ifstream >> res;
	return res;
}

void IOHandler::outputInt(const int n) {
	ofstream << n << endl;
}