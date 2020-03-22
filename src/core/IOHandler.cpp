#include "pch.h"
#include "IOHandler.h"

IOHandler::IOHandler(string readFile,string writeFile) {
	ifstream = new std::ifstream();
	ofstream = new std::ofstream();
		ifstream->open(readFile, ios::in);
		if (!*ifstream) {
			throw file_not_exist_exception();
		}
		ofstream->open(writeFile);
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