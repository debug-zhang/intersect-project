#include <fstream>
#include "exception.h"

using namespace std;

class _declspec(dllexport) IOHandler {
private:
	ifstream *ifstream;
	ofstream *ofstream;

	/*
	just read an integer
	params: None
	returns: an integer from ifstream
	exceptions: not_integer_exception - if is not an integer(decimal, char, ect)
	*/
	int readInt();

public:
	IOHandler(string readFile, string writeFile);

	/*
	read an integer, ensure in range(-100000, 100000)
	params: None
	returns: aa integer in range(-100000,100000) from ifstream
	exceptions: not_integer_exception - if is not an integer(decimal, char, ect)
						over_range_exception - if integer is not in range (-100000, 100000)
	*/
	int readNum();
	
	/*
	read an integer, ensure in range[1, inf), which means how many graphs in the map
	params: None
	returns: an integer in range[1,inf) from ifstream
	exceptions: not_integer_exception - if is not an integer(decimal, char, ect)
						not_valid_integer_exception - if not in range[1, inf)
	*/
	int readLine();

	/*
	read a char which means graph type, which must in [L, R, S, C]
	params: None
	returns: a char in [L, R, S, C]
	exceptions:  undefined_graph_exception - if is not a valid type of graph 
	*/
	char readGraphType();

	/*
	print an integer into ofstream
	params: const int n
	returns:
	exceptions:
	*/
	void outputInt(const int n);

	void reset();
};