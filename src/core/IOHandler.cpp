#include "pch.h"
#include "IOHandler.h"

IOHandler::IOHandler(int argc, char* argv[], bool DEBUG) {
	ifstream = new std::ifstream();
	ofstream = new std::ofstream();
	if (DEBUG) {
		ifstream->open("input.txt", ios::in);
		if (!*ifstream) {
			throw file_not_exist_exception();
		}
		ofstream->open("output.txt");
	} else {
		for (int arg = 0; arg < argc; arg++) {
			if ((string)argv[arg] == "-i") {
				ifstream->open(argv[arg + 1]);
			} else if ((string)argv[arg] == "-o") {
				ofstream->open(argv[arg + 1]);
			}
		}
	}
}

int IOHandler::readInt() {
	int res;
	*ifstream >> res;
	if (ifstream->peek() != ' ' && ifstream->peek() != '\n') {
		ifstream->clear();
		throw not_integer_exception();
	}
	return res;
}

int IOHandler::readNum() {
	int res = readInt();
	if (res >= RANGE || res <= -RANGE) {
		throw over_range_exception();
	}
	return res;
}

int IOHandler::readLine() {
	int res = readInt();
	if (res < 1) {
		throw not_valid_integer_exception();
	}
	return res;
}

char IOHandler::readGraphType() {
	char res;
	*ifstream >> res;
	if (res != 'L' && res != 'R' && res != 'S' && res != 'C') {
		throw undefined_graph_exception();
	}
	return res;
}

void IOHandler::outputInt(const int n) {
	*ofstream << n << endl;
}

void IOHandler::reset() {
	ifstream->seekg(0);
}