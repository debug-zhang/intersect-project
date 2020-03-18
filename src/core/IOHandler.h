#include <fstream>

using namespace std;

class IOHandler {
private:
	ifstream ifstream;
	ofstream ofstream;

public:
	IOHandler(int argc, char* argv[], bool DEBUG);

	int readInt();

	char readChar();

	void outputInt(const int n);
};