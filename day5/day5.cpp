#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
using namespace std;

typedef struct {
	// entry: x1, y1 -> x2, y2
	int x1, y1, x2, y2;
} Entry;

int main(int argc, char* argv[]) {
	string line;
	int x1, y1, x2, y2;
	int maxX = 0;
	int maxY = 0;
	int nlines = 0;
	int position = 0;
	int depth = 0;
	char* tok;
	vector<Entry> coord;

	// error check
	if (argc != 2) {
		cerr << "usage: " << argv[0] << " <input-file>.\n";
		exit(1);
	}

	// open file for reading
	ifstream fin(argv[1]);
	if (fin.is_open()) {
		// read file entries
		while (getline(fin, line)) {
			char l[line.length()];
			strcpy(l, line.c_str());

			// get coordinates
			tok = strtok(l, ",");
			x1 = atoi(tok);

			tok = strtok(NULL, " ");
			y1 = atoi(tok);

			tok = strtok(NULL, " ");
			tok = strtok(NULL, ",");
			x2 = atoi(tok);

			tok = strtok(NULL, "\n");
			y2 = atoi(tok);

			// insert entry
			coord.push_back({ x1, y1, x2, y2 });

			// get max
			if (x1>maxX) maxX = x1;
			if (x2>maxX) maxX = x2;
			if (y1>maxY) maxY = y1;
			if (y2>maxY) maxY = y2;
		}
		fin.close();
	} else {
		cerr << argv[0] << ": unable to read file.\n";
		exit(1);
	}

	// since numbers begin at 0, increment max
	maxX++;
	maxY++;

	int grid[maxX][maxY] = {};

	for (int i=0; i<coord.size(); i++) {
		if (coord[i].x1 == coord[i].x2) {
			if (coord[i].y1 < coord[i].y2) { //inc col
				for (y1 = coord[i].y1; y1 <= coord[i].y2; y1++) {
					grid[coord[i].x2][y1]++;
				}
			} else if (coord[i].y1 > coord[i].y2) { // dec col
				for (y1 = coord[i].y1; coord[i].y2 <= y1; y1--) {
					grid[coord[i].x2][y1]++;
				}
			}
		} else if (coord[i].y1 == coord[i].y2) {
			if (coord[i].x1 < coord[i].x2) { // inc row
				for (x1 = coord[i].x1; x1 <= coord[i].x2; x1++) {
					grid[x1][coord[i].y1]++;
				}
			} else if (coord[i].x1 > coord[i].x2) { // dec row
				for (x1 = coord[i].x1; coord[i].x2 <= x1; x1--) {
					grid[x1][coord[i].y1]++;
				}
			} 
		}
	}

	// count occurences of numbers >=2 in grid
	int count = 0;
	for (int i=0; i<maxX; i++) {
		for (int j=0; j<maxY; j++) {
			if (grid[i][j] >= 2) count++;
		}
	}

	cout << "Read occurrences of two or more from grid as " << count << ".\n";
}
