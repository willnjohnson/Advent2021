#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
	string line;
	int nlines = 0;
	int position = 0;
	int depth = 0;

	// error check
	if (argc != 2) {
		cerr << "usage: " << argv[0] << " <input-file>.\n";
		exit(1);
	}

	// open file for reading
	ifstream fin(argv[1]);
	if (fin.is_open()) {

		// read rest of file to get occurences of depth increase
		while (getline(fin, line)) {
			// get move and value
			string move = line.substr(0, line.find(' '));
			int value = stoi(line.substr(move.length() + 1, line.find('\0')));
			
			// calculate depth and position depending on move
			if (move == "forward") {
				position += value;
			} else if (move == "down") {
				depth += value;	
			} else {
				depth -= value;
			}

			nlines++;
		}
		fin.close();
	} else {
		cerr << argv[0] << ": unable to read file.\n";
		exit(1);
	}

	// calculate product of position and depth
	cout << "Read depth " << depth << " and position " << position << " to yield the product " << (depth * position) << ".\n";
}
