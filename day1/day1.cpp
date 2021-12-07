#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
	string line;
	int count = 0;
       	int nlines = 0;
	
	// error check
	if (argc != 2) {
		cerr << "usage: " << argv[0] << " <input-file>.\n";
		exit(1);
	}

	// open file for reading
	ifstream fin(argv[1]);
	if (fin.is_open()) {

		// initialize prev
		getline(fin, line);
		int prev = stoi(line);
		nlines++;
		
		// read rest of file to get occurences of depth increase
		while (getline(fin, line)) {
			int depth = stoi(line);
			if (depth > prev) count++;
			
			prev = depth;
			nlines++;
		}
		fin.close();
	} else {
		cerr << argv[0] << ": unable to read file.\n";
		exit(1);
	}

	// print occurences of depth increase
	cout << count << endl;
}
