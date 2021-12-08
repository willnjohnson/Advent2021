#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
using namespace std;

#define LEN 5
#define BOARDSIZE 100

typedef struct {
	int num;
	bool isMarked;
} BingoEntry;

int main(int argc, char* argv[]) {
	string line;
	int h, i, j;
	int nlines = 0;
	char* tok;
	BingoEntry be[BOARDSIZE][LEN][LEN];
	vector<int> numsCalled;

	// error check
	if (argc != 2) {
		cerr << "usage: " << argv[0] << " <input-file>.\n";
		exit(1);
	}

	// open file for reading
	ifstream fin(argv[1]);
	if (fin.is_open()) {
		// read line denoting bingo inputs
		getline(fin, line);
		char l[line.length()];
		strcpy(l, line.c_str());

		// read each individual input of our bingo inputs
		tok = strtok(l, ",");
		while (tok != NULL) {
			numsCalled.push_back(atoi(tok));
			tok = strtok(NULL, ",");
		}
		
		// read entries of bingo board
		h = 0;
		while (getline(fin, line)) {
			for (i=0; i<LEN; i++) {
				// get row line
				getline(fin, line);
				l[line.length()];
				strcpy(l, line.c_str());

				// get first entry of row
				tok = strtok(l, " ");
				for (j=0; j<LEN; j++) {
					// read each column value, sticking it to bingo entry struct
					be[h][i][j] = { atoi(tok), false };
					tok = strtok(NULL, " ");
				}
			}
			// done reading matrix first matrix, visit next matrix for reading
			h++;
		}

		fin.close();
	} else {
		cerr << argv[0] << ": unable to read file.\n";
		exit(1);
	}

	// set flag to true by default
	// we will use this as a "proof by contradiction" when we scan
	bool bingoFound = true;

	// let's play bingo
	for (int num : numsCalled) {
		// check each board starting with the first
		for (h=0; h<BOARDSIZE; h++) {
			// scan through board to find matching num
			for (i=0; i<LEN; i++) {
				for (j=0; j<LEN; j++) {
					// match found
					if (be[h][i][j].num == num) {
						// mark entry
						be[h][i][j].isMarked = true;

						// scan row for a bingo
						for (int n = i+1; (n = n % LEN) != i; n++) {
							if (be[h][n][j].isMarked != true) bingoFound = false;
						}
						
						// bingo?
						if (bingoFound) goto done;
						bingoFound = true;

						// scan col for a bingo
						for (int n = j+1; (n = n % LEN) != j; n++) {
							if (be[h][i][n].isMarked != true) bingoFound = false;
						}
						
						// bingo?
						if (bingoFound) goto done;
						bingoFound = true;
					}
				}
			}
		}
	}

	done:
	int winningNum = be[h][i][j].num;

	// get sum of unmarked entries in board
	int sum = 0;
	for (i=0; i < LEN; i++) {
		for (j=0; j < LEN; j++) {
			if (!be[h][i][j].isMarked) sum += be[h][i][j].num;
		}
	}
	
	// calculate final score
	cout << "Read winning board's sum of unmarked entries " 
		<< sum << " and winning number " 
		<< winningNum << " to yield product " 
		<< (sum*winningNum) << ".\n";
}
